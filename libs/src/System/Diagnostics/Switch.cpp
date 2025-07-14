#include "System/Diagnostics/Switch.hpp"
#include "System/Diagnostics/Trace.hpp"

#include <stdexcept>
#include <set>
#include <mutex>



namespace System::Diagnostics
{

static std::set<Switch *> GlobalSwitches;
static std::mutex         GlobalSwitchesMutex;

Switch::Switch(std::string_view display_name,
               std::string_view description)
    :
    Switch(display_name, description, std::string_view{"0"})
{
}

Switch::Switch(std::string_view display_name,
               std::string_view description,
               std::string_view default_value)
    :
    _displayName(display_name),
    _description(description),
    _defaultValue(default_value)
{
    // ASSUME: "default_value" has already been checked to be an
    //         appropriate value.

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
        OnValueChanged(); // This shouldn't throw exceptions at this point

        _initialized = true;
        _initializing = false;
    }

    return true;
}

void Switch::OnInitializing()
{
    // Possibly read from external source...
    // TODO
    if ( Initializing() )
    {
        InitializingSwitchEventArgs data( *this );

        Initializing()( data );
    }
}

void Switch::Initialize()
{
    InitializeWithStatus();
}

void Switch::OnSwitchSettingChanged()
{
}

void Switch::OnValueChanged()
{
    // Assume a string that is convertable to an int
    int value_converted = std::stoi( _value ); // NOTE: Throws exceptions!

    SwitchSetting( value_converted );
}

std::string_view Switch::Value()
{
    Initialize();
    return _value;
}

void Switch::Value(std::string_view new_value)
{
    Initialize();
    if ( _value != new_value )
    {
        auto backup_value = _value;

        try
        {
            _value = new_value;
            OnValueChanged();
        }
        catch(const std::invalid_argument &ia)
        {
            // Undo the operation...
            _value = backup_value;
            Trace::TraceError("Unable to set switch '{}' to new value '{}'", DisplayName(), new_value);
        }
        
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

System::EventHandler<InitializingSwitchEventArgs> &Switch::Initializing()
{
    static System::EventHandler<InitializingSwitchEventArgs> Handle;

    return Handle;
}

}