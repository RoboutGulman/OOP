// CopyFile.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "CopyFile.h"

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: CopyFile.exe <input file name> <output file name>\n";
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	// Проверка правильности аргументов командной строки
	if (!args)
	{
		return 1;
	}

	//Открываем входной файл
	std::ifstream input;
	input.open(args->inputFileName);
	if (!input.is_open())
	{
		std::cout << "Failed to open '" << args->inputFileName << "' for reading\n";
		return 1;
	}
	//Открываем выходной файл
	std::ofstream output;
	output.open(args->outputFileName);
	if (!output.is_open())
	{
		std::cout << "Failed to open '" << args->outputFileName << "' for writing\n";
		return 1;
	}

	CopyStreams(input, output);

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return 1;
	}

	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return 1;
	}
	return 0;
}

void CopyStreams(std::ifstream& input, std::ofstream& output)
{
	//Копируем содержимое входного файла в выходной
	char ch;
	while (input.get(ch))
	{
		if (!output.put(ch))
		{
			break;
		}
	}
}


