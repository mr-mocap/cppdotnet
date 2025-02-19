#pragma once

#include <string>
#include <string_view>

namespace System
{

template <class ImplementationType>
struct IFormattable
{
    std::string ToString(const std::string_view format) const;
};

}