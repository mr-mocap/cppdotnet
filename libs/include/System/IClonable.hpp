#pragma once

#include <memory>

namespace System
{

template <class Type>
struct IClonable
{
    virtual std::unique_ptr<Type> Clone() const = 0;
};

}