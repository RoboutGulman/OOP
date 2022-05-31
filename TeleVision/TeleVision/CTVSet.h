#pragma once

struct Info
{
	bool isOn;
	int currentChannel;
};

class CTVSet
{
public:
	CTVSet();
	~CTVSet();
	void TurnCTVOn();
	void TurnCTVOff();
	bool SelectCTVChannel(int channel);
	void SelectCTVPreviousChannel();
	//name по конст ссылке
	void SetCTVChannelName(int number, std::string name);
	//void DeleteChannelName(int number);
	Info GetCTVInfo() const;
private:
	static const int MIN_CHANNEL = 1;
	static const int MAX_CHANNEL = 99;
	bool _isOn;
	int _currentChannel, _previousChannel;
	std::map <int, std::string> numberAndNameOfChannel;
	std::map <std::string, int> nameAndNumberOfChannel;
};
//минимальный канал в константу
//приватные свойства с  m_
