module;

export module System:EventArgs;

namespace System
{

export
struct EventArgs
{
    EventArgs() = default;

    static constexpr EventArgs Empty() { return { }; }
};

}