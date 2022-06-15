// TemplateTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "../StringStack/stdafx.h"

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../StringStack/CStackUnderflowError.h"
#include "../StringStack/CStringStack.h"
#include "../StringStack/stdafx.h"

SCENARIO("Creating stack")
{
    WHEN("we create stack with no arguments constructor")
    {
        CStringStack stack;

        THEN("it's size is 0")
        {
            CHECK(stack.Size() == 0);
        }

        THEN("it's empty")
        {
            CHECK(stack.Empty());
        }

        THEN("watch the top of stack throws error")
        {
            REQUIRE_THROWS_AS(stack.Top(), CStackUnderflowError);
        }

        THEN("trying to pop stack throws error")
        {
            REQUIRE_THROWS_AS(stack.Pop(), CStackUnderflowError);
        }
    }

    GIVEN("empty stack")
    {
        CStringStack originalStack;
        WHEN("creating a new steak by copying the original")
        {
            CStringStack newStack(originalStack);
            THEN("new stack is empty")
            {
                CHECK(newStack.Empty());
                CHECK(newStack.Size() == 0);
            }

            THEN("original stack is empty")
            {
                CHECK(originalStack.Empty());
                CHECK(originalStack.Size() == 0);
            }
        }
        WHEN("creating a new steak by moving the original")
        {
            CStringStack newStack(std::move(originalStack));
            THEN("new stack is empty")
            {
                CHECK(newStack.Empty());
                CHECK(newStack.Size() == 0);
            }

            THEN("original stack is empty")
            {
                CHECK(originalStack.Empty());
                CHECK(originalStack.Size() == 0);
            }
        }
    }

    GIVEN("stack with 1 value")
    {
        CStringStack originalStack;
        std::string value = "test value\n for string stack";
        originalStack.Push(value);
        WHEN("we create another stack with copy of original")
        {
            CStringStack copiedStack(originalStack);
            THEN("new stack will contain 1 value")
            {
                CHECK(copiedStack.Size() == 1);
            }

            THEN("this value equal to value in old stack")
            {
                CHECK(copiedStack.Top() == value);
            }

            THEN("the origignal stack didn't change")
            {
                CHECK(originalStack.Size() == 1);
                CHECK(originalStack.Top() == value);
            }
        }
        WHEN("we create another stack with copy of original and then change the original stack")
        {
            CStringStack copiedStack(originalStack);
            originalStack.Push("another test value");
            THEN("original stack now contain 2 values")
            {
                CHECK(originalStack.Size() == 2);
                CHECK(originalStack.Top() == "another test value");
            }

            THEN("but new stack didn't change")
            {
                CHECK(copiedStack.Size() == 1);
                CHECK(copiedStack.Top() == value);
            }
        }
        WHEN("moving to new stack")
        {
            CStringStack movedStack = std::move(originalStack);
            THEN("original stack is empty and it's size is 0")
            {
                CHECK(originalStack.Empty());
                CHECK(originalStack.Size() == 0);
            }

            THEN("new stack contain value of original stack")
            {
                CHECK(movedStack.Size() == 1);
                CHECK(movedStack.Top() == value);
            }
        }
    }

    GIVEN("stack with some values")
    {
        CStringStack originalStack;
        std::string value1 = "string";
        std::string value2 = "test string";
        std::string value3 = "test string for stack";
        originalStack.Push(value1);
        originalStack.Push(value2);
        originalStack.Push(value3);
        WHEN("we create another stack with copy of original")
        {
            CStringStack copiedStack(originalStack);
            THEN("new stack will contain 1 value")
            {
                CHECK(copiedStack.Size() == 3);
            }

            THEN("this value equal to value in old stack")
            {
                CHECK(copiedStack.Top() == value3);
            }

            THEN("the origignal stack didn't change")
            {
                CHECK(originalStack.Size() == 3);
                CHECK(originalStack.Top() == value3);
            }
        }
        WHEN("we create another stack with copy of original and then change the original stack")
        {
            CStringStack copiedStack(originalStack);
            originalStack.Push("another test value");
            THEN("original stack now contain 2 values")
            {
                CHECK(originalStack.Size() == 4);
                CHECK(originalStack.Top() == "another test value");
            }

            THEN("but new stack didn't change")
            {
                CHECK(copiedStack.Size() == 3);
                CHECK(copiedStack.Top() == value3);
            }
        }
        WHEN("moving to new stack")
        {
            CStringStack movedStack = std::move(originalStack);
            THEN("original stack is empty and it's size is 0")
            {
                CHECK(originalStack.Empty());
                CHECK(originalStack.Size() == 0);
            }

            THEN("new stack contain value of original stack")
            {
                CHECK(movedStack.Size() == 3);
                CHECK(movedStack.Top() == value3);
            }
        }
    }
}

SCENARIO("empty check")
{
    std::string value1 = "string";
    std::string value2 = "test string";
    std::string value3 = "test string for stack";
    GIVEN("empty stack")
    {
        CStringStack stack;
        WHEN("we do nothing with it")
        {
            THEN("it's empty")
            {
                CHECK(stack.Empty());
            }
        }
        WHEN("we push 1 value")
        {
            stack.Push(value1);
            THEN("it isn't empty")
            {
                CHECK(!stack.Empty());
            }
        }
        WHEN("we push and pop value")
        {
            stack.Push(value1);
            stack.Pop();
            THEN("it is still empty")
            {
                CHECK(stack.Empty());
            }
        }
        WHEN("we push 2 values and pop 1")
        {
            stack.Push(value1);
            stack.Push(value2);
            THEN("stack isn't empty")
            {
                CHECK(!stack.Empty());
            }
        }
        WHEN("we try to watck top of empty stack")
        {
            REQUIRE_THROWS_AS(stack.Top(), CStackUnderflowError);
            THEN("stack still empty")
            {
                CHECK(stack.Empty());
            }
        }
    }
}

