#pragma once

#include "System/Collections/Generic/KeyNotFoundException.hpp"
#include "System/Collections/Generic/List.hpp"
#include "System/Exception.hpp"
#include "System/Private/private.hpp"
#include <map>
#include <format>
#include <ranges>
#include <compare>
#include <algorithm>

namespace System::Collections::Generic
{

template <class TKey,
          class TValue,
          class Compare   = std::less<TKey>,
          class Allocator = std::allocator<std::pair<const TKey, TValue>>>
class Dictionary
{
public:
    using key_type = TKey;
    using mapped_type = TValue;
    using value_type  = std::map<TKey, TValue, Compare, Allocator>::value_type;
    using size_type   = std::size_t;
    using difference_type = std::map<TKey, TValue, Compare, Allocator>::difference_type;
    using key_compare = Compare;
    using allocator_type = Allocator;
    using reference       = std::map<TKey, TValue, Compare, Allocator>::reference;
    using const_reference = std::map<TKey, TValue, Compare, Allocator>::const_reference;
    using iterator               = std::map<TKey, TValue, Compare, Allocator>::iterator;
    using const_iterator         = std::map<TKey, TValue, Compare, Allocator>::const_iterator;
    using reverse_iterator       = std::map<TKey, TValue, Compare, Allocator>::reverse_iterator;
    using const_reverse_iterator = std::map<TKey, TValue, Compare, Allocator>::const_reverse_iterator;

    using KeyCollection = List<key_type>;
    using ValueCollection = List<mapped_type>;

    constexpr Dictionary() = default;

    constexpr Dictionary(const Dictionary &) = default;
    constexpr Dictionary(Dictionary &&) = default;
    constexpr Dictionary &operator =(const Dictionary &) = default;
    constexpr Dictionary &operator =(Dictionary &&) = default;

    constexpr key_compare Comparer() const { return _data.key_comp(); }

    constexpr size_type Count() const { return _data.size(); }

    constexpr size_type Capacity() const { return Count(); }  // NOTE: This isn't really implementable, is it?

    constexpr mapped_type &operator[](const key_type &key)
    {
        return _data[key];
    }

    constexpr mapped_type &at(const key_type &key)
    {
        try
        {
            return _data.at( key );
        }
        catch(const std::out_of_range &)
        {
            ThrowWithTarget( KeyNotFoundException( std::format("Key '{}' not found in Dictionary", key) ) );
        }
        return mapped_type(); // We should NEVER get here!  Is this correct?
    }

    constexpr void Add(const key_type &key, const mapped_type &value)
    {
        using namespace std::literals;

        if ( _data.contains( key ) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the Dictionary", key), "key"sv ) );
        else
            _data[ key ] = value;
        
        POSTCONDITION( ContainsKey(key) );
    }

    constexpr bool TryAdd(const key_type &key, const mapped_type &value)
    {
        if ( _data.contains( key ) )
            return false;
        _data[ key ] = value;
        return true;
    }

    constexpr bool TryGetValue(const key_type &key, mapped_type &value) const
    {
        auto iter = _data.find( key );

        if ( iter == _data.end() )
        {
            value = mapped_type{};
            return false;
        }
        value = iter->second;
        return true;
    }

    constexpr bool Remove(const key_type &key)
    {
        return _data.erase( key );
    }

    constexpr void Clear()
    {
        _data.clear();

        POSTCONDITION( _data.empty() );
    }

    constexpr bool ContainsKey(const key_type &key) const
    {
        return _data.contains( key );
    }

    constexpr bool ContainsValue(const mapped_type &value) const
    {
        for (auto const &v : std::views::values( _data ) )
            if ( v == value )
                return true;
        return false;
    }

    KeyCollection Keys() const
    {
        std::vector<key_type> rv;

        rv.reserve( Count() );
        std::ranges::copy( std::views::keys( _data ), std::back_inserter( rv ) );
        return rv;
    }

    ValueCollection Values() const
    {
        std::vector<mapped_type> rv;

        rv.reserve( Count() );
        std::ranges::copy( std::views::values( _data ), std::back_inserter( rv ) );
        return rv;
    }

    // C++ speicfic stuff
    friend std::strong_ordering operator <=>(const Dictionary &left, const Dictionary &right)
    {
        return left._data <=> right._data;
    }

    // Range-for compatibility
          iterator  begin()       { return _data.begin(); }
    const_iterator  begin() const { return _data.begin(); }
    const_iterator cbegin() const noexcept { return _data.cbegin(); }

          iterator  end()        { return _data.end(); }
    const_iterator  end()  const { return _data.end(); }
    const_iterator cend() const noexcept { return _data.cend(); }

          reverse_iterator  rbegin()       { return _data.rbegin(); }
    const_reverse_iterator  rbegin() const { return _data.rbegin(); }
    const_reverse_iterator crbegin() const noexcept { return _data.crbegin(); }

          reverse_iterator  rend()       { return _data.rend(); }
    const_reverse_iterator  rend() const { return _data.rend(); }
    const_reverse_iterator crend() const noexcept { return _data.crend(); }
protected:
    std::map<TKey, TValue, Compare, Allocator> _data;
};

}