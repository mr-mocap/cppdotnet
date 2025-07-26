#pragma once

#include "System/Collections/Generic/List.hpp"
#include <string>
#include <string_view>


namespace System::Collections::Specialized
{

class StringCollection : public Generic::List<std::string>
{
public:
    using Base = Generic::List<std::string>;

    using Base::List;
    using Base::operator =;

    size_type IndexOf(std::string_view item) const
    {
        auto iter_found = std::find( begin(), end(), item );

        if ( iter_found == end() )
            return -1;
        
        return std::distance( _list.begin(), iter_found );
    }

    void Insert(size_type index, std::string_view item)
    {
        if ( IsReadOnly() )
            ThrowWithTarget( System::NotSupportedException( "List is read-only" ) );
        if ( index > Count() )
            ThrowWithTarget( System::ArgumentOutOfRangeException( "index", "Index out-of-range" ) );
        
        // OK to insert at end(), which is when index == Count()
        _list.emplace( std::next( begin(), index ), item );
    }

    void Add(std::string_view item)
    {
        _list.emplace_back( item );
    }

    void Add(std::string_view &&item)
    {
        _list.emplace_back( std::move(item) );
    }

    bool Remove(std::string_view item)
    {
        auto iter_found = std::find( begin(), end(), item );

        if ( iter_found == end() )
            return false;
        _list.erase( iter_found );
        return true;
    }

    bool Contains(std::string_view item) const
    {
        return std::find( begin(), end(), item ) != _list.end();
    }
};

}