#include "System/Diagnostics/TraceListener.hpp"
#include "System/Diagnostics/TraceEventCache.hpp"
#include "System/Convert.hpp"


namespace System::Diagnostics
{

TraceListener::TraceListener()
{
}

TraceListener::TraceListener(std::string_view name)
    :
    _name{ name }
{
}

bool TraceListener::IsThreadSafe() const
{
    return false;
}

std::string_view TraceListener::Name() const
{
    return _name;
}

int TraceListener::IndentLevel() const
{
    return _indentLevel;
}

void TraceListener::IndentLevel(int new_level)
{
    _indentLevel = std::max(new_level, 0);
    _indentString.resize( _indentLevel * _indentSize, ' ' );
    SetNeedIndent();
}

int TraceListener::IndentSize() const
{
    return _indentSize;
}

void TraceListener::IndentSize(int new_size)
{
    _indentSize = std::max(new_size, 0);
    _indentString.resize( _indentLevel * _indentSize, ' ' );
    SetNeedIndent();
}

void TraceListener::SetNeedIndent()
{
    _needIndent = (_indentSize > 0) && (_indentLevel > 0);
}

}
