#pragma once

#include "System/Collections/Generic/List.hpp"


namespace System::Collections::Specialized
{

template <class Compare   = std::less<std::string>,
          class Allocator = std::allocator<std::pair<const std::string, std::string>>>
class StringDictionary : public Dictionary<std::string, std::string, Compare, Allocator>
{
public:
    using Dictionary<std::string, std::string, Compare, Allocator>::Dictionary;
};

}