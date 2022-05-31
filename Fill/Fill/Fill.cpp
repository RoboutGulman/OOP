// Fill.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <array>
#include <fstream>
#include <iostream>
#include <optional>
#include <stack>
#include <string>
#include <vector>

const int MAX_SIZE_OF_FIELD = 100;
const char EMPTY_SYMBOL = ' ';
const char FILL_SYMBOL = '.';
const char BORDER_SYMBOL = '#';
const char START_SYMBOL = 'O';
typedef std::stack<Point> PointStack;
using Field = std::array<std::array<char, MAX_SIZE_OF_FIELD + 2>, MAX_SIZE_OF_FIELD + 2>;

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

struct Point
{
    int x;
    int y;
};
// Stack to PointStack
//обосновать, почему стек выгоднее очереди(или наоборот) с точки зрения памяти


std::optional<Args> ParseArgs(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments count\n";
        //исправить подсказку
        std::cout << "Usage: Fill.exe <input file name> <output file name>\n";
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}

Field InitField()
{
    Field field{};
    //заполняем поле пустыми символами
    //тело любой функции-в фигурные скобки
    for (int x = 1; x < MAX_SIZE_OF_FIELD + 1; x++)
    {
        for (int y = 1; y < MAX_SIZE_OF_FIELD + 1; y++)
        {
            field[x][y] = EMPTY_SYMBOL;
        }
    }
    //заполняем границы символами барьера
    for (int x = 0; x < MAX_SIZE_OF_FIELD + 2; x++)
    {
        field[x][0] = BORDER_SYMBOL;
        field[x][MAX_SIZE_OF_FIELD + 1] = BORDER_SYMBOL;
    }
    for (int y = 0; y < MAX_SIZE_OF_FIELD + 2; y++)
    {
        field[0][y] = BORDER_SYMBOL;
        field[MAX_SIZE_OF_FIELD + 1][y] = BORDER_SYMBOL;
    }
    return field;
}

//считывает поле из входного файла
// wasError  можно возвращать функцией(или Field обернуть в optional)
//в каждой функции wasError = false;
std::optional<Field> TryReadFieldFromInputFile(const std::string &inputFileName)
{
    auto field = InitField();
    //Открываем входной файл
    std::ifstream input;
    input.open(inputFileName);
    if (!input.is_open())
    {
        std::cout << "Failed to open '" << inputFileName << "' for reading\n";
        return std::nullopt;
    }

    //считываем символы из входного файла
    int currentLineIndex = 1;
    std::string buffer;
    while (getline(input, buffer) && currentLineIndex < MAX_SIZE_OF_FIELD + 1)
    {
        for (int y = 0; y < buffer.length() && y < MAX_SIZE_OF_FIELD; ++y)
        {
            if (buffer[y] != EMPTY_SYMBOL && buffer[y] != BORDER_SYMBOL && buffer[y] != START_SYMBOL)
            {
                std::cout << "Incorrect symbol was found in " << inputFileName << "\n";
                return std::nullopt;
            }
            field[currentLineIndex][y + 1] = buffer[y];
        }
        currentLineIndex++;
    }

    if (input.bad())
    {
        std::cout << "Failed to read data from input file\n";
        return std::nullopt;
    }
    return field;
}

//выводит поле в файл, не выводит границы поля
//сделать wasError возвращаемым значением(возвращать true в случае успеха, false в случае ошибки)
// wasError=false;
bool TryPrintFieldToFile(const Field &field, const std::string &outputFileName)
{
    bool wasSuccess = true;
    //Открываем выходной файл
    std::ofstream output;
    output.open(outputFileName);
    if (!output.is_open())
    {
        std::cout << "Failed to open '" << outputFileName << "' for writing\n";
        wasSuccess = false;
        return wasSuccess;
    }

    for (int x = 1; x < MAX_SIZE_OF_FIELD + 1; x++)
    {
        for (int y = 1; y < MAX_SIZE_OF_FIELD + 1; y++)
        {
            output << field[x][y];
        }
        output << std::endl;
    }

    if (!output.flush())
    {
        std::cout << "Failed to write data to output file\n";
        wasSuccess = false;
    }
    return wasSuccess;
}
//убрать функцию, добавить команды в место вызова

void PushPointToStackAndFillPoint(Field &field, Point point, PointStack &pointStack)
{
    if (field[point.x][point.y] == EMPTY_SYMBOL)
    {
        pointStack.push(point);
        field[point.x][point.y] = FILL_SYMBOL;
    }
}

//заполняет один контур начиная с символа старта в пределах границ
//перенести объявление стека в эту функцю
void FillAreaFromStartSymbol(Field &field, Point point)
{
    PointStack pointStack;
    pointStack.push(point);
    while (!pointStack.empty())
    {
        point = pointStack.top();
        pointStack.pop();
        PushPointToStackAndFillPoint(field, {point.x + 1, point.y}, pointStack);
        PushPointToStackAndFillPoint(field, {point.x - 1, point.y}, pointStack);
        PushPointToStackAndFillPoint(field, {point.x, point.y + 1}, pointStack);
        PushPointToStackAndFillPoint(field, {point.x, point.y - 1}, pointStack);
    }
}

//заполняет все контуры на поле
void FillField(Field &field)
{
    for (int x = 1; x <= MAX_SIZE_OF_FIELD; x++)
    {
        for (int y = 1; y <= MAX_SIZE_OF_FIELD; y++)
        {
            if (field[x][y] == START_SYMBOL)
            {
                FillAreaFromStartSymbol(field, {x, y});
            }
        }
    }
}

int main(int argc, char *argv[])
{
    bool wasError = false;
    //если парсинг аргументов не прошёл, все дальнейшие операции не имеют смысла

    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    auto field = TryReadFieldFromInputFile(args->inputFileName);
    if (!field)
    {
        return 1;
    }

    FillField(*field);

    if (!TryPrintFieldToFile(*field, args->outputFileName))
    {
        return 1;
    }

    return 0;
}
