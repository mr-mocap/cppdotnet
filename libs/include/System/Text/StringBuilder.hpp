#include "System/Exception.hpp"
#include <string>
#include <string_view>
#if __cplusplus >= 202002L
#include <format>
#include <concepts>
#endif
#include <cstdint>
#include <cstddef>

namespace System::Text
{

class StringBuilder
{
public:
    StringBuilder() = default;
    StringBuilder(std::string_view initial_value) : _string{ initial_value } { }
    StringBuilder(const StringBuilder &other) = default;
    StringBuilder(StringBuilder &&other) = default;

    constexpr size_t Capacity() const { return _string.capacity(); }
    constexpr void   SetCapacity(size_t new_capacity)
    {
        if ( new_capacity < Capacity() )
            ThrowWithTarget( ArgumentOutOfRangeException{"new_capacity", "Operation forces object to be less than the current length of this instance"} );
        if ( new_capacity > MaxCapacity() )
            ThrowWithTarget( ArgumentOutOfRangeException{"new_capacity", "Operation forces object to exceed MaxCapacity"} );

        _string.reserve(new_capacity);
    }

    constexpr size_t Length() const { return _string.size(); }
    constexpr size_t MaxCapacity() const { return _this_max_capacity; }

    StringBuilder &Append(bool value);
    StringBuilder &Append(std::byte value);
    StringBuilder &Append(char value);
    StringBuilder &Append(const char *value);
    StringBuilder &Append(std::string_view value);

    StringBuilder &Append(const StringBuilder &other);

    StringBuilder &Append(int16_t value);
    StringBuilder &Append(int32_t value);
    StringBuilder &Append(int64_t value);
    StringBuilder &Append(uint16_t value);
    StringBuilder &Append(uint32_t value);
    StringBuilder &Append(uint64_t value);

    StringBuilder &Append(float value);
    StringBuilder &Append(double value);

#ifdef __cpp_lib_format
    template <typename ...Args>
        requires (sizeof...(Args) > 0)
    StringBuilder &Append(std::format_string<Args...> &&fmt, Args &&... args)
    {
        return Append( std::string_view( std::vformat(fmt.get(), std::make_format_args(args...)) ) );
    }
#endif

    StringBuilder &AppendLine();
    StringBuilder &AppendLine(std::string_view value);

#ifdef __cpp_lib_format
    template <typename ...Args>
        requires (sizeof...(Args) > 0)
    StringBuilder &AppendLine(std::format_string<Args...> &&fmt, Args &&... args)
    {
        return AppendLine( std::string_view( std::vformat(fmt.get(), std::make_format_args(args...)) ) );
    }
#endif

    StringBuilder &Replace(std::string_view old_value, std::string_view new_value);

    constexpr StringBuilder &Clear()
    {
        _string.clear();
        return *this;
    }

    const std::string &ToString() const { return _string; }

    operator std::string() { return _string; }
    operator std::string_view() { return _string; }

    StringBuilder &operator =(const StringBuilder &other) = default;
    StringBuilder &operator =(StringBuilder &&other) = default;

    const std::string::value_type &operator [](size_t index) const { return _string[index]; }
          std::string::value_type &operator [](size_t index)       { return _string[index]; }
protected:
    std::string _string;
    size_t      _this_max_capacity = _string.max_size();
};

}