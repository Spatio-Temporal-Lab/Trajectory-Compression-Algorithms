$ErrorActionPreference = "Stop"
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
Set-Location $root
New-Item -ItemType Directory -Force build | Out-Null
g++ -std=c++17 -O2 -I. `
  algorithm/cost_compressor.cc `
  utils/input_bit_stream.cc utils/output_bit_stream.cc utils/elias_gamma_codec.cc `
  tests/cost_smoke_test.cc -o build/cost_smoke_test.exe
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }
& .\build\cost_smoke_test.exe
