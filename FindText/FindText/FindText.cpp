// FindText.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <fstream>
#include <iostream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
    string FileName;
    string SearchText;
};

optional<Args> ParseArgs(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "Invalid arguments count\n";
        cout << "Usage: findtext.exe <file name> <text to search>\n";
        return nullopt;
    }
    Args args;
    args.FileName = argv[1];
    args.SearchText = argv[2];
    return args;
}

bool FindString(istream &buffer, const string &searchText);

int main(int argc, char *argv[])
{
    auto args = ParseArgs(argc, argv);
    // Проверка правильности аргументов командной строки
    if (!args)
    {
        return 1;
    }

    //Открываем файл
    ifstream input;
    input.open(args->FileName);
    if (!input.is_open())
    {
        cout << "Failed to open '" << args->FileName << "' for reading\n";
        return 1;
    }

    //ищем искомую строку в файле
    if (!FindString(input, args->SearchText))
    {
        cout << "Text not found\n";
        return 1;
    }

    if (input.bad())
    {
        cout << "Failed to read data from input file\n";
        return 1;
    }

    return 0;
}

bool FindString(istream &input, const string &searchText)
{
    bool wasFound = false;
    int currentLineIndex = 0;
    string buffer;
    while (getline(input, buffer))
    {
        currentLineIndex++;
        if (buffer.find(searchText, 0) != -1)
        {
            if (!wasFound)
                wasFound = true;
            cout << "find in the line " << currentLineIndex << endl;
        }
    }
    return wasFound;
}
