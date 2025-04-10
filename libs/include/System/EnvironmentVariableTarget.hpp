#pragma once


namespace System
{

enum class environmentVariableTarget
{
    Process, ///@< The environment variable is stored or retrieved from the environment block associated with the current process
    User,
    Machine
};

}