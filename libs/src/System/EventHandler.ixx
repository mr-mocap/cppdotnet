module;

export module System:EventHandler;

import System:Delegate;
import System:EventArgs;
import <concepts>;


namespace System
{

template <class TEventArgs = EventArgs>
    requires std::derived_from<TEventArgs, EventArgs>
struct EventHandler : public Delegate<void, TEventArgs &>
{
    using Delegate<void, TEventArgs &>::Delegate;
    using Delegate<void, TEventArgs &>::operator =;
};

}