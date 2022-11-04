DEL /Q build\CMakeCache.txt
cmake -S . -B ./build
cmake --build ./build --config Debug
cmake --install ./build --prefix /tmp/install-test --config Debug
cd build
ctest [-VV] -C Debug -D Experimental
REM .\build\Debug\twin.exe