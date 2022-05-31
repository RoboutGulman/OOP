#pragma once

#include <optional>
#include <vector>

class Date
{
  public:
    enum class Month
    {
        JANUARY = 1,
        FEBRUARY,
        MARCH,
        APRIL,
        MAY,
        JUNE,
        JULY,
        AUGUST,
        SEPTEMBER,
        OCTOBER,
        NOVEMBER,
        DECEMBER,
    };

    enum class WeekDay
    {
        SUNDAY = 0,
        MONDAY,
        TUESDAY,
        WEDNESDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
    };
    // инициализируем дату заданными днем, мес€цем и годом.
    explicit Date(unsigned day, Month month, unsigned year);
    // инициализируем дату количеством дней, прошедших после 1 €нвар€ 1970 года
    explicit Date(unsigned timestamp = 0);

    // возвращает день мес€ца (от 1 до 31)
    unsigned GetDay() const;
    // возвращает мес€ц
    Month GetMonth() const;
    // возвращает год
    unsigned GetYear() const;
    // возвращает день недели
    //переделать через деление на 7 и вычисление остатка
    WeekDay GetWeekDay() const;
    // возвращает информацию о корректности хранимой даты
    bool IsValid() const;

    //постфиксна€ форма
    Date operator++(int);
    //префиксна€ форма
    Date &operator++();
    Date operator--(int);
    Date &operator--();
    friend Date operator+(const Date &date, unsigned day);
    friend Date operator+(unsigned day, const Date &date);
    friend Date operator-(const Date &date, unsigned day);
    friend long operator-(const Date &date1, const Date &date2);
    Date &operator+=(unsigned day);
    Date &operator-=(unsigned day);
    bool operator==(const Date &other) const;
    bool operator!=(const Date &other) const;
    bool operator<(const Date &other) const;
    bool operator>(const Date &other) const;
    bool operator<=(const Date &other) const;
    bool operator>=(const Date &other) const;
    //ќператор ввода даты из потока ввода
    friend std::istream &operator>>(std::istream &is, Date &date);
    //ќператор вывода даты в поток вывода
    friend std::ostream &operator<<(std::ostream &os, Date &date);

  private:
    void CalculateDate() const;
    void SetInvalidState();

    long m_dayCounter;
    mutable std::optional<unsigned> m_year;
    mutable std::optional<unsigned> m_monthDay;
    mutable std::optional<Month> m_month;
    bool m_isValidState;
};
