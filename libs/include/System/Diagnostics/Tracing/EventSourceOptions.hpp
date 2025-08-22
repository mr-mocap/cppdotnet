#include "System/Diagnostics/Tracing/EventActivityOptions.hpp"
#include "System/Diagnostics/Tracing/EventKeywords.hpp"
#include "System/Diagnostics/Tracing/EventLevel.hpp"
#include "System/Diagnostics/Tracing/EventOpcode.hpp"
#include "System/Diagnostics/Tracing/EventTags.hpp"

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