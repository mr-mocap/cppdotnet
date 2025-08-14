
namespace System
{

struct EventArgs
{
    EventArgs() = default;

    static constexpr EventArgs Empty() { return { }; }
};

}