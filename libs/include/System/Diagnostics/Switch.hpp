#pragma once

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
          void         Value(const std::string_view new_value);

    void Refresh();

    static void RefreshAll();

    virtual void OnSwitchSettingChanged();
    virtual void OnValueChanged();
protected:
    std::string _displayName;
    std::string _description;
    std::string _defaultValue = "0";
    std::string _value;
    int         _setting = 0;
    bool        _initializing = false;
    bool        _initialized = false;
    std::mutex  _initializedLock;

    Switch(const std::string_view display_name,
           const std::string_view description);
    Switch(const std::string_view display_name,
           const std::string_view description,
           const std::string_view default_value);

    int  SwitchSetting();
    void SwitchSetting(int new_value);
private:
    bool InitializeWithStatus();
    void OnInitializing();
    void Initialize();

    static std::set<Switch *> GlobalSwitches;
};

}
