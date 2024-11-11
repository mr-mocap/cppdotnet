#pragma once

#include <string>
#include <string_view>
#include <cstdint>

namespace System::Text
{

class StringBuilder
{
public:
    StringBuilder() = default;
    StringBuilder(const std::string_view initial_value) : _string{ initial_value } { }
    StringBuilder(const StringBuilder &other) = default;
    StringBuilder(StringBuilder &&other) = default;

    size_t Capacity() const { return _string.capacity(); }
    void   SetCapacity(size_t new_capacity) { _string.reserve(new_capacity); }

    size_t Length() const { return _string.size(); }
    size_t MaxCapacity() const { return _string.max_size(); }

    StringBuilder &Append(bool value);
    StringBuilder &Append(char value);
    StringBuilder &Append(const char *value);
    StringBuilder &Append(const std::string_view value);
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
    StringBuilder &AppendLine(const std::string_view value);

    StringBuilder &Replace(const std::string_view old_value, const std::string_view new_value);

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