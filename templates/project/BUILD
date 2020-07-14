To Build:

cd $SRC_DIR
mkdir build
cd build
conan install .. -s compiler.libcxx=libstdc++11 --build missing
cmake ..
cmake --build .

# Run the unit tests
ctest


# Build a deb package
cpack -G DEB
