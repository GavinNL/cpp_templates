# cppnew

A simple shell script to quickly build a folder for C++ projects

## Installation

Download a copy of the shell script to your Home directory's bin folder.

```Bash
cd $HOME/.local/bin
wget https://raw.githubusercontent.com/GavinNL/cppnew/master/cppnew
chmod +x cppnew
```

When you first run `cppnew` it will clone all the templates to your
`$HOME/.cache/cppnew` folder.

## Usage

Usage is very simple. Call `cppnew` to list all available templates

```bash
# List all templates
cppnew

Templates:

    conan_hello_world - Basic Hello-world C++ project with Conan Packages
    hello_world - Basic Hello-world C++ project
    project - A full library project for C++ with unit tests, executables and packaging

```

To create a project:

>
> cppnew [template name] [project folder]
>

`[project folder]` must not already exist.

```bash
# Create a Project
cppnew hello_world MyHelloWorldProject

cd MyHelloWorldProject
mkdir build  && cd build
cmake ..
cmake --build .

```

## External Libraries

For templates which require external libraries, the Conan Package Manager is
used to download the libraries.

```bash
# Create a Project
cppnew GUI_wxWidgets  myWxWidgetsProject

cd myWxWidgetsProject
mkdir build  && cd build
conan install .. -s compiler.libcxx=libstdc++11 --build missing
cmake ..
cmake --build .

```
