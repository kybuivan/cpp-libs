DEL /Q build\CMakeCache.txt
cmake -S . -B ./build
cmake --build ./build --config Debug
make install
cd build
ctest [-VV] -C Debug -D Experimental
cpack -G ZIP -C Debug