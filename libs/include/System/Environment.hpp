#pragma once

#include "System/Collections/Generic/Dictionary.hpp"
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

    static Collections::Generic::Dictionary<std::string, std::string> GetEnvironmentVariables();

    static std::string ExpandEnvironmentVariables(std::string_view input);

    static std::string_view NewLine();

    [[noreturn]] static void Exit(int exit_code);
};

}