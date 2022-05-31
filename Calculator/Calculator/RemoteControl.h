#pragma once
//перенести в privat

class CRemoteControl
{
  public:
    CRemoteControl(Calculator &calc, std::istream &input, std::ostream &output);
    //считывает строки и выполняет команды в строках до конца файла, ошибки или команды Exit
    void HandleCommands();

  private:
    //обрабатывает одну строчку m_input, если находит команду - выполняет её
    bool HandleCommand();
    //объявляет переменную, значение которой изначально не определено (nan)
    bool DeclareVariable(std::istream &args);
    //объявляет функцию, значение которой равно текущему значению переменной или результату операции между 2 переменными
    bool DeclareFunction(std::istream &args);
    //присваивает значение переменной (из сущности[переменной или функции] или числа с точкой)
    bool AssignValue(std::istream &args);
    //печатает в m_output значение сущности(переменной или функции)
    bool PrintEntity(std::istream &args);
    //Делит исходную строку на две. В первой то, что слева от разделителя, во второй - то, что справа
    std::optional<std::pair<std::string, std::string>> ParseIdentifiers(const std::string &expression, char separator);
    bool PrintAllVariables(std::istream &args);
    bool PrintAllFunctions(std::istream &args);

    //выводит текст подсказки
    bool PrintHint(std::istream &args);

  private:
    struct OperationSymbols
    {
        OperationType type;
        char symbol;
    };

    // функция-обработчик команды пользователя.
    // Возвращает true, если команда распознана и false, если были ошибки
    using Handler = std::function<bool(std::istream &args)>;

    // Отображает название команды на её обработчик
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
    //выводит map сущностей(имён переменных или функций и их значений)
    void PrintMapOfEntities(const std::map<std::string, std::optional<double>> &entities);
    //текст подсказки
};
