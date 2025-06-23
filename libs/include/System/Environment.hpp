#pragma once

#include "System/Collections/Specialized/StringDictionary.hpp"
#include <string>
#include <string_view>
#include <map>

namespace System
{

class Environment final
{
public:

    static std::string_view GetEnvironmentVariable(const char *var_name);
    static std::string_view GetEnvironmentVariable(std::string_view var_name);

    static void SetEnvironmentVariable(const char *var_name, const char *value);

    static Collections::Specialized::StringDictionary GetEnvironmentVariables();

    static std::string ExpandEnvironmentVariables(std::string_view input);

    static std::string_view NewLine();

    static std::string StackTrace();

    [[noreturn]] static void Exit(int exit_code);
};

}