#pragma once
enum class OperationType
{
    Addition = 0,
    Subtraction = 1,
    Multiplication = 2,
    Division = 3
};
class Calculator
{
  public:
    Calculator();
    ~Calculator();

    //строки по константной ссылке
    //
    //объ€вл€ет переменную с именем из аргумента и значением Nan
    bool DeclareVariable(const std::string &identity);

    //присваивает переменной значение из числа с точкой
    bool DeclareVariableAndAssignValueFromNumber(const std::string &identity, std::optional<double> number);

    //присваивает переменной значение из переменной или функции
    bool DeclareVariableAndAssignValueFromEntity(const std::string &receiverIdentity, const std::string &giverIdentity);

    //возвращает значение переменной или функции по идентификатору или nullopt, если сущностей с таким именем нет
    std::optional<double> GetValueByIdentity(const std::string &identity) const;

    std::map<std::string, std::optional<double>> GetAllVariables() const;

    std::map<std::string, std::optional<double>> GetAllFunctions() const;

    //провер€ет, объ€влена ли переменна€ с таким именем
    bool IsVariable(const std::string &identity) const;
    //провер€ет, объ€влена ли функци€ с таким именем
    bool IsFunction(const std::string &identity) const;

    //объ€вл€ет функцию, вычисл€емую по результату операции между двум€ переменными
    bool DeclareFunction(const std::string &identity, const std::string &firstOperand, const std::string &secondOperand,
                         OperationType operationType);

    //объ€вл€ет функцию, вычисл€емую по значению одной переменной
    bool DeclareFunction(const std::string &identity, const std::string &variableIdentity);

  private:
    struct Function
    {
        std::string firstOperand;
        std::optional<std::string> secondOperand;
        std::optional<OperationType> operationType;
    };
    //возвращает значение переменной или nullopt, если переменна€ с таким именем не объ€влена
    std::optional<double> GetVariable(const std::string &identity) const;
    //возвращает значение функции
    std::optional<double> CalculateFunction(const std::string &identity) const;

    //складывает х и у
    std::optional<double> AdditionFunction(double x, double y);
    //вычитает у из х
    std::optional<double> SubtractionFunction(double x, double y);
    //умножает х на у
    std::optional<double> —ompositionFunction(double x, double y);
    //делит х на у, возвращает nullopt, если у = 0
    std::optional<double> DivisionFunction(double x, double y);

    std::map<std::string, std::optional<double>> m_variables;
    std::map<std::string, Function> m_functions;
    //можно убрать static
    std::map<OperationType, std::function<std::optional<double>(double x, double y)>> const m_operations = {
        {OperationType::Addition, [this](double x, double y) { return AdditionFunction(x, y); }},
        {OperationType::Subtraction, [this](double x, double y) { return SubtractionFunction(x, y); }},
        {OperationType::Multiplication, [this](double x, double y) { return —ompositionFunction(x, y); }},
        {OperationType::Division, [this](double x, double y) { return DivisionFunction(x, y); }}};
};
