#include "System/Exception.hpp"
#include <list>
#include <string_view>
#include <algorithm>
#include <type_traits>



namespace System::Collections::Generic
{

template <typename T>
class LinkedList
{
public:
    using value_type      = T;
    using size_type       = std::list<T>::size_type;
    using difference_type = std::list<T>::difference_type;
    using reference       = std::list<T>::reference;
    using const_reference = std::list<T>::const_reference;
    using iterator        = std::list<T>::iterator;
    using const_iterator  = std::list<T>::const_iterator;
    using reverse_iterator = std::list<T>::reverse_iterator;
    using const_reverse_iterator = std::list<T>::const_reverse_iterator;

    LinkedList() = default;

    template <class InputIt>
    LinkedList(InputIt first, InputIt last)
        :
        _list( first, last )
    {
    }

    LinkedList(std::initializer_list<T> il)
        :
        _list( il )
    {
    }

    template <size_t ArraySize>
    LinkedList(std::type_identity_t<T> (&arr)[ArraySize])
        :
        _list( std::begin(arr), std::end(arr) )
    {
    }

    LinkedList(const LinkedList &other) = default;
    LinkedList(LinkedList &&other) = default;

    LinkedList &operator =(const LinkedList &other) = default;
    LinkedList &operator =(LinkedList &&other) = default;

          reference First()       { return _list.front(); }
    const_reference First() const { return _list.front(); }

          reference Last()       { return _list.back(); }
    const_reference Last() const { return _list.back(); }

    void AddFirst(const T &item)
    {
        _list.push_front( item );
    }

    void AddFirst(T &&item)
    {
        _list.push_front( std::move(item) );
    }

    void AddLast(const T &item)
    {
        _list.push_back( item );
    }

    void AddLast(T &&item)
    {
        _list.push_back( std::move(item) );
    }


    void RemoveFirst()
    {
        using namespace std::literals;

        if ( _list.empty() )
            ThrowWithTarget( System::InvalidOperationException{ "List is empty"sv } );

        _list.pop_front();
    }

    void RemoveLast()
    {
        using namespace std::literals;

        if ( _list.empty() )
            ThrowWithTarget( System::InvalidOperationException{ "List is empty"sv } );

        _list.pop_back();
    }
    
    const_iterator Find(const T &item) const
    {
        return std::find( begin(), end(), item );
    }

    iterator Find(const T &item)
    {
        return std::find( begin(), end(), item );
    }

    const_iterator FindLast(const T &item) const
    {
        const_iterator most_recently_found = end();

        for (const_iterator iter = begin(); iter != end(); ++iter)
        {
            iter = std::find( iter, end(), item );

            if ( iter != end() )
                most_recently_found = iter; // Match found
        }
        return most_recently_found;
    }

    iterator FindLast(const T &item)
    {
        iterator most_recently_found = end();

        for (iterator iter = begin(); iter != end(); ++iter)
        {
            iter = std::find( iter, end(), item );

            if ( iter != end() )
                most_recently_found = iter; // Match found
        }
        return most_recently_found;
    }

    // ICollection interface
    size_type Count() const { return _list.size(); }

    void Clear() noexcept { _list.clear(); }

    void Add(const T &item)
    {
        _list.push_back( item );
    }

    void Add(T &&item)
    {
        _list.push_back( std::move(item) );
    }

    bool Remove(const T &item)
    {
        using namespace std::literals;

        if ( IsReadOnly() )
            ThrowWithTarget( System::NotSupportedException( "LinkedList is read-only"sv ) );

        auto iter_found = Find( item );

        if ( iter_found == end() )
            return false;
        _list.erase( iter_found );
        return true;
    }

    bool Contains(const T &item) const
    {
        return Find( item ) != _list.end();
    }

    bool IsReadOnly() const { return true; }
    bool IsReadOnly()       { return false; }

    bool IsSynchronized() const { return false; }

    //void CopyTo(Array dest_array, size_t starting_at_index) { }

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
    std::list<T> _list;
};

}