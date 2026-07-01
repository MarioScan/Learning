let flashcards = [];
let tipoGiocoAttuale = "";   
let tipoStrutturaGioco = ""; // "allenamento", "challenge" o "learning"
let modalitaAttuale = "";     
let direzioneEffettiva = "";  
let difficoltaScelta = "";    
let numeroEffettivo = "";     
let cartaCorrente = null;
let ultimaCartaPescata = null;

// Gestione mazzo Challenge
let mazzoChallenge = [];
let indiceChallengeCorrente = 0;
let totaleDomandeChallenge = 0;
let risposteCorretteChallenge = 0;

// Gestione contatore risposte di fila (Streak)
let corretteDiFila = 0;

// Mappa per associare i nomi delle stanze salvati nel JSON con i titoli formattati
const nomiStanzeFormattati = {
    "schlafzimmer": "Camera da letto (Schlafzimmer)",
    "wohnzimmer": "Soggiorno / Salotto (Wohnzimmer)",
    "badezimmer": "Bagno (Badezimmer)",
    "kuche": "Cucina (Küche)",
    "flur": "Ingresso / Corridoio (Flur)",
    "keller": "Cantina (Keller)",
    "garten": "Giardino (Garten)",
    "balkon": "Balcone (Balkon)",
    "garage": "Garage (Garage)"
};

// Caricamento del vocabolario JSON e associazione punteggi utente
console.log("[INFO] Scaricamento vocabolario dal server...");
fetch('words.json')
    .then(answer => {
        if (!answer.ok) throw new Error("File JSON non trovato o errore server");
        return answer.json();
    })
    .then(data => {
        flashcards = data;
        console.log("[SUCCESS] Vocabolario sincronizzato dal server. Totale parole:", flashcards.length);
        
        const punteggiSalvati = localStorage.getItem('punteggi_utente_flashcards');
        if (punteggiSalvati) {
            const dizionarioPunteggi = JSON.parse(punteggiSalvati);
            flashcards.forEach(item => {
                const parolaTedesca = (item.type === "nome" ? item.de.singular : item.de).trim();
                const chiaveUnivoca = `${parolaTedesca}_${item.type.trim().toLowerCase()}`;
                
                if (dizionarioPunteggi[chiaveUnivoca]) {
                    item.stats.correct = dizionarioPunteggi[chiaveUnivoca].correct || 0;
                    item.stats.mistakes = dizionarioPunteggi[chiaveUnivoca].mistakes || 0;
                }
            });
            console.log("[SUCCESS] Punteggi personali ripristinati con successo.");
        }
        // Inizializza l'elenco dei bottoni nella schermata Learning Mode una volta che i dati sono pronti
        creaMenuLearning();
    })
    .catch(fail => console.error("[ERROR] Impossibile caricare i dati dal server:", fail));

function salvaProgressiNelBrowser() {
    const dizionarioPunteggi = {};
    flashcards.forEach(item => {
        if (item.stats.correct > 0 || item.stats.mistakes > 0) {
            const parolaTedesca = (item.type === "nome" ? item.de.singular : item.de).trim();
            const chiaveUnivoca = `${parolaTedesca}_${item.type.trim().toLowerCase()}`;
            
            dizionarioPunteggi[chiaveUnivoca] = {
                correct: item.stats.correct,
                mistakes: item.stats.mistakes
            };
        }
    });
    localStorage.setItem('punteggi_utente_flashcards', JSON.stringify(dizionarioPunteggi));
}

function mostraSottomenu(idSottomenu) {
    document.querySelectorAll('.schermata').forEach(s => s.classList.remove('attiva'));
    const target = document.getElementById(idSottomenu);
    if (target) target.classList.add('attiva');
}

