// TemplateTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../Calculator/stdafx.h"

#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Calculator/Calculator.h"
#include "../Calculator/RemoteControl.h"

SCENARIO("declare variable.")
{
    Calculator calc;
    std::string i = "i";
    WHEN("we declare a variable")
    {
        calc.DeclareVariable(i);
        THEN("it saved on calculator")
        {
            CHECK(calc.IsVariable(i));
        }
    }
    WHEN("we declare a variable with name of already declared variable")
    {
        calc.DeclareVariable(i);
        bool result = calc.DeclareVariable(i);
        THEN("the command is ignored and error drops")
        {
            CHECK(result == false);
        }
    }
    WHEN("we declare a variable")
    {
        calc.DeclareVariable(i);
        THEN("this value is nullopt")
        {
            CHECK(calc.GetValueByIdentity(i) == std::nullopt);
        }
    }
}

SCENARIO("assign value to variable from number.")
{
    Calculator calc;
    std::string i = "i";
    calc.DeclareVariable(i);
    std::string undeclaredVar = "q";
    WHEN("try to assign value to undeclared variable")
    {
        THEN("the variable becomes declared")
        {
            //переименовать функцию, потому что она объ€вл€ет переменную
            CHECK(calc.DeclareVariableAndAssignValueFromNumber(undeclaredVar, 2.3) == true);
            CHECK(calc.GetValueByIdentity(undeclaredVar) == 2.3);
        }
    }
    WHEN("try to assign value to variable with value")
    {
        calc.DeclareVariableAndAssignValueFromNumber(i, 2.3);
        THEN("the variable get new value")
        {
            CHECK(calc.DeclareVariableAndAssignValueFromNumber(i, 4.56) == true);
            CHECK(calc.GetValueByIdentity(i) == 4.56);
        }
    }
    WHEN("assign a negative value to a variable")
    {
        calc.DeclareVariableAndAssignValueFromNumber(i, -4.8);
        THEN("the variable get correct value")
        {
            CHECK(calc.GetValueByIdentity(i) == -4.8);
        }
    }
}

SCENARIO("assign value to variable from variable.")
{
    Calculator calc;
    std::string firstVarName = "a";
    calc.DeclareVariable(firstVarName);
    std::string secondVarName = "b";
    calc.DeclareVariable(secondVarName);
    calc.DeclareVariableAndAssignValueFromNumber(firstVarName, 1.1);
    calc.DeclareVariableAndAssignValueFromNumber(secondVarName, 2.2);
    WHEN("try to assign new value to variable")
    {
        calc.DeclareVariableAndAssignValueFromEntity(firstVarName, secondVarName);
        THEN("the variable assign new value")
        {
            CHECK(calc.GetValueByIdentity(firstVarName) == 2.2);
        }
    }
    WHEN("try to assign value to undeclared variable")
    {
        std::string undeclaredVar = "c";
        calc.DeclareVariableAndAssignValueFromEntity(undeclaredVar, secondVarName);
        THEN("the variable now is declared and have new value")
        {
            CHECK(calc.GetValueByIdentity(undeclaredVar) == 2.2);
        }
    }
    WHEN("try to assign value from undeclared variable")
    {
        std::string undeclaredVar = "c";
        THEN("the command is ignored and error drops")
        {
            CHECK(calc.DeclareVariableAndAssignValueFromEntity(firstVarName, undeclaredVar) == false);
        }
    }
    WHEN("try to assign value from same variable")
    {
        calc.DeclareVariableAndAssignValueFromEntity(firstVarName, firstVarName);
        THEN("the value of the variable will not change")
        {
            CHECK(calc.GetValueByIdentity(firstVarName) == 1.1);
        }
    }
    WHEN("assign a value from second variable and then change second variable")
    {
        calc.DeclareVariableAndAssignValueFromEntity(firstVarName, secondVarName);
        CHECK(calc.GetValueByIdentity(firstVarName) == 2.2);
        calc.DeclareVariableAndAssignValueFromNumber(secondVarName, 3.3);
        THEN("the value of the first variable will change only in the first case")
        {
            CHECK(calc.GetValueByIdentity(firstVarName) == 2.2);
        }
    }
    WHEN("try to assign value from variable without value")
    {
        std::string thirdVarName = "c";
        calc.DeclareVariable(thirdVarName);
        THEN("the command is ignored and error drops")
        {
            //при присвоении из переменной без значени€ должно передаватьс€ nullopt
            CHECK(calc.DeclareVariableAndAssignValueFromEntity(firstVarName, thirdVarName) == true);
            CHECK(calc.GetValueByIdentity(firstVarName)==std::nullopt);
        }
    }
}

