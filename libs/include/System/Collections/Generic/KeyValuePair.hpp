#include <string>
#include <format>


namespace System::Collections::Generic
{

template <class TKey, class TValue>
struct KeyValuePair : std::pair<const TKey, TValue>
{
    using std::pair<const TKey, TValue>::pair;

    //KeyValuePair(const std::pair<const TKey, TValue> &p) : std::pair<const TKey, TValue>( p ) { }

    std::string ToString() const
    {
        // NOTE: Use Key.ToString() & Value.ToString() in the future
        return std::format("[{}, {}]", Key(), Value());
    }

    const TKey &Key() const { return this->first; }
    const TKey &Key()       { return this->first; }

    const TValue &Value() const { return this->second; }
          TValue &Value()       { return this->second; }
    
    void Deconstruct(TKey &key_out, TValue &value_out)
    {
        key_out = Key();
        value_out = Value();
        
        // TODO: RE-setting the object does destroy the old one, but now we have a new one.
        //       Is this really what is wanted?
        this->first = TKey{};
        this->second = TValue{};
    }
};

}