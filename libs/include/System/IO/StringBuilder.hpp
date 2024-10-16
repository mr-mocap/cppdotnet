#pragma once

#include <string>
#include <string_view>

namespace System::IO
{

class StringBuilder
{
public:
    StringBuilder() = default;
    StringBuilder(const std::string_view initial_value) : _string{ initial_value } { }
    //StringBuilder(const StringBuilder &other) = default;
    //StringBuilder(const StringBuilder &&other) = default;

    size_t Length() const { return _string.size(); }

    StringBuilder &Append(char value);
    StringBuilder &Append(const std::string_view value);
    StringBuilder &Append(const std::string &value);

    StringBuilder &Clear();

    std::string_view ToString() const { return _string; }

    //StringBuilder &operator =(const StringBuilder &other) = default;
    //StringBuilder &operator =(const StringBuilder &&other) = default;
protected:
    std::string _string;
};

}