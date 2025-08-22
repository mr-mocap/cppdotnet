#include "System/Collections/Generic/KeyValuePair.hpp"
#include "System/Collections/Generic/ICollection.hpp"


namespace System::Collections::Generic::Private
{

template <class Policy>
struct IDictionaryInterface : Policy
{
    virtual ~IDictionaryInterface() { }

    // Collection
    virtual std::size_t Count() const = 0;
    virtual bool        IsReadOnly() const = 0;
    virtual bool        IsReadOnly()       = 0;
    virtual bool        IsSynchronized() const = 0;

    virtual void Add(const typename Policy::value_type &item)      = 0;
    virtual bool Remove(const typename Policy::value_type &item)   = 0;
    virtual void Clear() = 0;
    virtual bool Contains(const typename Policy::value_type &item) = 0;

    // TODO: Add CopyTo() ?

    // Dictionary
    virtual       typename Policy::mapped_type &operator[](const typename Policy::key_type &key) = 0;
    virtual const typename Policy::mapped_type &at(const typename Policy::key_type &key) const   = 0;
    virtual       typename Policy::mapped_type &at(const typename Policy::key_type &key)         = 0;

    virtual void Add(const typename Policy::key_type &key, const typename Policy::mapped_type &value)             = 0;
    virtual bool Remove(const typename Policy::key_type &key)                                                     = 0;
    virtual bool ContainsKey(const typename Policy::key_type &key)                                          const = 0;
    virtual bool TryGetValue(const typename Policy::key_type &key, typename Policy::mapped_type &value_out) const = 0;

    virtual ICollection<typename Policy::key_type>    Keys()   const = 0;
    virtual ICollection<typename Policy::mapped_type> Values() const = 0;

    virtual std::unique_ptr<IDictionaryInterface> Clone() = 0;
    virtual std::unique_ptr<IDictionaryInterface> Empty() = 0;

    // Range-for compatibility
    virtual typename Policy::IteratorType       begin()       = 0;
    virtual typename Policy::ConstIteratorType  begin() const = 0;
    virtual typename Policy::ConstIteratorType cbegin() const = 0;

    virtual typename Policy::IteratorType       end()       = 0;
    virtual typename Policy::ConstIteratorType  end() const = 0;
    virtual typename Policy::ConstIteratorType cend() const = 0;
};

}