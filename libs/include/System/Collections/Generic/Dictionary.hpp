#include "System/Collections/Generic/KeyNotFoundException.hpp"
#include "System/Collections/Generic/List.hpp"
#include "System/Collections/Generic/KeyValuePair.hpp"
#include "System/Exception.hpp"
#include "System/Private/private.hpp"
#include <unordered_map>
#include <functional>
#include <iterator>
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
class Dictionary
{
public:
    using underlying_datatype = std::unordered_map<TKey, TValue, Hash, KeyEqual, Allocator>;

    using key_type    = TKey;
    using mapped_type = TValue;
    using value_type  = KeyValuePair<TKey, TValue>;
    using size_type   = std::size_t;
    using difference_type = underlying_datatype::difference_type;
    using hasher          = Hash;
    using key_equal       = KeyEqual;
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

        Dictionary::reference operator*() noexcept
        {
            return reinterpret_cast<Dictionary::reference>( Base::operator *() );
        }

        Dictionary::pointer operator->() noexcept
        {
            return reinterpret_cast<Dictionary::pointer>( Base::operator ->() );
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

        Dictionary::const_reference operator*() noexcept
        {
            return reinterpret_cast<Dictionary::const_reference>( Base::operator *() );
        }

        Dictionary::const_pointer operator->() noexcept
        {
            return reinterpret_cast<Dictionary::const_pointer>( Base::operator ->() );
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

        friend bool operator==(const SpecializedConstIterator &left, const SpecializedConstIterator &right) noexcept
        {
            return reinterpret_cast<const Base &>(left) == reinterpret_cast<const Base &>(right);
        }
    };

    using iterator       = SpecializedIterator;
    using const_iterator = SpecializedConstIterator;

    using KeyCollection = List<key_type>;
    using ValueCollection = List<mapped_type>;

    constexpr Dictionary() = default;
    
    Dictionary(const std::unordered_map<TKey, TValue, Hash, KeyEqual, Allocator> &init_value)
        :
        m_data( init_value )
    {
    }

    // This allows the use of either explicit iterator pairs OR the new range syntax
    template <class InputIterator>
    Dictionary(InputIterator first, InputIterator one_past_last,
                     std::size_t minimum_initial_bucket_count = 0,
               const Hash       &hash = Hash(),
               const KeyEqual   &comp = KeyEqual(),
               const Allocator &alloc = Allocator())
        :
        m_data( first, one_past_last, minimum_initial_bucket_count, hash, comp, alloc )
    {
    }

    
    Dictionary(std::initializer_list<std::pair<const TKey, TValue>> il,
                     std::size_t minimum_initial_bucket_count = 0,
               const Hash       &hash = Hash(),
               const KeyEqual   &comp = KeyEqual(),
               const Allocator &alloc = Allocator())
        :
        m_data( il, minimum_initial_bucket_count, hash, comp, alloc )
    {
    }

    Dictionary(std::unordered_map<TKey, TValue, Hash, KeyEqual, Allocator> &&init_value)
        :
        m_data( std::move(init_value) )
    {
    }

    constexpr Dictionary(const Dictionary &) = default;
    constexpr Dictionary(Dictionary &&) = default;
    constexpr Dictionary &operator =(const Dictionary &) = default;
    constexpr Dictionary &operator =(Dictionary &&) = default;

    constexpr key_equal Comparer() const { return m_data.key_comp(); }

    constexpr size_type Capacity() const { return Count(); }  // NOTE: This isn't really implementable, is it?

    // ICollection interface
    constexpr size_type Count() const { return m_data.size(); }

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
        m_data.clear();

        POSTCONDITION( m_data.empty() );
    }

    constexpr bool Contains(const KeyValuePair<TKey, TValue> &key_value_pair) const
    {
        for (const std::pair<const TKey, TValue> &iCurrentIteration : m_data)
        {
            if ( iCurrentIteration == key_value_pair )
                return true;
        }
        return false;
    }

    // IDictionary
    constexpr mapped_type &operator[](const key_type &key)
    {
        return m_data[key];
    }

    constexpr const mapped_type &at(const key_type &key) const
    {
        try
        {
            return m_data.at( key );
        }
        catch(const std::out_of_range &)
        {
            ThrowWithTarget( KeyNotFoundException( std::format("Key '{}' not found in Dictionary", key) ) );
        }
    }

    constexpr mapped_type &at(const key_type &key)
    {
        try
        {
            return m_data.at( key );
        }
        catch(const std::out_of_range &)
        {
            ThrowWithTarget( KeyNotFoundException( std::format("Key '{}' not found in Dictionary", key) ) );
        }
    }

    constexpr void Add(const key_type &key, const mapped_type &value)
    {
        using namespace std::literals;

        if ( m_data.contains( key ) )
            ThrowWithTarget( ArgumentException( std::format("Key '{}' is already in the Dictionary", key), "key"sv ) );
        else
            m_data[ key ] = value;
        
        POSTCONDITION( ContainsKey(key) );
    }

    bool Remove(const key_type &key)
    {
        return m_data.erase( key );
    }

    constexpr bool ContainsKey(const key_type &key) const
    {
        return m_data.contains( key );
    }

    constexpr bool TryGetValue(const key_type &key, mapped_type &value_out) const
    {
        auto iter = m_data.find( key );

        if ( iter == m_data.end() )
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
        std::ranges::copy( std::views::keys( m_data ), std::back_inserter( rv ) );
        return rv;
    }

    ValueCollection Values() const
    {
        std::vector<mapped_type> rv;

        rv.reserve( Count() );
        std::ranges::copy( std::views::values( m_data ), std::back_inserter( rv ) );
        return rv;
    }

    // End of IDictionary interface

    constexpr bool TryAdd(const key_type &key, const mapped_type &value)
    {
        if ( m_data.contains( key ) )
            return false;
        m_data[ key ] = value;
        return true;
    }

    constexpr bool ContainsValue(const mapped_type &value) const
    {
        for (auto const &v : std::views::values( m_data ) )
            if ( v == value )
                return true;
        return false;
    }

    // Range-for compatibility
          iterator  begin()                { return m_data.begin(); }
    const_iterator  begin() const          { return m_data.begin(); }
    const_iterator cbegin() const noexcept { return m_data.cbegin(); }

          iterator  end()                { return m_data.end(); }
    const_iterator  end()  const         { return m_data.end(); }
    const_iterator cend() const noexcept { return m_data.cend(); }
protected:
    std::unordered_map<TKey, TValue, Hash, KeyEqual, Allocator> m_data;
};

// Deduction Guides

}