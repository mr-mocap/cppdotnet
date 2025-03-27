#pragma once

#include <string>
#include <format>


namespace System::Collections::Generic
{

template <class TKey, class TValue>
struct KeyValuePair : std::pair<const TKey, TValue>
{
    KeyValuePair(const TKey &k, const TValue &v)
        :
        std::pair( k, v )
    {
    }

    std::string ToString() const
    {
        // NOTE: Use Key.ToString() & Value.ToString() in the future
        return std::format("[{}, {}]", Key, Value);
    }

    const TKey &Key() const { return first; }
    const TKey &Key()       { return first; }

    const TValue &Value() const { return second; }
          TValue &Value()       { return second; }
    
    void Deconstruct(TKey &key_out, TValue &value_out)
    {
        key_out = Key();
        value_out = Value();
    }
};

}