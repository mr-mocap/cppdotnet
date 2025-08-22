#include <memory>

namespace System::Collections::Generic::Private
{

template <class Policy>
struct ICollectionInterface : Policy
{
    virtual ~ICollectionInterface() { }

    virtual typename Policy::size_type Count() const = 0;
    virtual bool        IsReadOnly() const = 0;
    virtual bool        IsReadOnly()       = 0;
    virtual bool        IsSynchronized() const = 0;

    virtual void Add(const typename Policy::value_type &item) = 0;
    virtual bool Remove(const typename Policy::value_type &item) = 0;
    virtual void Clear() = 0;
    virtual bool Contains(const typename Policy::value_type &item) = 0;

    // TODO: Add CopyTo() ?

    virtual std::unique_ptr<ICollectionInterface> Clone() = 0;
    virtual std::unique_ptr<ICollectionInterface> Empty() = 0;

    // Range-for compatibility
    virtual typename Policy::IteratorType       begin()       = 0;
    virtual typename Policy::ConstIteratorType  begin() const = 0;
    virtual typename Policy::ConstIteratorType cbegin() const = 0;

    virtual typename Policy::IteratorType       end()       = 0;
    virtual typename Policy::ConstIteratorType  end() const = 0;
    virtual typename Policy::ConstIteratorType cend() const = 0;
};

}