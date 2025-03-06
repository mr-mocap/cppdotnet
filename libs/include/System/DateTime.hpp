#pragma once

#include "System/DayOfWeek.hpp"
#include <cstddef>
#include <chrono>
#include <string>


namespace System
{

class DateTime
{
public:
    DateTime() = delete;
    DateTime(int year, int month, int day);
    DateTime(std::chrono::system_clock::time_point tp) : _point_in_time( tp ) { }

    DateTime(const DateTime &) = default;
    DateTime(DateTime &&) = default;

    DateTime &operator =(const DateTime &) = default;
    DateTime &operator =(DateTime &&) = default;

    DateTime Date() const;

    int Year() const;
    int Month() const;
    int Day() const;

    int Hour() const;

    enum DayOfWeek DayOfWeek() const;

    static DateTime Now();

    std::string ToString() const;
protected:
    std::chrono::system_clock::time_point _point_in_time;
};

}