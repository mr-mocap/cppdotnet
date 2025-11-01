#pragma once

#include <cppdotnet/System/PlatformID.hpp>
#include <cppdotnet/System/Version.hpp>
#include <cppdotnet/System/TypeCode.hpp>


namespace System
{

class OperatingSystem final
{
public:

    PlatformID      Platform() const;
    System::Version Version() const;

    bool IsLinux() const;
    bool IsAndroid() const;
    bool IsIOS() const;
    bool IsMacCatalyst() const;
    bool IsMacOS() const;
    bool IsTvOS() const;
    bool IsWatchOS() const;
    bool IsWindows() const;

    static constexpr TypeCode GetTypeCode() { return TypeCode::Object; }
};

}