module;

export module System:EventHandler;

export import System:Delegate;
export import System:EventArgs;
import <concepts>;


namespace System
{

export
template <class TEventArgs = EventArgs>
    requires std::derived_from<TEventArgs, EventArgs>
struct EventHandler : public Delegate<void, TEventArgs &>
{
    using Delegate<void, TEventArgs &>::Delegate;
    using Delegate<void, TEventArgs &>::operator =;
};

}