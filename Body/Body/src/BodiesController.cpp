#include "../stdafx.h"

#include "../headers/BodiesController.h"

CBodiesController::CBodiesController(std::istream &input, std::ostream &output, CBodiesContainer &container)
    : m_input(input), m_output(output), m_container(container),
      m_actionMap({{"newBody", [this](std::istream &strm) { return ReadBody(strm); }},
                   {"findMaxWeight", [this](std::istream &strm) { return FindMaxWeight(strm); }},
                   {"printAll", [this](std::istream &strm) { return PrintAllBodies(strm); }},
                   {"addTo", [this](std::istream &strm) { return AddBodyToCompoundBody(strm); }},
                   {"findMinWaterWeight", [this](std::istream &strm) { return FindMinWeightInWater(strm); }}})
{
}

bool CBodiesController::HandleCommand()
{
    std::string commandLine;
    getline(m_input, commandLine);
    std::istringstream strm(commandLine);

    std::string action;
    strm >> action;

    auto it = m_actionMap.find(action);

    if (it != m_actionMap.end())
    {
        bool result = it->second(strm);
        //если команда вернула false, мы сообщаем пользователю о неправильном синтаксисе команды
        //и игнорируем команду
        if (!result)
        {
            m_output << "Incorrect command syntax!" << std::endl;
        }
        return true;
    }

    //оставить Exit
    if (action == "Exit")
    {
        return false;
    }

    m_output << "Unknown command!" << std::endl;
    return true;
}

void CBodiesController::HandleCommands()
{
    while (!m_input.eof() && !m_input.fail())
    {
        //введите N-ое тело или команду
        m_output << "> ";
        if (!HandleCommand())
        {
            return;
        }
    }
    return;
}

bool CBodiesController::ReadBody(std::istream &args)
{
    std::string typeName;
    args >> typeName;

    auto typeIter = m_bodyTypeNames.find(typeName);
    if (typeIter == m_bodyTypeNames.end())
    {
        return false;
    }

    switch (typeIter->second)
    {
    case BodyType::Cone:
        ReadCone();
        break;
    case BodyType::Cylinder:
        ReadCylinder();
        break;
    case BodyType::Parallelepiped:
        ReadParallelepiped();
        break;
    case BodyType::Sphere:
        ReadSphere();
        break;
    case BodyType::Compound:
        return ReadCompoundBody();
    default:
        return false;
    }
    //переходим на следующую строку
    getline(m_input, typeName);
    return true;
}

bool CBodiesController::ReadCone()
{
    double density, baseRadius, heigth;
    m_output << "enter a density, base radius and heigth: ";

    if (m_input >> density >> baseRadius >> heigth)
    {
        m_container.AddCone(density, baseRadius, heigth);
        return true;
    }
    return false;
}

bool CBodiesController::ReadCylinder()
{
    double density, baseRadius, heigth;
    m_output << "enter a density, base radius and heigth: ";

    if (m_input >> density >> baseRadius >> heigth)
    {
        m_container.AddCylinder(density, baseRadius, heigth);
        return true;
    }
    return false;
}

bool CBodiesController::ReadParallelepiped()
{
    double density, width, length, height;
    m_output << "enter a density, width, length and height: ";

    if (m_input >> density >> width >> length >> height)
    {
        m_container.AddParallelepiped(density, width, length, height);
        return true;
    }
    return false;
}

bool CBodiesController::ReadSphere()
{
    double density, radius;
    m_output << "enter a density and radius: ";

    if (m_input >> density >> radius)
    {
        m_container.AddSphere(density, radius);
        return true;
    }
    return false;
}

//тест некорректного ввода
bool CBodiesController::ReadCompoundBody()
{
    m_container.AddCompoundBody();
    return true;
}

bool CBodiesController::PrintAllBodies(std::istream & /*args*/)
{
    auto bodies = m_container.GetAllBodies();

    if (bodies.empty())
    {
        std::cout << "there are no announced bodies" << std::endl;
        return false;
    }

    auto it = std::begin(bodies);
    for (int i = 1; it != std::end(bodies); ++it, ++i)
    {
        m_output << i << ')' << (*it)->ToString();
    }
    return true;
}

bool CBodiesController::FindMaxWeight(std::istream & /*args*/)
{
    auto result = m_container.FindMaxWeight();
    if (!result)
    {
        std::cout << "there are no announced bodies" << std::endl;
        return false;
    }
    m_output << "max weight is " << result->weight << " newtons of body:\n" << (result->body)->ToString();
    return true;
}

bool CBodiesController::FindMinWeightInWater(std::istream & /*args*/)
{
    auto result = m_container.FindMinWeightInWater();
    if (!result)
    {
        std::cout << "there are no announced bodies" << std::endl;
        return false;
    }
    m_output << "min weight in water is " << result->weight << " newtons of body:\n" << (result->body)->ToString();
    return true;
}

bool CBodiesController::AddBodyToCompoundBody(std::istream &args)
{
    int compoundBodyIndex, compositeBodyIndex;
    if (args >> compoundBodyIndex >> compositeBodyIndex)
    {
        return m_container.AddBodyToCompoundBody(compoundBodyIndex - 1, compositeBodyIndex - 1);
    }
    return false;
}
