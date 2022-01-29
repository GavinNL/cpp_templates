# cppnew

A set of small examples of various libraries.

Third-party libraries for the examples use the Conan Package Manager to download the package.

## Compiling

Navigate to the folder example you want to compile:

```bash
cd sodium
mkdir build
cd build
conan install ..

cmake ..
cmake --build .
```


