module System:DateOnly;

import System:DateTime;

namespace System
{

DateOnly DateOnly::FromDateTime(const DateTime &dt)
{
    return DateOnly{ dt.Year(), dt.Month(), dt.Day() };
}

}