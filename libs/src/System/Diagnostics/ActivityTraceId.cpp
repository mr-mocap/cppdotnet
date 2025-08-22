#include "System/Diagnostics/ActivityTraceId.hpp"


namespace System::Diagnostics
{

ActivityTraceId ActivityTraceId::CreateRandom()
{
    return ActivityTraceId( Guid::NewGuid() );
}

ActivityTraceId ActivityTraceId::CreateFromString(ReadOnlySpan<char> input)
{
    using namespace std::literals::string_view_literals;

    // We expect the "N" format for the string
    if ( input.Length() != 32 )
        ThrowWithTarget( ArgumentOutOfRangeException( "input"sv, "Does not have exactly 32 Hex characters"sv ) );

    // Now let the Guid::Parse() handle any other checking...
    std::string_view input_as_string_view( input.begin(), input.end() );

    return ActivityTraceId( Guid::Parse( input_as_string_view ) );
}

ActivityTraceId ActivityTraceId::CreateFromBytes(ReadOnlySpan<std::byte> id_data)
{
    return ActivityTraceId( Guid( id_data ) );
}

}