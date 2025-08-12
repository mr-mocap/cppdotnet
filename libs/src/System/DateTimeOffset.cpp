module

module System;

import "System/DateTimeOffset.hpp";


namespace System
{

DateTimeOffset DateTimeOffset::Now()
{
    return DateTimeOffset( DateTime::Now() );
}

DateTimeOffset DateTimeOffset::UtcNow()
{
    return DateTimeOffset( DateTime::UtcNow() );
}

}