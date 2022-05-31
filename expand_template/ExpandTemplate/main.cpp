// ExpandTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Expand.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Files
{
    std::ifstream input;
    std::ofstream output;
};
//создавать в мейне файлы, передавать по ссылкам
std::optional<Files> OpenFiles(std::string inputFileName, std::string outputFileName)
{
    Files files;
    //Открываем входной файл
    files.input.open(inputFileName);
    if (!files.input.is_open())
    {
        std::cout << "Failed to open '" << inputFileName << "' for reading\n";
        return std::nullopt;
    }
    //Открываем выходной файл
    files.output.open(outputFileName);
    if (!files.output.is_open())
    {
        std::cout << "Failed to open '" << outputFileName << "' for writing\n";
        return std::nullopt;
    }
    return files;
}

//переделать типы файлов в istream, функция будет переиспользуемая
//отправлять dictionary по константной ссылке
bool ExpandTemplatesInFile(std::ifstream &input, std::ofstream &output, Dictionary params)
{
    std::string buffer;
    while (getline(input, buffer))
    {
        output << ExpandTemplate(buffer, params) << std::endl;
    }

    if (input.bad())
    {
        std::cout << "Failed to read data from input file\n";
        return false;
    }

    if (!output.flush())
    {
        std::cout << "Failed to write data to output file\n";
        return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    setlocale(0, "");

    auto args = ParseArgs(argc, argv);
    if (!args)
    {
        return 1;
    }

    InitBohr();

    AddParamsToBohr(args->params);

    auto files = OpenFiles(args->inputFileName, args->outputFileName);
    if (!files)
    {
        return 1;
    }

    if (!ExpandTemplatesInFile(files->input, files->output, args->params))
    {
        return 1;
    }

    return 0;
}
