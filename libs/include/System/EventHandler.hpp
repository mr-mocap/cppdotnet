#pragma once

#include "System/Private/Delegate.hpp"
#include "System/EventArgs.hpp"
#include <concepts>


namespace System
{

template <class TEventArgs>
    requires std::derived_from<TEventArgs, EventArgs>
struct EventHandler : Delegate<void, TEventArgs>
{
    using Delegate<void, TEventArgs>::Delegate;
};

}