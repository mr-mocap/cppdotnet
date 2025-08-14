import "System/IObserver.hpp";

namespace System
{

template <class T>
class IObservable
{
public:
    virtual void Subscribe(IObserver<T> &observer) = 0;
protected:
};

}