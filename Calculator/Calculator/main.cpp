#include "stdafx.h"

#include "Calculator.h"
#include "RemoteControl.h"

//������� ������� help
int main()
{
    Calculator calc;
    CRemoteControl remoteControl(calc, std::cin, std::cout);

    remoteControl.HandleCommands();

    return 0;
}
