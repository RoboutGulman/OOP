#include "stdafx.h"

#include "CTVSet.h"
#include "RemoteControl.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet &tv, std::istream &input, std::ostream &output)
    : m_tv(tv), m_input(input), m_output(output),
      m_actionMap({
    //привести к единому виду, как в TurnOn
          {"TurnOn", [this](istream &strm) { return TurnOn(strm); }},
          {"TurnOff", bind(&CRemoteControl::TurnOff, this, std::placeholders::_1)},
          {"Info", bind(&CRemoteControl::Info, this, _1)},
          {"SelectChannel", bind(&CRemoteControl::SelectChannel, this, _1)},
          {"PreviousChannel", bind(&CRemoteControl::SelectPreviousChannel, this, _1)},
      })
{
}

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

    //сделать Exit одной из команд в actionMap
    if (action == "Exit")
    {
        return false;
    }

    m_output << "Unknown command!" << endl;
    return true;
}

void CRemoteControl::HandleCommands()
{
    //cin to m_input
    while (!cin.eof() && !cin.fail())
    {
        cout << "> ";
        if (!HandleCommand())
        {
            return;
        }
    }
    return;
}

bool CRemoteControl::TurnOn(std::istream &strm /*args*/)
{
    m_tv.TurnCTVOn();
    m_output << "TV is turned on\n";
    return true;
}

bool CRemoteControl::TurnOff(std::istream & /*args*/)
{
    m_tv.TurnCTVOff();
    m_output << "TV is turned off\n";
    return true;
}

bool CRemoteControl::SelectChannel(std::istream &args)
{
    string argument;
    int number = 0;
    try
    {
        args >> argument;
        number = std::stoi(argument);
    }
    catch (const std::exception &error)
    {
        m_output << error.what() << ". Argument must be integer" << std::endl;
        return false;
    }

    if (!m_tv.SelectCTVChannel(number))
    {
        return false;
    }
    m_output << "Select Channel " << argument << '\n';
    return true;
}

bool CRemoteControl::SelectPreviousChannel(std::istream & /*args*/)
{
    m_tv.SelectCTVPreviousChannel();
    m_output << "Previous channel selected\n";
    return true;
}

bool CRemoteControl::Info(std::istream & /*args*/)
{
    auto info = m_tv.GetCTVInfo();
    info.isOn ? m_output << "TV is turned on\nChannel is: " << info.currentChannel << "\n"
              : m_output << "TV is turned off\n";
    return true;
}
