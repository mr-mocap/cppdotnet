#pragma once

#include <cppdotnet/System/IObserver.hpp>
#include <cppdotnet/System/IDisposable.hpp>

namespace System
{

template <class T>
class IObservable
{
public:
    virtual ~IObservable() = 0;

    virtual IDisposable Subscribe(IObserver<T> &observer) = 0;
};

}