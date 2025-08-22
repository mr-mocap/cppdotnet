#include <string_view>

namespace System::Diagnostics
{

class Debugger final
{
public:

    static void Log(int level, std::string_view category, std::string_view message);
};

}
