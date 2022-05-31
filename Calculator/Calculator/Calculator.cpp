#include "stdafx.h"

#include "Calculator.h"

Calculator::Calculator()
{
}

Calculator::~Calculator()
{
}

bool Calculator::DeclareVariable(const std::string &identity)
{
    //добавить проверку на идентификатор
    //из availible name отдельная функция
    if (IsFunction(identity) || IsVariable(identity) || (identity[0] >= '0' && identity[0] <= '9'))
    {
        return false;
    }
    m_variables[identity] = std::nullopt;
    return true;
}

bool Calculator::DeclareVariableAndAssignValueFromNumber(const std::string &identity, std::optional<double> number)
{
    //разбить на 2 if
    if (!IsVariable(identity) && !DeclareVariable(identity))
    {
        return false;
    }
    m_variables[identity] = number;
    return true;
}

bool Calculator::DeclareVariableAndAssignValueFromEntity(const std::string &receiverIdentity, const std::string &giverIdentity)
{
    //разбить на 2 if
    auto giver = GetValueByIdentity(giverIdentity);
    if (!giver && !IsFunction(giverIdentity) && !IsVariable(giverIdentity))
    {
        return false;
    }
    if (!DeclareVariableAndAssignValueFromNumber(receiverIdentity, giver))
    {
        return false;
    }
    return true;
}

bool Calculator::IsVariable(const std::string &identity) const
{
    return m_variables.find(identity) != m_variables.end();
}

std::optional<double> Calculator::GetVariable(const std::string &identity) const
{
    if (!IsVariable(identity))
    {
        return std::nullopt;
    }
    auto iterator = m_variables.find(identity);
    return iterator->second;
}

std::map<std::string, std::optional<double>> Calculator::GetAllVariables() const
{
    return m_variables;
}

std::map<std::string, std::optional<double>> Calculator::GetAllFunctions() const
{
    std::map<std::string, std::optional<double>> functionResults;
    for (auto function : m_functions)
    {
        functionResults[function.first] = CalculateFunction(function.first);
    }
    return functionResults;
}

bool Calculator::DeclareFunction(const std::string &identity, const std::string &firstOperand,
                                 const std::string &secondOperand, OperationType operationType)
{
    if (IsFunction(identity))
    {
        return false;
    }
    if ((IsVariable(firstOperand) || IsFunction(firstOperand)) &&
        (IsVariable(secondOperand) || IsFunction(secondOperand)))
    {
        m_functions[identity] = {firstOperand, secondOperand, operationType};
        return true;
    }
    return false;
}

bool Calculator::DeclareFunction(const std::string &identity, const std::string &variableIdentity)
{
    if (IsFunction(identity))
    {
        return false;
    }
    if (IsVariable(variableIdentity) || IsFunction(variableIdentity))
    {
        m_functions[identity] = {variableIdentity, std::nullopt, std::nullopt};
        return true;
    }
    return false;
}

bool Calculator::IsFunction(const std::string &identity) const
{
    return m_functions.find(identity) != m_functions.end();
}

std::optional<double> Calculator::GetValueByIdentity(const std::string &identity) const
{
    if (IsVariable(identity))
    {
        return GetVariable(identity);
    }
    return CalculateFunction(identity);
}

std::optional<double> Calculator::CalculateFunction(const std::string &identity) const
{
    if (!IsFunction(identity))
    {
        return std::nullopt;
    }

    Function function = m_functions.find(identity)->second;
    if (!function.operationType || !function.secondOperand)
    {
        return GetValueByIdentity(function.firstOperand);
    }

    auto operation = m_operations.find(*function.operationType)->second;
    auto firstOperandValue = GetValueByIdentity(function.firstOperand);
    auto secondOperandValue = GetValueByIdentity(*function.secondOperand);

    if (!firstOperandValue || !secondOperandValue)
    {
        return std::nullopt;
    }
    return operation(*firstOperandValue, *secondOperandValue);
}

std::optional<double> Calculator::AdditionFunction(double x, double y)
{
    return x + y;
}

std::optional<double> Calculator::SubtractionFunction(double x, double y)
{
    return x - y;
}

std::optional<double> Calculator::СompositionFunction(double x, double y)
{
    return x * y;
}

std::optional<double> Calculator::DivisionFunction(double x, double y)
{
    if (y == 0)
    {
        return std::nullopt;
    }
    return x / y;
}
//перенести в приватную часть класса, переименовать, вынести в функции остальные операции

//перенести в calculator h
