import "System/Private/Delegate.hpp";
import "System/EventArgs.hpp";
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