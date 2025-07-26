#pragma once

#include "System/Private/Delegate.hpp"
#include "System/Exception.hpp"
#include "System/Diagnostics/Activity.hpp"
#include "System/Diagnostics/TagList.hpp"

namespace System::Diagnostics
{

/** Encapsulates a method that returns no value
 *   
 *   @tparam ArgTypes A variable-length list of the arguments for this type of @c Action
 */
struct ExceptionRecorder : Delegate<void, const Activity &, Exception &&, cosnt TagList &>
{
    using Delegate<void, const Activity &, Exception &&, const TagList &>::Delegate;
};
}