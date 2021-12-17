To Build:


# Linux

cd $SRC_DIR
mkdir build
cd build
conan install .. -s compiler.libcxx=libstdc++11 --build missing
cmake .. -DCMAKE_MODULE_PATH=$PWD
cmake --build .

# Windows

cd $SRC_DIR
mkdir build
cd build
conan install .. --build missing
cmake .. -DCMAKE_MODULE_PATH=$PWD
cmake --build . --config Release

