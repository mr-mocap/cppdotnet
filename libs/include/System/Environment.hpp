#pragma once

#include <string>
#include <string_view>
#include <map>

namespace System
{

class Environment final
{
public:

    static const std::string_view GetEnvironmentVariable(const char *var_name);
    static const std::string_view GetEnvironmentVariable(const std::string_view var_name);

    static void SetEnvironmentVariable(const char *var_name, const char *value);

    static std::map<std::string, std::string> GetEnvironmentVariables();

    static std::string ExpandEnvironmentVariables(const std::string_view input);

    static const std::string_view NewLine();

    [[noreturn]] static void Exit(int exit_code);
};

}