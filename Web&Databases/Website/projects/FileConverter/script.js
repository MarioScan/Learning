const $=id=>document.getElementById(id);
const enc=new TextEncoder();
const base=n=>n.replace(/\.[^.]+$/,'');
const loadImg=f=>createImageBitmap(f);
const toBlob=(c,t,q)=>new Promise(r=>c.toBlob(r,t,q));
async function canvasOf(f,white){const b=await loadImg(f);const c=document.createElement('canvas');c.width=b.width;c.height=b.height;const x=c.getContext('2d');if(white){x.fillStyle='#fff';x.fillRect(0,0,c.width,c.height)}x.drawImage(b,0,0);return c}

let pdfLibPromise;
let pdfJsPromise;
let lamePromise;
let zipPromise;
let videoEnginePromise;
async function loadPdfLib(){
  if(window.PDFLib)return window.PDFLib;
  if(!pdfLibPromise)pdfLibPromise=new Promise((resolve,reject)=>{
    const script=document.createElement('script');
    script.src=new URL('./vendor/pdf-lib.min.js',document.baseURI).href;
    script.onload=()=>resolve(window.PDFLib);
    script.onerror=()=>{pdfLibPromise=null;reject(new Error('Could not load the local PDF engine. Check that vendor/pdf-lib.min.js is present.'))};
    document.head.append(script);
  });
  return pdfLibPromise;
}
async function loadPdfJs(){
  if(window.pdfjsLib)return window.pdfjsLib;
  if(!pdfJsPromise)pdfJsPromise=new Promise((resolve,reject)=>{
    const script=document.createElement('script');
    script.src=new URL('./vendor/pdf.min.js',document.baseURI).href;
    script.onload=()=>{
      window.pdfjsLib.GlobalWorkerOptions.workerSrc=new URL('./vendor/pdf.worker.min.js',document.baseURI).href;
      resolve(window.pdfjsLib);
    };
    script.onerror=()=>{pdfJsPromise=null;reject(new Error('Could not load the local PDF preview engine. Check the vendor directory.'))};
    document.head.append(script);
  });
  return pdfJsPromise;
}
async function loadLame(){
  if(window.lamejs)return window.lamejs;
  if(!lamePromise)lamePromise=new Promise((resolve,reject)=>{
    const script=document.createElement('script');script.src=new URL('./vendor/lame.min.js',document.baseURI).href;
    script.onload=()=>resolve(window.lamejs);
    script.onerror=()=>{lamePromise=null;reject(new Error('Could not load the local MP3 encoder. Check vendor/lame.min.js.'))};
    document.head.append(script);
  });
  return lamePromise;
}
async function loadZip(){
  if(window.JSZip)return window.JSZip;
  if(!zipPromise)zipPromise=new Promise((resolve,reject)=>{
    const script=document.createElement('script');script.src=new URL('./vendor/jszip.min.js',document.baseURI).href;
    script.onload=()=>resolve(window.JSZip);
    script.onerror=()=>{zipPromise=null;reject(new Error('Could not load the local ZIP library. Check vendor/jszip.min.js.'))};
    document.head.append(script);
  });
  return zipPromise;
}
async function loadVideoEngine(){
  if(!videoEnginePromise)videoEnginePromise=(async()=>{
    if(!window.FFmpeg)await new Promise((resolve,reject)=>{
      const script=document.createElement('script');script.src=new URL('./vendor/ffmpeg.min.js',document.baseURI).href;
      script.onload=resolve;script.onerror=()=>reject(new Error('Could not load the local video library. Check vendor/ffmpeg.min.js.'));
      document.head.append(script);
    });
    const engine=window.FFmpeg.createFFmpeg({corePath:new URL('./vendor/ffmpeg-core.js',document.baseURI).href,log:false});
    await engine.load();
    return {engine,fetchFile:window.FFmpeg.fetchFile};
  })().catch(error=>{videoEnginePromise=null;throw error});
  return videoEnginePromise;
}
function clearVideoFiles(engine,names){names.forEach(name=>{try{engine.FS('unlink',name)}catch{}})}
function stopVideoEngine(){
  const pending=videoEnginePromise;videoEnginePromise=null;
  if(pending)pending.then(({engine})=>engine.exit()).catch(()=>{});
}
async function convertVideo(file,options){
  if(file.size>350*1024*1024)throw new Error('This video is too large for in-browser conversion (maximum 350 MB).');
  const {engine,fetchFile}=await loadVideoEngine(),inputExtension=file.name.match(/\.([^.]+)$/)?.[1]?.toLowerCase()||'video',inputName=`input.${inputExtension}`,outputName=`converted.${options.fmt}`;
  const codecs={
    mp4:['-c:v','libx264','-preset','ultrafast','-crf','25','-c:a','aac','-b:a','128k','-movflags','+faststart'],
    mov:['-c:v','libx264','-preset','ultrafast','-crf','25','-c:a','aac','-b:a','128k'],
    mkv:['-c:v','libx264','-preset','ultrafast','-crf','25','-c:a','aac','-b:a','128k'],
    avi:['-c:v','mpeg4','-q:v','5','-c:a','mp3','-q:a','4'],
    webm:['-c:v','libvpx','-deadline','realtime','-cpu-used','5','-crf','34','-b:v','0','-c:a','libvorbis','-q:a','4']
  };
  clearVideoFiles(engine,[inputName,outputName]);
  try{
    engine.FS('writeFile',inputName,await fetchFile(file));
    await engine.run('-i',inputName,'-map','0:v:0','-map','0:a?','-y',...codecs[options.fmt],outputName);
    const mimeTypes={mp4:'video/mp4',mov:'video/quicktime',avi:'video/x-msvideo',mkv:'video/x-matroska',webm:'video/webm'};
    const data=engine.FS('readFile',outputName),blob=new Blob([new Uint8Array(data)],{type:mimeTypes[options.fmt]});
    return {blob,name:`${base(file.name)}.${options.fmt}`};
  }finally{clearVideoFiles(engine,[inputName,outputName])}
}
async function loadPreviewDocument(file){
  const pdfjs=await loadPdfJs();
  return pdfjs.getDocument({data:await file.arrayBuffer(),disableWorker:location.protocol==='file:'}).promise;
}
async function renderPdfPreview(doc,pageNumber,width=180){
  const page=await doc.getPage(pageNumber),natural=page.getViewport({scale:1});
  const viewport=page.getViewport({scale:Math.min(1,width/natural.width)}),canvas=document.createElement('canvas');
  canvas.width=Math.ceil(viewport.width);canvas.height=Math.ceil(viewport.height);
  const hidden=document.hidden,requestFrame=window.requestAnimationFrame;
  if(hidden)window.requestAnimationFrame=callback=>setTimeout(()=>callback(performance.now()),16);
  try{await page.render({canvasContext:canvas.getContext('2d'),viewport}).promise}
  finally{if(hidden)window.requestAnimationFrame=requestFrame}
  return canvas.toDataURL('image/jpeg',.72);
}
async function mergePdfs(files){
  const {PDFDocument}=await loadPdfLib(),merged=await PDFDocument.create();
  for(const f of files){
    let source;
    try{source=await PDFDocument.load(await f.arrayBuffer())}catch{throw new Error(`${f.name} is not a valid or supported PDF.`)}
    const pages=await merged.copyPages(source,source.getPageIndices());
    pages.forEach(page=>merged.addPage(page));
  }
  return {blob:new Blob([await merged.save()],{type:'application/pdf'}),name:'merged.pdf'};
}
async function splitPdf(f,breaks,pageOrder){
  const {PDFDocument}=await loadPdfLib();
  let source;
  try{source=await PDFDocument.load(await f.arrayBuffer())}catch{throw new Error(`${f.name} is not a valid or supported PDF.`)}
  const orderedPages=pageOrder||Array.from({length:source.getPageCount()},(_,index)=>index+1),pageCount=orderedPages.length,ends=[...breaks,pageCount],files=[];let start=0;
  if(!pageCount)throw new Error('Keep at least one page in the PDF.');
  if(!Array.isArray(breaks)||breaks.some((page,i)=>!Number.isInteger(page)||page<=start||page>=pageCount||(i&&page<=breaks[i-1])))throw new Error('Choose valid page breaks in ascending order.');
  for(let i=0;i<ends.length;i++){
    const pagePdf=await PDFDocument.create(),indices=orderedPages.slice(start,ends[i]).map(page=>page-1);
    const pages=await pagePdf.copyPages(source,indices);
    pages.forEach(page=>pagePdf.addPage(page));
    files.push({blob:new Blob([await pagePdf.save()],{type:'application/pdf'}),name:`${base(f.name)}-part-${i+1}.pdf`});
    start=ends[i];
  }
  if(!files.length)throw new Error(`${f.name} contains no pages.`);
  return {files};
}

