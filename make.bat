gcc GBHeaderReader.c -o build/GBHeaderReader.exe
wsl -e gcc GBHeaderReader.c -o build/GBHeaderReader.Linux

gcc GBTileExtractor.c -o build/GBTileExtractor.exe
wsl -e gcc GBTileExtractor.c -o build/GBTileExtractor.Linux
pause