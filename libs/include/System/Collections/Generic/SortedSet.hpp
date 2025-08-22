#include "System/Private/private.hpp"
#include <set>
#include <functional>

namespace System::Collections::Generic
{

template <class Key,
          class Compare   = std::less<Key>,
          class Allocator = std::allocator<Key> >
class SortedSet
{
public:
    using underlying_datatype = std::set<Key, Compare, Allocator>;

    using key_type    = Key;
    using value_type  = Key;
    using size_type   = underlying_datatype::size_type;
    using difference_type = underlying_datatype::difference_type;
    using key_compare     = Compare;
    using value_compare   = Compare;
    using allocator_type  = Allocator;
    using reference       = value_type &; 
    using const_reference = const value_type &;
    using pointer       = value_type *; 
    using const_pointer = const value_type *;

    SortedSet() = default;
    SortedSet(Compare &comp, Allocator &alloc = Allocator())
        :
        m_data( comp, alloc )
    {
    }

    Compare Comparer() const { return m_data.key_comp(); }

    const_reference Max() const
    {
        if ( m_data.empty() )
        {
            static Key default_value;

            return default_value;
        }

        // NOTE: If we define Max() as the last item (since
        //       the data is sorted based on Compare), then
        //       we have a quick lookup.
        return *(m_data.end() - 1);
    }

    const_reference Min() const
    {
        if ( m_data.empty() )
        {
            static Key default_value;

            return default_value;
        }
        
        // NOTE: If we define Min() as the first item (since
        //       the data is sorted based on Compare), then
        //       we have a quick lookup.
        return *m_data.begin();
    }

    bool Remove(const value_type &key)
    {
        return m_data.erase( key );
    }

    bool TryGetValue(const value_type &key, value_type &value_out)
    {
        auto iter = m_data.find( key );

        if ( iter == m_data.end() )
        {
            value_out = value_type{};
            return false;
        }
        value_out = *iter;
        return true;
    }
#if 0
    void ExceptWith(range_of_values)
    {
        for (const_reference iValue : range)
            m_data.erase( iValue );
    }
#endif
    // ICollection interface
    size_type Count() const { return m_data.size(); }

    bool Add(const_reference value)
    {
        return m_data.insert( value ).second;
    }

    bool Add(key_type &&moved_value)
    {
        return m_data.insert( std::move(moved_value) ).second;
    }

    void Clear()
    {
        m_data.clear();

        POSTCONDITION( m_data.empty() );
    }

    bool Contains(const value_type &item) const
    {
        return m_data.count( item );
    }

#if 0
    void CopyTo();
#endif


protected:
    std::set<Key, Compare, Allocator> m_data;
};

}