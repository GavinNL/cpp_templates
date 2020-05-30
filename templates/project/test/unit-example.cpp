#include "catch.hpp"
#include <mylib/header.h>

SCENARIO( " Scenario 1" )
{
    REQUIRE( func() == 42);
}
