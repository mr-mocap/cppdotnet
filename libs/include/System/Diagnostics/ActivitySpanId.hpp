#include "System/ReadOnlySpan.hpp"
#include <cstddef>
#include <array>
#include <string>


namespace System::Diagnostics
{

class ActivitySpanId
{
public:
    ActivitySpanId()
    {
        _id.fill( std::byte(0) );
    }

    ActivitySpanId(const ActivitySpanId &other)
    {
        _id = other._id;
    }

    ActivitySpanId &operator =(const ActivitySpanId &other) = default;

    bool operator ==(const ActivitySpanId &other);

    static ActivitySpanId CreateRandom();

    static ActivitySpanId CreateFromString(ReadOnlySpan<char> input);
    static ActivitySpanId CreateFromBytes(ReadOnlySpan<std::byte> input);

    std::string ToHexString() const;

    std::string ToString() const { return ToHexString(); }
protected:
    std::array<std::byte, 8> _id;

    ActivitySpanId(const std::array<std::byte, 8> &array)
    {
        for (size_t i = 0; i < _id.size(); ++i)
            _id[ i ] = array[i];
    }
};

}