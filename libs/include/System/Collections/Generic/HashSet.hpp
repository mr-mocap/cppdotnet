#include "System/Private/private.hpp"
#include "System/Predicate.hpp"
#include "System/Exception.hpp"
#include <unordered_set>
#include <algorithm>


namespace System::Collections::Generic
{

template <class Key,
          class Hash = std::hash<Key>,
          class KeyEqual  = std::equal_to<Key>,
          class Allocator = std::allocator<Key> >
class HashSet
{
public:
    using underlying_datatype = std::unordered_set<Key, Hash, KeyEqual, Allocator>;

    using key_type   = Key;
    using value_type = Key;
    using size_type  = underlying_datatype::size_type;
    using difference_type = underlying_datatype::difference_type;
    using hasher     = Hash;
    using key_equal  = KeyEqual;
    using allocator_type = Allocator;

    using reference        =       value_type &;
    using const_reference  = const value_type &;
    using pointer          =       value_type *;
    using const_pointer    = const value_type *;

    using iterator       = underlying_datatype::iterator;
    using const_iterator = underlying_datatype::const_iterator;

    HashSet() = default;

    constexpr size_type Capacity() const { return Count(); }  // NOTE: This isn't really implementable, is it?

    constexpr key_equal Comparer() const { return m_data.key_comp(); }

    // ICollection interface
    constexpr size_type Count() const { return m_data.size(); }

    bool IsReadOnly() const { return true; }
    bool IsReadOnly()       { return false; }

    constexpr bool Add(const value_type &item)
    {
        std::pair<iterator, bool> result = m_data.insert( item );

        return result.second;
    }

    constexpr void Clear()
    {
        m_data.clear();

        POSTCONDITION( m_data.empty() );
    }

    bool Contains(const value_type &value) const
    {
        return m_data.contains( value );
    }

#if 0
    void CopyTo(Span destination) const
    {
        if ( destination.Length() < Length() )
            ThrowWithTarget( System::ArgumentException{"Destination Span is shorter than the source Span", "destination"} );
        
        std::ranges::copy( _data, destination._data.begin() );
    }
#endif

    bool Remove(const key_type &key)
    {
        bool result = m_data.erase( key );

        return result;
    }

    template <class T>
    size_type RemoveWhere(Predicate<T> &predicate)
    {
        if ( !predicate )
            ThrowWithTarget( System::ArgumentNullException{"predicate", "Predicate is not set"} );

        return std::erase_if( m_data, predicate );
    }

    bool TryGetValue(const key_type &key, key_type &value_out) const
    {
        auto iter = m_data.find( key );

        if ( iter == m_data.end() )
        {
            value_out = key_type{};
            return false;
        }
        value_out = iter->second;
        return true;
    }
protected:
    std::unordered_set<Key> m_data;
};

}