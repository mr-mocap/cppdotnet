#pragma once

#include "System/Diagnostics/Switch.hpp"


namespace System::Diagnostics
{

class BooleanSwitch : public Switch
{
public:
    BooleanSwitch(const std::string_view display_name,
                  const std::string_view description,
                  const std::string_view default_value);
    BooleanSwitch(const std::string_view display_name, const std::string_view description);

    bool Enabled();

    void OnValueChanged() override;
};

}
