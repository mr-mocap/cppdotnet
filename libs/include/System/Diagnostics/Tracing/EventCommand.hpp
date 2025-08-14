
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

namespace System
{

template <>
struct EnumTraits<Diagnostics::Tracing::EventCommand> : EnumTraitTypes<Diagnostics::Tracing::EventCommand>
{
    static auto EnumName() -> std::string_view { return "EventCommand"; }

    static constexpr name_value_pair_type NameValueArray[] = {
            { "Disable",      Diagnostics::Tracing::EventCommand::Disable      },
            { "Enable",       Diagnostics::Tracing::EventCommand::Enable       },
            { "SendManifest", Diagnostics::Tracing::EventCommand::SendManifest },
            { "Update",       Diagnostics::Tracing::EventCommand::Update       }
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
        // We can do this because the enumerations are consecutive..
        return (value >= min()) && (value <= max());
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

    static constexpr value_type min() { return Diagnostics::Tracing::EventCommand::Disable; }
    static constexpr value_type max() { return Diagnostics::Tracing::EventCommand::Update; }
};

}