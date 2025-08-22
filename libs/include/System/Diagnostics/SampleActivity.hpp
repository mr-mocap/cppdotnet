#include "System/Private/Delegate.hpp"


namespace System::Diagnostics
{

template <typename RetType, typename ...ArgTypes>
    requires ( !std::same_as<RetType, void> )
struct SampleActivity : Delegate<RetType, ArgTypes...>
{
    using Delegate<RetType, ArgTypes...>::Delegate;
};

}