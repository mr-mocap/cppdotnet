#include "System/Private/enum.hpp"

namespace System::Diagnostics
{

enum class ActivitySamplingResult
{
    None,              //@< The activity object does not need to be created
    PropagationData,   //@< The activity object needs to be created. It will have a Name, a Source, an Id and Baggage. Other properties are unnecessary and will be ignored by this listener.
    AllData,           //@< The activity object should be populated with all the propagation information and also all other properties such as Links, Tags, and Events. Using this value causes IsAllDataRequested to return true.
    AllDataAndRecorded //@< The activity object should be populated the same as the AllData case. Additionally, Activity.Recorded is set to true. For activities using the W3C trace ids, this sets a flag bit in the ID that will be propagated downstream requesting that the trace is recorded everywhere.
};

}

namespace System
{

template <>
struct EnumPolicy<System::Diagnostics::ActivitySamplingResult> : EnumTraitTypes<System::Diagnostics::ActivitySamplingResult>
{
public:

    static constexpr std::string_view EnumName = "ActivitySamplingResult";

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",               Diagnostics::ActivitySamplingResult::None               },
            { "PropagationData",    Diagnostics::ActivitySamplingResult::PropagationData    },
            { "AllData",            Diagnostics::ActivitySamplingResult::AllData            },
            { "AllDataAndRecorded", Diagnostics::ActivitySamplingResult::AllDataAndRecorded }
        };
};

}