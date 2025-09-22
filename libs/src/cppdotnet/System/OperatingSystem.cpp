#include <cppdotnet/System/OperatingSystem.hpp>


namespace System
{

PlatformID OperatingSystem::Platform() const
{
    return PlatformID::Unix;
}

Version OperatingSystem::Version() const
{
    return {};
}

bool OperatingSystem::IsLinux() const
{
    return true;
}

bool OperatingSystem::IsAndroid() const
{
    return false;
}

bool OperatingSystem::IsIOS() const
{
    return false;
}

bool OperatingSystem::IsMacCatalyst() const
{
    return false;
}

bool OperatingSystem::IsMacOS() const
{
    return false;
}

bool OperatingSystem::IsTvOS() const
{
    return false;
}

bool OperatingSystem::IsWatchOS() const
{
    return false;
}

bool OperatingSystem::IsWindows() const
{
    return false;
}

}