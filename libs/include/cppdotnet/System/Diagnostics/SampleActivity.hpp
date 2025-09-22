#pragma once

#include <cppdotnet/System/Private/Delegate.hpp>
#include <cppdotnet/System/Diagnostics/ActivitySamplingResult.hpp>
#include <cppdotnet/System/Diagnostics/Activity.hpp>
#include <concepts>


namespace System::Diagnostics
{

template <typename T>
    requires ( std::same_as<T, std::string> || std::same_as<T, ActivityContext> )
struct SampleActivity : Delegate<ActivitySamplingResult, ActivityCreationOptions<T>>
{
    using Delegate<ActivitySamplingResult, ActivityCreationOptions<T>>::Delegate;
    using Delegate<ActivitySamplingResult, ActivityCreationOptions<T>>::operator =;
};

}