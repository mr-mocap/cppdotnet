#pragma once

#include <cppdotnet/System/Action.hpp>
#include <cppdotnet/System/EventHandler.hpp>
#include <cppdotnet/System/TypeCode.hpp>
#include <cppdotnet/System/Private/private.hpp>
#include <utility>

namespace System
{

template <class T>
class Progress
{
public:
    Progress() = default;
   ~Progress() = default;
    Progress(const Action<T> &handler)
        :
        _action( handler )
    {
    }
    Progress(Action<T> &&handler)
        :
        _action( std::move(handler) )
    {
    }

    Progress &operator =(const Progress<T> &progress)
    {
        ProgressChanged = progress.ProgressChanged;
        _action = progress._action;
        return *this;
    }
    Progress &operator =(Progress<T> &&progress)
    {
        ProgressChanged = std::move(progress.ProgressChanged);
        _action = std::move(progress._action);
        return *this;
    }

    static constexpr TypeCode GetTypeCode() { return TypeCode::Object; }

    void Report(T value)
    {
        if ( _action )
            _action( value );
        this->OnReport( value );
    }

    struct ProgressEventArgs : EventArgs
    {
        ProgressEventArgs() = delete;
        ProgressEventArgs(const T &input) : data{input} { }

        T data;
    };

    EventHandler<ProgressEventArgs> ProgressChanged;

protected:
    Action<T> _action;

    virtual void OnReport(T value);
};


template <class T>
void Progress<T>::OnReport(T value)
{
    if ( ProgressChanged )
        ProgressChanged( ProgressEventArgs{ value } );
}

}
