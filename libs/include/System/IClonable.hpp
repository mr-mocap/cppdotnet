#pragma once

#include <memory>

namespace System
{

template <class Type>
struct IClonable
{
    std::unique_ptr<Type> Clone() const;
};

}