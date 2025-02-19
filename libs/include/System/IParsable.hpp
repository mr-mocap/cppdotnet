#pragma once

#include <optional>

namespace System
{

template <class Derived>
struct IParsable
{
#if 0
    static Derived Parse();
    static std::optional<Derived> TryParse();
#endif
};

}