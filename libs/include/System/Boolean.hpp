#pragma once

#include "System/IConvertible.hpp"
#include "System/IComparable.hpp"
#include "System/IEquatable.hpp"
#include <string_view>
#include <compare>

namespace System
{

class Boolean : public IComparable<Boolean>,
                public IConvertible,
                public IEquatable<Boolean>
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

    // IConvertible Interface
    TypeCode GetTypeCode() const override { return TypeCode::Boolean; }

    bool ToBoolean() const override { return _value; }

    std::byte ToByte() const override { return std::byte{_value}; }

    char ToChar() const override { return {_value}; }

    std::int16_t ToInt16() const override { return {_value}; }
    std::int32_t ToInt32() const override { return {_value}; }
    std::int64_t ToInt64() const override { return {_value}; }

    std::uint16_t ToUInt16() const override { return {_value}; }
    std::uint32_t ToUInt32() const override { return {_value}; }
    std::uint64_t ToUInt64() const override { return {_value}; }

    float  ToSingle() const override { return static_cast<float>(_value); }
    double ToDouble() const override { return static_cast<double>(_value); }

    std::string ToString() const override { return (_value) ? std::string{TrueString} : std::string{FalseString}; }

    // IComparable Interface
    int CompareTo(const Boolean &other) const override;

    // IEquatable Interface
    bool Equals(const Boolean &other) const override;

    operator bool() const { return _value; }

    std::strong_ordering operator <=>(const Boolean &other) const { return _value <=> other._value; }
    bool operator ==(const Boolean other) const { return _value == other._value; }
protected:
    bool _value = false;
};

}