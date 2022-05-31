// PrimeNumbersGeneratorTest.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение
// программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch/catch.hpp"
#include <sstream>

#include "../PrimeNumbersGenerator/Prime.h"

SCENARIO("zero is not a prime number")
{
    REQUIRE(GeneratePrimeNumbersSet(0).empty());
}

SCENARIO("there are no prime numbers among negative numbers")
{
    REQUIRE(GeneratePrimeNumbersSet(-12).empty());
}

SCENARIO("checking for INT_MIN")
{
    REQUIRE(GeneratePrimeNumbersSet(INT_MIN).empty());
}

SCENARIO("1 is not a prime number")
{
    REQUIRE(GeneratePrimeNumbersSet(1).empty());
}

SCENARIO("2 is the first prime number")
{
    std::set<int> set{2};
    REQUIRE(GeneratePrimeNumbersSet(2) == set);
}

SCENARIO("for a positive number, the function should return prime numbers up to that number")
{
    std::set<int> set{2, 3, 5};
    REQUIRE(GeneratePrimeNumbersSet(5) == set);
}

SCENARIO("for a 100 000 000 the function should return set with size 5761455")
{
    auto set = GeneratePrimeNumbersSet(100000000);
    REQUIRE(set.size() == 5761455);
}
