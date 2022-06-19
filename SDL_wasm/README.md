# Compiling


## Compiling with Emscripten

```bash
cd SDL_WASM
mkdir build
cd build
 
export CXX=$(which em++)
export CC=$(which emcc)

cmake .. -DCMAKE_CXX_FLAGS="-s USE_SDL=2" -DCMAKE_EXECUTABLE_SUFFIX_CXX=".html"
make

python3 -m http.server
```

## Compiling for Desktop

```bash
mkdir build
cd build

conan install .. -s compiler.libcxx=libstdc++11
cmake .. -DCMAKE_MODULE_PATH=$PWD

make
```
