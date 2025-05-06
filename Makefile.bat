g++ tests/main.cpp src/*cpp -lm -std=c++23 -D_POSIX_C_SOURCE=200809L -o bin/main.exe
cd bin
main.exe
pause