#pragma once

#include "System/IObserver.hpp"
#include "System/IDisposable.hpp"

namespace System
{

template <class T>
class IObservable
{
public:
    virtual IDisposable Subscribe(IObserver<T> &observer) = 0;
};

}