// AGGIORNATA: Implementazione completa di tutte le regole e le eccezioni degli articoli italiani
function ottieniArticolo(elemento, lingua, numero = "singular", parolaSpecificata = null, genereSpecificato = null) {
    if (elemento.type !== "nome") return "";
    
    let parola = parolaSpecificata || (elemento[lingua] && elemento[lingua][numero]) || "";
    parola = parola.trim().toLowerCase(); // Lavoriamo in minuscolo per evitare errori di case
    if (!parola) return "";
    
    const genere = genereSpecificato || (elemento[lingua].gender ? elemento[lingua].gender.trim().toLowerCase() : "m");

    // --- CASO LINGUA TEDESCA ---
    if (lingua === "de") {
        if (numero === "plural") return "die ";
        if (genere === "m") return "der ";
        if (genere === "f") return "die ";
        if (genere === "n") return "das ";
    } 
    
    // --- CASO LINGUA ITALIANA (Regole Grammaticali Complete) ---
    else if (lingua === "it") {
        const primaLettera = parola.charAt(0);
        const primeDueLettere = parola.substring(0, 2);
        
        const èVocale = ['a', 'e', 'i', 'o', 'u', 'à', 'è', 'é', 'ì', 'ò', 'ù'].includes(primaLettera);
        
        // Controllo eccezioni particolari italiane: s+consonante, z, gn, ps, pn, x, y
        const èS_Consonante = primaLettera === 's' && !['a', 'e', 'i', 'o', 'u'].includes(parola.charAt(1));
        const èZ_GN_PS_PN_X_Y = ['z', 'gn', 'ps', 'pn', 'x', 'y'].includes(primaLettera) || ['gn', 'ps', 'pn'].includes(primeDueLettere);
        const richiedeLoGli = èS_Consonante || èZ_GN_PS_PN_X_Y;

        if (numero === "singular") {
            // FEMMINILE SINGOLARE
            if (genere === "f") {
                return èVocale ? "l'" : "la "; // l'asola, la sedia
            }
            // MASCHILE SINGOLARE
            else {
                if (èVocale) return "l'"; // l'armadio, l'orologio
                if (richiedeLoGli) return "lo "; // lo specchio, lo zaino, lo psicologo
                return "il "; // il tavolo, il tappeto
            }
        } else {
            // FEMMINILE PLURALE
            if (genere === "f") {
                return "le "; // le sedie, le lampade, le autorimesse
            }
            // MASCHILE PLURALE
            else {
                // Al plurale, le parole che al singolare volevano "l'" o "lo" vogliono "gli"
                if (èVocale || richiedeLoGli) return "gli "; // gli armadi, gli specchi, gli zaini
                return "i "; // i tavoli, i tappeti
            }
        }
    }
    return "";
}


function estraiParolaFormattata(elemento, lingua, numero = "singular", parolaSpecificata = null) {
    if (elemento.type === "nome") {
        if (!elemento[lingua] || typeof elemento[lingua] === "string") {
            return (elemento[lingua] || "").trim();
        }
        const sostantivo = (parolaSpecificata || elemento[lingua][numero] || "").trim();
        const articolo = ottieniArticolo(elemento, lingua, numero, sostantivo);
        return `${articolo}${sostantivo}`;
    }
    return (elemento[lingua] || "").trim();
}

// 1. MODIFICA: Funzione per iniettare le Umlaut e la doppia ss (ß) nella casella di testo
function inserisciCarattere(carattere) {
    const inputField = document.getElementById("input-risposta");
    if (inputField && !inputField.disabled) {
        const startPos = inputField.selectionStart;
        const endPos = inputField.selectionEnd;
        const valoreCorrente = inputField.value;
        
        // Inserisce il carattere speciale nel punto esatto del cursore di scrittura
        inputField.value = valoreCorrente.substring(0, startPos) + carattere + valoreCorrente.substring(endPos);
        inputField.focus();
        
        // Riposiziona il cursore subito dopo il carattere speciale inserito
        inputField.selectionStart = inputField.selectionEnd = startPos + carattere.length;
    }
}

// AGGIORNATA: Memorizza i parametri correnti per la funzione Riprova
let ultimaModalitaLinguistica = ""; 
let ultimoLimiteChallenge = null;   

function start(tipo, struttura, modalita, limiteChallenge = null) {
    if (flashcards.length === 0) return;
    
    tipoGiocoAttuale = tipo;
    tipoStrutturaGioco = struttura;
    modalitaAttuale = modalita;
    ultimaCartaPescata = null;
    risposteCorretteChallenge = 0;
    
    // Memorizziamo i parametri per il tasto Riprova
    ultimaModalitaLinguistica = modalita;
    ultimoLimiteChallenge = limiteChallenge;

    if (tipo === "scrivi") {
        difficoltaScelta = document.querySelector('input[name="difficolta-scrivi"]:checked').value;
        document.getElementById("interfaccia-scrittura").style.display = "block";
        document.getElementById("interfaccia-flashcard").style.display = "none";
    } else {
        difficoltaScelta = document.querySelector('input[name="difficolta-flashcard"]:checked').value;
        document.getElementById("interfaccia-scrittura").style.display = "none";
        document.getElementById("interfaccia-flashcard").style.display = "block";
    }

    if (struttura === "challenge") {
        let mazzoMescolato = [...flashcards];
        for (let i = mazzoMescolato.length - 1; i > 0; i--) {
            const j = Math.floor(Math.random() * (i + 1));
            [mazzoMescolato[i], mazzoMescolato[j]] = [mazzoMescolato[j], mazzoMescolato[i]];
        }

        if (limiteChallenge === "all") {
            totaleDomandeChallenge = mazzoMescolato.length;
        } else {
            totaleDomandeChallenge = Math.min(parseInt(limiteChallenge), mazzoMescolato.length);
        }

        mazzoChallenge = mazzoMescolato.slice(0, totaleDomandeChallenge);
        indiceChallengeCorrente = 0;
        document.getElementById("progresso-challenge").innerText = `Parola 1 / ${totaleDomandeChallenge}`;
    } else {
        document.getElementById("progresso-challenge").innerText = "";
    }

    const bloccoStreak = document.getElementById("blocco-streak");
    if (bloccoStreak) bloccoStreak.className = "streak-container streak-attiva";

    mostraSottomenu('zona-gioco');
    prossimaCarta();
}

