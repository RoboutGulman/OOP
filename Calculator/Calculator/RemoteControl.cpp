#include "stdafx.h"

#include "Calculator.h"
#include "RemoteControl.h"
#include <iomanip>
#include <regex>

//неиспользовать namespace
using namespace std;
using namespace std::placeholders;
CRemoteControl::CRemoteControl(Calculator &calc, std::istream &input, std::ostream &output)
    : m_calc(calc), m_input(input), m_output(output),
      m_actionMap({{"var", [this](istream &strm) { return DeclareVariable(strm); }},
                   {"let", [this](istream &strm) { return AssignValue(strm); }},
                   {"fn", [this](istream &strm) { return DeclareFunction(strm); }},
                   {"printvars", [this](istream &strm) { return PrintAllVariables(strm); }},
                   {"printfns", [this](istream &strm) { return PrintAllFunctions(strm); }},
                   {"print", [this](istream &strm) { return PrintEntity(strm); }},
                   {"help", [this](istream &strm) { return PrintHint(strm); }}}),
      m_hint("Calculator program\nAvailable commands:\nvar <id> - declare a variable\n"
             "let <id >= <id> / <number with a dot> - assign a value to a variable \n"
             "fn <id>=<id>/<id><operation symbol><id> - declare a function\n"
             "print <id> - print a value of function or variable\n"
             "printvars - print values of all variables\nprintfns - print values of all "
             "functions\nExit - exit from program\n")
{
}

//перенести в remote control h

bool CRemoteControl::HandleCommand()
{
    string commandLine;
    getline(m_input, commandLine);
    istringstream strm(commandLine);

    string action;
    strm >> action;

    auto it = m_actionMap.find(action);

    if (it != m_actionMap.end())
    {
        bool result = it->second(strm);
        //если команда вернула false, мы сообщаем пользователю о неправильном синтаксисе команды
        //и игнорируем команду
        if (!result)
        {
            m_output << "Incorrect command syntax!" << endl;
        }
        return true;
    }

    //оставить Exit
    if (action == "Exit")
    {
        return false;
    }

    m_output << "Unknown command!" << endl;
    return true;
}

void CRemoteControl::HandleCommands()
{
    while (!m_input.eof() && !m_input.fail())
    {
        cout << "> ";
        if (!HandleCommand())
        {
            return;
        }
    }
    return;
}

bool CRemoteControl::DeclareFunction(std::istream &args)
{
    string expression;
    args >> expression;
    auto identifiers = ParseIdentifiers(expression, '=');

    if (!identifiers)
    {
        m_output << "Error. Incorrect command syntax" << std::endl;
        return false;
    }

    string functionName = identifiers->first;
    for (int i = 0; i < size(m_operationSymbols); i++)
    {
        auto ident = ParseIdentifiers(identifiers->second, m_operationSymbols[i].symbol);
        if (ident)
        {
            if (m_calc.DeclareFunction(functionName, ident->first, ident->second, m_operationSymbols[i].type))
            {
                return true;
            }
        }
        if (m_calc.DeclareFunction(functionName, identifiers->second))
        {
            return true;
        }
    }
    return false;
}

bool CRemoteControl::DeclareVariable(std::istream &args)
{
    string identify;
    args >> identify;

    if (identify.empty())
    {
        m_output << "Error. After 'var' expected identify" << std::endl;
        return false;
    }

    if (!m_calc.DeclareVariable(identify))
    {
        return false;
    }

    return true;
}

//регул€рные выражени€
optional<pair<string, string>> CRemoteControl::ParseIdentifiers(const string &expression, char separator)
{
/*    std::string str = "" + separator;
    regex r("^((\w+)" + str + "(\w+)$)");

    smatch m;
    if (regex_search(expression, m, r))
    {
        return make_pair(m[1].str(), m[2].str());
    }*/
    auto iterator = expression.find(separator);
    if (iterator == 0 || iterator == std::string::npos || iterator == expression.size() - 1)
    {
        return nullopt;
    }

    std::string identifier1 = expression;
    identifier1.erase(iterator);

    std::string identifier2 = expression;
    identifier2.erase(0, iterator + 1);

    return make_pair(identifier1, identifier2);
}

bool CRemoteControl::AssignValue(std::istream &args)
{
    std::string expression;
    args >> expression;

    auto identifiers = ParseIdentifiers(expression, '=');
    if (!identifiers)
    {
        m_output << "Error. Incorrect command syntax" << std::endl;
        return false;
    }

    try
    {
        // 2 эксепшена out of range и invalid argument
        //обрабатывать их отдельно
        double number = std::stod(identifiers->second);
        if (!m_calc.DeclareVariableAndAssignValueFromNumber(identifiers->first, number))
        {
            return false;
        }
    }
    catch (const std::exception)
    {
        if (!m_calc.DeclareVariableAndAssignValueFromEntity(identifiers->first, identifiers->second))
        {
            return false;
        }
    }
    return true;
}

bool CRemoteControl::PrintEntity(std::istream &args)
{
    string identify;
    args >> identify;

    std::optional<double> result = m_calc.GetValueByIdentity(identify);
    //убрать вложенность if
    if (result)
    {
        m_output << fixed << std::setprecision(2) << *result << std::endl;
        return true;
    }
    if (m_calc.IsVariable(identify) || m_calc.IsFunction(identify))
    {
        m_output << "nan" << std::endl;
        return true;
    }
    m_output << "A variable or function with this name was not declared" << std::endl;
    return false;
}

void CRemoteControl::PrintMapOfEntities(const std::map<std::string, std::optional<double>> &entities)
{
    for (auto entity : entities)
    {
        if (!entity.second)
        {
            m_output << entity.first << ":nan" << std::endl;
        }
        else
        {
            m_output << entity.first << ":" << fixed << setprecision(2) << *entity.second << std::endl;
        }
    }
}

bool CRemoteControl::PrintAllVariables(std::istream & /*args*/)
{
    auto variables = m_calc.GetAllVariables();
    if (variables.empty())
    {
        m_output << "There are no declared variables in the calculator" << std::endl;
        return true;
    }

    //вынести в отдельную функцию
    PrintMapOfEntities(variables);
    return true;
}

bool CRemoteControl::PrintAllFunctions(std::istream & /*args*/)
{
    auto functions = m_calc.GetAllFunctions();
    if (functions.empty())
    {
        m_output << "There are no declared functions in the calculator" << std::endl;
        return true;
    }

    PrintMapOfEntities(functions);
    return true;
}

bool CRemoteControl::PrintHint(std::istream & /*args*/)
{
    m_output << m_hint;
    return true;
}
