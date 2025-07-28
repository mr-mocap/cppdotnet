#pragma once

#include "System/Private/Delegate.hpp"
#include "System/Exception.hpp"
#include "System/Diagnostics/Activity.hpp"
#include "System/Diagnostics/TagList.hpp"

namespace System::Diagnostics
{

struct ExceptionRecorder : Delegate<void, const Activity &, const Exception &, const TagList &>
{
    using Delegate<void, const Activity &, const Exception &, const TagList &>::Delegate;
    using Delegate<void, const Activity &, const Exception &, const TagList &>::operator =;
};

}