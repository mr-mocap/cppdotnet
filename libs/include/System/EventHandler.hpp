#pragma once

#include "System/Private/Delegate.hpp"
#include "System/EventArgs.hpp"
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