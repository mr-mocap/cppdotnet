#pragma once

namespace System
{

class Exception;

template <class T>
class IObserver
{
public:
    virtual void OnNext(const T &value) = 0;
    virtual void OnError(Exception &error) = 0;
    virtual void OnCompleted() = 0;
};

}