/* ---------- Immagini: JPG/PNG/WebP ---------- */
async function convImg(f,o){
  if(o.fmt==='svg'){
    if(f.type==='image/svg+xml'||/\.svg$/i.test(f.name))return {blob:new Blob([await f.text()],{type:'image/svg+xml'}),name:base(f.name)+'.svg'};
    const bitmap=await loadImg(f),source=await new Promise((resolve,reject)=>{const reader=new FileReader();reader.onload=()=>resolve(reader.result);reader.onerror=()=>reject(new Error('Could not read this image.'));reader.readAsDataURL(f)});
    const svg=`<svg xmlns="http://www.w3.org/2000/svg" width="${bitmap.width}" height="${bitmap.height}" viewBox="0 0 ${bitmap.width} ${bitmap.height}"><image href="${source}" width="${bitmap.width}" height="${bitmap.height}"/></svg>`;
    bitmap.close?.();return {blob:new Blob([svg],{type:'image/svg+xml'}),name:base(f.name)+'.svg'};
  }
  const formats={jpg:['image/jpeg','jpg'],jpeg:['image/jpeg','jpeg'],png:['image/png','png'],webp:['image/webp','webp']},[mime,extension]=formats[o.fmt];
  const c=await canvasOf(f,mime==='image/jpeg');
  return {blob:await toBlob(c,mime,.92),name:base(f.name)+'.'+extension};
}
async function decodeGifFrames(file){
  if(typeof ImageDecoder==='undefined'||!await ImageDecoder.isTypeSupported('image/gif'))throw new Error('GIF frame previews are not supported by this browser.');
  const decoder=new ImageDecoder({data:await file.arrayBuffer(),type:'image/gif'});
  try{
    await decoder.tracks.ready;
    const track=decoder.tracks.selectedTrack;
    if(!track||!track.frameCount)throw new Error('This GIF contains no frames.');
    const frames=[];let timestamp=0;
    for(let index=0;index<track.frameCount;index++){
      const {image}=await decoder.decode({frameIndex:index}),width=image.displayWidth||image.codedWidth,height=image.displayHeight||image.codedHeight,canvas=document.createElement('canvas');
      const frameTimestamp=timestamp,frameDuration=(image.duration||0)/1000000;timestamp+=frameDuration;
      canvas.width=width;canvas.height=height;canvas.getContext('2d').drawImage(image,0,0,width,height);image.close();
      const blob=await toBlob(canvas,'image/png');
      if(!blob)throw new Error(`Could not export frame ${index+1}.`);
      const preview=document.createElement('canvas'),scale=Math.min(1,220/width);
      preview.width=Math.max(1,Math.round(width*scale));preview.height=Math.max(1,Math.round(height*scale));preview.getContext('2d').drawImage(canvas,0,0,preview.width,preview.height);
      const previewBlob=await toBlob(preview,'image/png');
      frames.push({index,timestamp:frameTimestamp,duration:frameDuration,blob,preview:URL.createObjectURL(previewBlob),selected:true});
    }
    return frames;
  }finally{decoder.close()}
}
async function decodeVideoFrames(file){
  if(file.size>350*1024*1024)throw new Error('This video is too large to process in the browser (maximum 350 MB).');
  const {engine,fetchFile}=await loadVideoEngine(),extension=file.name.match(/\.([^.]+)$/)?.[1]?.toLowerCase()||'video',inputName=`frames-input.${extension}`;
  const timestamps=[],durations=[];
  clearVideoFiles(engine,[inputName,...engine.FS('readdir','/').filter(name=>/^video-frame-\d+\.jpg$/.test(name))]);
  try{
    engine.FS('writeFile',inputName,await fetchFile(file));
    engine.setLogger(({message})=>{const match=message.match(/\bn:\s*(\d+)\s+pts:\s*-?\d+\s+pts_time:\s*(-?[\d.]+)(?:\s+duration:\s*-?\d+\s+duration_time:\s*([\d.]+))?/);if(match){const index=Number(match[1]);timestamps[index]=Number(match[2]);if(match[3])durations[index]=Number(match[3])}});
    await engine.run('-i',inputName,'-vf','showinfo,scale=240:-2','-vsync','0','-q:v','8','-y','video-frame-%03d.jpg');
    engine.setLogger(()=>{});
    const names=engine.FS('readdir','/').filter(name=>/^video-frame-\d+\.jpg$/.test(name)).sort((a,b)=>Number(a.match(/\d+/)[0])-Number(b.match(/\d+/)[0]));
    if(!names.length)throw new Error('No video frames could be extracted.');
    const frames=[];
    for(let index=0;index<names.length;index++){
      const blob=new Blob([new Uint8Array(engine.FS('readFile',names[index]))],{type:'image/jpeg'});
      const timestamp= timestamps[index]??index/30,duration=durations[index]??(timestamps[index+1]===undefined?1/30:timestamps[index+1]-timestamp);
      frames.push({index,timestamp,duration,preview:URL.createObjectURL(blob),selected:true});
      clearVideoFiles(engine,[names[index]]);
    }
    return frames;
  }finally{engine.setLogger(()=>{});clearVideoFiles(engine,[inputName,...engine.FS('readdir','/').filter(name=>/^video-frame-\d+\.jpg$/.test(name))])}
}
async function exportVideoFrames(file,indices){
  const {engine,fetchFile}=await loadVideoEngine(),Zip=await loadZip(),extension=file.name.match(/\.([^.]+)$/)?.[1]?.toLowerCase()||'video',inputName=`export-input.${extension}`;
  const ordered=[...indices].sort((a,b)=>a-b),ranges=[];
  ordered.forEach(index=>{const last=ranges[ranges.length-1];if(last&&index===last[1]+1)last[1]=index;else ranges.push([index,index])});
  const filters=ranges.map(([start,end])=>start===end?String.raw`eq(n\,${start})`:String.raw`between(n\,${start}\,${end})`).join('+'),zip=new Zip();
  clearVideoFiles(engine,[inputName,...engine.FS('readdir','/').filter(name=>/^selected-frame-\d+\.png$/.test(name))]);
  try{
    engine.FS('writeFile',inputName,await fetchFile(file));
    await engine.run('-i',inputName,'-vf',`select=${filters}`,'-vsync','0','-y','selected-frame-%08d.png');
    const names=engine.FS('readdir','/').filter(name=>/^selected-frame-\d+\.png$/.test(name)).sort((a,b)=>Number(a.match(/\d+/)[0])-Number(b.match(/\d+/)[0]));
    if(names.length!==ordered.length)throw new Error(`Expected ${ordered.length} frames but extracted ${names.length}.`);
    names.forEach((name,index)=>{zip.file(`frame-${String(ordered[index]+1).padStart(6,'0')}.png`,new Uint8Array(engine.FS('readFile',name)));clearVideoFiles(engine,[name])});
    return {blob:await zip.generateAsync({type:'blob',compression:'STORE'}),name:`${base(file.name)}-frames.zip`};
  }finally{clearVideoFiles(engine,[inputName,...engine.FS('readdir','/').filter(name=>/^selected-frame-\d+\.png$/.test(name))])}
}
function mediaTime(seconds){const value=Math.max(0,Number(seconds)||0),hours=Math.floor(value/3600),minutes=Math.floor(value%3600/60),whole=Math.floor(value%60),fraction=Math.floor(value%1*1000);return `${String(hours).padStart(2,'0')}:${String(minutes).padStart(2,'0')}:${String(whole).padStart(2,'0')}.${String(fraction).padStart(3,'0')}`}
function renderCutWorkspace(){
  const workspace=$('cutWorkspace');workspace.replaceChildren();
  if(cutError){workspace.append(node('p','pdf-error',cutError));return}
  if(!cutFile){workspace.append(node('p','pdf-empty','Select one video or GIF to load a frame-by-frame preview.'));return}
  if(cutLoading){workspace.append(node('p','pdf-empty',`Extracting every frame from ${cutFile.name}… This may take time for long videos.`));return}
  const toolbar=node('div','cut-toolbar'),summary=node('p','',`${cutFile.name} · ${cutFrames.length} frames · ${mediaTime(cutFrames.at(-1)?.timestamp||0)}`),actions=node('div','pdf-actions'),cut=actionButton(`Export ${opt.fmt.toUpperCase()} clip`,true,cutVideo);
  cut.disabled=!cutFrames.length;actions.append(cut);toolbar.append(summary,actions);workspace.append(toolbar);
  const controls=node('div','cut-controls');
  [['Start frame',cutStart],['End frame',cutEnd]].forEach(([labelText,value],index)=>{
    const label=node('label','',labelText),input=node('input');input.type='number';input.min='1';input.max=String(cutFrames.length);input.value=String(value+1);input.setAttribute('aria-label',labelText);
    input.onchange=()=>{const next=Math.max(0,Math.min(cutFrames.length-1,Math.trunc(Number(input.value)||1)-1));if(index===0){cutStart=next;if(cutEnd<next)cutEnd=next}else{cutEnd=next;if(cutStart>next)cutStart=next}renderCutWorkspace()};
    label.append(input);controls.append(label);
  });
  controls.append(node('p','cut-status',cutProgress||`Selected range: ${mediaTime(cutFrames[cutStart]?.timestamp)} to ${mediaTime((cutFrames[cutEnd]?.timestamp||0)+(cutFrames[cutEnd]?.duration||0))}.`));workspace.append(controls);
  const grid=node('div','cut-grid');workspace.append(grid);
  cutFrames.forEach((frame,index)=>{
    const card=node('article',`cut-frame${index>=cutStart&&index<=cutEnd?' in-range':''}${index===cutStart||index===cutEnd?' boundary':''}`),image=node('img');
    image.src=frame.preview;image.alt=`Frame ${index+1} at ${mediaTime(frame.timestamp)}`;image.loading='lazy';
    const info=node('div','cut-frame-info');info.append(node('strong','',`Frame ${index+1}`),node('span','',mediaTime(frame.timestamp)));
    const frameActions=node('div','cut-frame-actions'),markStart=actionButton('Set start',false,()=>{cutStart=index;if(cutEnd<index)cutEnd=index;renderCutWorkspace()}),markEnd=actionButton('Set end',false,()=>{cutEnd=index;if(cutStart>index)cutStart=index;renderCutWorkspace()});
    card.append(image,info,frameActions);frameActions.append(markStart,markEnd);grid.append(card);
  });
}
async function loadCutFile(file){
  cutFrames.forEach(frame=>URL.revokeObjectURL(frame.preview));cutFile=file;cutFrames=[];cutError='';cutLoading=true;cutProgress='';cutStart=0;cutEnd=0;renderCutWorkspace();
  if(!isVideoFile(file)&&!/\.gif$/i.test(file.name)){cutError='Select an MP4, MOV, AVI, MKV, WebM, or GIF file.';cutLoading=false;renderCutWorkspace();return}
  const generation=viewGeneration;
  try{
    const frames=/\.gif$/i.test(file.name)?await decodeGifFrames(file):await decodeVideoFrames(file);
    if(cutFile!==file||generation!==viewGeneration){frames.forEach(frame=>URL.revokeObjectURL(frame.preview));return}
    cutFrames=frames;cutLoading=false;cutEnd=Math.max(0,frames.length-1);renderCutWorkspace();
  }catch(error){if(cutFile===file&&generation===viewGeneration){cutLoading=false;cutError=error.message||'Could not read every frame from this media file.';renderCutWorkspace()}}
}
async function cutVideo(){
  if(!cutFile||!cutFrames.length)return;
  const generation=viewGeneration,format=opt.fmt||'mp4',startFrame=cutStart,endFrame=cutEnd,key=conversionSignature('cut',[cutFile],{format,startFrame,endFrame}),record=beginConversion(key);if(!record)return;
  const result=row(`Cutting ${cutFile.name}`);cutProgress='Encoding the selected frame range…';renderCutWorkspace();
  try{
    const output=await encodeVideoCut(cutFile,cutFrames,startFrame,endFrame,format);
    if(generation!==viewGeneration)return;
    done(result,output,record);record.status='done';cutProgress='Clip ready in downloads.';renderCutWorkspace();
  }catch(error){if(generation===viewGeneration){fail(result,error);cutProgress='Cut failed.';renderCutWorkspace()}conversionRuns.delete(key)}
}
async function encodeVideoCut(file,frames,startFrame,endFrame,format){
  if(file.size>350*1024*1024)throw new Error('This media file is too large for in-browser cutting (maximum 350 MB).');
  const {engine,fetchFile}=await loadVideoEngine(),extension=file.name.match(/\.([^.]+)$/)?.[1]?.toLowerCase()||'video',inputName=`cut-input.${extension}`,outputName=`cut-output.${format}`;
  const startTime=frames[startFrame].timestamp,endFrameData=frames[endFrame],endTime=endFrameData.timestamp+(endFrameData.duration||1/30);
  const codecs={mp4:['-c:v','libx264','-preset','ultrafast','-crf','25','-c:a','aac','-b:a','128k','-movflags','+faststart'],mov:['-c:v','libx264','-preset','ultrafast','-crf','25','-c:a','aac','-b:a','128k'],mkv:['-c:v','libx264','-preset','ultrafast','-crf','25','-c:a','aac','-b:a','128k'],avi:['-c:v','mpeg4','-q:v','5','-c:a','mp3','-q:a','4'],webm:['-c:v','libvpx','-deadline','realtime','-cpu-used','5','-crf','34','-b:v','0','-c:a','libvorbis','-q:a','4']};
  clearVideoFiles(engine,[inputName,outputName]);
  try{
    engine.FS('writeFile',inputName,await fetchFile(file));
    const rangeFilter=`select=between(n\\,${startFrame}\\,${endFrame}),setpts=PTS-STARTPTS`;
    if(format==='gif')await engine.run('-i',inputName,'-vf',rangeFilter,'-map','0:v:0','-an','-loop','0','-y',outputName);
    else await engine.run('-i',inputName,'-vf',rangeFilter,'-af',`atrim=start=${startTime}:end=${endTime},asetpts=PTS-STARTPTS`,'-map','0:v:0','-map','0:a?',...codecs[format],'-y',outputName);
    const mimeTypes={mp4:'video/mp4',mov:'video/quicktime',avi:'video/x-msvideo',mkv:'video/x-matroska',webm:'video/webm',gif:'image/gif'};
    return {blob:new Blob([new Uint8Array(engine.FS('readFile',outputName))],{type:mimeTypes[format]}),name:`${base(file.name)}-cut.${format}`};
  }finally{clearVideoFiles(engine,[inputName,outputName])}
}
function renderGifWorkspace(){
  const workspace=$('gifWorkspace');workspace.replaceChildren();
  if(gifError){workspace.append(node('p','pdf-error',gifError));return}
  if(!gifFile){workspace.append(node('p','pdf-empty','Select a GIF or video file to preview its frames.'));return}
  if(gifLoading){workspace.append(node('p','pdf-empty',`Loading frames from ${gifFile.name}…`));return}
  const selected=gifFrames.filter(frame=>frame.selected).length,toolbar=node('div','gif-toolbar'),summary=node('p','',`${selected} of ${gifFrames.length} frames selected${isVideoFile(gifFile)?' · every frame':''}`),actions=node('div','pdf-actions');
  const selectAll=actionButton(selected===gifFrames.length?'Deselect all':'Select all',false,()=>{const next=selected!==gifFrames.length;gifFrames.forEach(frame=>frame.selected=next);renderGifWorkspace()});
  const download=actionButton('Download selected frames',true,downloadGifFrames);download.disabled=!selected;actions.append(selectAll,download);toolbar.append(summary,actions);workspace.append(toolbar);
  const grid=node('div','merge-grid');workspace.append(grid);
  gifFrames.forEach(frame=>{
    const card=node('article','pdf-card gif-card'),preview=node('div','pdf-thumb'),image=node('img');
    image.src=frame.preview;image.alt=`GIF frame ${frame.index+1}`;image.loading='lazy';preview.append(image);
    const label=node('label','gif-frame-select'),checkbox=document.createElement('input');checkbox.type='checkbox';checkbox.checked=frame.selected;checkbox.onchange=()=>{frame.selected=checkbox.checked;summary.textContent=`${gifFrames.filter(item=>item.selected).length} of ${gifFrames.length} frames selected`;download.disabled=!frame.selected&&!gifFrames.some(item=>item.selected);selectAll.textContent=gifFrames.every(item=>item.selected)?'Deselect all':'Select all'};
    label.append(checkbox,node('span','',`Frame ${frame.index+1}`));card.append(preview,label);grid.append(card);
  });
}
async function loadGifFile(file){
  gifFrames.forEach(frame=>URL.revokeObjectURL(frame.preview));gifFile=file;gifFrames=[];gifError='';gifLoading=true;renderGifWorkspace();
  if(file.type!=='image/gif'&&!/\.gif$/i.test(file.name)&&!isVideoFile(file)){gifError='Select a GIF or supported video file.';gifLoading=false;renderGifWorkspace();return}
  try{
    const frames=isVideoFile(file)?await decodeVideoFrames(file):await decodeGifFrames(file);
    if(gifFile!==file){frames.forEach(frame=>URL.revokeObjectURL(frame.preview));return}
    gifFrames=frames;gifLoading=false;renderGifWorkspace();
  }catch(error){if(gifFile!==file)return;gifLoading=false;gifError=error.message||'Could not decode this GIF.';renderGifWorkspace()}
}
async function downloadGifFrames(){
  const selected=gifFrames.filter(frame=>frame.selected);
  if(!selected.length){showNotice('Select at least one GIF frame to download.');return}
  const key=conversionSignature('gif',[gifFile],{frames:selected.map(frame=>frame.index)}),record=beginConversion(key);if(!record)return;
  if(isVideoFile(gifFile)){
    const generation=viewGeneration,result=row(`Extracting ${selected.length} frames from ${gifFile.name}`);
    try{const output=await exportVideoFrames(gifFile,selected.map(frame=>frame.index));if(generation!==viewGeneration)return;done(result,output,record);record.status='done'}
    catch(error){if(generation===viewGeneration)fail(result,error);conversionRuns.delete(key)}
    return;
  }
  selected.forEach(frame=>{const number=String(frame.index+1).padStart(3,'0');done(row(`${base(gifFile.name)}-frame-${number}.png`),{blob:frame.blob,name:`${base(gifFile.name)}-frame-${number}.png`},record)});
  record.status='done';
}

