#pragma once

namespace System
{

template <class T>
class IProgress
{
public:
    virtual ~IProgress() = default;

    virtual void Report(T value) = 0;
};

}