// Gestione della logica di pesca carta e interazione round
function prossimaCarta() {
    if (flashcards.length === 0) return;

    document.getElementById("zona-dettagli-risposta").style.display = "none";
    document.getElementById("parola-tradotta").innerText = "";
    document.getElementById("parola-singolare-extra").innerText = "";

    document.getElementById("input-risposta").value = "";
    document.getElementById("feedback-scrittura").innerText = "";
    document.getElementById("btn-prossima-scrivi").style.display = "none";
    document.getElementById("btn-invia-scrivi").style.display = "inline-block";
    document.getElementById("input-risposta").disabled = false;

    document.getElementById("btn-gira").style.display = "inline-block";
    document.getElementById("zona-bottoni-flashcard").style.display = "none";

    // CONTROLLO PESCA: Allenamento vs Challenge
    if (tipoStrutturaGioco === "challenge") {
        if (indiceChallengeCorrente >= totaleDomandeChallenge) {
            alert(`🎉 Challenge completata con successo! Punteggio finale: ${risposteCorretteChallenge} / ${totaleDomandeChallenge}`);
            tornaAlMenu();
            return;
        }
        
        cartaCorrente = mazzoChallenge[indiceChallengeCorrente];
        document.getElementById("progresso-challenge").innerText = `Parola ${indiceChallengeCorrente + 1} / ${totaleDomandeChallenge}`;
        indiceChallengeCorrente++;
    } else {
        // Modalità Allenamento: pesca casuale infinita anti-ripetizione
        let indiceCasuale, nuovaCarta, tentativi = 0;
        do {
            indiceCasuale = Math.floor(Math.random() * flashcards.length);
            nuovaCarta = flashcards[indiceCasuale];
            tentativi++;
        } while (nuovaCarta === ultimaCartaPescata && flashcards.length > 1 && tentativi < 10);

        cartaCorrente = nuovaCarta;
        ultimaCartaPescata = cartaCorrente;
    }

    if (modalitaAttuale === "casuali") {
        direzioneEffettiva = Math.random() < 0.5 ? "de-it" : "it-de";
    } else {
        direzioneEffettiva = modalitaAttuale;
    }

    if (cartaCorrente.type === "nome" && difficoltaScelta === "misto") {
        numeroEffettivo = Math.random() < 0.5 ? "singular" : "plural";
    } else {
        numeroEffettivo = "singular";
    }

    let linguaDomanda = direzioneEffettiva === "de-it" ? "de" : "it";
    let quesitoVisuale = estraiParolaFormattata(cartaCorrente, linguaDomanda, numeroEffettivo);
    let etichettaNumero = (cartaCorrente.type === "nome") ? ` - ${numeroEffettivo === "singular" ? "Singolare" : "Plurale"}` : "";

    document.getElementById("parola-quesito").innerText = `${quesitoVisuale} (${cartaCorrente.type}${etichettaNumero})`;
    
    if (tipoGiocoAttuale === "scrivi") {
        setTimeout(() => document.getElementById("input-risposta").focus(), 50);
    }

        // === AGGIUNTA LOGICA: Cambio dinamico dei tasti speciali (Accenti vs Umlaut) ===
    const bloccoTasti = document.getElementById("blocco-tasti-caratteri");
    const notaTastiera = document.getElementById("nota-spiegazione-tastiera");
    
    if (bloccoTasti && notaTastiera) {
        bloccoTasti.innerHTML = ""; // Svuota i vecchi tasti
        let linguaRisposta = direzioneEffettiva === "de-it" ? "it" : "de";

        if (linguaRisposta === "it") {
            // Se scrivi in Italiano, mostra gli accenti frequenti
            const accentiIt = ['à', 'è', 'é', 'ì', 'ò', 'ù'];
            accentiIt.forEach(char => {
                bloccoTasti.innerHTML += `<button type="button" class="btn-char" onclick="inserisciCarattere('${char}')">${char}</button>`;
            });
            notaTastiera.innerHTML = "<em>* Accenti frequenti della lingua italiana per facilitare la scrittura</em>";
        } else {
            // Se scrivi in Tedesco, mostra Umlaut e doppia S
            const caratteriDe = ['ä', 'Ä', 'ö', 'Ö', 'ü', 'Ü', 'ß'];
            caratteriDe.forEach(char => {
                bloccoTasti.innerHTML += `<button type="button" class="btn-char" onclick="inserisciCarattere('${char}')">${char}</button>`;
            });
            notaTastiera.innerHTML = "<em>* Umlaut indica i doppi punti; ß indica il simbolo della doppia ss (Eszett)</em>";
        }
    }
}

function mostraInfoSingolariExtra() {
    if (cartaCorrente.type === "nome" && numeroEffettivo === "plural") {
        let linguaDomanda = direzioneEffettiva === "de-it" ? "de" : "it";
        let linguaRisposta = direzioneEffettiva === "de-it" ? "it" : "de";
        
        let singDomanda = estraiParolaFormattata(cartaCorrente, linguaDomanda, "singular");
        let singRisposta = estraiParolaFormattata(cartaCorrente, linguaRisposta, "singular");

        document.getElementById("parola-singolare-extra").innerText = `(Sing: ${singDomanda} ➔ ${singRisposta})`;
    } else {
        document.getElementById("parola-singolare-extra").innerText = "";
    }
    document.getElementById("zona-dettagli-risposta").style.display = "block";
}

