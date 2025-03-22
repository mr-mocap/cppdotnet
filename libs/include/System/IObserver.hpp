#pragma once


namespace System
{

template <class T>
class IObserver
{
public:

    void OnNext(T value);
    void OnError(Exception &error);
    void OnCompleted();
};

}