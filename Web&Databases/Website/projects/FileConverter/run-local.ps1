param(
  [ValidateRange(1024,65535)]
  [int]$Port = 8765
)

$root = [IO.Path]::GetFullPath($PSScriptRoot)
$rootPrefix = $root.TrimEnd([IO.Path]::DirectorySeparatorChar) + [IO.Path]::DirectorySeparatorChar
$listener = New-Object Net.HttpListener
$listener.Prefixes.Add("http://127.0.0.1:$Port/")
$contentTypes = @{
  '.css' = 'text/css; charset=utf-8'
  '.html' = 'text/html; charset=utf-8'
  '.js' = 'text/javascript; charset=utf-8'
  '.json' = 'application/json; charset=utf-8'
  '.txt' = 'text/plain; charset=utf-8'
  '.wasm' = 'application/wasm'
}

try {
  $listener.Start()
  Write-Host "File Converter is available at http://127.0.0.1:$Port/"
  Write-Host 'This server listens only on this computer. Press Ctrl+C to stop it.'

  while ($listener.IsListening) {
    $context = $listener.GetContext()
    try {
      $relativePath = [Uri]::UnescapeDataString($context.Request.Url.AbsolutePath.TrimStart('/'))
      if ([string]::IsNullOrWhiteSpace($relativePath)) { $relativePath = 'index.html' }
      $relativePath = $relativePath.Replace('/', [IO.Path]::DirectorySeparatorChar)
      $filePath = [IO.Path]::GetFullPath((Join-Path $root $relativePath))

      if (-not $filePath.StartsWith($rootPrefix, [StringComparison]::OrdinalIgnoreCase) -and $filePath -ne (Join-Path $root 'index.html')) {
        $context.Response.StatusCode = 404
      } elseif (-not (Test-Path -LiteralPath $filePath -PathType Leaf)) {
        $context.Response.StatusCode = 404
      } else {
        $extension = [IO.Path]::GetExtension($filePath).ToLowerInvariant()
        $context.Response.ContentType = if ($contentTypes.ContainsKey($extension)) { $contentTypes[$extension] } else { 'application/octet-stream' }
        $context.Response.Headers['X-Content-Type-Options'] = 'nosniff'
        $context.Response.Headers['Referrer-Policy'] = 'no-referrer'
        $context.Response.Headers['Cross-Origin-Opener-Policy'] = 'same-origin'
        $context.Response.Headers['Cross-Origin-Embedder-Policy'] = 'require-corp'
        $context.Response.Headers['Cross-Origin-Resource-Policy'] = 'same-origin'
        $context.Response.Headers['Content-Security-Policy'] = "default-src 'self'; script-src 'self' 'unsafe-eval' 'wasm-unsafe-eval' blob:; worker-src 'self' blob:; connect-src 'self' blob:; img-src 'self' data: blob:; media-src 'self' blob:; style-src 'self' 'unsafe-inline'; object-src 'none'; base-uri 'self'; form-action 'self'"
        $bytes = [IO.File]::ReadAllBytes($filePath)
        $context.Response.ContentLength64 = $bytes.Length
        if ($context.Request.HttpMethod -ne 'HEAD') { $context.Response.OutputStream.Write($bytes, 0, $bytes.Length) }
      }
    } catch {
      $context.Response.StatusCode = 500
      Write-Warning $_.Exception.Message
    } finally {
      $context.Response.Close()
    }
  }
} finally {
  if ($listener.IsListening) { $listener.Stop() }
  $listener.Close()
}