g++ tests/tests.cpp src/*.cpp -lm -std=c++23 -D_POSIX_C_SOURCE=200809L -o bin/tests.exe
cd bin
tests.exe
pause