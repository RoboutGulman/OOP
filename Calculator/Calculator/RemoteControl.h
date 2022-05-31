#pragma once
//��������� � privat

class CRemoteControl
{
  public:
    CRemoteControl(Calculator &calc, std::istream &input, std::ostream &output);
    //��������� ������ � ��������� ������� � ������� �� ����� �����, ������ ��� ������� Exit
    void HandleCommands();

  private:
    //������������ ���� ������� m_input, ���� ������� ������� - ��������� �
    bool HandleCommand();
    //��������� ����������, �������� ������� ���������� �� ���������� (nan)
    bool DeclareVariable(std::istream &args);
    //��������� �������, �������� ������� ����� �������� �������� ���������� ��� ���������� �������� ����� 2 �����������
    bool DeclareFunction(std::istream &args);
    //����������� �������� ���������� (�� ��������[���������� ��� �������] ��� ����� � ������)
    bool AssignValue(std::istream &args);
    //�������� � m_output �������� ��������(���������� ��� �������)
    bool PrintEntity(std::istream &args);
    //����� �������� ������ �� ���. � ������ ��, ��� ����� �� �����������, �� ������ - ��, ��� ������
    std::optional<std::pair<std::string, std::string>> ParseIdentifiers(const std::string &expression, char separator);
    bool PrintAllVariables(std::istream &args);
    bool PrintAllFunctions(std::istream &args);

    //������� ����� ���������
    bool PrintHint(std::istream &args);

  private:
    struct OperationSymbols
    {
        OperationType type;
        char symbol;
    };

    // �������-���������� ������� ������������.
    // ���������� true, ���� ������� ���������� � false, ���� ���� ������
    using Handler = std::function<bool(std::istream &args)>;

    // ���������� �������� ������� �� � ����������
    using ActionMap = std::map<std::string, Handler>;

    Calculator &m_calc;
    std::istream &m_input;
    std::ostream &m_output;

    const ActionMap m_actionMap;
    const std::string m_hint;
    // OperationSymbols const m_operationSymbols[];
    OperationSymbols const m_operationSymbols[4] = {{OperationType::Addition, '+'},
                                                    {OperationType::Subtraction, '-'},
                                                    {OperationType::Multiplication, '*'},
                                                    {OperationType::Division, '/'}};
    //������� map ���������(��� ���������� ��� ������� � �� ��������)
    void PrintMapOfEntities(const std::map<std::string, std::optional<double>> &entities);
    //����� ���������
};
