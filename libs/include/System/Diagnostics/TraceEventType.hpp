#pragma once

namespace System::Diagnostics
{
    enum class TraceEventType
    {
        Critical    = 0x01,
        Error       = 0x02,
        Warning     = 0x04,
        Information = 0x08,
        Verbose     = 0x10,
        Start       = 0x0100,
        Stop        = 0x0200,
        Suspend     = 0x0400,
        Resume      = 0x0800,
        Transfer    = 0x1000
    };
}
