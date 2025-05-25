#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventChannel
{
    None        =  0,  //@< No channel specified
    Admin       = 16,  //@< The administrator log channel
    Operational = 17,  //@< The operational log channel
    Analytic    = 18,  //@< The analytic log channel
    Debug       = 19   //@< The debug channel
};

}