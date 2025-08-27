module;

export module System:Predicate;

import <concepts>;
export import System:Delegate;

namespace System
{

export
template <typename T>
    requires ( !std::same_as<T, void> )
struct Predicate : Delegate<bool, T>
{
    using Delegate<bool, T>::Delegate;
};

}