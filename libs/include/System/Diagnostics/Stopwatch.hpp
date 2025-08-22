#include "System/TimeSpan.hpp"
#include "System/Private/private.hpp"
#include <chrono>
#include <format>
#include <cstdint>


namespace System::Diagnostics
{

class Stopwatch
{
public:
    using clock_type = std::chrono::steady_clock;

    Stopwatch() = default;
    Stopwatch(const Stopwatch &) = default;
    Stopwatch(Stopwatch &&) = default;

    Stopwatch &operator =(const Stopwatch &) = default;
    Stopwatch &operator =(Stopwatch &&) = default;

    static constexpr long Frequency()        { return clock_type::period::den; }
    static constexpr bool IsHighResolution() { return false; }

    static Stopwatch StartNew()
    {
        return Stopwatch( true );
    }

    void Start()
    {
        if ( _is_running )
            return;
        _start_time = clock_type::now();
        _is_running = true;
        
        POSTCONDITION( IsRunning() );
    }

    void Stop()
    {
        auto n = clock_type::now();

        _accumulated_time += n - _start_time;
        _is_running = false;
        _start_time = n;

        POSTCONDITION( !IsRunning() );
    }

    void Restart()
    {
        // This is to make Start() function as we want
        // (i.e. pretend that we are stopped right now and then call Start())
        _is_running = false;

        _accumulated_time = clock_type::duration::zero();
        Start();

        POSTCONDITION( IsRunning() );
    }

    void Reset()
    {
        _is_running = false;
        _accumulated_time = clock_type::duration::zero();

        POSTCONDITION( !IsRunning() );
        POSTCONDITION( _accumulated_time == clock_type::duration::zero() );
    }

    bool IsRunning() const
    {
        return _is_running;
    }

    static long GetTimestamp()
    {
        return clock_type::now().time_since_epoch().count();
    }

    static TimeSpan GetElapsedTime(long starting_time_stamp)
    {
        clock_type::duration difference( clock_type::now().time_since_epoch().count() - starting_time_stamp );

        return { difference };
    }

    static TimeSpan GetElapsedTime(long starting_time_stamp, long ending_time_stamp)
    {
        clock_type::duration difference( ending_time_stamp - starting_time_stamp );

        return { difference };
    }

    TimeSpan Elapsed()
    {
        if ( _is_running )
        {
            auto n = clock_type::now();

            // Capture the current time difference...
            _accumulated_time += (n - _start_time);
            
            // Reset the start time
            _start_time = n;
        }
        return { _accumulated_time };
    }

    long ElapsedMilliseconds()
    {
        clock_type::duration d = Elapsed();

        return std::chrono::floor<std::chrono::milliseconds>(d).count();
    }

    long ElapsedTicks()
    {
        clock_type::duration d = Elapsed();

        return d.count();
    }

    std::string ToString() const
    {
        if ( _is_running )
            return std::format("{} and running", _accumulated_time);
        else
            return std::format("{}", _accumulated_time);
    }
protected:
    clock_type::time_point _start_time;
    clock_type::duration   _accumulated_time = clock_type::duration::zero();
    bool                   _is_running = false;

    Stopwatch(bool startnow)
        :
        _start_time{ clock_type::now() },
        _is_running{ startnow }
    {
    }
};

}

template <>
struct std::formatter<System::Diagnostics::Stopwatch>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return ctx.begin();
    }

    template <typename FormatContext>
    auto format(const System::Diagnostics::Stopwatch &object, FormatContext &ctx) const
    {
        return std::format_to( ctx.out(), "{}", object.ToString());
    }
};