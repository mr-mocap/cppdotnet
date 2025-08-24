export module System:OperatingSystem;

import System:PlatformID;
import System:Version;


namespace System
{

export
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
};

}


namespace System
{

export
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

}