/* ---------- Immagini -> PDF (scritto a mano, JPEG incorporato) ---------- */
async function imgToPdf(files){
  const parts=[],off=[];let len=0;
  const add=x=>{const u=typeof x==='string'?enc.encode(x):x;parts.push(u);len+=u.length};
  const obj=(id,fn)=>{off[id]=len;add(id+' 0 obj\n');fn();add('\nendobj\n')};
  const pages=[];
  for(const f of files){
    const c=await canvasOf(f,true);
    pages.push({w:c.width,h:c.height,jpg:new Uint8Array(await(await toBlob(c,'image/jpeg',.9)).arrayBuffer())});
  }
  const n=pages.length;
  add('%PDF-1.4\n');
  obj(1,()=>add('<</Type/Catalog/Pages 2 0 R>>'));
  obj(2,()=>add(`<</Type/Pages/Count ${n}/Kids[${pages.map((_,i)=>`${3+3*i} 0 R`).join(' ')}]>>`));
  pages.forEach((p,i)=>{
    const W=Math.round(p.w*.75),H=Math.round(p.h*.75),pid=3+3*i;
    obj(pid,()=>add(`<</Type/Page/Parent 2 0 R/MediaBox[0 0 ${W} ${H}]/Contents ${pid+1} 0 R/Resources<</XObject<</Im0 ${pid+2} 0 R>>>>>>`));
    const cs=`q ${W} 0 0 ${H} 0 0 cm /Im0 Do Q`;
    obj(pid+1,()=>add(`<</Length ${cs.length}>>\nstream\n${cs}\nendstream`));
    obj(pid+2,()=>{add(`<</Type/XObject/Subtype/Image/Width ${p.w}/Height ${p.h}/ColorSpace/DeviceRGB/BitsPerComponent 8/Filter/DCTDecode/Length ${p.jpg.length}>>\nstream\n`);add(p.jpg);add('\nendstream')});
  });
  const total=3+3*n,xref=len;
  add(`xref\n0 ${total}\n0000000000 65535 f \n`+off.slice(1).map(o=>String(o).padStart(10,'0')+' 00000 n \n').join('')+`trailer\n<</Size ${total}/Root 1 0 R>>\nstartxref\n${xref}\n%%EOF`);
  return {blob:new Blob(parts,{type:'application/pdf'}),name:'images.pdf'};
}

