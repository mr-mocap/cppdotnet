module System:TimeOnly;

import System:DateTime;

namamespace System
{

TimeOnly TimeOnly::FromDateTime(const System::DateTime &datetime)
{
    return TimeOnly( datetime.TimeOfDay() );
}

}