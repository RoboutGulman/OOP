// TemplateTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../EquationSolve/stdafx.h"

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../EquationSolve/Solve3.h"
#include "../EquationSolve/SolveEquation.h"

SCENARIO("Case with rationales roots")
{
    // 3x^2+4x^2+2x=0
    auto result = Solve3(3, 4, 2, 0);
    CHECK(result.numRoots == 1);
    CHECK((fabs(result.roots[0])) <= std::numeric_limits<double>::epsilon());

    // 2x^2-11x^2+12x+9=0
    result = Solve3(2, -11, 12, 9);
    CHECK(result.numRoots == 2);
    std::vector<double> requireRoots = { -1.0 / 2, 3.0 };
    for (int i = 0; i < result.numRoots; i++)
    {
        CHECK((fabs(result.roots[i] - requireRoots[i]) <=
            std::numeric_limits<double>::epsilon() * fabs(result.roots[i] + requireRoots[i])));
    }
}

SCENARIO("Case with real roots")
{
    // 5x^2-8x^2-8x+5=0
    auto result = Solve3(5, -8, -8, 5);
    CHECK(result.numRoots == 3);
    std::vector<double> requireRoots = {-1, (13. + sqrt(69)) / 10, (13. - sqrt(69)) / 10};
    for (int i = 0; i < result.numRoots; i++)
    {
        CHECK((fabs(result.roots[i] - requireRoots[i]) <=
               std::numeric_limits<double>::epsilon() * fabs(result.roots[i] + requireRoots[i])));
    }
}

SCENARIO("Case with real coefficient")
{
    // 5.6x^3+3.4x^2+4x+13=0
    auto result = Solve3(5.6, 3.4, 4, 13);
    CHECK(result.numRoots == 1);
    const double requireRoot = -1.351;
    CHECK((fabs(result.roots[0] - requireRoot) <= 0.001));

    // -3.45x^2+9.34x^2+1x-11=0
    result = Solve3(-3.45, 9.34, 1, -11);
    CHECK(result.numRoots == 3);
    std::vector<double> requireRoots = { -0.971, 2.155, 1.523 };
    for (int i = 0; i < result.numRoots; i++)
    {
        CHECK(fabs(result.roots[i] - requireRoots[i]) <= 0.001);
    }
}

SCENARIO("zero coefficient")
{
    WHEN("zero coefficient on x^3")
    {
        bool isFailed = false;
        try
        {
            auto result = Solve3(0, -8, -8, 5);
        }
        catch (const std::invalid_argument &e)
        {
            isFailed = true;
        }
        THEN("exeption throw")
        {
            CHECK(isFailed);
        }
    }
    WHEN("zero coefficient on x^2 and x")
    {
        bool isFailed = false;
        // x^2+8=0
        auto result = Solve3(1, 0, 0, 8);

        THEN("program works correctly")
        {
            CHECK(result.numRoots == 1);
            CHECK((fabs(result.roots[0] + 2) <= std::numeric_limits<double>::epsilon() * fabs(result.roots[0] - 2)));
        }
    }
}
