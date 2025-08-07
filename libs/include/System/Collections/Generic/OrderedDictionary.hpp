#pragma once

#include "System/Collections/Generic/Dictionary.hpp"
#include "System/Collections/Generic/Private/IListInterface.hpp"
#include "System/Private/private.hpp"
#include <format>
#include <ranges>
#include <compare>
#include <algorithm>

namespace System::Collections::Generic
{

template <class TKey,
          class TValue,
          class Hash      = std::hash<TKey>,
          class KeyEqual  = std::equal_to<TKey>,
          class Allocator = std::allocator<std::pair<const TKey, TValue>>>
class OrderedDictionary
{
public:
    using underlying_datatype = List<TKey>;

    using key_type    = TKey;
    using mapped_type = TValue;
    using value_type  = KeyValuePair<TKey, TValue>;
    using size_type   = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_equal       = KeyEqual;
    using allocator_type  = Allocator;
    using reference       =       value_type &;
    using const_reference = const value_type &;
    using pointer         =       KeyValuePair<TKey, TValue> *;
    using const_pointer   = const KeyValuePair<TKey, TValue> *;

    // NOTE: Key Assumption!
    static_assert( sizeof(KeyValuePair<TKey, TValue>) == sizeof(std::pair<const TKey, TValue>) );

    using iterator               = Dictionary<TKey, TValue, Hash, KeyEqual, Allocator>::iterator;
    using const_iterator         = Dictionary<TKey, TValue, Hash, KeyEqual, Allocator>::const_iterator;

    using KeyCollection   = List<key_type>;
    using ValueCollection = List<mapped_type>;

    constexpr OrderedDictionary() = default;
    
    OrderedDictionary(const std::unordered_map<key_type, mapped_type> &init_value)
        :
        _list( std::views::keys( init_value ) ),
        _dictionary( init_value )
    {
    }

    // This allows the use of either explicit iterator pairs OR the new range syntax
    template <class InputIterator>
    OrderedDictionary(InputIterator first, InputIterator one_past_last)
        :
        _dictionary( first, one_past_last )
    {
        _list = _dictionary.Keys();
    }

    OrderedDictionary(std::initializer_list<std::pair<const TKey, TValue>> il)
        :
        _dictionary( il )
    {
        _list = _dictionary.Keys();
    }

    OrderedDictionary(std::unordered_map<key_type, mapped_type> &&init_value)
        :
        _dictionary( std::move(init_value) )
    {
        _list = _dictionary.Keys();
    }

    constexpr OrderedDictionary(const OrderedDictionary &) = default;
    constexpr OrderedDictionary(OrderedDictionary &&) = default;
    constexpr OrderedDictionary &operator =(const OrderedDictionary &) = default;
    constexpr OrderedDictionary &operator =(OrderedDictionary &&) = default;

    constexpr key_equal Comparer() const { return _dictionary.key_comp(); }

    constexpr size_type Capacity() const { return Count(); }  // NOTE: This isn't really implementable, is it?

    // ICollection interface
    constexpr size_type Count() const { return _dictionary.Count(); }

    bool IsReadOnly() const { return true; }
    bool IsReadOnly()       { return false; }

    bool IsSynchronized() const { return false; }

    constexpr void Add(const value_type &item)
    {
        Add( item.Key(), item.Value() );
    }

    bool Remove(const value_type &kvp)
    {
        return Remove( kvp.Key() );
    }

    constexpr void Clear()
    {
        _dictionary.Clear();
        _list.Clear();

        POSTCONDITION( _dictionary.Count() == 0 );
        POSTCONDITION( _list.Count() == 0 );
    }

    constexpr bool Contains(const value_type &key_value_pair) const
    {
        for (const std::pair<const TKey, TValue> &iCurrentIteration : _dictionary)
        {
            if ( iCurrentIteration == key_value_pair )
                return true;
        }
        return false;
    }

    // From IDictionary interface

    constexpr mapped_type &operator[](const key_type &key)
    {
        return _dictionary[key];
    }

    constexpr mapped_type &at(const key_type &key)
    {
        try
        {
            return _dictionary.at( key );
        }
        catch(const KeyNotFoundException &)
        {
            ThrowWithTarget( KeyNotFoundException( std::format("Key '{}' not found in OrderedDictionary", key) ) );
        }
    }

    constexpr const mapped_type &at(const key_type &key) const
    {
        try
        {
            return _dictionary.at( key );
        }
        catch(const KeyNotFoundException &)
        {
            ThrowWithTarget( KeyNotFoundException( std::format("Key '{}' not found in OrderedDictionary", key) ) );
        }
    }

