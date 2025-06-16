#pragma once

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
struct EnumTraits<Diagnostics::ActivitySamplingResult> : EnumTraitTypes<Diagnostics::ActivitySamplingResult>
{
    static auto EnumName() -> std::string_view { return "ActivitySamplingResult"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",               Diagnostics::ActivitySamplingResult::None },
            { "PropagationData",    Diagnostics::ActivitySamplingResult::PropagationData },
            { "AllData",            Diagnostics::ActivitySamplingResult::AllData },
            { "AllDataAndRecorded", Diagnostics::ActivitySamplingResult::AllDataAndRecorded }
        };

    static constexpr auto NameValuePairs() -> std::span<const name_value_pair_type>
    {
        return std::span{ NameValueArray };
    }

    static constexpr auto Count() -> std::size_t { return NameValuePairs().size(); }

    static constexpr auto Names() -> std::ranges::keys_view<std::span<const name_value_pair_type>>
    {
        return std::views::keys( NameValuePairs() );
    }

    static constexpr auto Values() -> std::ranges::values_view<std::span<const name_value_pair_type>>
    {
        return std::views::values( NameValuePairs() );
    }

    static constexpr auto ValuesAsUnderlyingType()
    {
        auto to_underlying_type = [](const value_type item) { return static_cast<underlying_type>(item); };

        return Values() | std::views::transform( to_underlying_type );
    }

    static constexpr bool IsDefined(value_type value)
    {
        return std::ranges::find( NameValuePairs(),
                                  value,
                                  &name_value_pair_type::second
                                ) != NameValuePairs().end();
    }

    static constexpr bool IsDefined(underlying_type value)
    {
        return IsDefined( static_cast<value_type>(value) );
    }

    static constexpr bool IsDefined(std::string_view value_string)
    {
        return std::ranges::find( NameValuePairs(),
                                  value_string,
                                  &name_value_pair_type::first
                                ) != NameValuePairs().end();
    }

    static constexpr auto ToName(value_type value) -> std::string_view
    {
        auto found = std::ranges::find( NameValuePairs(),
                                        value,
                                        &name_value_pair_type::second
                                      );

        if ( found == NameValuePairs().end() )
            return {};

        return found->first;
    }

    static constexpr auto ToName(underlying_type value) -> std::string_view
    {
        return ToName( static_cast<value_type>(value) );
    }

    static constexpr value_type min() { return Diagnostics::ActivitySamplingResult::None; }
    static constexpr value_type max() { return Diagnostics::ActivitySamplingResult::AllDataAndRecorded; }
};

}