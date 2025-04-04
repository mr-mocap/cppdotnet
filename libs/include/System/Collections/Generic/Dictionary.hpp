#pragma once

#include "System/Collections/Generic/KeyNotFoundException.hpp"
#include "System/Collections/Generic/List.hpp"
#include "System/Collections/Generic/KeyValuePair.hpp"
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
    using underlying_datatype = std::map<TKey, TValue, Compare, Allocator>;

    using key_type    = TKey;
    using mapped_type = TValue;
    using value_type  = KeyValuePair<TKey, TValue>;
    using size_type   = std::size_t;
    using difference_type = underlying_datatype::difference_type;
    using key_compare     = Compare;
    using allocator_type  = Allocator;
    using reference       =       value_type &;
    using const_reference = const value_type &;
    using pointer         =       KeyValuePair<TKey, TValue> *;
    using const_pointer   = const KeyValuePair<TKey, TValue> *;

    // NOTE: Key Assumption!
    static_assert( sizeof(KeyValuePair<TKey, TValue>) == sizeof(std::pair<const TKey, TValue>) );

    struct SpecializedIterator : public underlying_datatype::iterator
    {
        using Base = underlying_datatype::iterator;
        using underlying_datatype::iterator::iterator;

        SpecializedIterator(Base i) : Base( i ) { }

        Dictionary::reference operator*() const _GLIBCXX_NOEXCEPT
        {
            return reinterpret_cast<Dictionary::reference>( Base::operator *() );
        }

        Dictionary::pointer operator->() const _GLIBCXX_NOEXCEPT
        {
            return reinterpret_cast<Dictionary::pointer>( Base::operator ->() );
        }

        SpecializedIterator &operator++() _GLIBCXX_NOEXCEPT
        {
            Base::operator++();
            return *this;
        }

        SpecializedIterator operator++(int) _GLIBCXX_NOEXCEPT
        {
            SpecializedIterator tmp = Base::operator++(1);

            return tmp;
        }

        SpecializedIterator &operator--() _GLIBCXX_NOEXCEPT
        {
            Base::operator--();
            return *this;
        }

        SpecializedIterator operator--(int) _GLIBCXX_NOEXCEPT
        {
            SpecializedIterator tmp = Base::operator--(1);

            return tmp;
        }

        friend bool operator==(const SpecializedIterator &left, const SpecializedIterator &right) _GLIBCXX_NOEXCEPT
        {
            return reinterpret_cast<const Base &>(left) == reinterpret_cast<const Base &>(right);
        }
    };

    struct SpecializedConstIterator : public underlying_datatype::const_iterator
    {
        using Base = underlying_datatype::const_iterator;
        using underlying_datatype::const_iterator::const_iterator;

        SpecializedConstIterator(Base i) : Base( i ) { }

        Dictionary::const_reference operator*() const _GLIBCXX_NOEXCEPT
        {
            return reinterpret_cast<Dictionary::const_reference>( Base::operator *() );
        }

        Dictionary::const_pointer operator->() const _GLIBCXX_NOEXCEPT
        {
            return reinterpret_cast<Dictionary::const_pointer>( Base::operator ->() );
        }

        SpecializedConstIterator &operator++() _GLIBCXX_NOEXCEPT
        {
            Base::operator++();
            return *this;
        }

        SpecializedConstIterator operator++(int) _GLIBCXX_NOEXCEPT
        {
            SpecializedConstIterator tmp = Base::operator++(1);

            return tmp;
        }

        SpecializedConstIterator &operator--() _GLIBCXX_NOEXCEPT
        {
            Base::operator--();
            return *this;
        }

        SpecializedConstIterator operator--(int) _GLIBCXX_NOEXCEPT
        {
            SpecializedConstIterator tmp = Base::operator--(1);

            return tmp;
        }

        friend bool operator==(const SpecializedConstIterator &left, const SpecializedConstIterator &right) _GLIBCXX_NOEXCEPT
        {
            return reinterpret_cast<const Base &>(left) == reinterpret_cast<const Base &>(right);
        }
    };

    using iterator               = SpecializedIterator;
    using const_iterator         = SpecializedConstIterator;
    using reverse_iterator       = std::reverse_iterator<SpecializedIterator>;
    using const_reverse_iterator = std::reverse_iterator<SpecializedConstIterator>;

    using KeyCollection = List<key_type>;
    using ValueCollection = List<mapped_type>;

    constexpr Dictionary() = default;
    
    Dictionary(const std::map<key_type, mapped_type> &init_value)
        :
        _data( init_value )
    {
    }

    // This allows the use of either explicit iterator pairs OR the new range syntax
    template <class InputIterator>
    Dictionary(InputIterator first, InputIterator one_past_last)
        :
        _data( first, one_past_last )
    {
    }

    Dictionary(std::initializer_list<std::pair<const TKey, TValue>> il,
               const Compare   &comp = Compare(),
               const Allocator &alloc = Allocator())
        :
        _data( il, comp, alloc )
    {
    }

    Dictionary(std::map<key_type, mapped_type> &&init_value)
        :
        _data( std::move(init_value) )
    {
    }

    constexpr Dictionary(const Dictionary &) = default;
    constexpr Dictionary(Dictionary &&) = default;
    constexpr Dictionary &operator =(const Dictionary &) = default;
    constexpr Dictionary &operator =(Dictionary &&) = default;

    constexpr key_compare Comparer() const { return _data.key_comp(); }

    constexpr size_type Capacity() const { return Count(); }  // NOTE: This isn't really implementable, is it?

    constexpr mapped_type &operator[](const key_type &key)
    {
        return _data[key];
    }

    constexpr const mapped_type &operator[](const key_type &key) const
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

    constexpr const mapped_type &at(const key_type &key) const
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

    // ICollection interface
    constexpr size_type Count() const { return _data.size(); }

    bool IsReadOnly() const { return true; }
    bool IsReadOnly()       { return false; }

    bool IsSynchronized() const { return false; }

    constexpr void Add(const key_type &key, const mapped_type &value)
    {
        using namespace std::literals;

        if ( _data.contains( key ) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the Dictionary", key), "key"sv ) );
        else
            _data[ key ] = value;
        
        POSTCONDITION( ContainsKey(key) );
    }

    constexpr void Clear()
    {
        _data.clear();

        POSTCONDITION( _data.empty() );
    }

    constexpr bool Contains(const KeyValuePair<TKey, TValue> &key_value_pair) const
    {
        for (const std::pair<const TKey, TValue> &iCurrentIteration : _data)
        {
            if ( iCurrentIteration == key_value_pair )
                return true;
        }
        return false;
    }

    // C++ speicfic stuff
    friend std::strong_ordering operator <=>(const Dictionary &left, const Dictionary &right)
    {
        return left._data <=> right._data;
    }

    // Range-for compatibility
          iterator  begin()       { return iterator{ _data.begin() }; }
    const_iterator  begin() const { return const_iterator{ _data.begin() }; }
    const_iterator cbegin() const noexcept { return const_iterator{ _data.cbegin() }; }

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

// Deduction Guides
template <class TKey, class TValue>
Dictionary(const std::map<TKey, TValue> &) -> Dictionary<TKey, TValue>;

template <class TKey, class TValue>
Dictionary(std::map<TKey, TValue> &&) -> Dictionary<TKey, TValue>;

}