function aggiornaStreakGrafica(isCorrect) {
    const bloccoStreak = document.getElementById("blocco-streak");
    
    if (isCorrect) {
        corretteDiFila += 1;
        bloccoStreak.className = "streak-container streak-attiva";
    } else {
        corretteDiFila = 0;
        bloccoStreak.className = "streak-container";
        void bloccoStreak.offsetWidth; 
        bloccoStreak.className = "streak-container  streak-rotta";
    }
    
    document.getElementById("contatore-streak").innerText = corretteDiFila;
}

function gestisciErroreChallenge() {
    if (tipoStrutturaGioco === "challenge") {
        document.getElementById("punteggio-game-over").innerText = `Punteggio: ${risposteCorretteChallenge} / ${totaleDomandeChallenge}`;
        mostraSottomenu("zona-game-over");
        return true;
    }
    return false;
}

// LOGICA FLASHCARDS
function giraCarta() {
    if (!cartaCorrente) return;
    let linguaRisposta = direzioneEffettiva === "de-it" ? "it" : "de";
    let testoRisposta = estraiParolaFormattata(cartaCorrente, linguaRisposta, numeroEffettivo);

    document.getElementById("parola-tradotta").innerText = testoRisposta;
    document.getElementById("btn-gira").style.display = "none";
    document.getElementById("zona-bottoni-flashcard").style.display = "block";

    mostraInfoSingolariExtra();
}
function registraRisultatoFlashcard(indovinata) {
    if (indovinata) {
        cartaCorrente.stats.correct += 1;
        if (tipoStrutturaGioco === "challenge") risposteCorretteChallenge++;
        aggiornaStreakGrafica(true);
        salvaProgressiNelBrowser();
        prossimaCarta();
    } else {
        cartaCorrente.stats.mistakes += 1;
        aggiornaStreakGrafica(false);
        salvaProgressiNelBrowser();
        if (!gestisciErroreChallenge()) {
            prossimaCarta();
        }
    }
}

// LOGICA SCRITTURA (Italiano: Case-Insensitive | Tedesco: Severo sul Sostantivo, tollerante sull'Articolo Iniziale)
function controllaScrittura() {
    let inputUtente = document.getElementById("input-risposta").value.trim();
    let linguaRisposta = direzioneEffettiva === "de-it" ? "it" : "de";
    const feedback = document.getElementById("feedback-scrittura");
    
    let risposteValide = [];
    let principaleCorretta = estraiParolaFormattata(cartaCorrente, linguaRisposta, numeroEffettivo);
    risposteValide.push(principaleCorretta);
    
    if (cartaCorrente.type === "nome" && cartaCorrente[linguaRisposta].synonyms) {
        cartaCorrente[linguaRisposta].synonyms.forEach(sinonimo => {
            let parolaSinonimo = sinonimo.trim();
            
            if (numeroEffettivo === "plural" && linguaRisposta === "it") {
                if (parolaSinonimo.endsWith("e") || parolaSinonimo.endsWith("o")) parolaSinonimo = parolaSinonimo.slice(0, -1) + "i";
                else if (parolaSinonimo.endsWith("a")) parolaSinonimo = parolaSinonimo.slice(0, -1) + "e";
            }
            
            let sinonimoFormattato = estraiParolaFormattata(cartaCorrente, linguaRisposta, numeroEffettivo, parolaSinonimo);
            risposteValide.push(sinonimoFormattato);
        });
    }

    let isCorrect = false;

    if (linguaRisposta === "it") {
        inputUtente = inputUtente.toLowerCase();
        let risposteValideMinuscole = risposteValide.map(r => r.toLowerCase());
        isCorrect = risposteValideMinuscole.includes(inputUtente);
    } else {
        let inputNormalizzato = inputUtente.charAt(0).toLowerCase() + inputUtente.slice(1);
        let risposteValideNormalizzate = risposteValide.map(r => r.charAt(0).toLowerCase() + r.slice(1));
        isCorrect = risposteValideNormalizzate.includes(inputNormalizzato);
    }

    if (isCorrect) {
        feedback.innerText = "Corretto! 🎉";
        feedback.className = "feedback corretto";
        cartaCorrente.stats.correct += 1;
        if (tipoStrutturaGioco === "challenge") risposteCorretteChallenge++;
        aggiornaStreakGrafica(true);
    } else {
        let rispostaVisuale = estraiParolaFormattata(cartaCorrente, linguaRisposta, numeroEffettivo);
        feedback.innerText = `Sbagliato! La risposta corretta era: ${rispostaVisuale}`;
        feedback.className = "feedback sbagliato";
        cartaCorrente.stats.mistakes += 1;
        aggiornaStreakGrafica(false);
    }

    salvaProgressiNelBrowser();

    document.getElementById("contatore-streak").innerText = corretteDiFila;
    document.getElementById("parola-tradotta").innerText = estraiParolaFormattata(cartaCorrente, linguaRisposta, numeroEffettivo);
    mostraInfoSingolariExtra();

    document.getElementById("input-risposta").disabled = true;
    document.getElementById("btn-invia-scrivi").style.display = "none";
    
    if (tipoStrutturaGioco === "challenge" && !isCorrect) {
        setTimeout(() => { gestisciErroreChallenge(); }, 1200);
    } else {
        document.getElementById("btn-prossima-scrivi").style.display = "inline-block";
    }
}

