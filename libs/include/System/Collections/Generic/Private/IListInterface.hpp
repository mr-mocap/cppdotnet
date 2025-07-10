#pragma once

#include <memory>
#include <iterator>

namespace System::Collections::Generic::Private
{

template <class T, class IteratorType, class ConstIteratorType, class ReverseIteratorType, class ConstReverseIteratorType>
struct IListInterface
{
    virtual ~IListInterface() { }

    // Collection
    virtual std::size_t Count() const = 0;
    virtual bool        IsReadOnly() const = 0;
    virtual bool        IsReadOnly()       = 0;
    virtual bool        IsSynchronized() const = 0;

    virtual void Add(const T &item) = 0;
    virtual bool Remove(const T &item) = 0;
    virtual void Clear() = 0;
    virtual bool Contains(const T &item) = 0;

    // TODO: Add CopyTo() ?

    // List
    virtual const T &operator [](std::size_t index) const = 0;
    virtual       T &operator [](std::size_t index)       = 0;

    virtual std::size_t IndexOf(const T &item) const = 0;

    virtual void Insert(std::size_t index, const T &item) = 0;
    virtual void RemoveAt(std::size_t index) = 0;

    virtual std::unique_ptr<IListInterface> Clone() = 0;
    virtual std::unique_ptr<IListInterface> Empty() = 0;

    // Range-for compatibility
    virtual IteratorType       begin()       = 0;
    virtual ConstIteratorType  begin() const = 0;
    virtual ConstIteratorType cbegin() const = 0;

    virtual IteratorType       end()       = 0;
    virtual ConstIteratorType  end() const = 0;
    virtual ConstIteratorType cend() const = 0;

    virtual ReverseIteratorType       rbegin()       = 0;
    virtual ConstReverseIteratorType  rbegin() const = 0;
    virtual ConstReverseIteratorType crbegin() const = 0;

    virtual ReverseIteratorType       rend()       = 0;
    virtual ConstReverseIteratorType  rend() const = 0;
    virtual ConstReverseIteratorType crend() const = 0;
};

template <class ListType>
struct IListIndexer
{
    static typename ListType::const_reference GetAt(const ListType &d, std::size_t index) { return d[index]; }
    static typename ListType::reference       GetAt(      ListType &d, std::size_t index) { return d[index]; }

    static typename ListType::const_reference GetAt(const ListType *d, std::size_t index) { return (*d)[index]; }
    static typename ListType::reference       GetAt(      ListType *d, std::size_t index) { return (*d)[index]; }
};

}