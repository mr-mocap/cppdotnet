#pragma once

#include <cppdotnet/System/Collections/Generic/KeyValuePair.hpp>
#include <cppdotnet/System/Collections/Generic/List.hpp>
#include <string>

namespace System::Diagnostics::Types
{

using NameObjectPair = Collections::Generic::KeyValuePair<std::string, void *>;

using NameObjectPairList = Collections::Generic::List<NameObjectPair>;

}