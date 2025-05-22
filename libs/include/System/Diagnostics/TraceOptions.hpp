#pragma once

namespace System::Diagnostics
{

enum class TraceOptions
{
    None = 0,
    LogicalOperationStack = 1,
    DateTime = 2,
    Timestamp = 4,
    ProcessId = 8,
    ThreadId = 16,
    Callstack = 32
};

}

namespace System
{

template <>
struct EnumTraits<Diagnostics::TraceOptions> : EnumTraitTypes<Diagnostics::TraceOptions>
{
    static auto EnumName() -> const std::string_view { return "TraceOptions"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "None",      Diagnostics::TraceOptions::None },
            { "LogicalOperationStack", Diagnostics::TraceOptions::LogicalOperationStack },
            { "DateTime",  Diagnostics::TraceOptions::DateTime },
            { "Timestamp", Diagnostics::TraceOptions::Timestamp },
            { "ProcessId", Diagnostics::TraceOptions::ProcessId },
            { "ThreadId",  Diagnostics::TraceOptions::ThreadId },
            { "Callstack", Diagnostics::TraceOptions::Callstack }
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
        // Is it out-of-range?
        if ( (value < min()) || (value > max()) )
            return false;

        return std::ranges::find( NameValuePairs(),
                                  value_string,
                                  &name_value_pair_type::first
                                ) != NameValuePairs().end();
    }

    static constexpr bool IsDefined(underlying_type value)
    {
        return IsDefined( static_cast<value_type>(value) );
    }

    static constexpr bool IsDefined(const std::string_view value_string)
    {
        return std::ranges::find( NameValuePairs(),
                                  value_string,
                                  &name_value_pair_type::first
                                ) != NameValuePairs().end();
    }

    static constexpr auto ToName(value_type value) -> const std::string_view
    {
        auto found = std::ranges::find( NameValuePairs(),
                                        value,
                                        &name_value_pair_type::second
                                      );

        if ( found == NameValuePairs().end() )
            return {};

        return found->first;
    }

    static constexpr auto ToName(underlying_type value) -> const std::string_view
    {
        return ToName( static_cast<value_type>(value) );
    }

    static constexpr value_type min() { return Diagnostics::TraceOptions::None; }
    static constexpr value_type max() { return Diagnostics::TraceOptions::Callstack; }
};

}