module;

export module System:IObserver;

export import System:Exception;

namespace System
{

export
template <class T>
class IObserver
{
public:

    virtual void OnNext(const T &value) = 0;
    virtual void OnError(Exception &error) = 0;
    virtual void OnCompleted() = 0;
};

}