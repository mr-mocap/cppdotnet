#include "System/Numerics/INumberBase.hpp"


namespace System::Numerics
{

bool INumberBase<bool>::Parse(const std::string_view s)
{
    using namespace std::literals;

    if ( s.empty() )
        ThrowWithTarget( ArgumentNullException("s"sv) );

    bool converted;

    auto [ptr, ec] = std::from_chars( s.data(), s.data() + s.size(), converted);
    
    if ( ec == std::errc::invalid_argument )
        ThrowWithTarget( System::FormatException{ "Parameter 's' is not in the correct format"sv } );
    else if ( ec == std::errc::result_out_of_range )
        ThrowWithTarget( System::OverflowException{ "Parameter 's' is not representable by int32_t"sv } );
    else if ( ec != std::errc() )
        ThrowWithTarget( System::ArgumentException{ "Argument does not contain integer information", "s" } );

    return converted;
}

bool INumberBase<bool>::TryParse(const std::string_view s)
{
    if ( s.empty() )
        return {};

    using namespace std::literals;

    bool converted;

    auto [ptr, ec] = std::from_chars( s.data(), s.data() + s.size(), converted);
    
    if ( ec != std::errc() )
        return {};

    return converted;
}

}