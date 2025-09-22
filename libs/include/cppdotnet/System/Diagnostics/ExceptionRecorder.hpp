#pragma once

#include <cppdotnet/System/Private/Delegate.hpp>
#include <cppdotnet/System/Exception.hpp>
#include <cppdotnet/System/Diagnostics/Activity.hpp>
#include <cppdotnet/System/Diagnostics/TagList.hpp>

namespace System::Diagnostics
{

struct ExceptionRecorder : Delegate<void, const Activity &, const Exception &, const TagList &>
{
    using Delegate<void, const Activity &, const Exception &, const TagList &>::Delegate;
    using Delegate<void, const Activity &, const Exception &, const TagList &>::operator =;
};

}