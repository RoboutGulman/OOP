#include "Prime.h"
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNumbers;
    //если upperBound 1 или ниже, возвращаем пустое множество
    //т.к. 0 и 1 не являются простыми числами
    if (upperBound <= 1)
    {
        return primeNumbers;
    }
    std::vector<bool> allNumbers(upperBound + 1, true);
    for (int i = 2; i * i <= upperBound; i++)
    {
        if (allNumbers[i])
        {
            for (int j = i * i; j <= upperBound; j += i)
            {
                allNumbers[j] = false;
            }
        }
    }

    for (int i = 2; i <= upperBound; i++)
    {
        if (allNumbers[i])
        {
            primeNumbers.insert(i);
        }
    }
    return primeNumbers;
}
