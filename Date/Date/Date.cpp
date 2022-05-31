#include "stdafx.h"

#include "Date.h"

#include <sstream>
#include <string>

const long LOWER_COUNTER_BOUND = 0;       // 01.01.1970
const long UPPER_COUNTER_BOUND = 2932896; // 31.12.9999

bool DateIsValid(unsigned day, Date::Month month, unsigned year);
unsigned ConvertDateInfoToTimeStamp(unsigned day, Date::Month month, unsigned year);

Date::Date(unsigned day, Month month, unsigned year)
    : m_dayCounter(LOWER_COUNTER_BOUND), m_monthDay(day), m_month(month), m_year(year),
      m_isValidState(DateIsValid(day, month, year))
{
    if (IsValid())
    {
        m_dayCounter = ConvertDateInfoToTimeStamp(day, month, year);
    }
    else
    {
        SetInvalidState();
    }
}

Date::Date(unsigned timestamp)
    : m_dayCounter(timestamp), m_monthDay(std::nullopt), m_month(std::nullopt), m_year(std::nullopt),
      m_isValidState(timestamp <= UPPER_COUNTER_BOUND)
{
    if (!IsValid())
    {
        SetInvalidState();
    }
}

bool Date::IsValid() const
{
    return m_isValidState;
}

bool IsYearLeap(unsigned year)
{
    return (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
}

const unsigned START_YEAR = 1970;
const unsigned END_YEAR = 9999;
const Date::Month START_MONTH = Date::Month(1);
const int START_MONTH_DAY = 1;

void Date::SetInvalidState()
{
    if (m_isValidState)
    {
        m_dayCounter = LOWER_COUNTER_BOUND;
        m_year.emplace(START_YEAR);
        m_month.emplace(START_MONTH);
        m_monthDay.emplace(START_MONTH_DAY);
        m_isValidState = false;
    }
}

unsigned Date::GetYear() const
{
    if (!IsValid())
    {
        return START_YEAR;
    }

    if (!m_year.has_value())
    {
        CalculateDate();
    }

    return *m_year;
}

Date::Month Date::GetMonth() const
{
    if (!IsValid())
    {
        return START_MONTH;
    }

    if (!m_month.has_value())
    {
        CalculateDate();
    }

    return *m_month;
}

unsigned Date::GetDay() const
{
    if (!IsValid())
    {
        return START_MONTH_DAY;
    }

    if (!m_monthDay.has_value())
    {
        CalculateDate();
    }

    return *m_monthDay;
}

const Date::WeekDay START_WEEK_DAY = Date::WeekDay(4);
Date::WeekDay DayOfWeek(unsigned day, Date::Month month, unsigned year);

Date::WeekDay Date::GetWeekDay() const
{
    if (!IsValid())
    {
        return START_WEEK_DAY;
    }

    if (!m_year.has_value() || !m_month.has_value() || !m_monthDay.has_value())
    {
        CalculateDate();
    }

    return DayOfWeek(*m_monthDay, *m_month, *m_year);
}

const int START_MONTH_INDEX = 1;
const int END_MONTH_INDEX = 12;

const std::vector<unsigned> DAYS_TO_MONTH_365 = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
const std::vector<unsigned> DAYS_TO_MONTH_366 = {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};

unsigned ConvertDateInfoToTimeStamp(unsigned day, Date::Month month, unsigned year)
{
    const int providedMonthIndex = static_cast<int>(month);
    bool isProvidedYearLeap = IsYearLeap(year);
    const std::vector<unsigned> *daysToMonth = isProvidedYearLeap ? &DAYS_TO_MONTH_366 : &DAYS_TO_MONTH_365;

    if (!DateIsValid(day, month, year))
    {
        return 0;
    }

    unsigned counter = LOWER_COUNTER_BOUND;
    unsigned yearPassed = year;
    short monthIndex = END_MONTH_INDEX;

    while (yearPassed >= START_YEAR)
    {
        daysToMonth = IsYearLeap(yearPassed) ? &DAYS_TO_MONTH_366 : &DAYS_TO_MONTH_365;
        counter += (*daysToMonth)[monthIndex];

        if (yearPassed == START_YEAR)
        {
            counter -= (*daysToMonth)[monthIndex];
            counter += (*daysToMonth)[static_cast<size_t>(providedMonthIndex - 1)];
            counter += isProvidedYearLeap && static_cast<int>(month) <= 2 ? day - 2 : day - 1;
        }
        --yearPassed;
    }

    return counter;
}

bool DateIsValid(unsigned day, Date::Month month, unsigned year)
{
    const int monthIndex = static_cast<int>(month);
    const std::vector<unsigned> *daysToMonth = IsYearLeap(year) ? &DAYS_TO_MONTH_366 : &DAYS_TO_MONTH_365;

    const size_t daysInMonth = (*daysToMonth)[monthIndex] - (*daysToMonth)[static_cast<size_t>(monthIndex - 1)];
    if (day == 0 || day > daysInMonth || year < START_YEAR || year > END_YEAR || monthIndex < START_MONTH_INDEX ||
        monthIndex > END_MONTH_INDEX)
    {
        return false;
    }

    if (day > (*daysToMonth)[monthIndex] - (*daysToMonth)[static_cast<size_t>(monthIndex - 1)])
    {
        return false;
    }
    return true;
}

Date::WeekDay DayOfWeek(unsigned day, Date::Month month, unsigned year)
{
    if (!DateIsValid(day, month, year))
    {
        return START_WEEK_DAY;
    }

    //константа для алгоритма Томохико Сакамото
    const std::vector<int> MONTH_TABLE = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

    const int monthIndex = static_cast<int>(month);

    if (monthIndex < 3)
    {
        year -= 1;
    }

    //сам алгоритм
    return Date::WeekDay(
        (year + year / 4 - year / 100 + year / 400 + MONTH_TABLE[static_cast<size_t>(monthIndex - 1)] + day) % 7);
}

//сделать проще(чтобы не было итераций цикла)
void Date::CalculateDate() const
{
    if (m_dayCounter == 0)
    {
        m_year.emplace(START_YEAR);
        m_month.emplace(START_MONTH);
        m_monthDay.emplace(START_MONTH_DAY);
        return;
    }

    long counter = LOWER_COUNTER_BOUND;

    short monthIndex = END_MONTH_INDEX;
    long year = START_YEAR - 1;
    long mem = 0, day = 0;
    const std::vector<unsigned> *daysToMonth = &DAYS_TO_MONTH_365;
    while (counter < m_dayCounter)
    {
        ++year;
        daysToMonth = IsYearLeap(year) ? &DAYS_TO_MONTH_366 : &DAYS_TO_MONTH_365;

        counter += (*daysToMonth)[monthIndex];
        if (counter == m_dayCounter)
        {
            day = 1;
            monthIndex = 0;
            ++year;
            break;
        }
        while (counter > m_dayCounter)
        {
            --monthIndex;
            counter -= (*daysToMonth)[static_cast<size_t>(monthIndex + 1)] - (*daysToMonth)[monthIndex];
            if (counter <= m_dayCounter)
            {
                mem = counter - 1;
            }
            while (counter < m_dayCounter)
            {
                ++counter;
            }
            day = counter - mem;
        }
    }
    if (monthIndex != 12)
    {
        ++monthIndex;
    }

    m_year.emplace(year);
    m_month.emplace(Month(monthIndex));
    m_monthDay.emplace(day);
}

Date Date::operator++(int)
{
    Date tempDate(*this);
    ++*this;
    return tempDate;
}

Date &Date::operator++()
{
    if (!IsValid())
    {
        return *this;
    }

    ++m_dayCounter;

    CalculateDate();

    if (!DateIsValid(*m_monthDay, *m_month, *m_year))
    {
        SetInvalidState();
    }

    return *this;
}

Date Date::operator--(int)
{
    Date tempDate(*this);
    --*this;
    return tempDate;
}

Date &Date::operator--()
{
    if (!IsValid())
    {
        return *this;
    }

    --m_dayCounter;

    CalculateDate();

    if (!DateIsValid(*m_monthDay, *m_month, *m_year))
    {
        SetInvalidState();
    }

    return *this;
}

Date operator+(const Date &date, unsigned day)
{
    if (!date.IsValid())
    {
        return date;
    }

    Date tempDate(date);
    tempDate.m_dayCounter += day;

    tempDate.CalculateDate();

    if (!DateIsValid(*tempDate.m_monthDay, *tempDate.m_month, *tempDate.m_year))
    {
        tempDate.SetInvalidState();
    }

    return tempDate;
}

Date operator+(unsigned day, const Date &date)
{
    return date + day;
}

Date operator-(const Date &date, unsigned day)
{
    if (!date.IsValid())
    {
        return date;
    }

    Date tempDate(date);
    tempDate.m_dayCounter -= day;

    tempDate.CalculateDate();

    if (!DateIsValid(*tempDate.m_monthDay, *tempDate.m_month, *tempDate.m_year))
    {
        tempDate.SetInvalidState();
    }

    return tempDate;
}

long operator-(const Date &date1, const Date &date2)
{
    if (!date1.IsValid() || !date2.IsValid())
    {
        return 0;
    }

    return date1.m_dayCounter - date2.m_dayCounter;
}

Date &Date::operator+=(unsigned day)
{
    *this = *this + day;
    return *this;
}

Date &Date::operator-=(unsigned day)
{
    *this = *this - day;
    return *this;
}

bool Date::operator==(const Date &other) const
{
    return m_dayCounter == other.m_dayCounter;
}

bool Date::operator!=(const Date &other) const
{
    return m_dayCounter != other.m_dayCounter;
}

bool Date::operator<(const Date &other) const
{
    return m_dayCounter < other.m_dayCounter;
}

bool Date::operator>(const Date &other) const
{
    return m_dayCounter > other.m_dayCounter;
}

bool Date::operator<=(const Date &other) const
{
    return m_dayCounter <= other.m_dayCounter;
}

bool Date::operator>=(const Date &other) const
{
    return m_dayCounter >= other.m_dayCounter;
}

constexpr auto DELIMETER = '.';

std::ostream &operator<<(std::ostream &os, Date &date)
{
    if (os.fail() || os.bad())
    {
        return os;
    }

    if (!date.IsValid())
    {
        os << "INVALID";
        return os;
    }

    unsigned day = date.GetDay();
    unsigned month = static_cast<unsigned>(date.GetMonth());
    os << (day >= 10 ? "" : "0") << day << DELIMETER << (month >= 10 ? "" : "0") << month << DELIMETER
       << date.GetYear();
    return os;
}

Date ParseStringToDate(const std::string &str)
{
    std::stringstream ss{str}, ssBuffer{};
    std::string buffer;
    std::getline(ss, buffer, DELIMETER);
    ssBuffer << buffer;

    unsigned day;
    if (!(ssBuffer >> day))
    {
        return Date(START_MONTH_DAY - 1, START_MONTH, START_YEAR - 1);
    }
    ssBuffer.str("");
    ssBuffer.clear();

    std::getline(ss, buffer, DELIMETER);
    ssBuffer << buffer;
    unsigned m;
    if (!(ssBuffer >> m))
    {
        return Date(START_MONTH_DAY - 1, START_MONTH, START_YEAR - 1);
    }
    ssBuffer.str("");
    ssBuffer.clear();
    ssBuffer.flush();

    unsigned year;
    if (!(ss >> year))
    {
        return Date(START_MONTH_DAY - 1, START_MONTH, START_YEAR - 1);
    }

    return Date(day, Date::Month(m), year);
}

std::istream &operator>>(std::istream &is, Date &date)
{
    std::istream::sentry sentry(is);
    if (!sentry)
    {
        return is;
    }

    std::string str;
    is >> str;

    date = ParseStringToDate(str);

    if (!date.IsValid())
    {
        is.setstate(std::ios_base::failbit | is.rdstate());
        return is;
    }

    return is;
}
