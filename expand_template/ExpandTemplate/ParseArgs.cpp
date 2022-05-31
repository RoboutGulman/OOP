#include <iostream>
#include <map>
#include <optional>
struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    std::map<std::string, std::string> params;
};

std::optional<Args> ParseArgs(int argc, char *argv[])
{
    if ((argc < 3) || (argc % 2 == 0))
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: expand_template.exe <input file name> <output file name> [<param> <value> [<param> "
                     "<value> …]]\n";
        return std::nullopt;
    }
    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    for (int i = 3; i < argc; i += 2)
    {
        if (argv[i] != "")
        {
            args.params[argv[i]] = argv[i + 1];
        }
    }
    return args;
}
