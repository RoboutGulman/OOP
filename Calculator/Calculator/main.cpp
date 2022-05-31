#include "stdafx.h"

#include "Calculator.h"
#include "RemoteControl.h"

//сделать команду help
int main()
{
    Calculator calc;
    CRemoteControl remoteControl(calc, std::cin, std::cout);

    remoteControl.HandleCommands();

    return 0;
}
