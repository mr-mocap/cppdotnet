module;

export module System:Action;

export import System:Delegate;


namespace System
{

/** Encapsulates a method that returns no value
 *   
 *   @tparam ArgTypes A variable-length list of the arguments for this type of @c Action
 */
export
template <typename ...ArgTypes>
struct Action : Delegate<void, ArgTypes...>
{
    using Delegate<void, ArgTypes...>::Delegate;
};

// Deduction guides
Action(std::function<void ()> ) -> Action<>; ///@< Default to function that neither takes nor returns a value

}
