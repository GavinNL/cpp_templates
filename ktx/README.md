# KTX

The KTX library is a library for loading KTX images. It is maintained by the KhronosGroup and can be used 
to transcode images into GPU compressed data:

https://github.com/KhronosGroup/KTX-Software/


## Build the example


This example demonstrates how to load a KTX image, and transcode it into BC3, ASTC and ETC2 formats for use
in vulkan or OpenGL. Uplaoding of data to the gpu is not demonstrated, just the transcoding.

We will use the conan package manager to download/build the ktx library.

To install conan use pip

```bash
pip3 install conan
conan user
```


To compile the example:

```bash

mkdir build
cd build

# download or build the ktx library and any other libraries it might
# need
conan install .. -s compiler.libcxx=libstdc++11 --build missing

cmake .. -DCMAKE_MODULE_PATH=$PWD

make

./ktxTranscodeTest path_to.ktx2

```

## Creating a KTX2 file from png/jpg

The conan package manager when asked to build the ktx library will also build the tools that
come with KTX.


```bash
mkdir build

cd build
conan install .. -s compiler.libcxx=libstdc++11 --build missing

# Source the activate script to add the the location of the 
# tools to your PATH
source activate_run.sh

# generate a ktx2 file
toktx --genmipmap --t2 --bcmp  outputimage.ktx2   inputimage.png

```
