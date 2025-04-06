#pragma once

#include "System/TimeSpan.hpp"
#include <chrono>


namespace System::Diagnostics
{

class Stopwatch
{
public:
    using clock_type = std::chrono::steady_clock;

    Stopwatch();

    static long Frequency() { return 0; } // Ticks per second
    static bool IsHighResolution() { return false; }

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
    }

    void Stop()
    {
        auto n = clock_type::now();

        _accumulated_time += n - _start_time;
        _is_running = false;
        _start_time = n;
    }

    void Restart()
    {
        // This is to make Start() function as we want
        // (i.e. pretend that we are stopped right now and then call Start())
        _is_running = false;

        _accumulated_time = 0;
        Start();
    }

    void Reset()
    {
        _is_running = false;
        _accumulated_time = 0;
    }

    bool IsRunning() const
    {
        return _is_running;
    }

    static long GetTimestamp()
    {
        return clock_type::now().time_since_epoch().count();
    }

    static TimeSpan GetElapsedTime(long starting_time_stamp, long ending_time_stamp)
    {
        clock_type::duration difference( ending_time_stamp - starting_time_stamp ):

        return { difference };
    }

    static TimeSpan GetElapsedTime(long starting_time_stamp)
    {
        clock_type::duration difference( clock_type::now().time_since_epoch().count() - starting_time_stamp ):

        return { difference };
    }

    TimeSpan Elapsed() const
    {
        if ( _is_running )
        {
            auto n = clock_type::now();

            // Capture the current time difference...
            _accumulated_time += n - _start_time;
            
            // Reset the start time
            _start_time = n;
        }
        return { _accumulated_time };
    }

    long ElapsedMilliseconds() const
    {
        clock_type::duration d = Elapsed();

        return std::chrono::floor<std::chrono::milliseconds>(d).count();
    }

    long GetElapsedTicks() const
    {
        clock_type::duration d = Elapsed();

        return d.count();
    }

protected:
    clock_type::time_point _start_time;
    clock_type::duration   _accumulated_time;
    bool                   _is_running = false;

    Stopwatch(bool startnow)
        :
        _start_time{ clock_type::now() },
        _is_running{ startnow }
    {
    }
};

}