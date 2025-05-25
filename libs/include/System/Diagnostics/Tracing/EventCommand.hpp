#pragma once


namespace System::Diagnostics::Tracing
{

enum class EventCommand
{
    Disable      = -3, //@< Disable the event
    Enable       = -2, //@< Enable the event
    SendManifest = -1, //@< Send the manifest
    Update       =  0  //@< Update the event
};

}