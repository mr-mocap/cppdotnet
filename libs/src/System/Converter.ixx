module;

export module System:Converter;

export import System:Delegate;


namespace System
{

export
template <typename TInput, typename TOutput>
struct Converter : public Delegate<TInput, TOutput>
{
    using Delegate<TInput, TOutput>::Delegate;
    using Delegate<TInput, TOutput>::operator =;
};

}