    constexpr void Add(const key_type &key, const mapped_type &value)
    {
        if ( _dictionary.ContainsKey( key ) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the OrderedDictionary", key), "key" ) );

        _list.Add( key );
        _dictionary[ key ] = value;
        
        POSTCONDITION( ContainsKey(key) );
    }

    bool Remove(const key_type &key)
    {
        return _dictionary.Remove( key ) && _list.Remove( key );
    }

    constexpr bool ContainsKey(const key_type &key) const
    {
        return _dictionary.ContainsKey( key );
    }

    constexpr bool TryGetValue(const key_type &key, mapped_type &value_out) const
    {
        return _dictionary.TryGetValue( key, value_out );
    }

    KeyCollection Keys() const
    {
        return _list;
    }

    ValueCollection Values() const
    {
        std::vector<mapped_type> rv;

        rv.reserve( Count() );
        std::ranges::copy( std::views::values( _dictionary ), std::back_inserter( rv ) );
        return rv;
    }

    // IList interface

    size_type IndexOf(const value_type &item) const
    {
        return _list.IndexOf( item.Key() );
    }

    void Insert(size_type index, const value_type &kvp)
    {
        if ( index > Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        if ( _list.Contains( kvp.Key() ) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the OrderedDictionary", kvp.Key()), "key" ) );

        _list.Insert( index, kvp.Key() );
        _dictionary.Add( kvp );
    }

    void RemoveAt(size_type index)
    {
        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        auto &item = _list[ index ];

        _dictionary.Remove( item );
        _list.RemoveAt( index );
    }

    // End of IList interface

    constexpr bool TryAdd(const key_type &key, const mapped_type &value)
    {
        if ( _dictionary.TryAdd( key, value ) )
        {
            _list.Add( key );
            return true;
        }
        return false;
    }

    constexpr bool ContainsValue(const mapped_type &value) const
    {
        return _dictionary.ContainsValue( value );
    }

    const_reference GetAt(size_type index) const
    {
        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        auto iter = std::next( _dictionary.begin(), index );

        return *iter;
    }

    reference GetAt(size_type index)
    {
        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        auto iter = std::next( _dictionary.begin(), index );

        return *iter;
    }

    void SetAt(size_type index, const key_type &key, const mapped_type &value)
    {
        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        auto iter = std::next( _dictionary.begin(), index );

        *iter = std::make_pair( key, value );
        _list[ index ] = key;
    }

    void SetAt(size_type index, const mapped_type &value)
    {
        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        auto iter = std::next( _dictionary.begin(), index );

        iter->second = value;
    }

    void Insert(size_type index, const key_type &key, const mapped_type &value)
    {
        Insert( index, KeyValuePair<key_type, mapped_type>( key, value ) );
    }

    bool Remove(const key_type &key, mapped_type &value_out)
    {
        if ( _dictionary.TryGetValue( key, value_out ) )
        {
            _list.Remove( key );
            return true;
        }
        return false;
    }

    size_t IndexOf(const key_type &key) const
    {
        return _list.IndexOf( key );
    }

    // C++ speicfic stuff
    friend std::strong_ordering operator <=>(const OrderedDictionary &left, const OrderedDictionary &right)
    {
        return (left._list <=> right._list) && (left._dictionary <=> right._dictionary);
    }

    // Range-for compatibility
          iterator  begin()                { return _dictionary.begin(); }
    const_iterator  begin() const          { return _dictionary.begin(); }
    const_iterator cbegin() const noexcept { return _dictionary.cbegin(); }

          iterator  end()                { return _dictionary.end(); }
    const_iterator  end()  const         { return _dictionary.end(); }
    const_iterator cend() const noexcept { return _dictionary.cend(); }

    //       reverse_iterator  rbegin()                { return _dictionary.rbegin(); }
    // const_reverse_iterator  rbegin() const          { return _dictionary.rbegin(); }
    // const_reverse_iterator crbegin() const noexcept { return _dictionary.crbegin(); }

    //       reverse_iterator  rend()                { return _dictionary.rend(); }
    // const_reverse_iterator  rend() const          { return _dictionary.rend(); }
    // const_reverse_iterator crend() const noexcept { return _dictionary.crend(); }
protected:
    List<TKey>   _list;
    Dictionary<TKey, TValue, Hash, KeyEqual, Allocator> _dictionary;
};

// Deduction Guides
template <class TKey, class TValue>
OrderedDictionary(const std::unordered_map<TKey, TValue> &) -> OrderedDictionary<TKey, TValue>;

template <class TKey, class TValue>
OrderedDictionary(std::unordered_map<TKey, TValue> &&) -> OrderedDictionary<TKey, TValue>;

}

namespace System::Collections::Generic::Private
{

template <typename KeyT, typename ValueT>
struct IListIndexer<Generic::OrderedDictionary<KeyT, ValueT>>
{
    static typename Generic::OrderedDictionary<KeyT, ValueT>::const_reference GetAt(const Generic::OrderedDictionary<KeyT, ValueT> &d, std::size_t index) { return d.GetAt(index); }
    static typename Generic::OrderedDictionary<KeyT, ValueT>::reference       GetAt(      Generic::OrderedDictionary<KeyT, ValueT> &d, std::size_t index) { return d.GetAt(index); }

    static typename Generic::OrderedDictionary<KeyT, ValueT>::const_reference GetAt(const Generic::OrderedDictionary<KeyT, ValueT> *d, std::size_t index) { return d->GetAt(index); }
    static typename Generic::OrderedDictionary<KeyT, ValueT>::reference       GetAt(      Generic::OrderedDictionary<KeyT, ValueT> *d, std::size_t index) { return d->GetAt(index); }
};

}