#include "Prime.h"
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    std::set<int> primeNumbers;
    //���� upperBound 1 ��� ����, ���������� ������ ���������
    //�.�. 0 � 1 �� �������� �������� �������
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
