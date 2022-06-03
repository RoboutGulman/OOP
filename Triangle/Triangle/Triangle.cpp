// Triangle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "CTriangle.h"
#include <array>
#include <iostream>
#include <stdexcept>

int main()
try
{
    // тело функции main
    CTriangle triangle(-1, 4, 5);
    std::cout << triangle.GetSide1();
    return 0;
}
catch (std::exception const &e)
{
    std::cout << "Error: " << e.what() << "\n";
    return 1;
}
catch (...)
{
    std::cout << "Unknown exception has been caught\n";
    return 2;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
