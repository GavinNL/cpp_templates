#include <iostream>
#include <cassert>
#include <mylib/header.h>

int main(int argc, char ** argv)
{
    assert( argc > 0);
    assert( argv );
    return func();
}
