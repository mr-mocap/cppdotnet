#pragma once

namespace System::Diagnostics
{

enum class SourceLevels
{
    All      = -1,
    Off      = 0,
    Critical = 1,
    Error    = 3,
    Warning  = 7,
    Information = 15,
    Verbose  = 31,
    ActivityTracing = 65280
};

}