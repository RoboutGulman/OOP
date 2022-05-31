#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <optional>
//для каждого модуля отдельный заголовочный файл
struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    std::map<std::string, std::string> params;
};
typedef std::pair<int, std::string> EntryPointAndSubstring;
typedef std::map<std::string, std::string> Dictionary;

void AddStringToBohr(const std::string& s);
void FindAllPos(const std::string& s, std::vector<EntryPointAndSubstring>& result);
void InitBohr();
void AddParamsToBohr(Dictionary params);
std::string ExpandTemplate(std::string const& tpl, Dictionary const& params);
std::optional<Args> ParseArgs(int argc, char* argv[]);