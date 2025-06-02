#pragma once

#include <string>

namespace System::Diagnostics
{

class Debugger final
{
public:

    //static void Log(int level, const std::string &category, const std::string &message);
    static void Log(std::string_view message);
};

}
