import "System/Diagnostics/BooleanSwitch.hpp";
import "System/Boolean.hpp";
import <stdexcept>;


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
    if ( _value == Boolean::FalseString )
        SwitchSetting( 0 );
    else if ( _value == Boolean::TrueString )
        SwitchSetting( 1 );
    else
        Switch::OnValueChanged();
}

}
