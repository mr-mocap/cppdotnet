#include <utility>
#include <string>
#include <span>

class ExampleEnumPolicyWithInternalEnum
{
public:
    enum Values {
        Value1 = 0,
        Value2,
        Value3
    };

    using value_type = enum Values;
    using underlying_type = std::underlying_type_t<value_type>;

    template <class InstantiationType>
    using array_type = std::array<InstantiationType, Count()>;

    using name_array_type = array_type<std::string_view>;
    using value_array_type = array_type<value_type>;
    using underlying_value_array_type = array_type<underlying_type>;
    using name_value_pair_type = std::pair<const char *, value_type>;

protected:

    constexpr static std::span<name_value_pair_type> NameValueArray()
    {
        static name_value_pair_type array[] = {
            { "Value1", Value1 },
            { "Value2", Value2 },
            { "Value3", Value3 }
        };

        return std::span( array );
    }

    constexpr std::size_t Count() const { return NameValueArray().size(); }
};

template <enum ExternalEnum>
class ExampleEnumPolicyWithExternalEnum
{
public:
    using enum ExternalEnum; // Pulls the enumerated values into this class scope

    using value_type = ExternalEnum;
    using underlying_type = std::underlying_type_t<value_type>;

    template <class InstantiationType>
    using array_type = std::array<InstantiationType, Count()>;

    using name_array_type = array_type<std::string_view>;
    using value_array_type = array_type<value_type>;
    using underlying_value_array_type = array_type<underlying_type>;
    using name_value_pair_type = std::pair<const char *, value_type>;

protected:

    constexpr static std::span<name_value_pair_type> NameValueArray()
    {
        static name_value_pair_type array[] = {
// Use your external data here
#if 0
            { "Value1", Value1 },
            { "Value2", Value2 },
            { "Value3", Value3 }
#endif
        };

        return std::span( array );
    }

    constexpr std::size_t Count() const { return NameValueArray().size(); }
};