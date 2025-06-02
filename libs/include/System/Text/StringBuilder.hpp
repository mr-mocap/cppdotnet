#pragma once

#include <string>
#include <string_view>
#if __cplusplus >= 202002L
#include <format>
#endif
#include <cstdint>

namespace System::Text
{

class StringBuilder
{
public:
    StringBuilder() = default;
    StringBuilder(std::string_view initial_value) : _string{ initial_value } { }
    StringBuilder(const StringBuilder &other) = default;
    StringBuilder(StringBuilder &&other) = default;

    size_t Capacity() const { return _string.capacity(); }
    void   SetCapacity(size_t new_capacity) { _string.reserve(new_capacity); }

    size_t Length() const { return _string.size(); }
    size_t MaxCapacity() const { return _string.max_size(); }

    StringBuilder &Append(bool value);
    StringBuilder &Append(char value);
    StringBuilder &Append(const char *value);
    StringBuilder &Append(std::string_view value);
    StringBuilder &Append(const std::string &value);

    StringBuilder &Append(const StringBuilder &other);

    StringBuilder &Append(int16_t value);
    StringBuilder &Append(int32_t value);
    StringBuilder &Append(int64_t value);
    StringBuilder &Append(uint16_t value);
    StringBuilder &Append(uint32_t value);
    StringBuilder &Append(uint64_t value);

    StringBuilder &Append(float value);
    StringBuilder &Append(double value);

    StringBuilder &AppendLine();
    StringBuilder &AppendLine(std::string_view value);

#ifdef __cpp_lib_format
    template <typename ...Args>
    StringBuilder &AppendFormat(std::string_view fmt, Args&&... args)
    {
        Append( std::vformat(fmt, std::make_format_args(args...)) );
        return *this;
    }
#endif

    StringBuilder &Replace(std::string_view old_value, std::string_view new_value);

    StringBuilder &Clear();

    const std::string &ToString() const { return _string; }

    operator std::string() { return _string; }
    operator std::string_view() { return _string; }

    StringBuilder &operator =(const StringBuilder &other) = default;
    StringBuilder &operator =(StringBuilder &&other) = default;

    const std::string::value_type &operator [](size_t index) const { return _string[index]; }
          std::string::value_type &operator [](size_t index)       { return _string[index]; }
protected:
    std::string _string;
};

}