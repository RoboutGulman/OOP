// TemplateTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../catch/catch.hpp"
#include "../Date/Date.h"

SCENARIO("Initialize of date with day delta")
{
    WHEN("initializating date with zero delta")
    {
        Date date(0);
        THEN("it shows 1st of January 1970")
        {
            CHECK(date.GetDay() == 1);
            CHECK(date.GetMonth() == Date::Month::JANUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(date.IsValid());
        }
    }
    WHEN("initializating date without arguments")
    {
        Date date;
        THEN("it shows 1st of January 1970")
        {
            CHECK(date.GetDay() == 1);
            CHECK(date.GetMonth() == Date::Month::JANUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(date.IsValid());
        }
    }
    WHEN("initializating date with date as number")
    {
        Date date(32);
        THEN("it adding this delta to 1st of January 1970(in this case, it shows 2 February 1970)")
        {
            CHECK(date.GetDay() == 2);
            CHECK(date.GetMonth() == Date::Month::FEBRUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(date.IsValid());
        }
        Date date2(370);
        THEN("in this case, it shows 6 January 1971")
        {
            CHECK(date2.GetDay() == 6);
            CHECK(date2.GetMonth() == Date::Month::JANUARY);
            CHECK(date2.GetYear() == 1971);
            CHECK(date.IsValid());
        }
    }
    WHEN("try to create max date")
    {
        Date date(2932896);
        THEN("it shows correct date, 31.12.9999")
        {
            CHECK(date.GetDay() == 31);
            CHECK(date.GetMonth() == Date::Month::DECEMBER);
            CHECK(date.GetYear() == 9999);
            CHECK(date.IsValid());
        }
    }
    WHEN("try to overflow date")
    {
        Date date(2932897);
        THEN("it shows start date and not valid flag")
        {
            CHECK(date.GetDay() == 1);
            CHECK(date.GetMonth() == Date::Month::JANUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(!date.IsValid());
        }
    }
    WHEN("try to create date with negative delta")
    {
        Date date(-1);
        THEN("it shows start date and not valid flag")
        {
            CHECK(date.GetDay() == 1);
            CHECK(date.GetMonth() == Date::Month::JANUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(!date.IsValid());
        }
    }
}

SCENARIO("Initialize of date with day, month, year")
{
    WHEN("try to initialize date until 1st of January 1970")
    {
        Date date(31, Date::Month::DECEMBER, 1969);
        THEN("it shows start date and not valid flag")
        {
            CHECK(date.GetDay() == 1);
            CHECK(date.GetMonth() == Date::Month::JANUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(!date.IsValid());
        }
    }
    WHEN("initialize 1 Jan of 1970")
    {
        Date date(1, static_cast<Date::Month>(1), 1970);
        THEN("it shows correct date")
        {
            CHECK(date.GetDay() == 1);
            CHECK(date.GetMonth() == Date::Month::JANUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(date.IsValid());
        }
    }
    WHEN("initialize correct date")
    {
        Date date(16, static_cast<Date::Month>(4), 2020);
        THEN("it shows correct date")
        {
            CHECK(date.GetDay() == 16);
            CHECK(date.GetMonth() == Date::Month::APRIL);
            CHECK(date.GetYear() == 2020);
            CHECK(date.IsValid());
        }
    }
    WHEN("initialize max date")
    {
        Date date(31, Date::Month::DECEMBER, 9999);
        THEN("it shows correct date, 31.12.9999")
        {
            CHECK(date.GetDay() == 31);
            CHECK(date.GetMonth() == Date::Month::DECEMBER);
            CHECK(date.GetYear() == 9999);
            CHECK(date.IsValid());
        }
    }
    WHEN("initialize max date+1")
    {
        Date date(1, Date::Month::JANUARY, 10000);
        THEN("it shows start date and not valid flag")
        {
            CHECK(date.GetDay() == 1);
            CHECK(date.GetMonth() == Date::Month::JANUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(!date.IsValid());
        }
    }
    WHEN("initialize incorrect day for month")
    {
        Date date(31, Date::Month::APRIL, 2022);
        THEN("it shows start date and not valid flag")
        {
            CHECK(date.GetDay() == 1);
            CHECK(date.GetMonth() == Date::Month::JANUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(!date.IsValid());
        }
    }
    WHEN("initialize max correct day for month")
    {
        Date date(31, Date::Month::MAY, 2022);
        THEN("it shows start date and not valid flag")
        {
            CHECK(date.GetDay() == 31);
            CHECK(date.GetMonth() == Date::Month::MAY);
            CHECK(date.GetYear() == 2022);
            CHECK(date.IsValid());
        }
    }
}

SCENARIO("get week day function")
{
    WHEN("try to get a day of week of incorrect date")
    {
        Date date1(45, Date::Month::MAY, 2022);
        Date date2(1, Date::Month::DECEMBER, 1969);
        Date date3(1, Date::Month::JANUARY, 10000);
        THEN("it returns a Thursday because its a day of week of first date")
        {
            CHECK(date1.GetWeekDay() == Date::WeekDay::THURSDAY);
            CHECK(date2.GetWeekDay() == Date::WeekDay::THURSDAY);
            CHECK(date3.GetWeekDay() == Date::WeekDay::THURSDAY);
            CHECK(!date1.IsValid());
            CHECK(!date2.IsValid());
            CHECK(!date3.IsValid());
        }
    }
    WHEN("get week day for some date")
    {
        Date date(5, Date::Month::JULY, 2011);
        Date date2(2, Date::Month::DECEMBER, 1991);
        THEN("it returns a correct weekday")
        {
            CHECK(date.GetWeekDay() == Date::WeekDay::TUESDAY);
            CHECK(date2.GetWeekDay() == Date::WeekDay::MONDAY);
        }
    }
    WHEN("get week day for date on leap year")
    {
        Date date(5, Date::Month::JUNE, 2020);
        THEN("it returns a correct weekday")
        {
            CHECK(date.GetWeekDay() == Date::WeekDay::FRIDAY);
        }
    }
    WHEN("get week day for 2 dates with a difference of 7 days")
    {
        Date date(14, Date::Month::JANUARY, 1999);
        Date date1(14 + 7, Date::Month::JANUARY, 1999);
        THEN("it returns the same weekday")
        {
            CHECK(date.GetWeekDay() == date1.GetWeekDay());
        }
    }
    WHEN("get week day for seven consecutive dates")
    {
        Date date1(1, Date::Month::NOVEMBER, 2021);
        Date date2(2, Date::Month::NOVEMBER, 2021);
        Date date3(3, Date::Month::NOVEMBER, 2021);
        Date date4(4, Date::Month::NOVEMBER, 2021);
        Date date5(5, Date::Month::NOVEMBER, 2021);
        Date date6(6, Date::Month::NOVEMBER, 2021);
        Date date7(7, Date::Month::NOVEMBER, 2021);
        THEN("it returns all weekdays")
        {
            CHECK(date1.GetWeekDay() == Date::WeekDay::MONDAY);
            CHECK(date2.GetWeekDay() == Date::WeekDay::TUESDAY);
            CHECK(date3.GetWeekDay() == Date::WeekDay::WEDNESDAY);
            CHECK(date4.GetWeekDay() == Date::WeekDay::THURSDAY);
            CHECK(date5.GetWeekDay() == Date::WeekDay::FRIDAY);
            CHECK(date6.GetWeekDay() == Date::WeekDay::SATURDAY);
            CHECK(date7.GetWeekDay() == Date::WeekDay::SUNDAY);
        }
    }
    Date date(23, Date::Month::MAY, 2022);
    CHECK(date.GetWeekDay() == Date::WeekDay::MONDAY);
}

SCENARIO("increment and decrement operators(++ --)")
{
    WHEN("we use posfix form of increment")
    {
        Date date(1, Date::Month::NOVEMBER, 2021);
        date++;
        THEN("the date is increased by 1 day")
        {
            CHECK(date.GetDay() == 2);
        }
    }
    WHEN("we use posfix form of decrement")
    {
        Date date(2, Date::Month::NOVEMBER, 2021);
        date--;
        THEN("the date is reduced by 1 day")
        {
            CHECK(date.GetDay() == 1);
        }
    }
    WHEN("we use prefix form of increment")
    {
        Date date(1, Date::Month::NOVEMBER, 2021);
        date = ++date + 2;
        THEN("it return a link and can be modified in the future")
        {
            CHECK(date.GetDay() == 4);
        }
    }
    WHEN("we use prefix form of decrement")
    {
        Date date(4, Date::Month::NOVEMBER, 2021);
        date = --date - 2;
        THEN("it return a link and can be modified in the future")
        {
            CHECK(date.GetDay() == 1);
        }
    }
    WHEN("increment the unvalid date ")
    {
        Date date(1, Date::Month::NOVEMBER, 1600);
        date++;
        THEN("default value will not change")
        {
            CHECK(date.GetDay() == 1);
            CHECK(date.GetMonth() == Date::Month::JANUARY);
            CHECK(date.GetYear() == 1970);
            CHECK(!date.IsValid());
        }
    }
}

SCENARIO("reading from a stream(>>)")
{
    WHEN("input correct date from stream")
    {
        std::string input = "30.11.2010";
        Date date;
        std::istringstream strmIn(input);
        strmIn >> date;
        THEN("it allows correct values")
        {
            CHECK(date.GetDay() == 30);
            CHECK(date.GetMonth() == static_cast<Date::Month>(11));
            CHECK(date.GetYear() == 2010);
        }
    }
    WHEN("input correct date from stream there day and month are less than 10")
    {
        std::string input = "03.02.2010";
        Date date;
        std::istringstream strmIn(input);
        strmIn >> date;
        THEN("it allows correct values")
        {
            CHECK(date.GetDay() == 3);
            CHECK(date.GetMonth() == static_cast<Date::Month>(2));
            CHECK(date.GetYear() == 2010);
        }
    }
    WHEN("input incorrect date from stream")
    {
        std::string input = "44.11.2010";
        Date date;
        std::istringstream strmIn(input);
        strmIn >> date;
        THEN("we receive invalid date")
        {
            CHECK(!date.IsValid());
        }
    }
}

SCENARIO("ouptut to stream(<<)")
{
    WHEN("output correct date to stream")
    {
        Date date(30, static_cast<Date::Month>(11), 2010);
        std::ostringstream strmOut;
        strmOut << date;
        THEN("it display correctly")
        {
            CHECK(strmOut.str() == "30.11.2010");
        }
    }
    WHEN("output correct date to stream, there day and month are less than 10")
    {
        Date date(1, static_cast<Date::Month>(3), 2010);
        std::ostringstream strmOut;
        strmOut << date;
        THEN("it display correctly")
        {
            CHECK(strmOut.str() == "01.03.2010");
        }
    }
    WHEN("output incorrect date to stream")
    {
        Date date(44, static_cast<Date::Month>(11), 2010);
        std::ostringstream strmOut;
        strmOut << date;
        THEN("failbit error appears")
        {
            CHECK(strmOut.str() == "INVALID");
        }
    }
}

SCENARIO("summation and subtraction(+ - += -=)")
{
    WHEN("we sum up the date with the number of days")
    {
        Date date(28, Date::Month::FEBRUARY, 2010);
        date = date + 3;
        THEN("the date is increased")
        {
            CHECK(date.GetDay() == 3);
            CHECK(date.GetMonth() == Date::Month::MARCH);
            CHECK(date.GetYear() == 2010);
        }
    }
    WHEN("we subtract the number of days from the date")
    {
        Date date(3, Date::Month::MARCH, 2010);
        date = date - 3;
        THEN("the date is decreased")
        {
            CHECK(date.GetDay() == 28);
            CHECK(date.GetMonth() == Date::Month::FEBRUARY);
            CHECK(date.GetYear() == 2010);
        }
    }
    WHEN("we subtract the smaller date from the larger one")
    {
        Date date1(1, Date::Month::JANUARY, 2010);
        Date date2(30, Date::Month::DECEMBER, 2009);
        THEN("the result will be a difference between the dates in days")
        {
            CHECK(date1 - date2 == 2);
        }
    }
    WHEN("we subtract the larger date from the smaller one")
    {
        Date date1(1, Date::Month::JANUARY, 2010);
        Date date2(3, Date::Month::JANUARY, 2010);
        THEN("the result will be a difference between the dates in days. it can be less than 0")
        {
            CHECK(date1 - date2 == -2);
        }
    }
    WHEN("we substract the date from the same date")
    {
        Date date(1, Date::Month::JANUARY, 2010);
        THEN("the result will be 0")
        {
            CHECK(date - date == 0);
        }
    }
    WHEN("one of operators is the unvalid date")
    {
        Date date1(1, Date::Month::JANUARY, 1600);
        Date date2(3, Date::Month::JANUARY, 2010);
        THEN("the result will be 0")
        {
            CHECK(date1 - date2 == 0);
        }
    }
    WHEN("after substracting or adding date become unvalid")
    {
        Date date1(1, Date::Month::JANUARY, 1970);
        Date date2(31, Date::Month::DECEMBER, 9999);
        date1 = date1 - 3;
        date2 = date2 + 3;
        THEN("they become unvalid and display start date")
        {
            CHECK(!date1.IsValid());
            CHECK(!date2.IsValid());
            CHECK(date1.GetDay() == 1);
            CHECK(date2.GetDay() == 1);
            CHECK(date1.GetMonth() == Date::Month::JANUARY);
            CHECK(date2.GetMonth() == Date::Month::JANUARY);
            CHECK(date1.GetYear() == 1970);
            CHECK(date2.GetYear() == 1970);
        }
    }
    WHEN("+= is equivalent of +")
    {
        Date date(1, Date::Month::JANUARY, 2000);
        date += 3;
        CHECK(date.GetDay() == 4);
    }
    WHEN("-= is equivalent of -")
    {
        Date date(4, Date::Month::JANUARY, 2000);
        date -= 3;
        CHECK(date.GetDay() == 1);
    }
}

SCENARIO("checking the compare operators")
{
    WHEN("we compare 2 different dates")
    {
        Date date1(1, Date::Month::JANUARY, 2000);
        Date date2(4, Date::Month::JANUARY, 2000);
        THEN("the dates are not equal and one of them is more than the other")
        {
            CHECK(date1 != date2);
            CHECK(!(date1 == date2));
            CHECK(date1 < date2);
            CHECK(date2 > date1);
            CHECK(date2 >= date1);
            CHECK(date1 <= date2);
        }
    }
    WHEN("we compare 2 equal dates")
    {
        Date date1(4, Date::Month::JANUARY, 2000);
        Date date2(4, Date::Month::JANUARY, 2000);
        THEN("the dates are equal")
        {
            CHECK(!(date1 != date2));
            CHECK(date1 == date2);
            CHECK(!(date1 < date2));
            CHECK(!(date1 > date2));
            CHECK(!(date2 > date1));
            CHECK(!(date2 < date1));
            CHECK(date2 >= date1);
            CHECK(date1 <= date2);
        }
    }
    WHEN("we compare 2 dates and one is unvalid")
    {
        Date date1(4, Date::Month::JANUARY, 1600);
        Date date2(4, Date::Month::JANUARY, 2000);
        THEN("the dates are not equal and one of them is more than the other, invalid date display 1.01.1970")
        {
            CHECK(date1 != date2);
            CHECK(!(date1 == date2));
            CHECK(date1 < date2);
            CHECK(date2 > date1);
            CHECK(date2 >= date1);
            CHECK(date1 <= date2);
            CHECK(!date1.IsValid());
        }
    }
}