function audioToWav(buf,name){
  const ch=buf.numberOfChannels,n=buf.length,out=new DataView(new ArrayBuffer(44+n*ch*2));
  const s=(o,t)=>[...t].forEach((c,i)=>out.setUint8(o+i,c.charCodeAt(0)));
  s(0,'RIFF');out.setUint32(4,36+n*ch*2,true);s(8,'WAVEfmt ');out.setUint32(16,16,true);out.setUint16(20,1,true);out.setUint16(22,ch,true);
  out.setUint32(24,buf.sampleRate,true);out.setUint32(28,buf.sampleRate*ch*2,true);out.setUint16(32,ch*2,true);out.setUint16(34,16,true);s(36,'data');out.setUint32(40,n*ch*2,true);
  const d=[...Array(ch)].map((_,i)=>buf.getChannelData(i));let p=44;
  for(let i=0;i<n;i++)for(let c=0;c<ch;c++){const v=Math.max(-1,Math.min(1,d[c][i]));out.setInt16(p,v<0?v*32768:v*32767,true);p+=2}
  return {blob:new Blob([out],{type:'audio/wav'}),name};
}
async function audioToMp3(buf,name){
  const lame=await loadLame(),channels=Math.min(2,buf.numberOfChannels),sampleRate=44100;
  let source=buf;
  if(buf.sampleRate!==sampleRate){
    const offline=new OfflineAudioContext(channels,Math.ceil(buf.duration*sampleRate),sampleRate),node=offline.createBufferSource();
    node.buffer=buf;node.connect(offline.destination);node.start();source=await offline.startRendering();
  }
  const left=Int16Array.from(source.getChannelData(0),sample=>Math.max(-1,Math.min(1,sample))*32767|0),right=channels===2?Int16Array.from(source.getChannelData(1),sample=>Math.max(-1,Math.min(1,sample))*32767|0):null;
  const encoder=new lame.Mp3Encoder(channels,sampleRate,128),chunks=[];
  for(let offset=0;offset<left.length;offset+=1152){const chunk=encoder.encodeBuffer(left.subarray(offset,offset+1152),right?.subarray(offset,offset+1152));if(chunk.length)chunks.push(chunk)}
  const last=encoder.flush();if(last.length)chunks.push(last);
  return {blob:new Blob(chunks,{type:'audio/mpeg'}),name};
}
async function audioToMp4(buf,context,name){
  if(typeof MediaRecorder==='undefined'||!MediaRecorder.isTypeSupported('audio/mp4'))throw new Error('MP4 audio encoding is not supported by this browser.');
  const destination=context.createMediaStreamDestination(),source=context.createBufferSource(),chunks=[];
  source.buffer=buf;source.connect(destination);
  let recorder;try{recorder=new MediaRecorder(destination.stream,{mimeType:'audio/mp4'})}catch{throw new Error('Could not start the MP4 audio encoder in this browser.')}
  const finished=new Promise((resolve,reject)=>{
    recorder.ondataavailable=event=>{if(event.data.size)chunks.push(event.data)};
    recorder.onerror=event=>reject(event.error||new Error('MP4 audio encoding failed.'));
    recorder.onstop=resolve;
  });
  recorder.start();source.onended=()=>{if(recorder.state!=='inactive')recorder.stop()};
  if(context.state==='suspended')await context.resume();
  source.start();
  try{await finished;return {blob:new Blob(chunks,{type:'audio/mp4'}),name}}
  finally{destination.stream.getTracks().forEach(track=>track.stop())}
}
async function captureMediaAudio(file,context){
  const video=file.type.startsWith('video/')||/\.(mp4|mov|webm|mkv)$/i.test(file.name),media=document.createElement(video?'video':'audio'),url=URL.createObjectURL(file);
  media.preload='auto';media.playsInline=true;media.style.cssText='position:fixed;width:1px;height:1px;opacity:0;pointer-events:none';media.setAttribute('aria-hidden','true');media.src=url;document.body.append(media);
  const source=context.createMediaElementSource(media),processor=context.createScriptProcessor(4096,2,2),silent=context.createGain(),chunks=[[],[]];let channels=0;
  source.connect(processor);processor.connect(silent);silent.connect(context.destination);silent.gain.value=0;
  processor.onaudioprocess=event=>{channels=Math.min(2,event.inputBuffer.numberOfChannels);for(let channel=0;channel<channels;channel++)chunks[channel].push(new Float32Array(event.inputBuffer.getChannelData(channel)))};
  try{
    const ended=new Promise((resolve,reject)=>{media.addEventListener('ended',resolve,{once:true});media.addEventListener('error',()=>reject(new Error('This media format or codec is not supported by your browser.')),{once:true})});
    if(context.state==='suspended')await context.resume();
    await media.play();await ended;
    const length=chunks[0].reduce((total,chunk)=>total+chunk.length,0);
    if(!length||!channels)throw new Error('No audio track could be read from this file.');
    const buffer=context.createBuffer(channels,length,context.sampleRate);
    for(let channel=0;channel<channels;channel++){let offset=0;for(const chunk of chunks[channel]){buffer.getChannelData(channel).set(chunk,offset);offset+=chunk.length}}
    return buffer;
  }finally{
    processor.disconnect();source.disconnect();silent.disconnect();media.pause();media.removeAttribute('src');media.load();media.remove();URL.revokeObjectURL(url);
  }
}
async function convertAudio(file,options){
  const Context=window.AudioContext||window.webkitAudioContext;if(!Context)throw new Error('Audio conversion is not supported by this browser.');
  const context=new Context();let buffer;
  try{buffer=await context.decodeAudioData(await file.arrayBuffer())}catch{try{buffer=await captureMediaAudio(file,context)}catch(error){await context.close();throw new Error(error.message||'This audio format or codec is not supported by your browser.')}}
  const extension=options.fmt;
  try{
    if(extension==='wav')return audioToWav(buffer,base(file.name)+'.wav');
    if(extension==='mp3')return await audioToMp3(buffer,base(file.name)+'.mp3');
    if(extension==='mp4')return await audioToMp4(buffer,context,base(file.name)+'.mp4');
    throw new Error('Choose MP3, MP4, or WAV as the output format.');
  }finally{if(context.state!=='closed')await context.close()}
}

