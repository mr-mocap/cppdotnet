#include "System/Diagnostics/Switch.hpp"

#include <stdexcept>
#include <set>
#include <mutex>



namespace System::Diagnostics
{

std::set<Switch *> Switch::GlobalSwitches;
static std::mutex  GlobalSwitchesMutex;


Switch::Switch(const std::string_view display_name,
               const std::string_view description)
    :
    Switch(display_name, description, std::string_view{"0"})
{
}

Switch::Switch(const std::string_view display_name,
               const std::string_view description,
               const std::string_view default_value)
    :
    _displayName(display_name),
    _description(description),
    _defaultValue(default_value)
{
    std::lock_guard<std::mutex> guard( GlobalSwitchesMutex );

    GlobalSwitches.insert( this );
}

Switch::~Switch()
{
    std::lock_guard<std::mutex> guard( GlobalSwitchesMutex );

    GlobalSwitches.erase( this );
}

bool Switch::InitializeWithStatus()
{
    if ( !_initialized )
    {
        std::lock_guard<std::mutex> guard_this_object( _initializedLock );

        if ( _initialized || _initializing )
            return false;

        // Re-entrant during initialization, since calls to onValueChanged()
        // in subclasses could end up having InitializeWithStatus() called again.
        // We don't want to get caught in an infinite loop.
        _initializing = true;

        OnInitializing();

        _value = _defaultValue;
        OnValueChanged();

        _initialized = true;
        _initializing = false;
    }

    return true;
}

void Switch::OnInitializing()
{
    // Possibly read from external source...
    // TODO
}

void Switch::Initialize()
{
    InitializeWithStatus();
}

void Switch::OnSwitchSettingChanged()
{
}

void Switch::OnValueChanged()
try
{
    int value_converted = std::stoi( _value );

    SwitchSetting( value_converted );
}
catch (std::invalid_argument &ia)
{
    ;
}

const std::string &Switch::Value()
{
    Initialize();
    return _value;
}

void Switch::Value(const std::string_view new_value)
{
    Initialize();
    if ( _value != new_value )
    {
        _value = new_value;
        OnValueChanged();
    }
}

int Switch::SwitchSetting()
{
    if ( !_initialized )
        InitializeWithStatus();

    return _setting;
}

void Switch::SwitchSetting(int new_value)
{
    if ( _setting != new_value )
    {
        _setting = new_value;
        OnSwitchSettingChanged();
    }
}

void Switch::Refresh()
{
    std::lock_guard<std::mutex> guard_this_object( _initializedLock );

    _initialized = false;
    Initialize();
}

void Switch::RefreshAll()
{
    std::lock_guard<std::mutex> global_switches_guard( GlobalSwitchesMutex );

    for (Switch *iCurrentSwitch : GlobalSwitches)
        iCurrentSwitch->Refresh();
}

}