SCENARIO("Push 1 value to stack")
{
    CStringStack stack;
    WHEN("we push the rvalue to stack")
    {
        stack.Push("test rvalue");
        THEN("it takes string correctly")
        {
            CHECK(stack.Top() == "test rvalue");
        }
    }
    WHEN("we push the lvalue to stack")
    {
        std::string lvalue = "test lvalue";
        stack.Push(lvalue);
        THEN("it takes string correctly")
        {
            CHECK(stack.Top() == lvalue);
        }
    }
    WHEN("we push the lvalue to stack and then change it")
    {
        std::string lvalue = "test lvalue";
        stack.Push(lvalue);

        std::string oldLvalue = lvalue;
        lvalue = "new test lvalue";

        THEN("value in stack will not change")
        {
            CHECK(stack.Top() != lvalue);
            CHECK(stack.Top() == oldLvalue);
        }
    }
}

SCENARIO("location of values in the stack")
{
    std::string value1 = "string";
    std::string value2 = "string test";
    std::string value3 = "test string for stack";
    GIVEN("empty stack")
    {
        CStringStack stack;
        WHEN("we push one value")
        {
            stack.Push(value1);
            THEN("top point on it")
            {
                CHECK(stack.Top() == value1);
            }
        }
        WHEN("we push some values")
        {
            stack.Push(value1);
            stack.Push(value2);
            auto top = stack.Top();
            stack.Push(value3);
            THEN("top point on last added value")
            {
                CHECK(stack.Size() == 3);
                CHECK(stack.Top() == value3);
                CHECK(top == value2);
            }
        }
        WHEN("We push and then pop 2 values")
        {
            stack.Push(value1);
            stack.Push(value2);
            auto pop1 = stack.Top();
            stack.Pop();
            auto pop2 = stack.Top();
            stack.Pop();
            THEN("the value that we placed last, we will get first")
            {
                CHECK(pop2 == value1);
            }
            THEN("the value that we placed first, we will get last")
            {
                CHECK(pop1 == value2);
            }
            THEN("stack is empty")
            {
                CHECK(stack.Empty());
                CHECK(stack.Size() == 0);
            }
        }
        WHEN("we push some values and then pop values from stack")
        {
            stack.Push(value1);
            stack.Push(value2);
            stack.Push(value3);
            auto pop1 = stack.Top();
            stack.Pop();
            auto pop2 = stack.Top();
            stack.Pop();
            auto pop3 = stack.Top();
            stack.Pop();
            THEN("the value that we placed last, we will get first")
            {
                CHECK(pop3 == value1);
            }
            THEN("the value that we placed second, we will get second")
            {
                CHECK(pop2 == value2);
            }
            THEN("the value that we placed first, we will get last")
            {
                CHECK(pop1 == value3);
            }
            THEN("stack is empty")
            {
                CHECK(stack.Empty());
                CHECK(stack.Size() == 0);
            }
        }
    }
}

SCENARIO("Clear Stack")
{
    GIVEN("empty stack")
    {
        CStringStack stack;
        WHEN("we clean it")
        {
            stack.Clear();
            THEN("it stays empty")
            {
                CHECK(stack.Empty());
            }
        }
    }
    GIVEN("stack with 1 value")
    {
        CStringStack stack;
        stack.Push("test value");
        WHEN("we clean it")
        {
            stack.Clear();
            THEN("it becomes empty")
            {
                CHECK(stack.Empty());
                CHECK(stack.Size() == 0);
            }
        }
    }
    GIVEN("stack with some values")
    {
        CStringStack stack;
        stack.Push("test value");
        stack.Push("another test value");
        stack.Push("more test value");
        WHEN("we clean it")
        {
            stack.Clear();
            THEN("it becomes empty")
            {
                CHECK(stack.Empty());
                CHECK(stack.Size() == 0);
            }
        }
    }
}

SCENARIO("equalization operator")
{
    std::string value1 = "string";
    std::string value2 = "string test";
    std::string value3 = "test string for stack";
    GIVEN("empty stack and stack with 1 value")
    {
        CStringStack recieverStack;
        CStringStack giverStack;
        giverStack.Push(value1);
        WHEN("we equate an empty stack to a non-empty one")
        {
            recieverStack = giverStack;
            THEN("reciever stack become copy of giver")
            {
                CHECK(!recieverStack.Empty());
                CHECK(recieverStack.Size() == 1);
                CHECK(recieverStack.Top() == value1);
            }
            THEN("giver stack didn't change")
            {
                CHECK(!giverStack.Empty());
                CHECK(giverStack.Size() == 1);
                CHECK(giverStack.Top() == value1);
            }
        }
        WHEN("we equate an empty stack to a non-empty one and then change any of them")
        {
            recieverStack = giverStack;
            recieverStack.Push(value2);
            THEN("the reciever stack changed")
            {
                CHECK(!recieverStack.Empty());
                CHECK(recieverStack.Size() == 2);
                CHECK(recieverStack.Top() == value2);
            }
            THEN("the giver stackdidn't change")
            {
                CHECK(!giverStack.Empty());
                CHECK(giverStack.Size() == 1);
                CHECK(giverStack.Top() == value1);
            }
        }
        WHEN("we equate an non-empty stack to a empty one")
        {
            giverStack = recieverStack;
            THEN("both stacks is empty")
            {
                CHECK(giverStack.Empty());
                CHECK(recieverStack.Empty());
            }
        }
    }
}
