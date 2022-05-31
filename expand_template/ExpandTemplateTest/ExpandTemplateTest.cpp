// ExpandTemplateTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch/catch.hpp"
#include <sstream>

#include "../ExpandTemplate/Expand.h"
//заменить подстроку на др. подстроку
//заменить строку на себя саму
SCENARIO("when expanding a string, new symbol will not be replaced")
{
    InitBohr();
    std::string const tpl = "abbc";
    Dictionary params;
    params["a"] = "ab";
    params["bb"] = "h";
    params["bbbc"] = "z";
    AddParamsToBohr(params);
    REQUIRE(ExpandTemplate(tpl, params) == "abhc");
}

SCENARIO("an already changed symbol will not be replaced")
{
    InitBohr();
    std::string const tpl = "a";
    Dictionary params;
    params["a"] = "b";
    params["b"] = "z";
    AddParamsToBohr(params);
    REQUIRE(ExpandTemplate(tpl, params) == "b");
}

//очень ограниченный алфавит, надо тестить и менять
//не поддерживает заглавные бувкы, пробелы

SCENARIO("1st example")
{
    InitBohr();
    std::string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
    Dictionary params;
    params["%USER_NAME%"] = "Ivan Petrov";
    params["{WEEK_DAY}"] = "Friday";
    AddParamsToBohr(params);
    REQUIRE(ExpandTemplate(tpl, params) == "Hello, Ivan Petrov. Today is Friday.");
}

//проверить несколько вхождений. отсутствие вхождений. замена на пустую строку. замена пустой
SCENARIO("2nd example")
{
    InitBohr();
    std::string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
    Dictionary params;
    params["%USER_NAME%"] = "Super %USER_NAME% {WEEK_DAY}";
    params["{WEEK_DAY}"] = "Friday. {WEEK_DAY}";
    AddParamsToBohr(params);
    REQUIRE(ExpandTemplate(tpl, params) == "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.");
}

SCENARIO("3rd example")
{
    InitBohr();
    std::string const tpl = "-AABBCCCCCABC+";
    Dictionary params;
    params["A"] = "[a]";
    params["AA"] = "[aa]";
    params["B"] = "[b]";
    params["BB"] = "[bb]";
    params["C"] = "[c]";
    params["CC"] = "[cc]";
    AddParamsToBohr(params);
    REQUIRE(ExpandTemplate(tpl, params) == "-[aa][bb][cc][cc][c][a][b][c]+");
}
