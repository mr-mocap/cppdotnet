#pragma once

#include <cppdotnet/System/Exception.hpp>
#include <cppdotnet/System/Predicate.hpp>
#include <cppdotnet/System/TypeCode.hpp>
#include <vector>
#include <initializer_list>
#include <string_view>
#include <algorithm>


namespace System::Collections::Generic
{

template <typename T> class List;

template <typename T>
class ListIListInterfaceCustomization
{
public:
    template <typename U>
    size_t IndexOf(const U &item) const
    {
        return static_cast<const List<T> &>(*this).IListIndexOf( item );
    }

    template <typename U>
    void Insert(size_t index, const U &item)
    {
        static_cast<List<T> &>(*this).IListInsert( index, item );
    }

};

template <typename T>
class ListICollectionInterfaceCustomization
{
public:
    template <typename U>
    void Add(const U &item)
    {
        static_cast<List <T> &>(*this).ICollectionAdd( item );
    }

    template <typename U>
    bool Remove(const U &item)
    {
        return static_cast<List <T> &>(*this).ICollectionRemove( item );
    }

    template <typename U>
    bool Contains(const U &item) const
    {
        return static_cast<const List <T> &>(*this).ICollectionContains( item );
    }
};

template <class T>
class List : public ListICollectionInterfaceCustomization<T>,
             public ListIListInterfaceCustomization<T>
{
public:
    using underlying_type = std::vector<T>;

    using value_type      = T;
    using size_type       = underlying_type::size_type;
    using difference_type = underlying_type::difference_type;
    using reference       = underlying_type::reference;
    using const_reference = underlying_type::const_reference;
    using iterator               = underlying_type::iterator;
    using const_iterator         = underlying_type::const_iterator;
    using reverse_iterator       = underlying_type::reverse_iterator;
    using const_reverse_iterator = underlying_type::const_reverse_iterator;
    using predicate       = System::Predicate<const T &>;

    constexpr List() = default;

    constexpr List(const std::vector<value_type> &init_value)
        :
        _list( init_value )
    {
    }

    constexpr List(std::vector<value_type> &&init_value)
        :
        _list( std::move(init_value) )
    {
    }

    template <class InputIt>
    constexpr List(InputIt first, InputIt last)
        :
        _list( first, last )
    {
    }

    constexpr List(std::initializer_list<T> il)
        :
        _list( il )
    {
    }

    template <size_t ArraySize>
    List(std::type_identity_t<T> (&arr)[ArraySize])
        :
        _list( std::begin(arr), std::end(arr) )
    {
    }
  
    List(const List &other) = default;
    List(List &&other) = default;

    List &operator =(const List &other) = default;
    List &operator =(List &&other) = default;

    static constexpr TypeCode GetTypeCode() { return TypeCode::Object; }

    size_type Capacity() const { return _list.capacity(); }
    
    const_reference operator [](size_type pos) const
    {
      if ( pos >= Count() )
          ThrowWithTarget( ArgumentOutOfRangeException( "pos", "Index out-of-range" ) );

      return _list[pos];
    }

    reference operator [](size_type pos)
    {
      if ( pos >= Count() )
          ThrowWithTarget( ArgumentOutOfRangeException( "pos", "Index out-of-range" ) );

      return _list[pos];
    }

    bool Exists(predicate unary_predicate) const
    {
        return std::find_if( begin(), end(), unary_predicate ) != end();
    }

    const_reference Find(predicate unary_predicate) const
    {
        auto iter = std::find_if( begin(), end(), unary_predicate );

        if ( iter == end() )
        {
            static T default_value;
            
            return default_value;
        }
        
        return *iter;
    }

    reference Find(predicate unary_predicate)
    {
        auto iter = std::find_if( begin(), end(), unary_predicate );

        if ( iter == end() )
        {
            static T default_value;
            
            return default_value;
        }
        
        return *iter;
    }

    int FindIndex(predicate unary_predicate) const
    {
        auto iter = std::find_if( begin(), end(), unary_predicate );

        if ( iter == end() )
            return -1;
        return static_cast<int>( std::distance( begin(), iter ) );
    }

    const_reference FindLast(predicate unary_predicate) const
    {
        auto iter = std::find_if( rbegin(), rend(), unary_predicate );

        if ( iter == rend() )
        {
            static T default_value;
            
            return default_value;
        }
        
        return *(iter.base() - 1);
    }

    reference FindLast(predicate unary_predicate)
    {
        auto iter = std::find_if( rbegin(), rend(), unary_predicate );

        if ( iter == rend() )
        {
            static T default_value;
            
            return default_value;
        }
        
        return *(iter.base() - 1);
    }

    List<T> FindAll(predicate unary_predicate) const
    {
        std::vector<T> retval;

        std::copy_if( begin(), end(), std::back_inserter( retval ), unary_predicate );

        return List<T>( retval.begin(), retval.end() );
    }

    // IList-specific methods
    void RemoveAt(size_type index)
    {
        if ( IsReadOnly() )
            ThrowWithTarget( System::NotSupportedException( "List is read-only" ) );
        if ( index >= Count() )
            ThrowWithTarget( System::ArgumentOutOfRangeException( "index", "Index out-of-range" ) );
      
        _list.erase( std::next( begin(), index ) );
    }

    int RemoveAll(predicate unary_predicate)
    {
        auto [first, last] = std::ranges::remove_if( _list, unary_predicate );
        int  number_removed = static_cast<int>( std::distance(first, last) );

        _list.erase( first, last );
        return number_removed;
    }

    // ICollection interface
    size_type Count() const { return _list.size(); }

    void Clear() noexcept { _list.clear(); }

    bool IsReadOnly() const { return true; }
    bool IsReadOnly()       { return false; }

    bool IsSynchronized() const { return false; }

    // Range-for compatibility
          iterator  begin()       { return _list.begin(); }
    const_iterator  begin() const { return _list.begin(); }
    const_iterator cbegin() const noexcept { return _list.cbegin(); }

          iterator  end()        { return _list.end(); }
    const_iterator  end()  const { return _list.end(); }
    const_iterator cend() const noexcept { return _list.cend(); }

          reverse_iterator  rbegin()       { return _list.rbegin(); }
    const_reverse_iterator  rbegin() const { return _list.rbegin(); }
    const_reverse_iterator crbegin() const noexcept { return _list.crbegin(); }

          reverse_iterator  rend()       { return _list.rend(); }
    const_reverse_iterator  rend() const { return _list.rend(); }
    const_reverse_iterator crend() const noexcept { return _list.crend(); }
protected:
    std::vector<T> _list;

    // Default implementations...
    template <typename U>
    size_t IListIndexOf(const U &item) const
    {
        auto iter_found = std::find( begin(), end(), item );

        if ( iter_found == end() )
            return -1;
        
        return std::distance( begin(), iter_found );
    }

    template <typename U>
    void IListInsert(size_t index, const U &item)
    {
        if ( IsReadOnly() )
            ThrowWithTarget( System::NotSupportedException( "List is read-only" ) );
        if ( index > Count() )
            ThrowWithTarget( System::ArgumentOutOfRangeException( "index", "Index out-of-range" ) );
        
        // OK to insert at end(), which is when index == Count()
        _list.emplace( std::next( begin(), index ), item );
    }

    template <typename U>
    void ICollectionAdd(const U &item)
    {
        _list.emplace_back( item );
    }

    template <typename U>
    bool ICollectionRemove(const U &item)
    {
        auto iter_found = std::find( begin(), end(), item );

        if ( iter_found == end() )
            return false;
        _list.erase( iter_found );
        return true;
    }

    template <typename U>
    bool ICollectionContains(const U &item) const
    {
        return std::find( begin(), end(), item ) != end();
    }

    friend class ListIListInterfaceCustomization<T>;
    friend class ListICollectionInterfaceCustomization<T>;
};

}
