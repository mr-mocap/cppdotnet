import "System/Diagnostics/Tracing/EventActivityOptions.hpp";
import "System/Diagnostics/Tracing/EventKeywords.hpp";
import "System/Diagnostics/Tracing/EventLevel.hpp";
import "System/Diagnostics/Tracing/EventOpcode.hpp";
import "System/Diagnostics/Tracing/EventTags.hpp";

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