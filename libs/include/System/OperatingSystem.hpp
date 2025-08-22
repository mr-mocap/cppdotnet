#include "System/PlatformID.hpp"
#include "System/Version.hpp"


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
};

}