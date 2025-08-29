module;

export module System:Func;

export import System:Delegate;
import <concepts>;

namespace System
{

/** Encapsulates a method that returns any type of value and takes any type or amount of parameters
 *   
 *   @tparam RetType  The return type of this @c Func
 *   @tparam ArgTypes A variable-length list of the arguments for this type of @c Func
 */
export
template <typename RetType, typename ...ArgTypes>
    requires ( !std::same_as<RetType, void> )
struct Func : Delegate<RetType, ArgTypes...>
{
    using Delegate<RetType, ArgTypes...>::Delegate;
};

}