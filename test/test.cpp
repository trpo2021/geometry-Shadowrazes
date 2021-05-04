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
TEST_CASE("Calculating triangle", "")
{
    SECTION("sqrTriangle")
    {
        std::vector<double> a = {3, 6, 7};
        double p = 8;
        CHECK(sqrTriangle(p, a) == Approx(8.94427));
        a = {3.3, 6.65, 7.43};
        p = 8.69;
        CHECK(sqrTriangle(p, a) == Approx(10.97248));
    }
}
TEST_CASE("general", "")
{
    SECTION("lenLine")
    {
        std::pair<double, double> start(0, 0);
        std::pair<double, double> close(0, 5);
        CHECK(lenLine(start, close) == 5);
        std::pair<double, double> start2(1.2, 3.1);
        std::pair<double, double> close2(2.3, 7.5);
        CHECK(lenLine(start2, close2) == Approx(4.53542));
    }
    SECTION("vectCoord")
    {
        std::pair<double, double> start(0, 0);
        std::pair<double, double> close(0, 5);
        CHECK(vectCoord(start, close) == std::pair<double, double>(0, 5));
        std::pair<double, double> start2(1.2, 3.1);
        std::pair<double, double> close2(2.3, 7.5);
        double a = 2.3 - 1.2, b = 7.5 - 3.1;
        CHECK(vectCoord(start2, close2).first == Approx(a));
        CHECK(vectCoord(start2, close2).second == Approx(b));
    }
    SECTION("sqrSum")
    {
        std::vector<double> a{4, 0, 0};
        std::vector<double> b{0, 0, 0};
        std::vector<double> c{26.01, 29.58, 8.41};
        std::vector<double> d{83.5396, 78.9696, 18.6624};
        CHECK(sqrSum(2, 0) == a);
        CHECK(sqrSum(0, 0) == b);
        std::vector<double> temp = sqrSum(5.1, 2.9);
        for (int i = 0; i < 3; i++) {
            CHECK(temp[i] == Approx(c[i]));
        }
        temp = sqrSum(9.14, 4.32);
        for (int i = 0; i < 3; i++) {
            CHECK(temp[i] == Approx(d[i]));
        }
    }
    SECTION("sqrEq")
    {
        std::vector<double> a{-0.5, -1};
        std::vector<double> b{-0.60435, -2.89564};
        std::vector<double> input1{4, 6, 2};
        std::vector<double> temp1 = sqrEq(input1);
        for (int i = 0; i < 2; i++) {
            CHECK(temp1[i] == Approx(a[i]));
        }
        std::vector<double> input2{1.2, 4.2, 2.1};
        std::vector<double> temp2 = sqrEq(input2);
        for (int i = 0; i < 2; i++) {
            CHECK(temp2[i] == Approx(b[i]));
        }
    }
}
TEST_CASE("ClearVector", "")
{
    SECTION("Clear")
    {
        std::vector<double> temp = {3.9, 23, -2.3, 2.66547};
        std::vector<double> tempEmpty = {};
        CHECK(clearVec(temp).size() == 0);
        CHECK(clearVec(tempEmpty).size() == 0);
    }
}
TEST_CASE("allowedValue", "")
{
    SECTION("odz")
    {
        std::vector<char> a = {'a', '$', '3', ' ', ',', '.', '-'};
        CHECK(odz(a[0]) == true);
        CHECK(odz(a[1]) == true);
        CHECK(odz(a[2]) == false);
        CHECK(odz(a[3]) == false);
        CHECK(odz(a[4]) == false);
        CHECK(odz(a[5]) == false);
        CHECK(odz(a[6]) == false);
    }
    SECTION("odzBeforeAfter")
    {
        std::vector<char> a = {'a', '$', '3', ' ', ',', '.', '-'};
        CHECK(odzBeforeAfter(a[0]) == true);
        CHECK(odzBeforeAfter(a[1]) == true);
        CHECK(odzBeforeAfter(a[2]) == false);
        CHECK(odzBeforeAfter(a[3]) == false);
        CHECK(odzBeforeAfter(a[4]) == true);
        CHECK(odzBeforeAfter(a[5]) == false);
        CHECK(odzBeforeAfter(a[6]) == false);
    }
}