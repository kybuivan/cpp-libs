DEL /Q build\CMakeCache.txt
cmake -S . -B ./build
cmake --build ./build --config release --clean-first
.\build\Release\twin.exe