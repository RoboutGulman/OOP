#pragma once
#include <array>
class CTriangle
{
public:
	CTriangle(double side1, double side2, double side3);
	double GetSide1()const;
	double GetSide2()const;
	double GetSide3()const;
	double GetArea()const;
	double GetPerimeter()const;
private:
	std::array<double, 3> m_sides={0,0,0};
};
