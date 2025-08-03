#pragma once

#include "System/Exception.hpp"
#include "System/Predicate.hpp"
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
    size_t IListIndexOf(U &&item) const
    {
        const List<T> &derived_class = static_cast<const List<T> &>(*this);

        auto iter_found = std::find( derived_class.begin(), derived_class.end(), std::forward<U>(item) );

        if ( iter_found == derived_class.end() )
            return -1;
        
        return std::distance( derived_class.begin(), iter_found );
    }

    template <typename U>
    void IListInsert(size_t index, U &&item)
    {
        List<T> &derived_class = static_cast<List<T> &>(*this);

        if ( derived_class.IsReadOnly() )
            ThrowWithTarget( System::NotSupportedException( "List is read-only" ) );
        if ( index > derived_class.Count() )
            ThrowWithTarget( System::ArgumentOutOfRangeException( "index", "Index out-of-range" ) );
        
        // OK to insert at end(), which is when index == Count()
        derived_class._list.emplace( std::next( derived_class.begin(), index ), std::forward<U>(item) );
    }
};

template <typename T>
class ListICollectionInterfaceCustomization
{
public:
    template <typename U>
    void ICollectionAdd(U &&item)
    {
        List<T> &derived_class = static_cast<List<T> &>(*this);

        derived_class._list.emplace_back( std::forward<U>(item) );
    }

    template <typename U>
    bool ICollectionRemove(U &&item)
    {
        List<T> &derived_class = static_cast<List<T> &>(*this);

        auto iter_found = std::find( derived_class.begin(), derived_class.end(), std::forward<U>(item) );

        if ( iter_found == derived_class.end() )
            return false;
        derived_class._list.erase( iter_found );
        return true;
    }

    template <typename U>
    bool ICollectionContains(U &&item) const
    {
        const List<T> &derived_class = static_cast<const List<T> &>(*this);

        return std::find( derived_class.begin(), derived_class.end(), std::forward<U>(item) ) != derived_class.end();
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
    template <typename U>
    size_t IndexOf(U &&item) const
    {
        return this->IListIndexOf( std::forward<U>(item) );
    }

    template <typename U>
    void Insert(size_t index, U &&item)
    {
        this->IListInsert( index, std::forward<U>(item) );
    }

    void RemoveAt(size_type index)
    {
        if ( IsReadOnly() )
            ThrowWithTarget( System::NotSupportedException( "List is read-only" ) );
        if ( index >= Count() )
            ThrowWithTarget( System::ArgumentOutOfRangeException( "index", "Index out-of-range" ) );
      
        _list.erase( std::next( begin(), index ) );
    }

    // ICollection interface
    size_type Count() const { return _list.size(); }

    void Clear() noexcept { _list.clear(); }

    bool IsReadOnly() const { return true; }
    bool IsReadOnly()       { return false; }

    bool IsSynchronized() const { return false; }

    template <typename U>
    void Add(U &&item)
    {
        this->ICollectionAdd( std::forward<U>(item) );
    }

    template <typename U>
    bool Remove(U &&item)
    {
        return this->ICollectionRemove( std::forward<U>(item) );
    }

    template <typename U>
    bool Contains(U &&item) const
    {
        return this->ICollectionContains( std::forward<U>(item) );
    }

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

    friend class ListIListInterfaceCustomization<T>;
    friend class ListICollectionInterfaceCustomization<T>;
};

}
