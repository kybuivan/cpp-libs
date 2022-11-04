DEL /Q build\CMakeCache.txt
cmake -S . -B ./build
cmake --build ./build
.\build\Release\twin.exe