#include "stdafx.h"

#include "Solve3.h"
//приводит старший коэффициент к 1
void ReducePolynomial(double &a, double &b, double &c, double &d)
{
    if (!(fabs(a - 1) <= std::numeric_limits<double>::epsilon() * fabs(a + 1)))
    {
        b /= a;
        c /= a;
        d /= a;
        a = 1;
    }
    return;
}

EquationRoots3 SolveUsingTrigonometricFunctions(double r, double b, double q)
{
    EquationRoots3 result{};

    double q3 = pow(q, 3);
    double t = r / sqrt(q3);
    if (t < -1)
    {
        t = -1;
    }

    if (t > 1)
    {
        t = 1;
    }

    t = acos(t);
    b /= 3;
    q = -2 * sqrt(q);
    //вынести расчёт в отдельную функцию
    result.roots[0] = q * cos(t / 3) - b;
    result.roots[1] = q * cos((t + 2 * M_PI) / 3) - b;
    result.roots[2] = q * cos((t - 2 * M_PI) / 3) - b;
    result.numRoots = 3;
    return result;
}

EquationRoots3 SolveUsingHyperbolicFunctions(double r, double b, double q)
{
    EquationRoots3 result{};

    double r2 = pow(r, 2);
    double q3 = pow(q, 3);
    double a = -pow(fabs(r) + sqrt(r2 - q3), 1. / 3);
    if (r < 0)
    {
        a = -a;
    }
    double B = a == 0 ? 0 : B = q / a;

    b /= 3;
    result.roots[0] = (a + B) - b;
    result.roots[1] = -0.5 * (a + B) - b;
    result.roots[2] = 0.5 * sqrt(3.) * (a - B);
    if (fabs(result.roots[2]) < std::numeric_limits<double>::epsilon())
    {
        result.roots[2] = result.roots[1];
        result.numRoots = 2;
        return result;
    }
    result.numRoots = 1;
    return result;
}

EquationRoots3 Solve3(double a, double b, double c, double d)
{
    if ((fabs(a) <= std::numeric_limits<double>::epsilon() * fabs(a)))
    {
        throw std::invalid_argument("the coefficient at x cannot be equal to 0");
    }

    ReducePolynomial(a, b, c, d);
    double q = (pow(b, 2) - 3 * c) / 9;
    double r = (b * (2 * pow(b, 2) - 9 * c) + 27 * d) / 54;
    double r2 = pow(r, 2);
    double q3 = pow(q, 3);
    if (r2 < q3)
    {
        return SolveUsingTrigonometricFunctions(r, b, q);
    }
    else
    {
        return SolveUsingHyperbolicFunctions(r, b, q);
    }
}
