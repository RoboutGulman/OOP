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
    // �������������� ���� ��������� ����, ������� � �����.
    explicit Date(unsigned day, Month month, unsigned year);
    // �������������� ���� ����������� ����, ��������� ����� 1 ������ 1970 ����
    explicit Date(unsigned timestamp = 0);

    // ���������� ���� ������ (�� 1 �� 31)
    unsigned GetDay() const;
    // ���������� �����
    Month GetMonth() const;
    // ���������� ���
    unsigned GetYear() const;
    // ���������� ���� ������
    //���������� ����� ������� �� 7 � ���������� �������
    WeekDay GetWeekDay() const;
    // ���������� ���������� � ������������ �������� ����
    bool IsValid() const;

    //����������� �����
    Date operator++(int);
    //���������� �����
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
    //�������� ����� ���� �� ������ �����
    friend std::istream &operator>>(std::istream &is, Date &date);
    //�������� ������ ���� � ����� ������
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
