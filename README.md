# cppnew

A simple shell script to quickly build a folder for C++ projects

## Installation

Download a copy of the shell script to your Home directory's bin folder.

```Bash
wget https://github.com/GavinNL/cppnew/raw/master/cppnew -o  ${HOME}/.local/bin/cppnew
chmod +x $HOME/.local/bin/cppnew

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

> cppnew [template name] [project folder]

`[project folder]` must not already exist.

```bash
# Create a Project
cppnew hello_world MyHelloWorldProject

cd MyHelloWorldProject
mkdir build  && cd build
cmake ..
cmake --build .

```
