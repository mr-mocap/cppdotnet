#pragma once

import "System/Private/Delegate.hpp";


namespace System
{

/** Encapsulates a method that compares objects of the same type
 *   
 *  @tparam An object type
 * 
 *  @note This uses the three-way return value scheme 
 */
template <typename T>
struct Comparison : Delegate<int, T, T>
{
    using Delegate<int, T, T>::Delegate;
};

// Deduction guides
template <class T>
Comparison(std::function<int (T &, T &)> ) -> Comparison<T>;


}