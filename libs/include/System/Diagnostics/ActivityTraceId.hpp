#include "System/Guid.hpp"
#include "System/Exception.hpp"
#include <compare>


namespace System::Diagnostics
{

struct ActivityTraceId
{
    ActivityTraceId() = default;
    ActivityTraceId(const ActivityTraceId &) = default;

    ActivityTraceId &operator =(const ActivityTraceId &other) = default;

    static ActivityTraceId CreateRandom();

    static ActivityTraceId CreateFromString(ReadOnlySpan<char> input);
    static ActivityTraceId CreateFromBytes(ReadOnlySpan<std::byte> input);

    std::string ToHexString() const
    {
        return _id.ToString("N");
    }

    void CopyTo(Span<std::byte> destination) const
    {
        if ( destination.Length() < 16 )
            ThrowWithTarget( ArgumentException{"Destination Span is shorter than the source ReadOnlySpan", "destination"} );
        
        _id.ToByteArray().CopyTo( destination );
    }

    std::strong_ordering operator <=>(const ActivityTraceId &other) const
    {
        return _id <=> other._id;
    }
protected:
    Guid _id;

    ActivityTraceId(const Guid &guid)
        :
        _id( guid )
    {
    }
};


}