// ASCOLTO DEI TASTI DELLA TASTIERA
window.addEventListener('keydown', (event) => {
    const zonaGioco = document.getElementById("zona-gioco");
    if (!zonaGioco.classList.contains("attiva") || !cartaCorrente) return;

    if (tipoGiocoAttuale === "scrivi") {
        if (event.key === "Enter") {
            const bottoneInvia = document.getElementById("btn-invia-scrivi");
            const bottoneProssima = document.getElementById("btn-prossima-scrivi");

            if (bottoneInvia.style.display !== "none") {
                event.preventDefault();
                controllaScrittura();
            } else if (bottoneProssima.style.display !== "none") {
                prossimaCarta();
            }
        }
    } 
    else if (tipoGiocoAttuale === "flashcard") {
        const bloccoBottoniValutazione = document.getElementById("zona-bottoni-flashcard");
        
        if (bloccoBottoniValutazione.style.display === "none") {
            if (event.key === " " || event.key === "Enter") {
                event.preventDefault();
                giraCarta();
            }
        } else {
            if (event.key === "ArrowLeft") {
                registraRisultatoFlashcard(true);
            } else if (event.key === "ArrowRight") {
                registraRisultatoFlashcard(false);
            }
        }
    }
});

// GENERAZIONE DINAMICA SEZIONE LEARNING MODE
function creaMenuLearning() {
    const contenitoreMenu = document.getElementById("lista-stanze-learning");
    if (!contenitoreMenu) return;
    contenitoreMenu.innerHTML = "";

    const stanzeTrovate = [];
    flashcards.forEach(item => {
        if (item.room && !stanzeTrovate.includes(item.room.toLowerCase())) {
            stanzeTrovate.push(item.room.toLowerCase());
        }
    });

    stanzeTrovate.forEach(stanza => {
        const titoloStanza = nomiStanzeFormattati[stanza] || `Area: ${stanza.toUpperCase()}`;
        const bottone = document.createElement("button");
        bottone.className = "btn-stanza";
        bottone.innerHTML = `<span>🏠 In un'abitazione si trova... ➔ ${titoloStanza}</span> <span>👁️ Vedi</span>`;
        
        bottone.onclick = () => mostraVocabolarioStanza(stanza);
        contenitoreMenu.appendChild(bottone);
    });
}

let indiceParolaCorrente = 0;
let paroleDellaStanzaCorrente = [];

function mostraVocabolarioStanza(idStanza) {
    const contenitoreMenu = document.getElementById("lista-stanze-verticale-learning");
    if (!contenitoreMenu) return;
    
    // 1. Filtra le parole (con fix per array multi-stanza)
    paroleDellaStanzaCorrente = flashcards.filter(item => {
        if (!item.room) return false;
        if (Array.isArray(item.room)) {
            return item.room.map(r => r.toLowerCase()).includes(idStanza.toLowerCase());
        } else {
            return item.room.toLowerCase() === idStanza.toLowerCase();
        }
    });    

    // Reset dell'indice all'apertura della stanza
    indiceParolaCorrente = 0;

    // 2. Renderizza la struttura della flashcard singola con le freccette
    renderizzaFlashcardLearning(idStanza);
}

