module;

export module System:IObservable;

import System:IObserver;

namespace System
{

export
template <class T>
class IObservable
{
public:
    virtual void Subscribe(IObserver<T> &observer) = 0;
protected:
};

}