//вместить в сцеарий с функци€ми(офомить как отдельный given)
SCENARIO("assign value to variable from function.")
{
    Calculator calc;
    std::string firstVarName = "a";
    calc.DeclareVariable(firstVarName);
    std::string secondVarName = "b";
    calc.DeclareVariableAndAssignValueFromNumber(secondVarName, 2);
    std::string fuctionName = "A";
    WHEN("we declare variable and assing it a function value")
    {
        calc.DeclareFunction(fuctionName, secondVarName);
        calc.DeclareVariableAndAssignValueFromEntity(firstVarName, fuctionName);
        THEN("variable value equal to function value ")
        {
            CHECK(calc.GetValueByIdentity(firstVarName) == calc.GetValueByIdentity(fuctionName));
        }
        THEN("but if we change the value of the function, the value of the variable will not change")
        {
            calc.DeclareVariableAndAssignValueFromNumber(secondVarName, 4);
            CHECK(calc.GetValueByIdentity(fuctionName) == 4);
            CHECK(calc.GetValueByIdentity(firstVarName) == 2);
        }
    }
}

SCENARIO("functions")
{
    Calculator calc;
    std::string firstVarName = "a";
    calc.DeclareVariable(firstVarName);
    std::string secondVarName = "b";
    calc.DeclareVariable(secondVarName);
    calc.DeclareVariableAndAssignValueFromNumber(firstVarName, 4);
    calc.DeclareVariableAndAssignValueFromNumber(secondVarName, 5);
    std::string fuctionName = "A";
    WHEN("we declare fuction that returns the value of a single variable")
    {
        calc.DeclareFunction(fuctionName, firstVarName);
        THEN("it returns the value of this variable")
        {
            CHECK(calc.GetValueByIdentity(fuctionName) == calc.GetValueByIdentity(firstVarName));
        }
    }
    WHEN("we declare fuction that returns sum of two variables")
    {
        calc.DeclareFunction(fuctionName, firstVarName, secondVarName, OperationType::Addition);
        THEN("it returns the sum of two variables")
        {
            CHECK(calc.GetValueByIdentity(fuctionName) ==
                  *calc.GetValueByIdentity(firstVarName) + *calc.GetValueByIdentity(secondVarName));
        }
    }
    WHEN("we declare fuction that returns Subtraction of two variables")
    {
        calc.DeclareFunction(fuctionName, firstVarName, secondVarName, OperationType::Subtraction);
        THEN("it returns the subtraction of difference variables")
        {
            CHECK(calc.GetValueByIdentity(fuctionName) ==
                  *calc.GetValueByIdentity(firstVarName) - *calc.GetValueByIdentity(secondVarName));
        }
    }
    WHEN("we declare fuction that returns Division of two variables")
    {
        calc.DeclareFunction(fuctionName, firstVarName, secondVarName, OperationType::Division);
        THEN("it returns the Division of difference variables")
        {
            CHECK(calc.GetValueByIdentity(fuctionName) ==
                  *calc.GetValueByIdentity(firstVarName) / *calc.GetValueByIdentity(secondVarName));
        }
    }
    WHEN("we declare fuction that returns Division of two variables and second variable is 0")
    {
        calc.DeclareFunction(fuctionName, firstVarName, secondVarName, OperationType::Division);
        calc.DeclareVariableAndAssignValueFromNumber(secondVarName, 0);
        THEN("it returns nullopt")
        {
            //возвращать nullopt
            CHECK(calc.GetValueByIdentity(fuctionName) == std::nullopt);
        }
    }
    WHEN("we declare fuction that returns Multiplication of two variables")
    {
        calc.DeclareFunction(fuctionName, firstVarName, secondVarName, OperationType::Multiplication);
        THEN("it returns the Multiplication of difference variables")
        {
            CHECK(calc.GetValueByIdentity(fuctionName) ==
                  *calc.GetValueByIdentity(firstVarName) * *calc.GetValueByIdentity(secondVarName));
        }
    }
    WHEN("we declare fuction that contains another function")
    {
        std::string secondFunctionName = "B";
        calc.DeclareFunction(fuctionName, firstVarName, secondVarName, OperationType::Addition);
        calc.DeclareFunction(secondFunctionName, fuctionName, firstVarName, OperationType::Addition);
        THEN("it returns the sum of function and variable")
        {
            CHECK(calc.GetValueByIdentity(secondFunctionName) ==
                  *calc.GetValueByIdentity(fuctionName) + *calc.GetValueByIdentity(firstVarName));
        }
    }
}
//при необъ€вленной переменной в функии, функци€ возвращает null
// a=1 b=2 first=a+b second=second+first
//протестить GetAll variables and functions
SCENARIO("Declaration, assignment and output of variable values")
{
    std::string input = "var x\nprint x\nlet x=42\nprint x\nlet x=1.234\nprint x\nlet y=x\nlet x=99\nprintvars\nExit\n";
    Calculator calc;
    std::istringstream strmIn(input);
    std::ostringstream strmOut;
    CRemoteControl rc(calc, strmIn, strmOut);
    rc.HandleCommands();
    std::string s = strmOut.str();
    REQUIRE(s == "nan\n42.00\n1.23\nx:99.00\ny:1.23\n");
}

