#include <memory>
#include <iterator>

namespace System::Collections::Generic::Private
{

template <class Policy>
struct IListInterface : Policy
{
    virtual ~IListInterface() { }

    // Collection
    virtual std::size_t Count() const = 0;
    virtual bool        IsReadOnly() const = 0;
    virtual bool        IsReadOnly()       = 0;
    virtual bool        IsSynchronized() const = 0;

    virtual void Add(const typename Policy::value_type &item) = 0;
    virtual bool Remove(const typename Policy::value_type &item) = 0;
    virtual void Clear() = 0;
    virtual bool Contains(const typename Policy::value_type &item) = 0;

    // TODO: Add CopyTo() ?

    // List
    virtual const typename Policy::value_type &operator [](std::size_t index) const = 0;
    virtual       typename Policy::value_type &operator [](std::size_t index)       = 0;

    virtual std::size_t IndexOf(const typename Policy::value_type &item) const = 0;

    virtual void Insert(std::size_t index, const typename Policy::value_type &item) = 0;
    virtual void RemoveAt(std::size_t index) = 0;

    virtual std::unique_ptr<IListInterface> Clone() = 0;
    virtual std::unique_ptr<IListInterface> Empty() = 0;

    // Range-for compatibility
    virtual typename Policy::IteratorType       begin()       = 0;
    virtual typename Policy::ConstIteratorType  begin() const = 0;
    virtual typename Policy::ConstIteratorType cbegin() const = 0;

    virtual typename Policy::IteratorType       end()       = 0;
    virtual typename Policy::ConstIteratorType  end() const = 0;
    virtual typename Policy::ConstIteratorType cend() const = 0;

    virtual typename Policy::ReverseIteratorType       rbegin()       = 0;
    virtual typename Policy::ConstReverseIteratorType  rbegin() const = 0;
    virtual typename Policy::ConstReverseIteratorType crbegin() const = 0;

    virtual typename Policy::ReverseIteratorType       rend()       = 0;
    virtual typename Policy::ConstReverseIteratorType  rend() const = 0;
    virtual typename Policy::ConstReverseIteratorType crend() const = 0;
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