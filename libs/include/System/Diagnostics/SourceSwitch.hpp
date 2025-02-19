#pragma once

#include "System/Diagnostics/Switch.hpp"
#include "System/Diagnostics/SourceLevels.hpp"


namespace System::Diagnostics
{

class SourceSwitch : public Switch
{
public:
    SourceSwitch(const std::string_view display_name, const std::string_view default_switch_value);
    SourceSwitch(const std::string_view display_name);

    static SourceSwitch Make(const std::string_view display_name, const std::string_view default_switch_value);

    SourceLevels Level();

    void OnValueChanged() override;
};

}