#define CATCH_CONFIG_MAIN
#include <iostream>
#include "../thirdparty/catch.hpp"
#include <libgeometry/checks.h>
#include <libgeometry/calculations.h>
#include <string.h>
#include <vector>


TEST_CASE("Calculating circle", "")
{
    SECTION("lenCircle")
    {
        double a = 5;
        double b = 1;
        double c = 1.56;
        CHECK(lenCircle(a) == Approx(31.41593));
        CHECK(lenCircle(b) == Approx(6.28319));
        CHECK(lenCircle(c) == Approx(9.80177));
    }
    SECTION("sqrCircle")
    {
        double a = 5;
        double b = 1;
        double c = 1.56;
        CHECK(sqrCircle(a) == Approx(78.53982));
        CHECK(sqrCircle(b) == Approx(3.14159)); 
        CHECK(sqrCircle(c) == Approx(7.64538));
    }
}


