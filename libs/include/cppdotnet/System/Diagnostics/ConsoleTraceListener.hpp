#pragma once

#include <cppdotnet/System/Diagnostics/TextWriterTraceListener.hpp>


namespace System::Diagnostics
{

class ConsoleTraceListener : public TextWriterTraceListener
{
public:
    ConsoleTraceListener();
    ConsoleTraceListener(bool useErrorStream);
   ~ConsoleTraceListener();

protected:
};

}