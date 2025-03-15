#pragma once

#include <string>
#include <format>


namespace System::Collections::Generic
{

template <class TKey, class TValue>
struct KeyValuePair
{
    KeyValuePair(const TKey &k, const TValue &v)
        :
        Key{ k },
        Value{ v }
    {
    }

    std::string ToString() const
    {
        // NOTE: Use Key.ToString() & Value.ToString() in the future
        return std::format("[{}, {}]", Key, Value);
    }

    TKey   Key;
    TValue Value;
};

}