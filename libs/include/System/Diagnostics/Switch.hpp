#pragma once

#include "System/Collections/Specialized/StringDictionary.hpp"
#include <set>
#include <string>
#include <string_view>
#include <mutex>


namespace System::Diagnostics
{

class Switch {
public:
    virtual ~Switch();


    const std::string &DisplayName() const  { return _displayName; }
    const std::string &Description() const  { return _description; }
    const std::string &DefaultValue() const { return _defaultValue; }

    const std::string &Value();
          void         Value(std::string_view new_value);
    
    const Collections::Specialized::StringDictionary &Attributes() const { return _attributes; }

    void Refresh();

    static void RefreshAll();

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

    static std::set<Switch *> GlobalSwitches;
};

}
