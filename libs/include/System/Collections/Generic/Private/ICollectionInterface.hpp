#pragma once


namespace System::Collections::Generic::Private
{

template <class T, class IteratorType, class ConstIteratorType>
struct ICollectionInterface
{
    virtual ~ICollectionInterface() { }

    virtual std::size_t Count() const = 0;
    virtual bool        IsReadOnly() const = 0;
    virtual bool        IsReadOnly()       = 0;
    virtual bool        IsSynchronized() const = 0;

    virtual void Add(const T &item) = 0;
    virtual bool Remove(const T &item) = 0;
    virtual void Clear() = 0;
    virtual bool Contains(const T &item) = 0;

    // TODO: Add CopyTo() ?

    virtual std::unique_ptr<ICollectionInterface> Clone() = 0;
    virtual std::unique_ptr<ICollectionInterface> Empty() = 0;

    // Range-for compatibility
    virtual IteratorType       begin()       = 0;
    virtual ConstIteratorType  begin() const = 0;
    virtual ConstIteratorType cbegin() const = 0;

    virtual IteratorType       end()       = 0;
    virtual ConstIteratorType  end() const = 0;
    virtual ConstIteratorType cend() const = 0;
};

}