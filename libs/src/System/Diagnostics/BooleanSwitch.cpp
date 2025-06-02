#include "System/Diagnostics/BooleanSwitch.hpp"
#include <stdexcept>


namespace System::Diagnostics
{

BooleanSwitch::BooleanSwitch(std::string_view display_name,
                             std::string_view description,
                             std::string_view default_value)
    :
    Switch( display_name, description, default_value )
{
}

BooleanSwitch::BooleanSwitch(std::string_view display_name,
                             std::string_view description)
    :
    Switch( display_name, description, "0" )
{
}

bool BooleanSwitch::Enabled()
{
    return SwitchSetting() != 0;
}

void BooleanSwitch::OnValueChanged()
{
    try
    {
        int new_value = std::stoi( _value );

        if ( new_value == 0 || new_value == 1 )
            SwitchSetting( new_value );
        else
            Switch::OnValueChanged();
    }
    catch (const std::invalid_argument &ex)
    {
        Switch::OnValueChanged();
    }
    catch (const std::out_of_range &ex)
    {
        // TODO: Implement out_of_range exception
    }
}

}
