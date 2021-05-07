#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <iostream>
#include <libgeometry/calculations.h>
#include <libgeometry/checks.h>
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
TEST_CASE("aroundBrackets", "")
{
    SECTION("figureName")
    {
        int column = 0;
        std::string errorStr = "error";
        std::vector<std::string> a
                = {"CirCle(2, 3, 5)",
                   "tRiaNgle((2 3, 5 2.3, 0 0, -2 3))",
                   "ciHRrcle(2, 3, 5)",
                   "triaMGngle((2 3, 2.3, 0 0, -2 3))",
                   "circle 2, 3, 5)"};
        CHECK(figureName(a[0], column) == "circle");
        CHECK(figureName(a[1], column) == "triangle");
        CHECK(figureName(a[2], column) == "cihrrcle");
        CHECK(figureName(a[3], column) == "triamgngle");
        CHECK(figureName(a[4], column) == errorStr);
    }
    SECTION("afterBracket")
    {
        std::pair<bool, int> status(0, 0);
        std::vector<std::string> a
                = {"circle(2, 3, 5)    ",
                   "triangle((2 3, 5 2.3, 0 0, -2 3))    ",
                   "circle(2, 3, 5) gdf ff",
                   "triangle((2 3, 5 2.3, 0 0, -2 3)) gfd fg"};
        CHECK(afterBracket(a[0], a[0].find(")") + 1) == status);
        CHECK(afterBracket(a[1], a[1].find("))") + 2) == status);
        CHECK(afterBracket(a[2], a[2].find(")") + 1) != status);
        CHECK(afterBracket(a[3], a[3].find("))") + 2) != status);
    }
    SECTION("btwBrackets")
    {
        std::pair<bool, int> status(0, 0);
        std::vector<std::string> a
                = {"circle(2, 3, 5)",
                   "triangle((2 3, 5 2.3, 0 0, -2 3))",
                   "circle(2,$ 3, 5)",
                   "triangle((2 3,  a 2.3, 0 0, -2 3))"};
        CHECK(btwBrackets(a[0], a[0].find("(") + 1, a[0].find(")") - 1)
              == status);
        CHECK(btwBrackets(a[1], a[1].find("((") + 2, a[1].find("))") - 1)
              == status);
        CHECK(btwBrackets(a[2], a[2].find("(") + 1, a[2].find(")") - 1)
              != status);
        CHECK(btwBrackets(a[3], a[3].find("((") + 2, a[3].find("))") - 1)
              != status);
    }
    SECTION("commaBeforeAfter")
    {
        std::pair<bool, int> status(0, 0);
        std::vector<std::string> a
                = {"circle(2, 3, 5)",
                   "triangle((2 3, 5 2.3, 0 0, -2 3))",
                   "circle( ,2, 3, 5)",
                   "triangle((2 3, 2.3, 0 0, -2 3 ,))"};
        CHECK(commaBeforeAfter(a[0], a[0].find("(") + 1, a[0].find(")") - 1)
              == status);
        CHECK(commaBeforeAfter(a[1], a[1].find("((") + 2, a[1].find("))") - 1)
              == status);
        CHECK(commaBeforeAfter(a[2], a[2].find("(") + 1, a[2].find(")") - 1)
              != status);
        CHECK(commaBeforeAfter(a[3], a[3].find("((") + 2, a[3].find("))") - 1)
              != status);
    }
}
TEST_CASE("setFigure", "")
{
    SECTION("setCircle")
    {
        std::vector<std::string> a
                = {"circle(-3.0 2.2, -5.7)",
                   "circle(-3.5 2.2, 5.87)",
                   "circle -3 2, 5)"};
        CHECK(setCircle(a[0]).size() == 2);
        CHECK(setCircle(a[1]) == std::vector<double>{-3.5, 2.2, 5.87});
        CHECK(setCircle(a[2]).size() == 2);
    }
    SECTION("setTriangle")
    {
        std::vector<std::string> a
                = {"triangle((-3 2, 5 6, -23 -54, 65 43))",
                   "triangle((-3.0 -2, -1 0.0, -3.0 2.0, -3 -2))",
                   "triangle((-3 2, 5 6, -23 -54, 65 43"};
        CHECK(setTriangle(a[0]).size() == 2);
        CHECK(setTriangle(a[1])
              == std::vector<double>{-3.0, -2, -1, 0.0, -3.0, 2.0, -3, -2});
        CHECK(setTriangle(a[2]).size() == 2);
    }
}
TEST_CASE("intersects", "")
{
    SECTION("cirTOcir")
    {
        std::vector<double> c1{0, 0, 2};
        std::vector<double> c2{1, 1, 2};
        CHECK(cirTOcir(c1, c2) == 1);
        std::vector<double> c3{9.3, -4.2, 2.8};
        CHECK(cirTOcir(c1, c3) == 0);
        std::vector<double> c4{9, -4.2, 2.8};
        CHECK(cirTOcir(c1, c4) == 0);
    }
    SECTION("trTOcir")
    {
        std::vector<double> tr{-3.0, -2, -1, 0.0, -3.0, 2.0, -3, -2};
        std::vector<double> cir1{0, 0, 2};
        CHECK(trTOcir(tr, cir1) == 1);
        std::vector<double> cir2{5, 5, 2.8};
        CHECK(trTOcir(tr, cir2) == 0);
        std::vector<double> cir3{-2, 0, 7};
        CHECK(trTOcir(tr, cir3) == 0);
    }
    SECTION("trTOtr")
    {
        std::vector<double> tr1{-3.0, -2, -1, 0.0, -3.0, 2.0, -3, -2};
        std::vector<double> tr2{-3.0, -2, -1, 0.0, -3.0, 2.0, -3, -2};
        CHECK(trTOtr(tr1, tr2) == 1);
        std::vector<double> tr3{-6.0, -4, 5, 0.0, -6.0, 4.0, -6, -4};
        CHECK(trTOtr(tr1, tr3) == 0);
        std::vector<double> tr4{2, -3, 2, 3, 5, 0, 2, -3};
        CHECK(trTOtr(tr1, tr4) == 0);
    }
    system("pause");
}