function renderizzaFlashcardLearning(idStanza) {
    const contenitoreMenu = document.getElementById("lista-stanze-verticale-learning");
    if (!contenitoreMenu) return;
    
    contenitoreMenu.innerHTML = ""; // Svuota lo schermo

    const nomiStanze = typeof nomiStanzeFormattati !== 'undefined' ? nomiStanzeFormattati : {};
    const titoloFormattato = nomiStanze[idStanza] || idStanza.toUpperCase();

    if (paroleDellaStanzaCorrente.length === 0) {
        contenitoreMenu.innerHTML = `<p style="text-align:center;">Nessuna parola in questa sezione.</p>`;
        return;
    }

    const item = paroleDellaStanzaCorrente[indiceParolaCorrente];

    // Estrazione e formattazione dei testi
    const deSing = estraiParolaFormattata(item, "de", "singular");
    const dePlur = item.type === "nome" ? estraiParolaFormattata(item, "de", "plural") : "";
    const itSing = estraiParolaFormattata(item, "it", "singular");
    const itPlur = item.type === "nome" ? estraiParolaFormattata(item, "it", "plural") : "";

    let stringaTedesco = `🇩🇪 <strong>${deSing}</strong>`;
    if (dePlur) stringaTedesco += ` [Plur: ${dePlur}]`;

    let stringaItaliano = `🇮🇹 <em>${itSing}</em>`;
    if (itPlur) stringaItaliano += ` [Plur: ${itPlur}]`;

    // Creazione del box flashcard (modello a scorrimento)
    const areaBox = document.createElement("div");
    areaBox.className = "area-box-learning";
    
    let htmlContenuto = `
        <div class="titolo-area-learning">📍 ${titoloFormattato} (${indiceParolaCorrente + 1}/${paroleDellaStanzaCorrente.length})</div>
        <div class="elemento-vocabolo-learning" style="font-size: 1.2rem; margin: 20px 0; text-align: center;">
            ${stringaTedesco} <br> ➔ <br> ${stringaItaliano}
        </div>
    `;

    if (item.it && item.it.synonyms && item.it.synonyms.length > 0) {
        const sinonimiFormattati = item.it.synonyms.map(s => estraiParolaFormattata(item, "it", "singular", s)).join(", ");
        htmlContenuto += `<div class="sinonimi-learning" style="text-align:center; margin-bottom:15px;">💡 Sinonimi: ${sinonimiFormattati}</div>`;
    }

    // Aggiunta dei controlli per le freccette di navigazione sotto la parola
    htmlContenuto += `
        <div class="navigazione-learning" style="display: flex; justify-content: space-between; margin-top: 15px;">
            <button id="btn-prev-learning" style="padding: 8px 15px;">⬅ Precedente</button>
            <button id="btn-next-learning" style="padding: 8px 15px;">Successiva ➡</button>
        </div>
    `;

    areaBox.innerHTML = htmlContenuto;
    contenitoreMenu.appendChild(areaBox);

    // Gestione dei click sulle freccette
    const btnPrev = document.getElementById("btn-prev-learning");
    const btnNext = document.getElementById("btn-next-learning");

    // Disattiva i pulsanti se siamo all'inizio o alla fine
    if (indiceParolaCorrente === 0) btnPrev.disabled = true;
    if (indiceParolaCorrente === paroleDellaStanzaCorrente.length - 1) btnNext.disabled = true;

    btnPrev.onclick = () => {
        if (indiceParolaCorrente > 0) {
            indiceParolaCorrente--;
            renderizzaFlashcardLearning(idStanza);
        }
    };

    btnNext.onclick = () => {
        if (indiceParolaCorrente < paroleDellaStanzaCorrente.length - 1) {
            indiceParolaCorrente++;
            renderizzaFlashcardLearning(idStanza);
        }
    };
}
    

// DASHBOARD STATISTICHE AGGIORNATA
// FUNZIONE SHOWSTATS: Grafica moderna e ordinata per errori frequenti
function showStats() {
    if (flashcards.length === 0) return;
    mostraSottomenu('zona-statistiche');

    // Filtra solo le parole che sono state visualizzate ed esercitate almeno una volta
    const paroleViste = flashcards.filter(item => (item.stats.correct > 0 || item.stats.mistakes > 0));
    document.getElementById("titolo-stats").innerText = `Parole viste / Gesehene Wörter: ${paroleViste.length} / ${flashcards.length}`;

    const divMigliori = document.getElementById("stats-le-migliori");
    const divPeggiori = document.getElementById("stats-le-peggiori");
    const divCompleta = document.getElementById("tabella-stats-completa");

    // Pulizia totale dei tre contenitori per evitare scritte duplicate
    if (divMigliori) divMigliori.innerHTML = "";
    if (divPeggiori) divPeggiori.innerHTML = "";
    if (divCompleta) divCompleta.innerHTML = "";

    if (paroleViste.length === 0) {
        if (divCompleta) divCompleta.innerHTML = "<p>Non hai ancora studiato nessuna parola. Inizia a giocare per vedere i tuoi progressi! / Spiele jetzt, um deine Fortschritte zu sehen</p>";
        return;
    }

    // 1. TOP 5: Le parole più corrette (Ordinate per risposte esatte decrescenti)
    let miglioriScelte = [...paroleViste].sort((a, b) => b.stats.correct - a.stats.correct).slice(0, 5);
    miglioriScelte.forEach(item => {
        const p = document.createElement("p");
        let testoDe = estraiParolaFormattata(item, 'de', 'singular');
        testoDe = testoDe.charAt(0).toUpperCase() + testoDe.slice(1);
        p.innerHTML = `⭐ <strong>${testoDe}</strong> (${item.stats.correct} volte)`;
        if (divMigliori) divMigliori.appendChild(p);
    });
    if (miglioriScelte.length === 0 && divMigliori) divMigliori.innerHTML = "<p>Nessun dato</p>";

    // 2. WORST 5: Le parole più sbagliate (Ordinate per errori decrescenti)
    let peggioriScelte = [...paroleViste].sort((a, b) => b.stats.mistakes - a.stats.mistakes).slice(0, 5);
    peggioriScelte.forEach(item => {
        const p = document.createElement("p");
        let testoDe = estraiParolaFormattata(item, 'de', 'singular');
        testoDe = testoDe.charAt(0).toUpperCase() + testoDe.slice(1);
        p.innerHTML = `❌ <strong>${testoDe}</strong> (${item.stats.mistakes} errori)`;
        if (divPeggiori) divPeggiori.appendChild(p);
    });
    if (peggioriScelte.length === 0 && divPeggiori) divPeggiori.innerHTML = "<p>Nessun dato</p>";

    // 3. ELENCO COMPLETO: Ordinato rigorosamente per errori decrescenti (Regola 2)
    let tutteOrdinatePerErrore = [...paroleViste].sort((a, b) => b.stats.mistakes - a.stats.mistakes);
    tutteOrdinatePerErrore.forEach(item => {
        const riga = document.createElement("div");
        riga.className = "riga-stat";
        
        let textDe = estraiParolaFormattata(item, "de", "singular");
        let textIt = estraiParolaFormattata(item, "it", "singular");
        
        // Formattazione estetica iniziale maiuscola per l'elenco a schermo
        textDe = textDe.charAt(0).toUpperCase() + textDe.slice(1);
        textIt = textIt.charAt(0).toUpperCase() + textIt.slice(1);
        
        riga.innerHTML = `📌 <strong>${textDe}</strong> ➔ <em>${textIt}</em> | 👍 Corrette: ${item.stats.correct} | 👎 Errori: ${item.stats.mistakes}`;
        
        // CORRETTO: Adesso l'elemento viene iniettato regolarmente nel div corretto senza perdersi
        if (divCompleta) divCompleta.appendChild(riga);
    });
}
// === LOGICHE DI NAVIGAZIONE OTTIMIZZATE ===
// 1. Collegata ai pulsanti indietro dei sottomenu: riporta alla home con l'H1
function tornaAlMenuPrincipaleH1() {
    corretteDiFila = 0;
    if (document.getElementById("contatore-streak")) {
        document.getElementById("contatore-streak").innerText = corretteDiFila;
    }

    // RESET STATO LEARNING: Ripristina la schermata iniziale del sottomenu
    if (document.getElementById("macro-argomenti-learning")) {
        document.getElementById("macro-argomenti-learning").style.display = "block";
    }
    if (document.getElementById("zona-aree-casa-learning")) {
        document.getElementById("zona-aree-casa-learning").style.display = "none";
    }

    mostraSottomenu('menu-principale');
}

