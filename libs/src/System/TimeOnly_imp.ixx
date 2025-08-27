module;

module System:TimeOnly;

export import System:DateTime;

namespace System
{

TimeOnly TimeOnly::FromDateTime(const System::DateTime &datetime)
{
    return TimeOnly( datetime.TimeOfDay() );
}

}