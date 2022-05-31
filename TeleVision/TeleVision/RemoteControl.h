#pragma once
//���������� CTVSet.h ������ ������
class CTVSet;
//Remote Controller
class CRemoteControl
{
public:
	CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output);
	void HandleCommands();

private:
	bool HandleCommand();
	bool TurnOn(std::istream& args);
	bool TurnOff(std::istream& args);
	bool Info(std::istream& args);
	bool SelectChannel(std::istream& args);
	bool SelectPreviousChannel(std::istream& args);
private:
	// �������-���������� ������� ������������.
	// ���������� true, ���� ������� ���������� � false, ���� ���� ������
	using Handler = std::function<bool(std::istream& args)>;

	// ���������� �������� ������� �� � ����������
	using ActionMap = std::map<std::string, Handler>;

	CTVSet& m_tv;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};