/* ---------- Markdown -> DOC (HTML compatibile con Word) ---------- */
function md2html(src){
  const esc=s=>s.replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;');
  const inl=s=>esc(s).replace(/`([^`]+)`/g,'<code>$1</code>').replace(/\*\*([^*]+)\*\*/g,'<b>$1</b>').replace(/\*([^*]+)\*/g,'<i>$1</i>').replace(/!?\[([^\]]*)\]\(([^)]+)\)/g,'<a href="$2">$1</a>');
  const out=[];let list=null,code=null,para=[];
  const flushP=()=>{if(para.length)out.push('<p>'+inl(para.join(' '))+'</p>');para=[]};
  const flushL=()=>{if(list){out.push(`</${list}>`);list=null}};
  for(const line of src.replace(/\r/g,'').split('\n')){
    if(/^```/.test(line)){if(code){out.push('<pre>'+esc(code.join('\n'))+'</pre>');code=null}else{flushP();flushL();code=[]}continue}
    if(code){code.push(line);continue}
    let m;
    if(!line.trim()){flushP();flushL()}
    else if(m=line.match(/^(#{1,6})\s+(.*)/)){flushP();flushL();out.push(`<h${m[1].length}>${inl(m[2])}</h${m[1].length}>`)}
    else if(/^(-{3,}|\*{3,})$/.test(line.trim())){flushP();flushL();out.push('<hr>')}
    else if(m=line.match(/^\s*([-*+]|\d+\.)\s+(.*)/)){flushP();const t=/\d/.test(m[1])?'ol':'ul';if(list!==t){flushL();out.push(`<${t}>`);list=t}out.push('<li>'+inl(m[2])+'</li>')}
    else if(m=line.match(/^>\s?(.*)/)){flushP();flushL();out.push('<blockquote>'+inl(m[1])+'</blockquote>')}
    else para.push(line.trim());
  }
  flushP();flushL();return out.join('\n');
}
function xmlEscape(text){return text.replace(/[\u0000-\u0008\u000B\u000C\u000E-\u001F]/g,'').replace(/&/g,'&amp;').replace(/</g,'&lt;').replace(/>/g,'&gt;').replace(/"/g,'&quot;').replace(/'/g,'&apos;')}
function wordRuns(node,style={}){
  if(node.nodeType===Node.TEXT_NODE){if(!node.nodeValue)return '';const properties=`${style.bold?'<w:b/>':''}${style.italic?'<w:i/>':''}${style.code?'<w:rFonts w:ascii="Consolas" w:hAnsi="Consolas"/>':''}`;return `<w:r>${properties?`<w:rPr>${properties}</w:rPr>`:''}<w:t xml:space="preserve">${xmlEscape(node.nodeValue)}</w:t></w:r>`}
  if(node.nodeType!==Node.ELEMENT_NODE)return '';
  const next={bold:style.bold||node.tagName==='B'||node.tagName==='STRONG',italic:style.italic||node.tagName==='I'||node.tagName==='EM',code:style.code||node.tagName==='CODE'};
  return [...node.childNodes].map(child=>wordRuns(child,next)).join('');
}
function wordParagraph(element,kind=''){
  const heading=kind.match(/^H([1-6])$/),list=kind==='LI',quote=kind==='BLOCKQUOTE';
  let content=wordRuns(element);
  if(list)content=`<w:r><w:t>- </w:t></w:r>${content}`;
  if(quote)content=`<w:r><w:t>&gt; </w:t></w:r>${content}`;
  const size=heading?Math.max(22,36-(Number(heading[1])-1)*2):22;
  const pPr=heading?'<w:pPr><w:keepNext/></w:pPr>':'';
  return `<w:p>${pPr}<w:r><w:rPr>${heading?'<w:b/>':''}<w:sz w:val="${size}"/></w:rPr></w:r>${content||'<w:r><w:t></w:t></w:r>'}</w:p>`;
}
function markdownWordParagraphs(source){
  const doc=new DOMParser().parseFromString(`<body>${md2html(source)}</body>`,'text/html'),paragraphs=[];
  const visit=element=>{
    if(/^H[1-6]$/.test(element.tagName)||element.tagName==='P'||element.tagName==='PRE'){paragraphs.push(wordParagraph(element,element.tagName));return}
    if(element.tagName==='UL'||element.tagName==='OL'){[...element.children].forEach(item=>paragraphs.push(wordParagraph(item,'LI')));return}
    if(element.tagName==='BLOCKQUOTE'){paragraphs.push(wordParagraph(element,'BLOCKQUOTE'));return}
    if(element.tagName==='LI'){paragraphs.push(wordParagraph(element,'LI'));return}
    [...element.children].forEach(visit);
  };
  [...doc.body.children].forEach(visit);return paragraphs.join('');
}
function markdownPdfBlocks(source){
  const doc=new DOMParser().parseFromString(`<body>${md2html(source)}</body>`,'text/html'),blocks=[];
  const visit=element=>{
    const heading=element.tagName.match(/^H([1-6])$/);
    if(heading){blocks.push({text:element.textContent,heading:Number(heading[1])});return}
    if(element.tagName==='P'||element.tagName==='PRE'){blocks.push({text:element.textContent});return}
    if(element.tagName==='UL'||element.tagName==='OL'){[...element.children].forEach(item=>blocks.push({text:`- ${item.textContent}`}));return}
    if(element.tagName==='BLOCKQUOTE'){blocks.push({text:`> ${element.textContent}`});return}
    if(element.tagName==='LI'){blocks.push({text:`- ${element.textContent}`});return}
    [...element.children].forEach(visit);
  };
  [...doc.body.children].forEach(visit);return blocks;
}
async function textToPdf(source,fileName,isMarkdown){
  const {PDFDocument,StandardFonts}=await loadPdfLib(),pdf=await PDFDocument.create();
  const regular=await pdf.embedFont(StandardFonts.Helvetica),bold=await pdf.embedFont(StandardFonts.HelveticaBold),margin=54,pageWidth=612,pageHeight=792;
  let page,y;
  const addPage=()=>{page=pdf.addPage([pageWidth,pageHeight]);y=pageHeight-margin};
  const safeText=(text,font)=>text.split('\n').map(line=>{try{font.encodeText(line);return line}catch{return line.normalize('NFKD').replace(/[\u0300-\u036f]/g,'').replace(/[^\x20-\x7e]/g,'?')}}).join('\n');
  const wrapLine=(text,font,size)=>{
    const words=text.split(/\s+/).filter(Boolean),lines=[];let line='';
    for(const word of words){
      const candidate=line?`${line} ${word}`:word;
      if(font.widthOfTextAtSize(candidate,size)<=pageWidth-margin*2){line=candidate;continue}
      if(line)lines.push(line);
      if(font.widthOfTextAtSize(word,size)<=pageWidth-margin*2){line=word;continue}
      let chunk='';
      for(const character of word){if(chunk&&font.widthOfTextAtSize(chunk+character,size)>pageWidth-margin*2){lines.push(chunk);chunk=character}else chunk+=character}
      line=chunk;
    }
    if(line)lines.push(line);
    return lines.length?lines:[''];
  };
  const blocks=isMarkdown?markdownPdfBlocks(source):source.replace(/\r/g,'').split('\n').map(text=>({text}));
  addPage();
  for(const block of blocks){
    const size=block.heading?Math.max(12,20-(block.heading-1)*2):11,font=block.heading?bold:regular;
    const content=safeText(block.text||'',font);
    for(const sourceLine of content.split('\n'))for(const line of wrapLine(sourceLine,font,size)){
      const lineHeight=size*1.4;
      if(y<margin+lineHeight)addPage();
      if(line)page.drawText(line,{x:margin,y:y-lineHeight+2,size,font});
      y-=lineHeight;
    }
    y-=block.heading?8:5;
  }
  return {blob:new Blob([await pdf.save()],{type:'application/pdf'}),name:base(fileName)+'.pdf'};
}
async function convertText(file,options){
  const isDocx=/\.docx$/i.test(file.name),text=isDocx?await readDocxText(file):await file.text();
  if(options.fmt==='txt')return {blob:new Blob([text],{type:'text/plain;charset=utf-8'}),name:base(file.name)+'.txt'};
  if(options.fmt==='pdf')return textToPdf(text,file.name,!isDocx&&/\.(md|markdown)$/i.test(file.name));
  if(isDocx)return {blob:file,name:file.name};
  const Zip=await loadZip(),zip=new Zip(),documentXml=`<?xml version="1.0" encoding="UTF-8" standalone="yes"?><w:document xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main"><w:body>${markdownWordParagraphs(text)}<w:sectPr><w:pgSz w:w="12240" w:h="15840"/><w:pgMar w:top="1440" w:right="1440" w:bottom="1440" w:left="1440"/></w:sectPr></w:body></w:document>`;
  zip.file('[Content_Types].xml','<?xml version="1.0" encoding="UTF-8"?><Types xmlns="http://schemas.openxmlformats.org/package/2006/content-types"><Default Extension="rels" ContentType="application/vnd.openxmlformats-package.relationships+xml"/><Default Extension="xml" ContentType="application/xml"/><Override PartName="/word/document.xml" ContentType="application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml"/></Types>');
  zip.file('_rels/.rels','<?xml version="1.0" encoding="UTF-8"?><Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships"><Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument" Target="word/document.xml"/></Relationships>');
  zip.file('word/document.xml',documentXml);
  const blob=await zip.generateAsync({type:'blob',mimeType:'application/vnd.openxmlformats-officedocument.wordprocessingml.document'});
  return {blob,name:base(file.name)+'.docx'};
}
async function readDocxText(file){
  if(file.size>100*1024*1024)throw new Error('This DOCX file is too large to process in the browser (maximum 100 MB).');
  const Zip=await loadZip(),archive=await Zip.loadAsync(await file.arrayBuffer()),entry=archive.file('word/document.xml');
  if(!entry)throw new Error('This DOCX file does not contain a Word document.');
  const xml=new DOMParser().parseFromString(await entry.async('text'),'application/xml');
  if(xml.querySelector('parsererror'))throw new Error('This DOCX document is damaged or unsupported.');
  const namespace='http://schemas.openxmlformats.org/wordprocessingml/2006/main',paragraphs=[...xml.getElementsByTagNameNS(namespace,'p')];
  const read=node=>[...node.childNodes].map(child=>{
    if(child.nodeType!==Node.ELEMENT_NODE)return '';
    if(child.localName==='t')return child.textContent;
    if(child.localName==='br')return '\n';
    if(child.localName==='tab')return '\t';
    return read(child);
  }).join('');
  return paragraphs.map(read).join('\n');
}

/* ---------- TTF -> WOFF2 (Brotli "store": valido, non compresso) ---------- */
const KT=['cmap','head','hhea','hmtx','maxp','name','OS/2','post','cvt ','fpgm','glyf','loca','prep','CFF ','VORG','EBDT','EBLC','gasp','hdmx','kern','LTSH','PCLT','VDMX','vhea','vmtx','BASE','GDEF','GPOS','GSUB','EBSC','JSTF','MATH','CBDT','CBLC','COLR','CPAL','SVG ','sbix','acnt','avar','bdat','bloc','bsln','cvar','fdsc','feat','fmtx','fvar','gvar','hsty','just','lcar','mort','morx','opbd','prop','trak','Zapf','Silf','Glat','Gloc','Feat','Sill'];
const pad4=n=>(n+3)&~3;
function u128(v){const b=[v&127];while((v>>>=7))b.unshift((v&127)|128);return b}
function brotliStore(data){
  const out=[];
  for(let p=0;p<data.length;p+=32768){
    const c=data.subarray(p,p+32768),sh=p===0?1:0,h=((c.length-1)<<(sh+3))|(1<<(sh+19));
    out.push(new Uint8Array([h&255,(h>>8)&255,(h>>16)&255]),c);
  }
  out.push(new Uint8Array([3]));return new Blob(out);
}
async function ttfToWoff2(f){
  const buffer=await f.arrayBuffer(),src=new DataView(buffer),bytes=new Uint8Array(buffer),flavor=src.getUint32(0);
  if(flavor===0x74746366)throw new Error('TTC font collections are not supported.');
  if(![0x00010000,0x74727565,0x4f54544f].includes(flavor))throw new Error('This is not a valid TTF or OTF file.');
  const nt=src.getUint16(4);let tb=[];
  for(let i=0;i<nt;i++){const r=12+i*16;tb.push({tag:String.fromCharCode(...bytes.subarray(r,r+4)),offset:src.getUint32(r+8),length:src.getUint32(r+12)})}
  const loca=tb.find(t=>t.tag==='loca');
  if(loca){tb=tb.filter(t=>t!==loca);tb.splice(tb.findIndex(t=>t.tag==='glyf')+1,0,loca)}
  const dir=[];let sfnt=12+16*nt,ds=0;
  for(const t of tb){const i=KT.indexOf(t.tag),nul=t.tag==='glyf'||t.tag==='loca'?192:0;
    dir.push(i<0?63:i|nul);if(i<0)for(let k=0;k<4;k++)dir.push(t.tag.charCodeAt(k));
    dir.push(...u128(t.length));sfnt+=pad4(t.length);ds+=t.length}
  const td=new Uint8Array(ds);let p=0;
  for(const t of tb){td.set(bytes.subarray(t.offset,t.offset+t.length),p);p+=t.length}
  const comp=brotliStore(td),total=pad4(48+dir.length+comp.size),h=new DataView(new ArrayBuffer(48));
  h.setUint32(0,0x774f4632);h.setUint32(4,flavor);h.setUint32(8,total);h.setUint16(12,nt);h.setUint32(16,sfnt);h.setUint32(20,comp.size);
  return {blob:new Blob([h,new Uint8Array(dir),comp,new Uint8Array(total-48-dir.length-comp.size)],{type:'font/woff2'}),name:base(f.name)+'.woff2'};
}

/* ---------- Registro strumenti ---------- */
const TOOLS=[
 {id:'img',n:'Images',s:'JPG · JPEG · PNG · SVG · WebP',accept:'image/jpeg,image/png,image/webp,image/svg+xml,.jpg,.jpeg,.png,.webp,.svg',multi:true,each:true,run:convImg,
  d:'Convert between JPG, JPEG, PNG, SVG, and WebP. SVG export wraps raster images; it does not vectorize them. Transparency becomes white in JPG/JPEG.',
  opts:[['Convert to',[['png','PNG'],['jpg','JPG'],['jpeg','JPEG'],['svg','SVG'],['webp','WebP']],'fmt']]},
 {id:'gif',n:'GIF & Video Frames',s:'Preview and export every frame',accept:'image/gif,.gif,video/mp4,video/quicktime,video/x-msvideo,video/x-matroska,video/webm,.mp4,.mov,.avi,.mkv,.webm',multi:false,
  d:'Preview every frame of a GIF or video and save selected frames as PNG files. Video previews are reduced-size; exported frames retain their original resolution.'},
 {id:'cut',n:'Video Cut',s:'Frame-accurate trim · video · GIF',accept:'image/gif,.gif,video/mp4,video/quicktime,video/x-msvideo,video/x-matroska,video/webm,.mp4,.mov,.avi,.mkv,.webm',multi:false,
  d:'Preview every frame of a video or GIF, set exact start and end frames, and export the selected interval locally.',
  opts:[['Export as',[['mp4','MP4'],['mov','MOV'],['avi','AVI'],['mkv','MKV'],['webm','WebM'],['gif','GIF']],'fmt']]},
 {id:'vid',n:'Video Conversion',s:'MP4 · MOV · AVI · MKV · WebM',accept:'video/*,.mp4,.mov,.avi,.mkv,.webm',multi:true,each:true,run:convertVideo,
  d:'Convert between MP4, MOV, AVI, MKV, and WebM in your browser using the bundled offline video engine.',
  opts:[['Convert to',[['mp4','MP4'],['mov','MOV'],['avi','AVI'],['mkv','MKV'],['webm','WebM']],'fmt']]},
 {id:'pdf',n:'Images to PDF',s:'One page per image',accept:'image/*',multi:true,run:imgToPdf,
  d:'Combine images into a PDF. Pages follow the order in which files are selected.'},
 {id:'aud',n:'Audio Format',s:'MP3 · MP4 · WAV',accept:'audio/*,video/*',multi:true,each:true,run:convertAudio,
  d:'Convert audio or extract a browser-decodable audio track to MP3, MP4 (AAC), or WAV.',
  opts:[['Convert to',[['mp3','MP3'],['mp4','MP4 (AAC)'],['wav','WAV']],'fmt']]},
 {id:'md',n:'Text & Markdown',s:'.md · .txt · .docx → .docx · .pdf · .txt',accept:'.md,.markdown,.txt,.docx,text/plain,application/vnd.openxmlformats-officedocument.wordprocessingml.document',multi:true,each:true,run:convertText,
  d:'Convert Markdown, text, or Word documents to PDF, DOCX, or plain text. Word formatting is reduced to text when exported as PDF or TXT.',
  opts:[['Convert to',[['docx','DOCX'],['pdf','PDF'],['txt','TXT']],'fmt']]},
 {id:'ttf',n:'Font to WOFF2',s:'TTF · OTF → WOFF2',accept:'.ttf,.otf',multi:true,each:true,run:ttfToWoff2,
  d:'Convert a TrueType or OpenType font to WOFF2 for web use. Output is not compressed.'},
 {id:'mrg',n:'Merge PDFs',s:'Combine PDF files',accept:'.pdf,application/pdf',multi:true,run:mergePdfs,
  d:'Preview each PDF and arrange the merge order by dragging files or editing their order numbers. Processing uses bundled local libraries.'},
 {id:'split',n:'Split PDF',s:'Choose page ranges',accept:'.pdf,application/pdf',multi:false,run:splitPdf,
  d:'Preview every page, choose the number of parts, and set the page where each part ends. Processing uses bundled local libraries.'}
];
let cur=TOOLS[0],opt={};
let mergeItems=[],mergeSequence=0,mergeDragId=null;
let splitFile=null,splitDoc=null,splitPreviews=[],splitPageOrder=[],splitCount=2,splitBreaks=[],splitError='',splitDragPage=null;
let gifFile=null,gifFrames=[],gifError='',gifLoading=false;
let cutFile=null,cutFrames=[],cutError='',cutLoading=false,cutStart=0,cutEnd=0,cutProgress='';
let splitDownloadVisible=false,viewGeneration=0;
const sessionFiles=new Map();
const conversionRuns=new Map();
const nav=$('nav');
TOOLS.forEach(t=>{const b=document.createElement('button');b.innerHTML=`<b>${t.n}</b><small>${t.s}</small>`;if(t.off)b.disabled=true;b.onclick=()=>pick(t);t.el=b;nav.append(b)});
function pick(t){
  viewGeneration++;clearDownloadResults();$('toolView').hidden=false;$('privacyPage').hidden=true;
  if(cur.id==='mrg'&&t.id!=='mrg')mergeItems=[];
  if(cur.id==='split'&&t.id!=='split'){splitFile=null;splitDoc=null;splitPreviews=[];splitPageOrder=[];splitBreaks=[];splitDownloadVisible=false}
  if(cur.id==='gif'&&t.id!=='gif'){gifFrames.forEach(frame=>URL.revokeObjectURL(frame.preview));gifFile=null;gifFrames=[];gifError='';gifLoading=false}
  if(cur.id==='cut'&&t.id!=='cut'){cutFrames.forEach(frame=>URL.revokeObjectURL(frame.preview));cutFile=null;cutFrames=[];cutError='';cutLoading=false;cutProgress=''}
  cur=t;opt={};TOOLS.forEach(x=>x.el.setAttribute('aria-current',x===t));
  $('t').textContent=t.n;$('d').textContent=t.d;
  $('fi').accept=t.accept;$('fi').multiple=t.multi;$('notice').hidden=true;
  $('ds').textContent=t.s;
  const pdfMode=t.id==='mrg'||t.id==='split'||t.id==='gif'||t.id==='cut',gifMode=t.id==='gif',cutMode=t.id==='cut';
  $('main').classList.toggle('pdf-mode',pdfMode);$('pdfWorkspace').hidden=!(t.id==='mrg'||t.id==='split');$('gifWorkspace').hidden=!gifMode;$('cutWorkspace').hidden=!cutMode;
  if(t.id==='split'){splitFile=null;splitDoc=null;splitPreviews=[];splitPageOrder=[];splitCount=2;splitBreaks=[];splitError='';splitDownloadVisible=false;renderSplitWorkspace()}
  else if(t.id==='mrg')renderMergeWorkspace();
  else $('pdfWorkspace').replaceChildren();
  if(cutMode){cutFrames=[];cutFile=null;cutError='';cutLoading=false;cutStart=0;cutEnd=0;cutProgress='';renderCutWorkspace()}else $('cutWorkspace').replaceChildren();
  if(gifMode){gifFrames.forEach(frame=>URL.revokeObjectURL(frame.preview));gifFile=null;gifFrames=[];gifError='';gifLoading=false;renderGifWorkspace()}else $('gifWorkspace').replaceChildren();
  const o=$('opts');o.innerHTML='';
  (t.opts||[]).forEach(([lab,vals,key])=>{const l=document.createElement('label');l.textContent=lab+' ';const s=document.createElement('select');
    vals.forEach(([v,x])=>s.add(new Option(x,v)));opt[key]=vals[0][0];s.onchange=()=>opt[key]=s.value;l.append(s);o.append(l)});
}
function node(tag,className,text){const item=document.createElement(tag);if(className)item.className=className;if(text!==undefined)item.textContent=text;return item}
function clearDownloadResults(){
  $('list').querySelectorAll('a.dl').forEach(link=>URL.revokeObjectURL(link.href));
  $('list').replaceChildren();conversionRuns.clear();$('notice').hidden=true;$('notice').textContent='';
}
function trackSessionFiles(files){files.forEach(file=>sessionFiles.set(`${file.name}:${file.size}:${file.lastModified}`,{name:file.name,size:file.size}))}
function privacyBlock(title){const section=node('section','privacy-block');section.append(node('h2','',title));return section}
function renderPrivacyPage(){
  const details=$('privacyDetails');details.replaceChildren();
  $('privacyIntro').textContent=`Updated ${new Date().toLocaleDateString()}. All conversion libraries are included in this local copy. No conversion code or selected file contents are fetched from the internet.`;
  const session=privacyBlock('Data in this session'),inventory=node('dl');
  const files=[...sessionFiles.values()],fileNames=files.length?files.map(file=>`${file.name} (${(file.size/1024).toFixed(0)} KB)`).join(', '):'No selected file names are currently retained.';
  [['Selected files',fileNames],['Saved on this site','No account, cookies, analytics, or local storage are used by this app.'],['Downloads','Generated files are held in temporary browser object URLs until you navigate to another tool or clear this session.']].forEach(([label,value])=>{inventory.append(node('dt','',label),node('dd','',value))});
  session.append(inventory,node('p','','Input file bytes may remain in browser memory while a conversion or preview is active. Clearing this session drops the app references and revokes generated download URLs. The browser controls where downloaded files are saved.'));details.append(session);
  const libraries=privacyBlock('Local conversion libraries'),libraryList=node('ul','privacy-library-list');
  [['PDF creation','pdf-lib.min.js'],['PDF preview','pdf.min.js'],['PDF worker','pdf.worker.min.js'],['MP3 encoder','lame.min.js'],['ZIP support','jszip.min.js'],['Video engine','ffmpeg.min.js'],['FFmpeg WebAssembly core','ffmpeg-core.wasm'],['FFmpeg core loader','ffmpeg-core.js'],['FFmpeg worker','ffmpeg-core.worker.js']].forEach(([label,file])=>{
    const item=node('li'),link=node('a','',`${label} (${file})`);link.href=`vendor/${file}`;link.download=file;item.append(link);libraryList.append(item);
  });
  const notices=node('a','','Third-party notices and license texts');notices.href='vendor/THIRD_PARTY_NOTICES.txt';notices.download='THIRD_PARTY_NOTICES.txt';
  libraries.append(libraryList,node('p','','These exact files are already bundled with this copy; the links are provided for inspection or a separate offline backup.'),notices,node('p','','To run this copy fully offline, start run-local.ps1 from PowerShell in the app folder, then open http://127.0.0.1:8765/. The local server listens only on this computer.'));details.append(libraries);
  const network=privacyBlock('Network and third parties');
  network.append(node('p','','Conversion does not contact a server. When hosted on a website, the hosting provider receives the ordinary requests needed to load the page and its local assets. The Powered by MarioScan link opens an external website only when you choose to click it.'));details.append(network);
  const choices=privacyBlock('Your controls');choices.append(node('p','','You can stop using a tool at any time, clear the session below, or remove downloaded files using your browser. This app does not retain files between page loads.'));details.append(choices);
  const limits=privacyBlock('Privacy notice');limits.append(node('p','','This page describes this app’s current behavior; it is not a legal-compliance guarantee. The site owner’s legal identity, contact address, and applicable jurisdiction are not supplied here and should be added before relying on this as a statutory privacy notice.'));details.append(limits);
}
function showPrivacyPage(){
  viewGeneration++;clearDownloadResults();$('toolView').hidden=true;$('privacyPage').hidden=false;renderPrivacyPage();window.scrollTo({top:0,behavior:'smooth'});
}
function showToolPage(){viewGeneration++;$('privacyPage').hidden=true;$('toolView').hidden=false;window.scrollTo({top:0,behavior:'smooth'})}
function clearSessionData(){
  viewGeneration++;clearDownloadResults();stopVideoEngine();sessionFiles.clear();mergeItems=[];splitFile=null;splitDoc=null;splitPreviews=[];splitPageOrder=[];splitCount=2;splitBreaks=[];splitError='';splitDownloadVisible=false;
  gifFrames.forEach(frame=>URL.revokeObjectURL(frame.preview));gifFile=null;gifFrames=[];gifError='';gifLoading=false;$('fi').value='';
  cutFrames.forEach(frame=>URL.revokeObjectURL(frame.preview));cutFile=null;cutFrames=[];cutError='';cutLoading=false;cutProgress='';
  if(cur.id==='mrg')renderMergeWorkspace();if(cur.id==='split')renderSplitWorkspace();if(cur.id==='gif')renderGifWorkspace();if(cur.id==='cut')renderCutWorkspace();renderPrivacyPage();
}
function actionButton(text,primary,onClick){const button=node('button','pdf-action'+(primary?' primary':''),text);button.type='button';button.onclick=onClick;return button}
function isPdfFile(file){return file.type==='application/pdf'||/\.pdf$/i.test(file.name)}
function isVideoFile(file){return file.type.startsWith('video/')||/\.(mp4|mov|avi|mkv|webm)$/i.test(file.name)}
function renderMergeWorkspace(){
  const workspace=$('pdfWorkspace');workspace.replaceChildren();
  const toolbar=node('div','pdf-toolbar'),summary=node('p','',`${mergeItems.length} PDF${mergeItems.length===1?'':'s'} loaded. Drag to reorder or edit the order number.`),actions=node('div','pdf-actions');
  const merge=actionButton('Merge PDFs',true,mergeLoadedPdfs);
  merge.disabled=mergeItems.length<2||mergeItems.some(item=>item.error||!item.preview);
  const clear=actionButton('Clear all',false,()=>{mergeItems=[];renderMergeWorkspace()});
  clear.disabled=!mergeItems.length;actions.append(clear,merge);toolbar.append(summary,actions);workspace.append(toolbar);
  if(!mergeItems.length){workspace.append(node('p','pdf-empty','Add PDF files above to preview and arrange the merge order.'));return}
  const grid=node('div','merge-grid');workspace.append(grid);
  mergeItems.forEach((item,index)=>{
    const card=node('article','pdf-card');card.draggable=true;card.dataset.id=String(item.id);
    card.addEventListener('dragstart',event=>{mergeDragId=item.id;card.classList.add('dragging');event.dataTransfer.effectAllowed='move';event.dataTransfer.setData('text/plain',String(item.id))});
    card.addEventListener('dragend',()=>{mergeDragId=null;document.querySelectorAll('.pdf-card').forEach(entry=>entry.classList.remove('dragging','drag-target'))});
    card.addEventListener('dragover',event=>{event.preventDefault();card.classList.add('drag-target')});
    card.addEventListener('dragleave',()=>card.classList.remove('drag-target'));
    card.addEventListener('drop',event=>{event.preventDefault();card.classList.remove('drag-target');const id=Number(event.dataTransfer.getData('text/plain'))||mergeDragId;moveMergeItem(id,item.id)});
    const preview=node('div','pdf-thumb');
    if(item.preview){const image=node('img');image.src=item.preview;image.alt=`First page of ${item.file.name}`;preview.append(image)}
    else preview.textContent=item.error?'Preview unavailable':'Loading preview…';
    const name=node('div','pdf-name',item.file.name);name.title=item.file.name;
    const meta=node('div','pdf-card-meta',item.error||`${item.pageCount||'…'} page${item.pageCount===1?'':'s'}`);
    const bottom=node('div','pdf-card-bottom'),orderLabel=node('label','order-field','Order');
    const order=node('input');order.type='number';order.min='1';order.max=String(mergeItems.length);order.step='1';order.value=String(index+1);order.setAttribute('aria-label',`Order for ${item.file.name}`);
    order.onchange=()=>{const requested=Number(order.value),position=Math.max(0,Math.min(mergeItems.length-1,Number.isFinite(requested)?Math.trunc(requested)-1:0));moveMergeItem(item.id,mergeItems[position].id)};orderLabel.append(order);
    const remove=node('button','remove-pdf','Remove');remove.type='button';remove.onclick=()=>{mergeItems=mergeItems.filter(entry=>entry.id!==item.id);renderMergeWorkspace()};
    bottom.append(orderLabel,remove);card.append(preview,name,meta,bottom);grid.append(card);
  });
}
function moveMergeItem(fromId,toId){
  const from=mergeItems.findIndex(item=>item.id===fromId),to=mergeItems.findIndex(item=>item.id===toId);
  if(from<0||to<0||from===to)return;
  const [item]=mergeItems.splice(from,1);mergeItems.splice(to,0,item);renderMergeWorkspace();
}
async function addMergeFiles(files){
  const additions=files.map(file=>({id:++mergeSequence,file,pageCount:0,preview:'',error:isPdfFile(file)?'':'Select a PDF file.'}));
  mergeItems.push(...additions);renderMergeWorkspace();
  for(const item of additions){
    if(item.error){renderMergeWorkspace();continue}
    try{const doc=await loadPreviewDocument(item.file);item.pageCount=doc.numPages;if(!item.pageCount)throw new Error('This PDF has no pages.');item.preview=await renderPdfPreview(doc,1)}
    catch(error){item.error=error.message||'Could not preview this PDF.'}
    renderMergeWorkspace();
  }
}
function defaultSplitBreaks(pageCount,partCount){
  return Array.from({length:Math.max(0,partCount-1)},(_,index)=>Math.round((index+1)*pageCount/partCount));
}
function partForPosition(position){let part=1;for(const end of splitBreaks){if(position+1>end)part++;else break}return part}
function renderSplitWorkspace(){
  const workspace=$('pdfWorkspace');workspace.replaceChildren();
  if(splitError)workspace.append(node('p','pdf-error',splitError));
  const layout=node('div','split-layout'),pages=node('div','split-pages'),panel=node('section','split-panel');
  if(!splitDoc)pages.append(node('p','pdf-empty',splitFile?'Loading PDF pages…':'Select one PDF to preview its pages and configure the split.'));
  else splitPageOrder.forEach((pageNumber,index)=>{
    const card=node('article','split-page');card.draggable=true;
    card.addEventListener('dragstart',event=>{splitDragPage=pageNumber;card.classList.add('dragging');event.dataTransfer.effectAllowed='move';event.dataTransfer.setData('text/plain',String(pageNumber))});
    card.addEventListener('dragend',()=>{splitDragPage=null;document.querySelectorAll('.split-page').forEach(entry=>entry.classList.remove('dragging','drag-target'))});
    card.addEventListener('dragover',event=>{event.preventDefault();card.classList.add('drag-target')});
    card.addEventListener('dragleave',()=>card.classList.remove('drag-target'));
    card.addEventListener('drop',event=>{event.preventDefault();card.classList.remove('drag-target');const fromPage=Number(event.dataTransfer.getData('text/plain'))||splitDragPage;moveSplitPage(fromPage,pageNumber)});
    card.addEventListener('contextmenu',event=>{event.preventDefault();removeSplitPage(pageNumber)});
    const preview=node('div','split-page-preview'),image=node('img');
    image.alt=`Preview of page ${pageNumber}`;image.dataset.previewPage=String(pageNumber);
    if(splitPreviews[pageNumber-1])image.src=splitPreviews[pageNumber-1];else preview.textContent='Loading…';
    if(splitPreviews[pageNumber-1])preview.append(image);else preview.dataset.previewPage=String(pageNumber);
    const info=node('div','split-page-info');info.append(node('strong','',`Page ${pageNumber}`),node('span','part-label',`Part ${partForPosition(index)}`));
    card.append(preview,info);pages.append(card);
    if(splitBreaks.includes(index+1)){const divider=node('div','split-divider',`End of part ${partForPosition(index)}`);pages.append(divider)}
  });
  if(splitDoc)layout.before(node('p','split-help','Drag pages to reorder. Right-click a page to remove it. The lines mark where the PDF will split.'));
  panel.append(node('h2','','Split settings'));
  const countLabel=node('label','','Number of parts'),countInput=node('input');
  countInput.type='number';countInput.min='1';countInput.max=String(splitPageOrder.length||2);countInput.step='1';countInput.value=String(splitCount);countInput.disabled=!splitDoc||splitPageOrder.length<2;countInput.setAttribute('aria-label','Number of parts');countLabel.append(countInput);panel.append(countLabel);
  const breakFields=node('div','split-breaks');
  if(splitDoc)splitBreaks.forEach((page,index)=>{
    const label=node('label','',`Part ${index+1} ends after position`),input=node('input');
    input.type='number';input.min=String(index?splitBreaks[index-1]+1:1);input.max=String(splitPageOrder.length-(splitBreaks.length-index));input.value=String(page);input.setAttribute('aria-label',`Part ${index+1} ends after position`);
    input.onchange=()=>{const low=Number(input.min),high=Number(input.max);splitBreaks[index]=Math.max(low,Math.min(high,Math.trunc(Number(input.value)||low)));for(let next=index+1;next<splitBreaks.length;next++){const min=splitBreaks[next-1]+1,max=splitPageOrder.length-(splitBreaks.length-next);splitBreaks[next]=Math.max(min,Math.min(max,splitBreaks[next]))}renderSplitWorkspace()};
    label.append(input);breakFields.append(label);
  });
  panel.append(breakFields,node('p','split-help',splitDoc?`${splitPageOrder.length} pages selected. Each part includes its ending position.`:'Page break fields appear after a PDF is loaded.'));
  const splitButton=actionButton(splitDoc?`Split into ${splitCount} parts`:'Split PDF',true,splitLoadedPdf);splitButton.disabled=!splitDoc||splitPageOrder.length<2;panel.append(splitButton);
  if(splitDownloadVisible)panel.append(actionButton('Go to downloads',false,()=>$('list').scrollIntoView({behavior:'smooth',block:'start'})));
  countInput.onchange=()=>{const pageCount=splitPageOrder.length;splitCount=Math.max(1,Math.min(pageCount,Math.trunc(Number(countInput.value)||1)));splitBreaks=defaultSplitBreaks(pageCount,splitCount);renderSplitWorkspace()};
  layout.append(pages,panel);workspace.append(layout);
}
function moveSplitPage(fromPage,toPage){
  const from=splitPageOrder.indexOf(fromPage),to=splitPageOrder.indexOf(toPage);
  if(from<0||to<0||from===to)return;
  const [page]=splitPageOrder.splice(from,1);splitPageOrder.splice(to,0,page);renderSplitWorkspace();
}
function removeSplitPage(pageNumber){
  if(splitPageOrder.length<=1){showNotice('At least one page must remain in the PDF.');return}
  splitPageOrder=splitPageOrder.filter(page=>page!==pageNumber);splitCount=Math.min(splitCount,splitPageOrder.length);splitBreaks=defaultSplitBreaks(splitPageOrder.length,splitCount);renderSplitWorkspace();
}
async function loadSplitFile(file){
  splitFile=file;splitDoc=null;splitPreviews=[];splitPageOrder=[];splitCount=2;splitBreaks=[];splitError='';renderSplitWorkspace();
  if(!isPdfFile(file)){splitError='Select a PDF file.';renderSplitWorkspace();return}
  try{
    const doc=await loadPreviewDocument(file);if(splitFile!==file)return;
    splitDoc=doc;splitPageOrder=Array.from({length:doc.numPages},(_,index)=>index+1);splitCount=Math.min(2,doc.numPages);splitBreaks=defaultSplitBreaks(splitPageOrder.length,splitCount);splitPreviews=new Array(doc.numPages);renderSplitWorkspace();
    for(let page=1;page<=doc.numPages;page++){
      splitPreviews[page-1]=await renderPdfPreview(doc,page,165);if(splitFile!==file)return;
      const preview=$('pdfWorkspace').querySelector(`[data-preview-page="${page}"]`);
      if(preview){const image=node('img');image.src=splitPreviews[page-1];image.alt=`Preview of page ${page}`;preview.replaceChildren(image)}
    }
  }catch(error){if(splitFile===file){splitError=error.message||'Could not open this PDF.';renderSplitWorkspace()}}
}
async function mergeLoadedPdfs(){
  const generation=viewGeneration;
  const files=mergeItems.map(item=>item.file),key=conversionSignature('mrg',files,{}),record=beginConversion(key);if(!record)return;
  const result=row(`Merging ${mergeItems.length} PDFs`);
  try{const output=await mergePdfs(files);if(generation!==viewGeneration)return;done(result,output,record);record.status='done'}catch(error){fail(result,error);conversionRuns.delete(key)}
}
async function splitLoadedPdf(){
  if(!splitFile)return;
  const generation=viewGeneration;
  const key=conversionSignature('split',[splitFile],{breaks:[...splitBreaks],pages:[...splitPageOrder]});
  const record=beginConversion(key);if(!record)return;
  splitDownloadVisible=true;renderSplitWorkspace();
  const result=row(`Splitting ${splitFile.name}`);
  try{const outputs=await splitPdf(splitFile,splitBreaks,splitPageOrder);if(generation!==viewGeneration)return;result.li.remove();outputs.files.forEach(file=>done(row(file.name),file,record));record.status='done'}catch(error){if(generation===viewGeneration)fail(result,error);conversionRuns.delete(key)}
}
const fi=$('fi'),drop=$('drop');
async function handleFiles(files){
  trackSessionFiles(files);
  if(cur.id==='mrg'){await addMergeFiles(files);return}
  if(cur.id==='cut'){
    if(files.length>1){cutError='Select one video or GIF at a time.';renderCutWorkspace();return}
    if(files[0])await loadCutFile(files[0]);
    return;
  }
  if(cur.id==='gif'){
    if(files.length>1){gifError='Select one GIF file at a time.';renderGifWorkspace();return}
    if(files[0])await loadGifFile(files[0]);
    return;
  }
  if(cur.id==='split'){
    if(files.length>1){splitError='Select one PDF at a time.';renderSplitWorkspace();return}
    if(files[0])await loadSplitFile(files[0]);
    return;
  }
  await run(files);
}
addEventListener('dragover',e=>e.preventDefault());addEventListener('drop',e=>e.preventDefault());
drop.ondragover=e=>{e.preventDefault();drop.classList.add('over')};
drop.ondragleave=()=>drop.classList.remove('over');
drop.ondrop=e=>{e.preventDefault();drop.classList.remove('over');handleFiles([...e.dataTransfer.files])};
fi.onchange=()=>{handleFiles([...fi.files]);fi.value=''};
function row(name){const li=document.createElement('li'),b=document.createElement('b'),s=document.createElement('span');b.textContent=name;s.className='st';s.textContent='Converting…';li.append(b,s);$('list').append(li);return {li,s}}
function conversionSignature(tool,files,settings){return JSON.stringify([tool,files.map(file=>[file.name,file.size,file.type,file.lastModified,file.webkitRelativePath||'']),settings])}
function showNotice(message){const notice=$('notice');notice.textContent=message;notice.hidden=false;notice.scrollIntoView({block:'nearest',behavior:'smooth'})}
function localTimestamp(date=new Date()){const pad=value=>String(value).padStart(2,'0');return `${date.getFullYear()}-${pad(date.getMonth()+1)}-${pad(date.getDate())} ${pad(date.getHours())}:${pad(date.getMinutes())}:${pad(date.getSeconds())}`}
function beginConversion(key){
  const existing=conversionRuns.get(key);
  if(existing&&(existing.status==='running'||existing.links.some(link=>document.body.contains(link)))){
    showNotice(existing.status==='running'?'This conversion is already in progress. Its download will appear below.':'This download is already available below. No duplicate was added.');
    return null;
  }
  const record={status:'running',links:[]};conversionRuns.set(key,record);$('notice').hidden=true;return record;
}
function appendResult(r,res,record){
  if(res.files){r.li.remove();res.files.forEach(file=>done(row(file.name),file,record));return}
  done(r,res,record);
}
function done(r,res,record){const a=document.createElement('a');a.className='dl';a.href=URL.createObjectURL(res.blob);a.download=res.name;
  a.textContent=`Download | ${res.name} | ${localTimestamp()} (${(res.blob.size/1024).toFixed(0)} KB)`;
  a.addEventListener('click',event=>{if(a.dataset.downloadStarted){event.preventDefault();showNotice('This download has already been started. The original is available below.')}else a.dataset.downloadStarted='true'});
  r.s.replaceWith(a);record.links.push(a)}
function fail(r,e){r.s.textContent='Conversion failed: '+e.message;r.s.classList.add('err')}
async function run(files){
  if(!files.length)return;const t=cur,generation=viewGeneration;
  const convert=async(sourceFiles,settings,label)=>{
    if(generation!==viewGeneration)return;
    const key=conversionSignature(t.id,sourceFiles,settings),record=beginConversion(key);if(!record)return;
    const result=row(label);
    try{const output=await t.run(t.each?sourceFiles[0]:sourceFiles,settings);if(generation!==viewGeneration)return;appendResult(result,output,record);record.status='done'}
    catch(error){if(generation===viewGeneration)fail(result,error);conversionRuns.delete(key)}
  };
  if(t.each){for(const file of files)await convert([file],{...opt},file.name)}
  else await convert(files,{...opt},`${files.length} file${files.length===1?'':'s'}`);
}
$('privacyOpen').addEventListener('click',showPrivacyPage);
$('privacyBack').addEventListener('click',showToolPage);
$('clearSession').addEventListener('click',clearSessionData);
pick(TOOLS[0]);