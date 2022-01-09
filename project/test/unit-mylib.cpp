#include "catch.hpp"
//#include <mylib/header.h>

int test(int xx)
{
  if( xx > 3) return 42;
  else return 0;
}

SCENARIO( " Scenario 1" )
{
    REQUIRE( test(33) == 42);
}
