module;

export module System:DateOnly;

export import <chrono>;
export import <compare>;
export import <string>;

namespace System
{

export class DateTime;
enum class DayOfWeek;

export
class DateOnly
{
public:
    DateOnly();
    explicit DateOnly(int year, int month, int day);
    DateOnly(const std::chrono::year_month_day &ymd);
    DateOnly(const std::chrono::sys_days &d);
   ~DateOnly();

    DateOnly(const DateOnly &);
    DateOnly &operator =(const DateOnly &);
    DateOnly(DateOnly &&);
    DateOnly &operator =(DateOnly &&);

    int Day() const
    {
        unsigned int temp{ _year_month_day.day() };

        return static_cast<int>( temp );
    }

    int Month() const
    {
        unsigned int temp{ _year_month_day.month() };

        return static_cast<int>( temp );
    }

    int Year() const
    {
        return static_cast<int>( _year_month_day.year() );
    }

    int DayNumber() const
    {
        std::chrono::sys_days num_days{ _year_month_day };

        return static_cast<int>( num_days.time_since_epoch().count() );
    }

    enum System::DayOfWeek DayOfWeek() const;

    int DayOfYear() const;

    static DateOnly MinValue() { return DateOnly( 1, 1, 1 ); }
    static DateOnly MaxValue() { return DateOnly( 9999, 12, 31 ); }

    static DateOnly FromDateTime(const System::DateTime &);
    static DateOnly FromDayNumber(int day_number);

    DateOnly AddDays(int num_days) const;
    DateOnly AddMonths(int num_months) const;
    DateOnly AddYears(int num_years) const;

    int CompareTo(const DateOnly &other) const;
    bool Equals(const DateOnly &other) const { return *this == other; }

    void Deconstruct(int &year, int &month, int &day);

    std::string ToString() const;
#if 0
    DateTime ToDateTime(const TimeOnly &time_only) const
    {
        return DateTime( *this, time_only );
    }
#endif

    operator std::chrono::sys_days() const { return _year_month_day; }
    operator std::chrono::year_month_day() const { return _year_month_day; }
protected:
    std::chrono::year_month_day _year_month_day;


    friend constexpr bool operator ==(const DateOnly &left, const DateOnly &right)
    {
        return left._year_month_day == right._year_month_day;
    }

    friend constexpr std::strong_ordering operator <=>(const DateOnly &left, const DateOnly &right)
    {
        return left._year_month_day <=> right._year_month_day;
    }
};

}