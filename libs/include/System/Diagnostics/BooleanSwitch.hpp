#include "System/Diagnostics/Switch.hpp"


namespace System::Diagnostics
{

class BooleanSwitch : public Switch
{
public:
    BooleanSwitch(std::string_view display_name,
                  std::string_view description,
                  std::string_view default_value);
    BooleanSwitch(std::string_view display_name, std::string_view description);

    bool Enabled();

    void OnValueChanged() override;
};

}
