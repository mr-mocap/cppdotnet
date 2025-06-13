#include "System/Diagnostics/Activity.hpp"
#include "System/Span.hpp"
#include "System/Convert.hpp"
#include <random>
#include <algorithm>



namespace System::Diagnostics
{

static bool IsHexChar(const char input)
{
    using namespace std::literals;

    std::string_view hex_digits("0123456789abcdefABCDEF"sv);

    return hex_digits.find( input ) != std::string_view::npos;
}

bool ActivitySpanId::operator ==(const ActivitySpanId &other)
{
    for (std::size_t i = 0; i < _id.size(); ++i)
    {
        if ( _id[ i ] != other._id[ i ] )
            return false;
    }
    return true;
}

ActivitySpanId ActivitySpanId::CreateRandom()
{
    std::array<std::byte, 8> buffer;
    std::random_device rd;
    std::mt19937 gen( rd() );
    std::uniform_int_distribution<> distrib(0, 255);

    for (std::size_t i = 0; i < buffer.size(); ++i)
        buffer[ i ] = std::byte( distrib( gen ) );

    return ActivitySpanId( buffer );
}

ActivitySpanId ActivitySpanId::CreateFromString(ReadOnlySpan<char> input)
{
    using namespace std::literals;

    if ( input.Length() != 16 )
        ThrowWithTarget( ArgumentOutOfRangeException( "input"sv, "Does not have exactly 16 Hex characters"sv ) );

    // Check that they are all hex characters
    for (std::size_t i = 0; i < 16; ++i)
    {
        if ( !IsHexChar( input[i] ) )
            ThrowWithTarget( ArgumentOutOfRangeException( "input"sv, "Does not have exactly 16 Hex characters"sv ) );
    }

    std::array<char, 16> buffer;

    input.CopyTo( Span<char>( buffer ) );

    std::vector<std::byte> converted_from_hex = Convert::FromHexString( std::string_view( buffer.begin(), buffer.end() ) );
    std::array<std::byte, 8> converted_to_array;

    std::copy( converted_from_hex.begin(), converted_from_hex.end(), converted_to_array.begin() );
    return ActivitySpanId( converted_to_array );
}

ActivitySpanId ActivitySpanId::CreateFromBytes(ReadOnlySpan<std::byte> input)
{
    using namespace std::literals;

    if ( input.Length() != 8 )
        ThrowWithTarget( ArgumentOutOfRangeException( "input"sv, "Does not have exactly 8 bytes"sv ) );

    std::array<std::byte, 8> buffer;

    input.CopyTo( Span<std::byte>( buffer ) );

    return ActivitySpanId( buffer );
}

std::string ActivitySpanId::ToHexString() const
{
    return System::Convert::ToHexString( _id );
}

ActivityLink::ActivityLink(const ActivityContext &context)
    :
    _context( context )
{
}

static Activity  DefaultActivity("No Activity");
static Activity *CurrentActivity = nullptr;
EventHandler<ActivityChangedEventArgs> Activity::CurrentChanged;


Activity &Activity::Current()
{
    if ( !CurrentActivity )
        return DefaultActivity;
    return *CurrentActivity;
}

void Activity::Current(Activity &new_activity)
{
    ActivityChangedEventArgs data( CurrentActivity, &new_activity );

    CurrentActivity = &new_activity;

    if ( CurrentChanged )
        CurrentChanged( data );
}

Activity &Activity::Start()
{
    _parent = &Current();
    Current( *this );

    _stopped = false;
    return SetStartTime( DateTime::Now() );
}

void Activity::Stop()
{
    SetEndTime( DateTime::Now() );
    _stopped = true;

    if ( _parent )
        Current( *_parent );
    else
        Current( DefaultActivity );
}

Activity &Activity::SetStartTime(DateTime time)
{
    _start_time = time;
    return *this;
}

Activity &Activity::SetEndTime(DateTime time)
{
    _end_time = time;
    return *this;
}

Activity &Activity::SetStatus(ActivityStatusCode code, std::string_view description)
{
    _status = code;
    if ( code == ActivityStatusCode::Error )
        _status_description = description;
    else
        _status_description.clear();

    return *this;
}

TimeSpan Activity::Duration() const
{
    if ( IsStopped() )
        if ( _start_time != DateTime() ) // Check if we actually started!
            return { _end_time - StartTimeUtc() };
    
    return TimeSpan::Zero();
}

Activity &Activity::AddBaggage(std::string_view key, std::string_view value)
{
    _baggage.Add( key, value );
    return *this;
}

Activity &Activity::AddTag(std::string_view key, std::string_view value)
{
    _tags_to_log.Add( key, value );
    return *this;
}

}