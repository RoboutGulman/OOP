#include "../TeleVision/stdafx.h"

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../TeleVision/CTVSet.h"
#include "../TeleVision/RemoteControl.h"

SCENARIO("When creating, the TV is turned off and current channel = 0")
{
    CTVSet teleVision;
    REQUIRE(teleVision.GetCTVInfo().isOn == false);
    REQUIRE(teleVision.GetCTVInfo().currentChannel == 0);
}

SCENARIO("Turning on.")
{
    CTVSet teleVision;
    WHEN("we turning on offed TV")
    {
        teleVision.TurnCTVOn();

        THEN("it turning on and starts show 1st channel")
        {
            CHECK(teleVision.GetCTVInfo().isOn == true);
            CHECK(teleVision.GetCTVInfo().currentChannel == 1);
        }
    }
    WHEN("we turning on TV already turned on")
    {
        teleVision.TurnCTVOn();
        teleVision.TurnCTVOn();
        THEN("it remains enabled")
        {
            CHECK(teleVision.GetCTVInfo().isOn == true);
        }
    }
}

SCENARIO("Turning off.")
{
    CTVSet teleVision;
    teleVision.TurnCTVOn();
    WHEN("we turning off TV on")
    {
        teleVision.TurnCTVOff();

        THEN("it turning off")
        {
            CHECK(teleVision.GetCTVInfo().isOn == false);
        }
    }
    WHEN("we turning off TV turned off")
    {
        teleVision.TurnCTVOff();
        teleVision.TurnCTVOff();
        THEN("it remains disabled")
        {
            CHECK(teleVision.GetCTVInfo().isOn == false);
        }
    }
    //вынести вверх
    WHEN("we select channel and turning off TV")
    {
        teleVision.SelectCTVChannel(10);
        teleVision.TurnCTVOff();
        THEN("it shows 0 channel")
        {
            CHECK(teleVision.GetCTVInfo().currentChannel == 0);
        }
    }
}

SCENARIO("SelectChannel.")
{
    CTVSet teleVision;
    WHEN("we select channel on disabled TV")
    {
        teleVision.SelectCTVChannel(3);
        THEN("it still shows 0")
        {
            CHECK(teleVision.GetCTVInfo().currentChannel == 0);
        }
    }
    WHEN("we select channel on TV turned on")
    {
        teleVision.TurnCTVOn();
        WHEN("we select channel between 1 and 99")
        {
            teleVision.SelectCTVChannel(3);
            THEN("it starts show this channel")
            {
                CHECK(teleVision.GetCTVInfo().currentChannel == 3);
            }
        }
        WHEN("we select channel more than 99 or less than 1")
        {
            teleVision.SelectCTVChannel(5);
            teleVision.SelectCTVChannel(100);
            THEN("it stays on the previous channel")
            {
                CHECK(teleVision.GetCTVInfo().currentChannel == 5);
                teleVision.SelectCTVChannel(0);
                CHECK(teleVision.GetCTVInfo().currentChannel == 5);
            }
        }
    }
}

//при переходе на прошлый канал текущий становится предыдущим
SCENARIO("Select previous channel.")
{
    CTVSet teleVision;
    teleVision.TurnCTVOn();
    WHEN("we moving to previous channel after first turning on TV ")
    {
        teleVision.SelectCTVPreviousChannel();
        THEN("it stayed on selected channel")
        {
            CHECK(teleVision.GetCTVInfo().currentChannel == 1);
        }
    }
    WHEN("we select channel after selecting another channel and moving to previous channel")
    {
        teleVision.SelectCTVChannel(5);
        teleVision.SelectCTVChannel(7);
        teleVision.SelectCTVPreviousChannel();
        THEN("it select to previous channel")
        {
            CHECK(teleVision.GetCTVInfo().currentChannel == 5);
        }
    }
    WHEN("we moving to previous channel after turning off and turning on TV")
    {
        teleVision.SelectCTVChannel(5);
        teleVision.SelectCTVChannel(7);
        teleVision.TurnCTVOff();
        teleVision.TurnCTVOn();
        teleVision.SelectCTVPreviousChannel();
        THEN("it select to previous channel")
        {
            CHECK(teleVision.GetCTVInfo().currentChannel == 5);
        }
    }
    WHEN("we select same channel 2 or more times")
    {
        teleVision.SelectCTVChannel(5);
        teleVision.SelectCTVChannel(7);
        teleVision.SelectCTVChannel(7);
        teleVision.SelectCTVPreviousChannel();
        THEN("TV will not overwrite previous channel")
        {
            CHECK(teleVision.GetCTVInfo().currentChannel == 5);
        }
    }
    WHEN("we move on previous channel more than 2 times")
    {
        teleVision.SelectCTVChannel(5);
        teleVision.SelectCTVChannel(7);
        teleVision.SelectCTVPreviousChannel();
        CHECK(teleVision.GetCTVInfo().currentChannel == 5);
        teleVision.SelectCTVPreviousChannel();
        THEN("TV will return to first channel")
        {
            CHECK(teleVision.GetCTVInfo().currentChannel == 7);
        }
    }
}

SCENARIO("Remote Control")
{
    CTVSet tv;
    std::ostringstream strmOut;

    WHEN("we try to select channel on turned on TV")
    {
        std::string input = "TurnOn\nSelectChannel 56\nInfo\nExit\n";

        std::istringstream strmIn(input);
        CRemoteControl rc(tv, strmIn, strmOut);
        rc.HandleCommands();
        std::string out = strmOut.str();
        THEN("Remote Control outputs 56 channel")
        {
            CHECK(out == "TV is turned on\nSelect Channel 56\nTV is turned on\nChannel is: 56\n");
        }
    }
    WHEN("we try to see info on turned off TV")
    {
        std::string input = "TurnOn\nSelectChannel 56\nTurnOff\nInfo\nExit\n";

        std::istringstream strmIn(input);
        CRemoteControl rc(tv, strmIn, strmOut);
        rc.HandleCommands();
        std::string out = strmOut.str();
        THEN("Remote Control outputs that TV is turned off")
        {
            CHECK(out == "TV is turned on\nSelect Channel 56\nTV is turned off\nTV is turned off\n");
        }
    }
    WHEN("we try to select Previous Channel")
    {
        std::string input = "TurnOn\nSelectChannel 56\nSelectChannel 1\nPreviousChannel\nInfo\nExit\n";

        std::istringstream strmIn(input);
        CRemoteControl rc(tv, strmIn, strmOut);
        rc.HandleCommands();
        std::string out = strmOut.str();
        THEN("TV move onto previous channel")
        {
            CHECK(out == "TV is turned on\nSelect Channel 56\nSelect Channel 1\nPrevious channel selected\nTV is turned on\nChannel is: 56\n");
        }
    }
}