// 2. Collegata al tasto della zona-gioco o del Game Over: torna alla selezione modalità
function tornaAlSottomenuPrecedente() {
    corretteDiFila = 0;
    if (document.getElementById("contatore-streak")) {
        document.getElementById("contatore-streak").innerText = corretteDiFila;
    }
    
    if (tipoGiocoAttuale === "scrivi") {
        mostraSottomenu('menu-scrivi');
    } else if (tipoGiocoAttuale === "flashcard") {
        mostraSottomenu('menu-flashcards');
    } else {
        mostraSottomenu('menu-principale');
    }
    tipoGiocoAttuale = ""; // Rilascia lo stato del gioco
}

// 3. Collegata al tasto "Riprova" della schermata di Game Over
function riprovaChallenge() {
    corretteDiFila = 0;
    if (document.getElementById("contatore-streak")) {
        document.getElementById("contatore-streak").innerText = corretteDiFila;
    }
    // Rilancia lo start con gli stessi identici dati memorizzati
    start(tipoGiocoAttuale, tipoStrutturaGioco, ultimaModalitaLinguistica, ultimoLimiteChallenge);
}


// ==============================================================================
// GESTIONE MODALITÀ LEARNING SEQUENZIALE (Meccanica Flashcard Ordinata)
// ==============================================================================
// ==============================================================================
// GESTIONE MODALITÀ LEARNING SEQUENZIALE (Pagina a sé stante e Schermo Intero)
// ==============================================================================
let mazzoLearningOrdinato = [];
let indiceLearningCorrente = 0;

function apriMacroArgomento(tipo) {
    if (tipo === 'casa') {
        document.getElementById("macro-argomenti-learning").style.display = "none";
        document.getElementById("zona-aree-casa-learning").style.display = "block";
        creaMenuStanzeVerticali();
    }
}

function indietroAilLivelloMacro() {
    document.getElementById("macro-argomenti-learning").style.display = "block";
    document.getElementById("zona-aree-casa-learning").style.display = "none";
}

