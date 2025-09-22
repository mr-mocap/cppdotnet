#pragma once

#include <cppdotnet/System/Private/Delegate.hpp>
#include <cppdotnet/System/EventArgs.hpp>
#include <concepts>


namespace System
{

template <class TEventArgs = EventArgs>
    requires std::derived_from<TEventArgs, EventArgs>
struct EventHandler : public Delegate<void, const TEventArgs &>
{
    using Delegate<void, const TEventArgs &>::Delegate;
    using Delegate<void, const TEventArgs &>::operator =;
};

}