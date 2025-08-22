#include "System/Collections/Generic/List.hpp"
#include "System/Collections/Generic/KeyValuePair.hpp"
#include "System/Collections/Generic/KeyNotFoundException.hpp"
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
class OrderedDictionary
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

        OrderedDictionary::reference operator*() noexcept
        {
            return reinterpret_cast<OrderedDictionary::reference>( Base::operator *() );
        }

        OrderedDictionary::pointer operator->() noexcept
        {
            return reinterpret_cast<OrderedDictionary::pointer>( Base::operator ->() );
        }

        SpecializedIterator &operator++() noexcept
        {
            Base::operator++();
            return *this;
        }

        SpecializedIterator operator++(int) noexcept
        {
            SpecializedIterator tmp = Base::operator++(1);

            return tmp;
        }

        SpecializedIterator &operator--() noexcept
        {
            Base::operator--();
            return *this;
        }

        SpecializedIterator operator--(int) noexcept
        {
            SpecializedIterator tmp = Base::operator--(1);

            return tmp;
        }

        friend bool operator==(const SpecializedIterator &left, const SpecializedIterator &right) noexcept
        {
            return reinterpret_cast<const Base &>(left) == reinterpret_cast<const Base &>(right);
        }
    };

    struct SpecializedConstIterator : public underlying_datatype::const_iterator
    {
        using Base = underlying_datatype::const_iterator;
        using underlying_datatype::const_iterator::const_iterator;

        SpecializedConstIterator(Base i) : Base( i ) { }

        OrderedDictionary::const_reference operator*() noexcept
        {
            return reinterpret_cast<OrderedDictionary::const_reference>( Base::operator *() );
        }

        OrderedDictionary::const_pointer operator->() noexcept
        {
            return reinterpret_cast<OrderedDictionary::const_pointer>( Base::operator ->() );
        }

        SpecializedConstIterator &operator++() noexcept
        {
            Base::operator++();
            return *this;
        }

        SpecializedConstIterator operator++(int) noexcept
        {
            SpecializedConstIterator tmp = Base::operator++(1);

            return tmp;
        }

        SpecializedConstIterator &operator--() noexcept
        {
            Base::operator--();
            return *this;
        }

        SpecializedConstIterator operator--(int) noexcept
        {
            SpecializedConstIterator tmp = Base::operator--(1);

            return tmp;
        }

        friend bool operator==(const SpecializedConstIterator &left, const SpecializedConstIterator &right) noexcept
        {
            return reinterpret_cast<const Base &>(left) == reinterpret_cast<const Base &>(right);
        }
    };

    struct SpecializedReverseIterator : public underlying_datatype::reverse_iterator
    {
        using Base = underlying_datatype::reverse_iterator;
        using underlying_datatype::reverse_iterator::reverse_iterator;

        SpecializedReverseIterator(Base i) : Base( i ) { }

        OrderedDictionary::reference operator*() noexcept
        {
            return reinterpret_cast<OrderedDictionary::reference>( Base::operator *() );
        }

        OrderedDictionary::pointer operator->() noexcept
        {
            return reinterpret_cast<OrderedDictionary::pointer>( Base::operator ->() );
        }

        SpecializedReverseIterator &operator++() noexcept
        {
            Base::operator++();
            return *this;
        }

        SpecializedReverseIterator operator++(int) noexcept
        {
            SpecializedReverseIterator tmp = Base::operator++(1);

            return tmp;
        }

        SpecializedReverseIterator &operator--() noexcept
        {
            Base::operator--();
            return *this;
        }

        SpecializedReverseIterator operator--(int) noexcept
        {
            SpecializedReverseIterator tmp = Base::operator--(1);

            return tmp;
        }

        friend bool operator==(const SpecializedReverseIterator &left, const SpecializedReverseIterator &right) noexcept
        {
            return reinterpret_cast<const Base &>(left) == reinterpret_cast<const Base &>(right);
        }
    };

    struct SpecializedConstReverseIterator : public underlying_datatype::const_reverse_iterator
    {
        using Base = underlying_datatype::const_reverse_iterator;
        using underlying_datatype::const_reverse_iterator::const_reverse_iterator;

        SpecializedConstReverseIterator(Base i) : Base( i ) { }

        OrderedDictionary::const_reference operator*() noexcept
        {
            return reinterpret_cast<OrderedDictionary::const_reference>( Base::operator *() );
        }

        OrderedDictionary::const_pointer operator->() noexcept
        {
            return reinterpret_cast<OrderedDictionary::const_pointer>( Base::operator ->() );
        }

        SpecializedConstReverseIterator &operator++() noexcept
        {
            Base::operator++();
            return *this;
        }

        SpecializedConstReverseIterator operator++(int) noexcept
        {
            SpecializedConstReverseIterator tmp = Base::operator++(1);

            return tmp;
        }

        SpecializedConstReverseIterator &operator--() noexcept
        {
            Base::operator--();
            return *this;
        }

        SpecializedConstReverseIterator operator--(int) noexcept
        {
            SpecializedConstReverseIterator tmp = Base::operator--(1);

            return tmp;
        }

        friend bool operator==(const SpecializedConstReverseIterator &left, const SpecializedConstReverseIterator &right) noexcept
        {
            return reinterpret_cast<const Base &>(left) == reinterpret_cast<const Base &>(right);
        }
    };
    using iterator               = SpecializedIterator;
    using const_iterator         = SpecializedConstIterator;
    using reverse_iterator       = SpecializedReverseIterator;
    using const_reverse_iterator = SpecializedConstReverseIterator;

    using KeyCollection   = List<key_type>;
    using ValueCollection = List<mapped_type>;

    constexpr OrderedDictionary() = default;
    
    OrderedDictionary(const std::map<key_type, mapped_type> &init_value)
        :
        _data( init_value )
    {
    }

    // This allows the use of either explicit iterator pairs OR the new range syntax
    template <class InputIterator>
    OrderedDictionary(InputIterator first, InputIterator one_past_last)
        :
        _data( first, one_past_last )
    {
    }

    OrderedDictionary(std::initializer_list<std::pair<const TKey, TValue>> il,
               const Compare   &comp = Compare(),
               const Allocator &alloc = Allocator())
        :
        _data( il, comp, alloc )
    {
    }

    OrderedDictionary(std::map<key_type, mapped_type> &&init_value)
        :
        _data( std::move(init_value) )
    {
    }

    constexpr OrderedDictionary(const OrderedDictionary &) = default;
    constexpr OrderedDictionary(OrderedDictionary &&) = default;
    constexpr OrderedDictionary &operator =(const OrderedDictionary &) = default;
    constexpr OrderedDictionary &operator =(OrderedDictionary &&) = default;

    constexpr key_compare Comparer() const { return _data.key_comp(); }

    constexpr size_type Capacity() const { return Count(); }  // NOTE: This isn't really implementable, is it?

    // ICollection interface
    constexpr size_type Count() const { return _data.size(); }

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
        _data.clear();

        POSTCONDITION( _data.empty() );
    }

    constexpr bool Contains(const value_type &key_value_pair) const
    {
        for (const std::pair<const TKey, TValue> &iCurrentIteration : _data)
        {
            if ( iCurrentIteration == key_value_pair )
                return true;
        }
        return false;
    }

    // From IDictionary interface

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
            ThrowWithTarget( KeyNotFoundException( std::format("Key '{}' not found in OrderedDictionary", key) ) );
        }
    }

    constexpr const mapped_type &at(const key_type &key) const
    {
        try
        {
            return _data.at( key );
        }
        catch(const std::out_of_range &)
        {
            ThrowWithTarget( KeyNotFoundException( std::format("Key '{}' not found in OrderedDictionary", key) ) );
        }
    }

    constexpr void Add(const key_type &key, const mapped_type &value)
    {
        using namespace std::literals;

        if ( _data.contains( key ) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the OrderedDictionary", key), "key"sv ) );
        else
            _data[ key ] = value;
        
        POSTCONDITION( ContainsKey(key) );
    }

    bool Remove(const key_type &key)
    {
        return _data.erase( key );
    }

    constexpr bool ContainsKey(const key_type &key) const
    {
        return _data.contains( key );
    }

    constexpr bool TryGetValue(const key_type &key, mapped_type &value_out) const
    {
        auto iter = _data.find( key );

        if ( iter == _data.end() )
        {
            value_out = mapped_type{};
            return false;
        }
        value_out = iter->second;
        return true;
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

    // IList interface

    int IndexOf(const value_type &item) const
    {
        auto iter = _data.find( item.Key() );

        if ( iter == _data.end() )
            return -1; // Not found
        if ( iter->second != item.Value() )
            return -1; // Not found

        return std::distance( _data.begin(), iter );
    }

    void Insert(size_type index, const value_type &kvp)
    {
        using namespace std::literals;

        if ( index > Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        if ( _data.contains( kvp.Key() ) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the OrderedDictionary", kvp.Key()), "key"sv ) );

        auto iter = _data.begin();

        std::advance( iter, index );
        _data.insert( iter, kvp );
    }

    void RemoveAt(size_type index)
    {
        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        auto iter = std::next( _data.begin(), index );

        _data.erase( iter );
    }

    // End of IList interface

    constexpr bool TryAdd(const key_type &key, const mapped_type &value)
    {
        if ( _data.contains( key ) )
            return false;
        _data[ key ] = value;
        return true;
    }

    constexpr bool ContainsValue(const mapped_type &value) const
    {
        for (auto const &v : std::views::values( _data ) )
            if ( v == value )
                return true;
        return false;
    }

    const_reference GetAt(size_type index) const
    {
        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        auto iter = std::next( _data.begin(), index );

        return static_cast<const_reference>(*iter);
    }

    reference GetAt(size_type index)
    {
        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        auto iter = std::next( _data.begin(), index );

        return static_cast<reference>(*iter);
    }

    void SetAt(size_type index, const key_type &key, const mapped_type &value)
    {
        // NOTE: This completely undermines the "ordered" part of OrderedDictionary, but it is here for compatibility with the C# version.
        //       Cannot really implement this in a way that makes sense because the "ordered" part of the dictionary is based on the key, not the index.

        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

#if 0
        auto iter = std::next( _data.begin(), index );

        *iter = std::make_pair( key, value );
#endif
    }

    void SetAt(size_type index, const mapped_type &value)
    {
        if ( index >= Count() )
            ThrowWithTarget( ArgumentOutOfRangeException( std::format("Index '{}' is out of range for OrderedDictionary", index) ) );

        auto iter = std::next( _data.begin(), index );

        iter->second = value; // Set the value at the given index
    }

    void Insert(size_type index, const key_type &key, const mapped_type &value)
    {
        Insert( index, KeyValuePair<key_type, mapped_type>( key, value ) );
    }

    bool Remove(const key_type &key, mapped_type &value_out)
    {
        auto iter = _data.find( key );

        if ( iter == _data.end() )
            return false; // Not found

        value_out = iter->second; // Store the value to return

        _data.erase( iter ); // Now remove the key
        return true;
    }

    int IndexOf(const key_type &key) const
    {
        auto iter = _data.find( key );

        if ( iter == _data.end() )
            return -1; // Not found

        return std::distance( _data.begin(), iter );
    }

    // C++ speicfic stuff
    friend std::strong_ordering operator <=>(const OrderedDictionary &left, const OrderedDictionary &right)
    {
        return left._data <=> right._data;
    }

    // Range-for compatibility
          iterator  begin()                { return _data.begin(); }
    const_iterator  begin() const          { return _data.begin(); }
    const_iterator cbegin() const noexcept { return _data.cbegin(); }

          iterator  end()                { return _data.end(); }
    const_iterator  end()  const         { return _data.end(); }
    const_iterator cend() const noexcept { return _data.cend(); }

          reverse_iterator  rbegin()                { return _data.rbegin(); }
    const_reverse_iterator  rbegin() const          { return _data.rbegin(); }
    const_reverse_iterator crbegin() const noexcept { return _data.crbegin(); }

          reverse_iterator  rend()                { return _data.rend(); }
    const_reverse_iterator  rend() const          { return _data.rend(); }
    const_reverse_iterator crend() const noexcept { return _data.crend(); }
protected:
    std::map<TKey, TValue, Compare, Allocator> _data;
};

// Deduction Guides
template <class TKey, class TValue>
OrderedDictionary(const std::map<TKey, TValue> &) -> OrderedDictionary<TKey, TValue>;

template <class TKey, class TValue>
OrderedDictionary(std::map<TKey, TValue> &&) -> OrderedDictionary<TKey, TValue>;

}

namespace System::Collections::Generic::Private
{

template <typename ...Args>
struct IListIndexer<Generic::OrderedDictionary<Args...>>
{
    static typename Generic::OrderedDictionary<Args...>::const_reference GetAt(const Generic::OrderedDictionary<Args...> &d, std::size_t index) { return d.GetAt(index); }
    static typename Generic::OrderedDictionary<Args...>::reference       GetAt(      Generic::OrderedDictionary<Args...> &d, std::size_t index) { return d.GetAt(index); }

    static typename Generic::OrderedDictionary<Args...>::const_reference GetAt(const Generic::OrderedDictionary<Args...> *d, std::size_t index) { return d->GetAt(index); }
    static typename Generic::OrderedDictionary<Args...>::reference       GetAt(      Generic::OrderedDictionary<Args...> *d, std::size_t index) { return d->GetAt(index); }
};

}