SCENARIO("Declaring functions")
{
    std::string input = "var x\nvar y\nfn XPlusY=x+y\nprint XPlusY\nlet x=3\nlet y=4\nprint XPlusY\nlet x=10\nprint "
                        "XPlusY\nlet z=3.5\nfn XPlusYDivZ=XPlusY/z\nprintfns\nExit\n";
    Calculator calc;
    std::istringstream strmIn(input);
    std::ostringstream strmOut;
    CRemoteControl rc(calc, strmIn, strmOut);
    rc.HandleCommands();
    std::string s = strmOut.str();
    REQUIRE(s == "nan\n7.00\n14.00\nXPlusY:14.00\nXPlusYDivZ:4.00\n");
}

SCENARIO("difference between fn and let")
{
    std::string input = "let v=42\nlet variable=v\nfn function=v\nlet v=43\nprint variable\nprint function\nExit";
    Calculator calc;
    std::istringstream strmIn(input);
    std::ostringstream strmOut;
    CRemoteControl rc(calc, strmIn, strmOut);
    rc.HandleCommands();
    std::string s = strmOut.str();
    REQUIRE(s == "42.00\n43.00\n");
}

SCENARIO("Calculating the area of a circle")
{
    std::string input =
        "var radius\nlet pi=3.14159265\nfn radiusSquared=radius*radius\nfn circleArea=pi*radiusSquared\nlet "
        "radius=10\nprint circleArea\nlet circle10Area=circleArea\nlet radius=20\nlet "
        "circle20Area=circleArea\nprintfns\nprintvars\nExit\n";
    Calculator calc;
    std::istringstream strmIn(input);
    std::ostringstream strmOut;
    CRemoteControl rc(calc, strmIn, strmOut);
    rc.HandleCommands();
    std::string s = strmOut.str();
    REQUIRE(s == "314.16\ncircleArea:1256.64\nradiusSquared:400.00\ncircle10Area:314.16\ncircle20Area:1256.64\npi:3."
                 "14\nradius:20.00\n");
}

/*SCENARIO("Calculating the Fibonacci sequence")
{
    std::string input =
        "let v0=0\nlet v1=1\nfn fib0=v0\nfn fib1=v1\nfn fib2=fib1+fib0\nfn fib3=fib2+fib1\nfn fib4=fib3+fib2\nfn "
        "fib5=fib4+fib3\nfn fib6=fib5+fib4\nprintfns\nlet v0=1\nlet v1=1\nprintfns\nExit\n";
    Calculator calc;
    std::istringstream strmIn(input);
    std::ostringstream strmOut;
    CRemoteControl rc(calc, strmIn, strmOut);
    rc.HandleCommands();
    std::string s = strmOut.str();
    REQUIRE(s == "fib0:0.00\nfib1:1.00\nfib2:1.00\nfib3:2.00\nfib4:3.00\nfib5:5.00\nfib6:8.00\nfib0:1.00\nfib1:1."
                 "00\nfib2:2.00\nfib3:3.00\nfib4:5.00\nfib5:8.00\nfib6:13.00\n ");
}*/
