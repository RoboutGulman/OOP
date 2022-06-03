#pragma once
#include "stdafx.h"

struct EquationRoots3
{
	int numRoots;
	double roots[3];
};

// ¬ычисл€ем корни кубического уравнени€ ax^3 + bx^2 + cx + d = 0
EquationRoots3 Solve3(double a, double b, double c, double d);