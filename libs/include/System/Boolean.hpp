#pragma once

#include <string_view>

namespace System
{

class Boolean
{
public:
    constexpr Boolean() { }
    constexpr Boolean(bool value) : _value{ value } { }

    static constexpr Boolean True() { return Boolean(true); }
    static constexpr Boolean False() { return Boolean(false); }

    static const std::string_view FalseString;
    static const std::string_view TrueString;

    bool Value() const { return _value; }
    void Value(bool new_value) { new_value = new_value; }
protected:
    bool _value = false;
};

}