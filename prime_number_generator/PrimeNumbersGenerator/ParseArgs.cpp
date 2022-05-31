#include "Prime.h"
#include <iostream>
#include <optional>
#include <string>

std::optional<Args> ParseArgs(int argc, char *argv[])
{
    Args args;
    //�������� �� ���������� ���������� ���������
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: PrimeNumbersGenerator.exe <upperBound>\n";
        return std::nullopt;
    }
    //������� upperBound �� ������ � int, ��� ������ �������� ��������� ���������� � �������
    try
    {
        args.upperBound = std::stoi(argv[1]);
    }
    catch (const std::exception &error)
    {
        std::cout << error.what() << ". Error, all 3 arguments must be integers" << std::endl;
        return std::nullopt;
    }

    return args;
}
