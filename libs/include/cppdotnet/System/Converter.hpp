#include <cppdotnet/System/Private/Delegate.hpp>
#include <concepts>


namespace System
{

template <typename TInput, typename TOutput>
struct Converter : public Delegate<TInput, TOutput>
{
    using Delegate<TInput, TOutput>::Delegate;
    using Delegate<TInput, TOutput>::operator =;
};

}