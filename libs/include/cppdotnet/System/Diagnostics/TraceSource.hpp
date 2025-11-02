#pragma once

#include <cppdotnet/System/TypeCode.hpp>
#include <cppdotnet/System/Diagnostics/SourceLevels.hpp>
#include <cppdotnet/System/Diagnostics/TraceListenerCollection.hpp>
#include <cppdotnet/System/Diagnostics/TraceEventType.hpp>
#include <cppdotnet/System/Diagnostics/TraceEventCache.hpp>
#include <cppdotnet/System/Collections/Specialized/StringDictionary.hpp>
#include <string>
#include <string_view>


namespace System::Diagnostics
{

class TraceSource
{
public:
    TraceSource(std::string_view name) : _name{ name } { }
    TraceSource(std::string_view name, Diagnostics::SourceLevels default_level) : _name{ name }, _level{ default_level } { }

    static constexpr TypeCode GetTypeCode() { return TypeCode::Object; }

    Diagnostics::SourceLevels DefaultLevel() const { return _level; }

    std::string_view Name() const { return _name; }

    const Collections::Specialized::StringDictionary &Attributes() const { return _attributes; }
          Collections::Specialized::StringDictionary &Attributes()       { return _attributes; }

    const Diagnostics::TraceListenerCollection &Listeners() const { return _listeners; }
          Diagnostics::TraceListenerCollection &Listeners()       { return _listeners; }

    // TODO: Implement the Switch() method
    // TODO: Implement the Initializing event

    void Close();
    void Flush();

    void TraceData(TraceEventType event_type, int id);
    void TraceEvent(TraceEventType event_type, int id);
    void TraceInformation(std::string_view message);
protected:
    std::string               _name;
    SourceLevels              _level{ Diagnostics::SourceLevels::Off };
    Collections::Specialized::StringDictionary _attributes;
    TraceListenerCollection   _listeners;
    TraceEventCache           _eventCache;
};

}