module;

export module System:EnvironmentVariableTarget;

export import System:Private_enum;


namespace System
{

export
enum class EnvironmentVariableTarget
{
    Process, ///@< The environment variable is stored or retrieved from the environment block associated with the current process
    User,
    Machine
};

}

namespace System
{

export
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
