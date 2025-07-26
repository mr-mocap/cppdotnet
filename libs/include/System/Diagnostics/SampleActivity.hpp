#pragma once

#include "System/Private/Delegate.hpp"
#include <concepts>


namespace System::Diagnostics
{

template <typename RetType, typename ...ArgTypes>
    requires ( !std::same_as<RetType, void> )
struct SampleActivity : Delegate<RetType, ArgTypes...>
{
    using Delegate<RetType, ArgTypes...>::Delegate;
    using Delegate<RetType, ArgTypes...>::operator =;
};

}