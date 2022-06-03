#include "CTriangle.h"
#include <array>
#include <iostream>
#include <stdexcept>
#include <fstream>

std::array<double, 3> GetValideSides(std::array<double, 3> sides)
{
    for (int i = 0; i < sides.size(); i++)
    {
        if (sides[i] < 0)
        {
            throw std::invalid_argument("Argument must not be negative");
        }
        double sumOfOtherSides = 0;
        for (int j = 0; j < sides.size(); j++)
        {
            if (i != j)
            {
                sumOfOtherSides += sides[j];
            }
        }
        if (sides[i] > sumOfOtherSides)
        {
            throw std::domain_error("one of the sides cannot be greater than the sum of the others");
        }
    }
    return sides;
}

CTriangle::CTriangle(double side1, double side2, double side3)
try : m_sides(GetValideSides({side1, side2, side3}))
{
}
catch (std::exception const &e)
{
    std::cout << "Unable to construct CTriangle instance\n";
    throw;
}

double CTriangle::GetSide1() const
{
    return m_sides[0];
}

double CTriangle::GetSide2() const
{
    return m_sides[1];
}

double CTriangle::GetSide3() const
{
    return m_sides[2];
}

double CTriangle::GetArea() const
{
    return 0.0;
}

double CTriangle::GetPerimeter() const
{
    double perimeter = 0;
    for (double side : m_sides)
    {
        perimeter += side;
    }
    return perimeter;
}
