// PrimeNumbersGenerator.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Prime.h"
#include <iostream>
#include <set>

int main(int argc, char *argv[])
{
    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }
    auto primeNumbersSet = GeneratePrimeNumbersSet(args->upperBound);
    std::cout << "runtime = " << clock() / 1000.0 << std::endl;
    //PrintNumbersSet(primeNumbersSet);
    return 1;
}

void PrintNumbersSet(std::set<int>& primeNumbersSet)
{
    std::set<int>::iterator setIterator = primeNumbersSet.begin();
    for (; setIterator != primeNumbersSet.end(); setIterator++)
    {
        std::cout << *setIterator << " ";
    }
    std::cout << std::endl << primeNumbersSet.size();
}
