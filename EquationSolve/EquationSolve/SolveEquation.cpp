#include "stdafx.h"

#include "Solve3.h"
#include "SolveEquation.h"

void PrintSolutionToStream(std::ostream& os, EquationRoots3 result)
{
    if (result.numRoots == 0)
    {
        std::cout << "the equation has no solution" << std::endl;
        return;
    }
    std::cout << "the roots of the equation: ";
    for (int i = 0; i < result.numRoots; i++)
    {
        std::cout << result.roots[i] << ' ';
    }
    std::cout << std::endl;
}

void SolveEquation(std::istream& is, std::ostream& os)
{
    std::string buffer;
    double a, b, c, d;
    while (std::cin >> a >> b >> c >> d)
    {
        try
        {
            auto result = Solve3(a, b, c, d);
            PrintSolutionToStream(os, result);
        }
        catch (const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}
