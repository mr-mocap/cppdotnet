module;

export module System:IConvertible;

export import System:TypeCode;
export import <cstddef>;
export import <cstdint>;
export import <string>;

namespace System
{

export
struct IConvertible
{
    virtual ~IConvertible() = default;

    virtual TypeCode GetTypeCode() const = 0;

    virtual bool ToBoolean() const = 0;

    virtual std::byte ToByte() const = 0;

    virtual char ToChar() const = 0;

    virtual std::int16_t ToInt16() const = 0;
    virtual std::int32_t ToInt32() const = 0;
    virtual std::int64_t ToInt64() const = 0;

    virtual std::uint16_t ToUInt16() const = 0;
    virtual std::uint32_t ToUInt32() const = 0;
    virtual std::uint64_t ToUInt64() const = 0;

    virtual float  ToSingle() const = 0;
    virtual double ToDouble() const = 0;

    virtual std::string ToString() const = 0;

    // virtual DateTime ToDateTime() const = 0;
    
    // virtual Decimal ToDecimal() const = 0;
};

}