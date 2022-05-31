// FindText.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <fstream>
#include <iostream>
#include <optional>
#include <set>
#include <string>

struct Args
{
    int sourceNotation = 0;
    int destinationNotation = 0;
    std::string value;
};

int StringToNumber(const std::string &str, int radix, bool &wasError);
int CharToDigit(char ch, int radix, bool &wasError);
std::string NumberToString(int n, int radix, bool &wasError);
char DigitToChar(int n);

std::optional<Args> ParseArgs(int argc, char *argv[])
{
    const int MIN_RADIX = 2;
    const int MAX_RADIX = 36;
    //проверка на количество аргументов программы
    if (argc != 4)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: findtext.exe <file name> <text to search>\n";
        return std::nullopt;
    }
    Args args;
    args.value = argv[3];
    //перевод оснований из строк в int, при ошибке перевода программа завершится с ошибкой
    try
    {
        args.sourceNotation = std::stoi(argv[1]);
        args.destinationNotation = std::stoi(argv[2]);
    }
    catch (const std::exception& error)
    {
        std::cout << error.what() << ". Error, all 3 arguments must be integers" << std::endl;
        return std::nullopt;
    }
    //проверка оснований на максимальное и минимальное значение
    if ((args.sourceNotation < MIN_RADIX) || (args.sourceNotation > MAX_RADIX) ||
        (args.destinationNotation < MIN_RADIX) || (args.destinationNotation > MAX_RADIX))
    {
        std::cout << "SourceNotation and DestinationNotation must take values from " << MIN_RADIX << " to " << MAX_RADIX
                  << std::endl;
        return std::nullopt;
    }
    return args;
}

int main(int argc, char *argv[])
{
    bool wasError = false;
    auto args = ParseArgs(argc, argv);
    // Проверка правильности аргументов командной строки
    if (!args)
    {
        return 1;
    }

    //переводим число из входного основания в основание 10
    int number = StringToNumber(args->value, args->sourceNotation, wasError);

    //переводим число из 10 основания в выходное
    std::string convertedNumber;
    if (!wasError)
    {
        convertedNumber = NumberToString(number, args->destinationNotation, wasError);
    }

    if (!wasError)
    {
        std::cout << convertedNumber << std::endl;
    }
    else
    {
        std::cout << "Error!" << std::endl;
        return 1;
    }
    return 0;
}

//принимает представление числа в основании из аргумента radix
//возвращает это число в переменной int
int StringToNumber(const std::string &str, int radix, bool &wasError)
{
    bool isNegative = (str[0] == '-');
    int number = 0;
    int digit = 0;

    for (int i = str.length() - 1; i >= (isNegative ? 1 : 0); i--)
    {
        digit = CharToDigit(str[i], radix, wasError);
        if (wasError)
        {
            std::cout << "An incorrect symbol was found for this radix" << std::endl;
            return 0;
        }

        digit *= pow(radix, str.length() - 1 - i);

        //проверка на переполнение
        if (INT_MAX - digit < number)
        {
            std::cout << "Overflow error!" << std::endl;
            wasError = true;
            return 0;
        }
        else
        {
            number += digit;
        }
    }
    return isNegative ? -number : number;
}

int CharToDigit(char ch, int radix, bool &wasError)
{
    const int LETTER_DELTA = 10;
    int digit = 0;
    //проверяет, есть ли символ среди заглавных букв английского алфавита
    if ('A' <= ch && ch <= 'Z')
    {
        digit = static_cast<int>(ch) - ('A' - LETTER_DELTA);
    }
    else
    {
        //проверяет, есть ли символ среди цифр
        if ('0' <= ch && ch <= '9')
        {
            digit = static_cast<int>(ch) - '0';
        }
        else
        {
            wasError = true;
        }
    }
    if (digit >= radix)
    {
        wasError = true;
    }
    return digit;
}

//принимает число int, возвращает представление этого числа в СС
//из аргумента radix(в виде строки)
std::string NumberToString(int number, int radix, bool &wasError)
{
    bool isNegative = false;
    std::string result;
    if (number < 0)
    {
        isNegative = true;
        number = -number;
    }

    do
    {
        result = DigitToChar(number % radix) + result;
    } while ((number /= radix) > 0);

    if (isNegative)
    {
        result = '-' + result;
    }
    return result;
}

char DigitToChar(int digit)
{
    const int LETTER_DELTA = 10;
    char ch;
    if (digit >= 10)
    {
        ch = digit + ('A' - LETTER_DELTA);
    }
    else
    {
        ch = digit + '0';
    }
    return ch;
}
