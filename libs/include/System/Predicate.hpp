import "System/Private/Delegate.hpp";
import <concepts>;


namespace System
{

template <typename T>
    requires ( !std::same_as<T, void> )
struct Predicate : Delegate<bool, T>
{
    using Delegate<bool, T>::Delegate;
};

}