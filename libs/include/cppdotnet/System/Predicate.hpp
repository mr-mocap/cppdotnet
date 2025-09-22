#pragma once

#include <cppdotnet/System/Private/Delegate.hpp>
#include <concepts>


namespace System
{

template <typename T>
    requires ( !std::same_as<T, void> )
struct Predicate : Delegate<bool, T>
{
    using Delegate<bool, T>::Delegate;
    using Delegate<bool, T>::operator =;
};

// Deduction guides
// template <typename T>
// Predicate(std::function<bool (const T &)> )   -> Predicate<T>;

// template <typename T>
// Predicate(std::function<bool (const T &)> &&) -> Predicate<T>;

}