#include "System/IComparable.hpp"
#include "System/Numerics/INumberBase.hpp"
#include <cstdint>
#include <algorithm>

namespace System::Numerics
{

template <class T>
struct INumber : public IComparable<INumber<T>>,
                 public INumberBase<INumber<T>>
{
    static constexpr T Clamp(T value, T min, T max);

    static constexpr T CopySign(T value, T sign);

    static constexpr T Max(T x, T y);

    static constexpr T MaxNumber(T x, T y);

    static constexpr T Min(T x, T y);
    static constexpr T MinNumber(T x, T y);

    static constexpr int Sign(T value);
};


template <>
struct INumber<bool> : public IComparable<INumber<bool>>,
                       public INumberBase<INumber<bool>>
{
    static constexpr bool Clamp(bool value, bool min, bool max)
    {
        return std::clamp(value, min, max);
    }

    static constexpr bool CopySign(bool value, bool sign)
    {
        UNUSED(value);
        
        return sign;
    }

    static constexpr bool Max(bool x, bool y)
    {
        return std::max(x, y);
    }

    static constexpr bool MaxNumber(bool x, bool y)
    {
        return Max(x, y);
    }

    static constexpr bool Min(bool x, bool y)
    {
        return std::min(x, y);
    }

    static constexpr bool MinNumber(bool x, bool y)
    {
        return Min(x, y);
    }

    static constexpr int Sign(bool value)
    {
        return (value == true) ? 1 : 0;
    }
};


template <>
struct INumber<std::int8_t> : public IComparable<INumber<std::int8_t>>,
                              public INumberBase<INumber<std::int8_t>>
{
    static constexpr std::int8_t Clamp(std::int8_t value, std::int8_t min, std::int8_t max)
    {
        return std::clamp(value, min, max);
    }

    static std::int8_t CopySign(std::int8_t value, std::int8_t sign)
    {
        std::int8_t a = static_cast<std::int8_t>(std::abs(value));

        return (sign < 0) ? 0 - a : a;
    }

    static constexpr std::int8_t Max(std::int8_t x, std::int8_t y)
    {
        return std::max(x, y);
    }
    static constexpr std::int8_t MaxNumber(std::int8_t x, std::int8_t y)
    {
        return Max(x, y);
    }

    static constexpr std::int8_t Min(std::int8_t x, std::int8_t y) { return std::min(x, y); }
    static constexpr std::int8_t MinNumber(std::int8_t x, std::int8_t y) { return Min(x, y); }

    static constexpr int Sign(std::int8_t value)
    {
        if (value < 0)
            return -1;

        if (value > 0)
            return 1;

        return 0; // value == 0 MUST be true
    }
};


template <>
struct INumber<std::int16_t> : public IComparable<INumber<std::int16_t>>,
                               public INumberBase<INumber<std::int16_t>>
{
    static constexpr std::int16_t Clamp(std::int16_t value, std::int16_t min, std::int16_t max)
    {
        return std::clamp(value, min, max);
    }

    static std::int16_t CopySign(std::int16_t value, std::int16_t sign)
    {
        std::int16_t a = static_cast<std::int16_t>(std::abs(value));

        return (sign < 0) ? 0 - a : a;
    }

    static constexpr std::int16_t Max(std::int16_t x, std::int16_t y)
    {
        return std::max(x, y);
    }
    static constexpr std::int16_t MaxNumber(std::int16_t x, std::int16_t y)
    {
        return Max(x, y);
    }

    static constexpr std::int16_t Min(std::int16_t x, std::int16_t y) { return std::min(x, y); }
    static constexpr std::int16_t MinNumber(std::int16_t x, std::int16_t y) { return Min(x, y); }

    static constexpr int Sign(std::int16_t value)
    {
        if (value < 0)
            return -1;

        if (value > 0)
            return 1;

        return 0; // value == 0 MUST be true
    }
};


template <>
struct INumber<std::int32_t> : public IComparable<INumber<std::int32_t>>,
                               public INumberBase<INumber<std::int32_t>>
{
    static constexpr std::int32_t Clamp(std::int32_t value, std::int32_t min, std::int32_t max)
    {
        return std::clamp(value, min, max);
    }

    static std::int32_t CopySign(std::int32_t value, std::int32_t sign)
    {
        std::int32_t a{ std::abs(value) };

        return (sign < 0) ? 0 - a : a;
    }

    static constexpr std::int32_t Max(std::int32_t x, std::int32_t y)
    {
        return std::max(x, y);
    }
    static constexpr std::int32_t MaxNumber(std::int32_t x, std::int32_t y)
    {
        return Max(x, y);
    }

    static constexpr std::int32_t Min(std::int32_t x, std::int32_t y) { return std::min(x, y); }
    static constexpr std::int32_t MinNumber(std::int32_t x, std::int32_t y) { return Min(x, y); }

    static constexpr int Sign(std::int32_t value)
    {
        if (value < 0)
            return -1;

        if (value > 0)
            return 1;

        return 0; // value == 0 MUST be true
    }
};


template <>
struct INumber<std::int64_t> : public IComparable<INumber<std::int64_t>>,
                               public INumberBase<INumber<std::int64_t>>
{
    static constexpr std::int64_t Clamp(std::int64_t value, std::int64_t min, std::int64_t max)
    {
        return std::clamp(value, min, max);
    }

    static std::int64_t CopySign(std::int64_t value, std::int64_t sign)
    {
        std::int64_t a{ std::abs(value) };

        return (sign < 0) ? 0 - a : a;
    }

    static constexpr std::int64_t Max(std::int64_t x, std::int64_t y)
    {
        return std::max(x, y);
    }
    static constexpr std::int64_t MaxNumber(std::int64_t x, std::int64_t y)
    {
        return Max(x, y);
    }

    static constexpr std::int64_t Min(std::int64_t x, std::int64_t y) { return std::min(x, y); }
    static constexpr std::int64_t MinNumber(std::int64_t x, std::int64_t y) { return Min(x, y); }

    static constexpr int Sign(std::int64_t value)
    {
        if (value < 0)
            return -1;

        if (value > 0)
            return 1;

        return 0; // value == 0 MUST be true
    }
};


template <>
struct INumber<std::uint8_t> : public IComparable<INumber<std::uint8_t>>,
                               public INumberBase<INumber<std::uint8_t>>
{
    static constexpr std::uint8_t Clamp(std::uint8_t value, std::uint8_t min, std::uint8_t max)
    {
        return std::clamp(value, min, max);
    }

    static std::uint8_t CopySign(std::uint8_t value, std::uint8_t sign)
    {
        UNUSED(sign);
        
        return value;
    }

    static constexpr std::uint8_t Max(std::uint8_t x, std::uint8_t y)
    {
        return std::max(x, y);
    }
    static constexpr std::uint8_t MaxNumber(std::uint8_t x, std::uint8_t y)
    {
        return Max(x, y);
    }

    static constexpr std::uint8_t Min(std::uint8_t x, std::uint8_t y) { return std::min(x, y); }
    static constexpr std::uint8_t MinNumber(std::uint8_t x, std::uint8_t y) { return Min(x, y); }

    static constexpr int Sign(std::uint8_t value)
    {
        if (value > 0)
            return 1;

        return 0; // value == 0 MUST be true
    }
};


template <>
struct INumber<std::uint16_t> : public IComparable<INumber<std::uint16_t>>,
                                public INumberBase<INumber<std::uint16_t>>
{
    static constexpr std::uint16_t Clamp(std::uint16_t value, std::uint16_t min, std::uint16_t max)
    {
        return std::clamp(value, min, max);
    }

    static std::uint16_t CopySign(std::uint16_t value, std::uint16_t sign)
    {
        UNUSED(sign);
        
        return value;
    }

    static constexpr std::uint16_t Max(std::uint16_t x, std::uint16_t y)
    {
        return std::max(x, y);
    }
    static constexpr std::uint16_t MaxNumber(std::uint16_t x, std::uint16_t y)
    {
        return Max(x, y);
    }

    static constexpr std::uint16_t Min(std::uint16_t x, std::uint16_t y) { return std::min(x, y); }
    static constexpr std::uint16_t MinNumber(std::uint16_t x, std::uint16_t y) { return Min(x, y); }

    static constexpr int Sign(std::uint16_t value)
    {
        if (value > 0)
            return 1;

        return 0; // value == 0 MUST be true
    }
};


template <>
struct INumber<std::uint32_t> : public IComparable<INumber<std::uint32_t>>,
                                public INumberBase<INumber<std::uint32_t>>
{
    static constexpr std::uint32_t Clamp(std::uint32_t value, std::uint32_t min, std::uint32_t max)
    {
        return std::clamp(value, min, max);
    }

    static std::uint32_t CopySign(std::uint32_t value, std::uint32_t sign)
    {
        UNUSED(sign);

        return value;
    }

    static constexpr std::uint32_t Max(std::uint32_t x, std::uint32_t y)
    {
        return std::max(x, y);
    }
    static constexpr std::uint32_t MaxNumber(std::uint32_t x, std::uint32_t y)
    {
        return Max(x, y);
    }

    static constexpr std::uint32_t Min(std::uint32_t x, std::uint32_t y) { return std::min(x, y); }
    static constexpr std::uint32_t MinNumber(std::uint32_t x, std::uint32_t y) { return Min(x, y); }

    static constexpr int Sign(std::uint32_t value)
    {
        if (value > 0)
            return 1;

        return 0; // value == 0 MUST be true
    }
};


template <>
struct INumber<std::uint64_t> : public IComparable<INumber<std::uint64_t>>,
                                public INumberBase<INumber<std::uint64_t>>
{
    static constexpr std::uint64_t Clamp(std::uint64_t value, std::uint64_t min, std::uint64_t max)
    {
        return std::clamp(value, min, max);
    }

    static std::uint64_t CopySign(std::uint64_t value, std::uint64_t sign)
    {
        UNUSED(sign);

        return value;
    }

    static constexpr std::uint64_t Max(std::uint64_t x, std::uint64_t y)
    {
        return std::max(x, y);
    }
    static constexpr std::uint64_t MaxNumber(std::uint64_t x, std::uint64_t y)
    {
        return Max(x, y);
    }

    static constexpr std::uint64_t Min(std::uint64_t x, std::uint64_t y) { return std::min(x, y); }
    static constexpr std::uint64_t MinNumber(std::uint64_t x, std::uint64_t y) { return Min(x, y); }

    static constexpr int Sign(std::uint64_t value)
    {
        if (value > 0)
            return 1;

        return 0; // value == 0 MUST be true
    }
};

}