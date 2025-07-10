#pragma once

#include "System/Collections/Generic/KeyValuePair.hpp"
#include "System/Collections/Generic/ICollection.hpp"


namespace System::Collections::Generic::Private
{

template <class KeyType, class MappedType, class IteratorType, class ConstIteratorType>
struct IDictionaryInterface
{
    virtual ~IDictionaryInterface() { }

    // Collection
    virtual std::size_t Count() const = 0;
    virtual bool        IsReadOnly() const = 0;
    virtual bool        IsReadOnly()       = 0;
    virtual bool        IsSynchronized() const = 0;

    virtual void Add(const KeyValuePair<KeyType, MappedType> &item)      = 0;
    virtual bool Remove(const KeyValuePair<KeyType, MappedType> &item)   = 0;
    virtual void Clear() = 0;
    virtual bool Contains(const KeyValuePair<KeyType, MappedType> &item) = 0;

    // TODO: Add CopyTo() ?

    // Dictionary
    virtual       MappedType &operator[](const KeyType &key) = 0;
    virtual const MappedType &at(const KeyType &key) const   = 0;
    virtual       MappedType &at(const KeyType &key)         = 0;

    virtual void Add(const KeyType &key, const MappedType &value)             = 0;
    virtual bool Remove(const KeyType &key)                                   = 0;
    virtual bool ContainsKey(const KeyType &key)                        const = 0;
    virtual bool TryGetValue(const KeyType &key, MappedType &value_out) const = 0;

    virtual ICollection<KeyType>    Keys()   const = 0;
    virtual ICollection<MappedType> Values() const = 0;

    virtual std::unique_ptr<IDictionaryInterface> Clone() = 0;
    virtual std::unique_ptr<IDictionaryInterface> Empty() = 0;

    // Range-for compatibility
    virtual IteratorType       begin()       = 0;
    virtual ConstIteratorType  begin() const = 0;
    virtual ConstIteratorType cbegin() const = 0;

    virtual IteratorType       end()       = 0;
    virtual ConstIteratorType  end() const = 0;
    virtual ConstIteratorType cend() const = 0;
};

}