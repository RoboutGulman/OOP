#pragma once
#include <iostream>
#include <set>
#include <optional>

struct Args
{
    int upperBound;
};

std::optional<Args> ParseArgs(int argc, char* argv[]);
std::set<int> GeneratePrimeNumbersSet(int upperBound);
void PrintNumbersSet(std::set<int>& primeNumbersSet);