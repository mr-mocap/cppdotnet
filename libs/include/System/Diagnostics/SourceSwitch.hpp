#pragma once

import "System/Diagnostics/Switch.hpp";
import "System/Diagnostics/SourceLevels.hpp";


namespace System::Diagnostics
{

class SourceSwitch : public Switch
{
public:
    SourceSwitch(std::string_view display_name, std::string_view default_switch_value);
    SourceSwitch(std::string_view display_name);

    static SourceSwitch Make(std::string_view display_name, std::string_view default_switch_value);

    SourceLevels Level();

    void OnValueChanged() override;
};

}