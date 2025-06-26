# Proyecto_TT1

Proyecto de estimación orbital con filtro de Kalman extendido, traducido desde MATLAB a C++.

## Compilación

**Tests unitarios:**
```bash
g++ tests/tests.cpp src/*.cpp -lm -std=c++23 -o bin/tests.exe
```

**Aplicación principal:**
```bash
g++ tests/EKF_GEOS3.cpp src/*.cpp -lm -std=c++23 -o bin/main.exe
```
