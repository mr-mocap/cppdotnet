#include "System/Collections/Specialized/StringDictionary.hpp"
#include "System/EventHandler.hpp"
#include <set>
#include <string>
#include <string_view>
#include <mutex>


namespace System::Diagnostics
{

class Switch;

class InitializingSwitchEventArgs : public EventArgs
{
public:
    InitializingSwitchEventArgs(Diagnostics::Switch &s) : _switch(s) { }

    const Diagnostics::Switch &Switch() const { return _switch; }
          Diagnostics::Switch &Switch()       { return _switch; }
protected:
    Diagnostics::Switch &_switch;
};

class Switch {
public:
    virtual ~Switch();


    std::string_view DisplayName() const  { return _displayName; }
    std::string_view Description() const  { return _description; }
    std::string_view DefaultValue() const { return _defaultValue; }

    std::string_view Value();
    void             Value(std::string_view new_value);
    
    const Collections::Specialized::StringDictionary &Attributes() const { return _attributes; }

    void Refresh();

    static void RefreshAll();

    static System::EventHandler<InitializingSwitchEventArgs> &Initializing();
protected:
    std::string _displayName;
    std::string _description;
    std::string _defaultValue = "0";
    std::string _value;
    int         _setting = 0;
    bool        _initializing = false;
    bool        _initialized = false;
    std::mutex  _initializedLock;
    Collections::Specialized::StringDictionary _attributes;

    Switch(std::string_view display_name,
           std::string_view description);
    Switch(std::string_view display_name,
           std::string_view description,
           std::string_view default_value);

    int  SwitchSetting();
    void SwitchSetting(int new_value);

    virtual void OnSwitchSettingChanged();
    virtual void OnValueChanged();
private:
    bool InitializeWithStatus();
    void OnInitializing();
    void Initialize();
};

}
