#pragma once

#include <string>
#include <string_view>

namespace System::Text
{

class StringBuilder
{
public:
    StringBuilder() = default;
    StringBuilder(const std::string_view initial_value) : _string{ initial_value } { }
    StringBuilder(const StringBuilder &other) = default;
    StringBuilder(StringBuilder &&other) = default;

    size_t Length() const { return _string.size(); }

    StringBuilder &Append(char value);
    StringBuilder &Append(const std::string_view value);
    StringBuilder &Append(const std::string &value);

    StringBuilder &Clear();

    std::string ToString() const { return _string; }

    operator std::string() { return _string; }
    operator std::string_view() { return _string; }

    StringBuilder &operator =(const StringBuilder &other) = default;
    StringBuilder &operator =(StringBuilder &&other) = default;
protected:
    std::string _string;
};

}