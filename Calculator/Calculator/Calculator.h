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

    //������ �� ����������� ������
    //
    //��������� ���������� � ������ �� ��������� � ��������� Nan
    bool DeclareVariable(const std::string &identity);

    //����������� ���������� �������� �� ����� � ������
    bool DeclareVariableAndAssignValueFromNumber(const std::string &identity, std::optional<double> number);

    //����������� ���������� �������� �� ���������� ��� �������
    bool DeclareVariableAndAssignValueFromEntity(const std::string &receiverIdentity, const std::string &giverIdentity);

    //���������� �������� ���������� ��� ������� �� �������������� ��� nullopt, ���� ��������� � ����� ������ ���
    std::optional<double> GetValueByIdentity(const std::string &identity) const;

    std::map<std::string, std::optional<double>> GetAllVariables() const;

    std::map<std::string, std::optional<double>> GetAllFunctions() const;

    //���������, ��������� �� ���������� � ����� ������
    bool IsVariable(const std::string &identity) const;
    //���������, ��������� �� ������� � ����� ������
    bool IsFunction(const std::string &identity) const;

    //��������� �������, ����������� �� ���������� �������� ����� ����� �����������
    bool DeclareFunction(const std::string &identity, const std::string &firstOperand, const std::string &secondOperand,
                         OperationType operationType);

    //��������� �������, ����������� �� �������� ����� ����������
    bool DeclareFunction(const std::string &identity, const std::string &variableIdentity);

  private:
    struct Function
    {
        std::string firstOperand;
        std::optional<std::string> secondOperand;
        std::optional<OperationType> operationType;
    };
    //���������� �������� ���������� ��� nullopt, ���� ���������� � ����� ������ �� ���������
    std::optional<double> GetVariable(const std::string &identity) const;
    //���������� �������� �������
    std::optional<double> CalculateFunction(const std::string &identity) const;

    //���������� � � �
    std::optional<double> AdditionFunction(double x, double y);
    //�������� � �� �
    std::optional<double> SubtractionFunction(double x, double y);
    //�������� � �� �
    std::optional<double> �ompositionFunction(double x, double y);
    //����� � �� �, ���������� nullopt, ���� � = 0
    std::optional<double> DivisionFunction(double x, double y);

    std::map<std::string, std::optional<double>> m_variables;
    std::map<std::string, Function> m_functions;
    //����� ������ static
    std::map<OperationType, std::function<std::optional<double>(double x, double y)>> const m_operations = {
        {OperationType::Addition, [this](double x, double y) { return AdditionFunction(x, y); }},
        {OperationType::Subtraction, [this](double x, double y) { return SubtractionFunction(x, y); }},
        {OperationType::Multiplication, [this](double x, double y) { return �ompositionFunction(x, y); }},
        {OperationType::Division, [this](double x, double y) { return DivisionFunction(x, y); }}};
};
