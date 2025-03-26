#pragma once

#include "System/Private/Delegate.hpp"
#include "System/EventArgs.hpp"
#include <concepts>


namespace System
{

template <class TEventArgs>
    requires std::derived_from<TEventArgs, EventArgs>
struct EventHandler : public Delegate<void, TEventArgs &>
{
    using Delegate<void, TEventArgs &>::Delegate;
    using Delegate<void, TEventArgs &>::operator =;
};


struct EmptyEventHandler : EventHandler<System::EventArgs>
{
    using EventHandler<System::EventArgs>::EventHandler;
    using EventHandler<System::EventArgs>::operator =;
};

}