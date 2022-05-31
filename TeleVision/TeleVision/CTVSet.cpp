#include "stdafx.h"

#include "CTVSet.h"

CTVSet::CTVSet() : _isOn(false), _currentChannel(0), _previousChannel(0)
{
}

CTVSet::~CTVSet()
{
}

Info CTVSet::GetCTVInfo() const
{
    if (!_isOn)
    {
        return {_isOn, 0};
    }

    return {_isOn, _currentChannel};
}

void CTVSet::TurnCTVOn()
{
    _isOn = true;

    if (!_currentChannel)
    {
        _currentChannel = 1;
    }
}

void CTVSet::TurnCTVOff()
{
    _isOn = false;
}

bool CTVSet::SelectCTVChannel(int channel)
{
    if (_isOn && channel >= MIN_CHANNEL && channel <= MAX_CHANNEL && channel != _currentChannel)
    {
        _previousChannel = _currentChannel;
        _currentChannel = channel;
        return true;
    }
    return false;
}

void CTVSet::SelectCTVPreviousChannel()
{
    if (_isOn && _previousChannel != 0)
    {
        auto temp = _currentChannel;
        _currentChannel = _previousChannel;
        _previousChannel = temp;
    }
}

void CTVSet::SetCTVChannelName(int number, std::string name)
{
    numberAndNameOfChannel[number] = name;
    nameAndNumberOfChannel[name] = number;
}
