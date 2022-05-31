// StringReverser_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include <sstream>
#include "../../catch/catch.hpp"

#include "../StringReverser/Reverse.h"

SCENARIO("Reversing of empty string gives an empty string")
{
	REQUIRE(Reverse("").empty());
}

SCENARIO("Reverse of string of 1 character is the string itself")
{
	REQUIRE(Reverse("a") == "a");
}

SCENARIO("Reverse of string longer than 1 character")
{
	REQUIRE(Reverse("1234") == "4321");
}

SCENARIO("ReverseLines")
{
	std::ostringstream output;
	WHEN("input stream is empty")
	{
		std::istringstream input("");
		
		THEN("output stream is also empty")
		{
			ReverseLines(input, output);
			CHECK(output.str().empty());
			CHECK(input.eof());
		}
	}

	WHEN("input stream contains one line")
	{
		std::istringstream input("1 line");
		THEN("output stream contains the line reversed")
		{
			ReverseLines(input, output);
			CHECK(output.str() == "enil 1");
			CHECK(input.eof());
		}
	}
	WHEN("input stream contains several lines")
	{
		std::istringstream input("1 line\n2line");
		THEN("output stream contains several lines reversed")
		{
			ReverseLines(input, output);
			CHECK(output.str() == "enil 1\nenil 2");
			CHECK(input.eof());
		}
	}
}