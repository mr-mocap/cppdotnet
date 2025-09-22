#pragma once

#include <cppdotnet/System/Private/Delegate.hpp>
#include <concepts>
#include <tuple>

namespace System
{

namespace Types
{

// Trait to reverse the order: takes ArgTypes..., RetType
template <typename...>
struct SplitArgs;

template <typename Last>
struct SplitArgs<Last> {
    using RetType = Last;
    using ArgTypesTuple = std::tuple<>;
};

template <typename First, typename... Rest>
struct SplitArgs<First, Rest...> {
private:
    using TailSplit = SplitArgs<Rest...>;
public:
    using RetType = typename TailSplit::RetType;

    template <typename... Args>
    struct Prepend;

    template <typename... Args>
    struct Prepend<std::tuple<Args...>> {
        using type = std::tuple<First, Args...>;
    };

    using ArgTypesTuple = typename Prepend<typename TailSplit::ArgTypesTuple>::type;
};

// Convert tuple to parameter pack
template <typename RetType, typename Tuple>
struct FuncImpl;

template <typename RetType, typename... ArgTypes>
struct FuncImpl<RetType, std::tuple<ArgTypes...>> : Delegate<RetType, ArgTypes...> {
    using Delegate<RetType, ArgTypes...>::Delegate;
    using Delegate<RetType, ArgTypes...>::operator=;
};

}

// Public-facing Func
template <typename... Args>
using Func = Types::FuncImpl<
    typename Types::SplitArgs<Args...>::RetType,
    typename Types::SplitArgs<Args...>::ArgTypesTuple
>;
#if 0
/** Encapsulates a method that returns any type of value and takes any type or amount of parameters
 *   
 *   @tparam RetType  The return type of this @c Func
 *   @tparam ArgTypes A variable-length list of the arguments for this type of @c Func
 */
template <typename RetType, typename ...ArgTypes>
    requires ( !std::same_as<RetType, void> )
struct Func : Delegate<RetType, ArgTypes...>
{
    using Delegate<RetType, ArgTypes...>::Delegate;
    using Delegate<RetType, ArgTypes...>::operator =;
};
#endif
}