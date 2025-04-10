#pragma once


namespace System
{

enum class EnvironmentVariableTarget
{
    Process, ///@< The environment variable is stored or retrieved from the environment block associated with the current process
    User,
    Machine
};

}