#pragma once

#include <cppdotnet/System/TypeCode.hpp>
#include <string>
#include <string_view>

namespace System
{

class Version final
{
public:
    Version() = default;
    Version(int major, int minor, int build, int revision)
        :
        _major{ major },
        _minor{ minor },
        _build{ build },
        _revision{ revision }
    {
    }
    Version(int major, int minor, int build)
        :
        _major{ major },
        _minor{ minor },
        _build{ build }
    {
    }
    Version(int major, int minor)
        :
        _major{ major },
        _minor{ minor }
    {
    }
    Version(std::string_view input);
    Version(const Version &other) = default;

    static constexpr TypeCode GetTypeCode() { return TypeCode::Object; }

    int Major() const { return _major; }
    int Minor() const { return _minor; }
    int Build() const { return _build; }
    int Revision() const { return _revision; }

    static Version Parse(std::string_view input);

    std::string ToString() const;
    std::string ToString(int field_count) const;

    Version &operator =(const Version &other) = default;
protected:
    int _major = 0;
    int _minor = 0;
    int _build = -1;
    int _revision = -1;
};

}