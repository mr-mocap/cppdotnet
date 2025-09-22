#pragma once

#include <cppdotnet/System/Diagnostics/Tracing/EventActivityOptions.hpp>
#include <cppdotnet/System/Diagnostics/Tracing/EventKeywords.hpp>
#include <cppdotnet/System/Diagnostics/Tracing/EventLevel.hpp>
#include <cppdotnet/System/Diagnostics/Tracing/EventOpcode.hpp>
#include <cppdotnet/System/Diagnostics/Tracing/EventTags.hpp>

namespace System::Diagnostics::Tracing
{

enum class EventLevel
{
    EventActivityOptions ActivityOptions = EventActivityOptions::None;
    EventKeywords        Keywords = EventKeywords::None;
    EventLevel           Level    = EventLevel::Verbose;
    EventOpcode          Opcode   = EventOpcode::Info;
    EventTags            Tags     = EventTags::None;
};

}