function creaMenuStanzeVerticali() {
    const contenitoreStanze = document.getElementById("lista-stanze-verticale-learning");
    if (!contenitoreStanze) return;
    contenitoreStanze.innerHTML = ""; 

    const stanzeTrovate = [];
    flashcards.forEach(item => {
        if (item.room) {
            const stanzeElemento = Array.isArray(item.room) ? item.room : [item.room];

            stanzeElemento.forEach(stanzaSingola => {
                let stanzaNormalizzata = stanzaSingola.trim().toLowerCase()
                    .replace(/ü/g, 'u').replace(/ä/g, 'a').replace(/ö/g, 'o');
                
                if (!stanzeTrovate.includes(stanzaNormalizzata) && stanzaNormalizzata !== "generale") {
                    stanzeTrovate.push(stanzaNormalizzata);
                }
            });
        }
    });

    // Generazione dei pulsanti
    stanzeTrovate.forEach(stanza => {
        const bottoneStanza = document.createElement("button");
        bottoneStanza.className = "btn-menu-stanza";
        
        const nomiStanze = typeof nomiStanzeFormattati !== 'undefined' ? nomiStanzeFormattati : {};
        const nomeVisibile = nomiStanze[stanza] ? nomiStanze[stanza] : stanza.toUpperCase();

        bottoneStanza.innerText = nomeVisibile;
        bottoneStanza.onclick = function() {
            mostraVocabolarioStanza(stanza);
        };
        contenitoreStanze.appendChild(bottoneStanza);
    });
}

// 4. AGGIORNATA: Sposta lo studio su una pagina a schermo intero indipendente (.schermata)
function avviaMazzoLearning(idStanza) {
    mazzoLearningOrdinato = flashcards.filter(item => {
        if (!item.room) return false;
        let stanzaItemNormalizzata = item.room.trim().toLowerCase()
            .replace(/ü/g, 'u').replace(/ä/g, 'a').replace(/ö/g, 'o');
        return stanzaItemNormalizzata === idStanza;
    });
    
    if (mazzoLearningOrdinato.length === 0) {
        alert("Nessuna parola disponibile per questa area.");
        return;
    }

    indiceLearningCorrente = 0;
    tipoGiocoAttuale = "learning"; // Intercetta la tastiera globale
    
    // Spostamento Schermata: Spegne il menu delle stanze e accende la pagina della card a schermo intero
    mostraSottomenu('schermata-card-learning');
    mostraParolaLearningAttuale();
}

function mostraParolaLearningAttuale() {
    if (indiceLearningCorrente >= mazzoLearningOrdinato.length) {
        alert("🎉 Hai completato lo studio di questa stanza!");
        chiudiPaginaCardLearning();
        return;
    }

    const item = mazzoLearningOrdinato[indiceLearningCorrente];

    const deSing = estraiParolaFormattata(item, "de", "singular");
    const dePlur = item.type === "nome" ? estraiParolaFormattata(item, "de", "plural") : "";
    const itSing = estraiParolaFormattata(item, "it", "singular");
    const itPlur = item.type === "nome" ? estraiParolaFormattata(item, "it", "plural") : "";

    let testoTedesco = deSing.charAt(0).toUpperCase() + deSing.slice(1);
    if (dePlur) testoTedesco += ` [Plur: ${dePlur.charAt(0).toUpperCase() + dePlur.slice(1)}]`;

    let testoItaliano = itSing.charAt(0).toUpperCase() + itSing.slice(1);
    if (itPlur) testoItaliano += ` [Plur: ${itPlur.charAt(0).toUpperCase() + itPlur.slice(1)}]`;

    document.getElementById("learning-de").innerHTML = `🇩🇪 ${testoTedesco}`;
    document.getElementById("learning-info-numero").innerText = `(${item.type})`;
    document.getElementById("learning-it").innerHTML = `🇮🇹 ${testoItaliano}`;

    const divSinonimi = document.getElementById("learning-sinonimi");
    if (item.it && item.it.synonyms && item.it.synonyms.length > 0) {
        const sinonimiFormattati = item.it.synonyms.map(s => {
            let formattato = estraiParolaFormattata(item, "it", "singular", s);
            return formattato.charAt(0).toUpperCase() + formattato.slice(1);
        }).join(", ");
        divSinonimi.innerHTML = `💡 <strong>Sinonimi accettati:</strong> ${sinonimiFormattati}`;
        divSinonimi.style.display = "block";
    } else {
        divSinonimi.style.display = "none";
    }

    document.getElementById("progresso-learning-card").innerText = `${indiceLearningCorrente + 1} / ${mazzoLearningOrdinato.length}`;
}

function prossimaParolaLearning() {
    indiceLearningCorrente++;
    mostraParolaLearningAttuale();
}

// 5. NUOVA: Gestisce l'uscita dalla pagina della card e il rientro pulito nel menu delle stanze
function chiudiPaginaCardLearning() {
    tipoGiocoAttuale = ""; // Rilascia la tastiera
    
    // Riaccende il menu di scelta stanze
    mostraSottomenu('menu-learning');
    document.getElementById("macro-argomenti-learning").style.display = "none";
    document.getElementById("zona-aree-casa-learning").style.display = "block";
}

// Sincronizzazione dell'evento tornaAlMenu principale per azzerare gli stati
const vecchiaFunzioneTornaAlMenu = tornaAlMenu;
tornaAlMenu = function() {
    vecchiaFunzioneTornaAlMenu();
    tipoGiocoAttuale = ""; 
    const macro = document.getElementById("macro-argomenti-learning");
    const aree = document.getElementById("zona-aree-casa-learning");
    if (macro && aree) {
        macro.style.display = "block";
        aree.style.display = "none";
    }
};
