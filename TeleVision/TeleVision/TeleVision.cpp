#include "stdafx.h"

#include "CTVSet.h"
#include "RemoteControl.h"

//std �� ������������
int main()
{
    CTVSet tv;
    CRemoteControl remoteControl(tv, std::cin, std::cout);

    remoteControl.HandleCommands();

    return 0;
}
