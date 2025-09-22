#pragma once

#include <cppdotnet/System/Private/enum.hpp>


namespace System
{

enum class EnvironmentVariableTarget
{
    Process, ///@< The environment variable is stored or retrieved from the environment block associated with the current process
    User,
    Machine
};

}

namespace System
{

template <>
struct EnumPolicy<System::EnvironmentVariableTarget> : EnumTraitTypes<System::EnvironmentVariableTarget>
{
    static constexpr std::string_view EnumName = "EnvironmentVariableTarget";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Process", EnvironmentVariableTarget::Process },
            { "User",    EnvironmentVariableTarget::User    },
            { "Machine", EnvironmentVariableTarget::Machine }
        };
};

}
