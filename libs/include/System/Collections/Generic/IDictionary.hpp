#pragma once

#include "System/Collections/Generic/KeyValuePair.hpp"
#include "System/Collections/Generic/ICollection.hpp"
#include <memory>

namespace System::Collections::Generic
{

template <typename KeyT, typename ValueT>
class IDictionary
{
    struct Interface
    {
        virtual ~Interface() { }

        virtual std::size_t Count() const = 0;
        virtual bool        IsReadOnly() const = 0;
        virtual bool        IsReadOnly()       = 0;
        virtual bool        IsSynchronized() const = 0;

        // Collection
        virtual void Add(const KeyValuePair<KeyT, ValueT> &item) = 0;
        virtual bool Remove(const KeyValuePair<KeyT, ValueT> &item) = 0;
        virtual void Clear() = 0;
        virtual bool Contains(const KeyValuePair<KeyT, ValueT> &item) = 0;

        // TODO: Add CopyTo() ?

        // Dictionary
        virtual       ValueT &operator[](const KeyT &key) = 0;
        virtual const ValueT &operator[](const KeyT &key) const = 0;
        virtual       ValueT &at(const KeyT &key)       = 0;
        virtual const ValueT &at(const KeyT &key) const = 0;

        virtual void Add(const KeyT &key, const ValueT &value) = 0;
        virtual bool TryAdd(const KeyT &key, const ValueT &value) = 0;
        virtual bool Remove(const KeyT &key) = 0;
        virtual bool ContainsKey(const KeyT &key) const = 0;
        virtual bool ContainsValue(const ValueT &value) const = 0;
        virtual bool TryGetValue(const KeyT &key, const ValueT &value_out) const = 0;
        virtual ICollection<KeyT>   Keys()   const = 0;
        virtual ICollection<ValueT> Values() const = 0;

#if 0
        virtual Dictionary<KeyT, ValueT>::iterator        begin()                = 0;
        virtual Dictionary<KeyT, ValueT>::const_iterator  begin() const          = 0;
        virtual Dictionary<KeyT, ValueT>::const_iterator cbegin() const noexcept = 0;

        virtual Dictionary<KeyT, ValueT>::iterator        end()                = 0;
        virtual Dictionary<KeyT, ValueT>::const_iterator  end()  const         = 0;
        virtual Dictionary<KeyT, ValueT>::const_iterator cend() const noexcept = 0;

        virtual Dictionary<KeyT, ValueT>::reverse_iterator        rbegin()                = 0;
        virtual Dictionary<KeyT, ValueT>::const_reverse_iterator  rbegin() const          = 0;
        virtual Dictionary<KeyT, ValueT>::const_reverse_iterator crbegin() const noexcept = 0;

        virtual Dictionary<KeyT, ValueT>::reverse_iterator        rend()                = 0;
        virtual Dictionary<KeyT, ValueT>::const_reverse_iterator  rend() const          = 0;
        virtual Dictionary<KeyT, ValueT>::const_reverse_iterator crend() const noexcept = 0;
#endif

        virtual std::unique_ptr<Interface> Clone() = 0;
        virtual std::unique_ptr<Interface> Empty() = 0;
    };

    template <class DictionaryType>
    struct InterfaceModel : Interface
    {
        InterfaceModel() = default;
        InterfaceModel(DictionaryType &input) : data( input ) { }
        InterfaceModel(DictionaryType &&input) : data( std::move(input) ) { }
        ~InterfaceModel() override { }
          
        // Default copy and move
        InterfaceModel(const InterfaceModel &other) = default;
        InterfaceModel(InterfaceModel &&other) = default;

        InterfaceModel &operator =(const InterfaceModel &) = default;
        InterfaceModel &operator =(InterfaceModel &&) = default;

        std::size_t Count() const override { return data.Count(); }

        bool IsReadOnly() const override { return data.IsReadOnly(); }
        bool IsReadOnly()       override { return data.IsReadOnly(); }

        bool IsSynchronized() const override { return data.IsSynchronized(); }

        void Add(const KeyValuePair<KeyT, ValueT> &item) override { data.Add(item); }

        bool Remove(const KeyValuePair<KeyT, ValueT> &item) override { return data.Remove(item); }

        void Clear() override { data.Clear(); }

        bool Contains(const KeyValuePair<KeyT, ValueT> &item) override { return data.Contains(item); }

        // Dictionary
              ValueT &operator[](const KeyT &key)       override { return data[key]; }
        const ValueT &operator[](const KeyT &key) const override { return data[key]; }
              ValueT &at(const KeyT &key)       override { return data.at(key); }
        const ValueT &at(const KeyT &key) const override { return data.at(key); }

        void Add(const KeyT &key, const ValueT &value) override { data.Add(key, value); }
        bool TryAdd(const KeyT &key, const ValueT &value) override { return data.TryAdd(key, value); }
        bool Remove(const KeyT &key) const override { return data.Remove(key); }
        bool ContainsKey(const KeyT &key) const override { return data.ContainsKey(key); }
        bool ContainsValue(const ValueT &value) const override { return data.ContainsValue(value); }
        bool TryGetValue(const KeyT &key, const ValueT &value_out) const override { data.TryGetValue(key, value_out); }
        ICollection<KeyT>   Keys()   const override { return data.Keys(); }
        ICollection<ValueT> Values() const override { return data.Values(); }

#if 0
        Dictionary<KeyT, ValueT>::iterator        begin()       { return iterator{ data.begin() }; }
        Dictionary<KeyT, ValueT>::const_iterator  begin() const { return const_iterator{ data.begin() }; }
        Dictionary<KeyT, ValueT>::const_iterator cbegin() const noexcept { return const_iterator{ data.cbegin() }; }
        
        Dictionary<KeyT, ValueT>::iterator        end()        { return data.end(); }
        Dictionary<KeyT, ValueT>::const_iterator  end()  const { return data.end(); }
        Dictionary<KeyT, ValueT>::const_iterator cend() const noexcept { return data.cend(); }

        Dictionary<KeyT, ValueT>::reverse_iterator        rbegin()       { return data.rbegin(); }
        Dictionary<KeyT, ValueT>::const_reverse_iterator  rbegin() const { return data.rbegin(); }
        Dictionary<KeyT, ValueT>::const_reverse_iterator crbegin() const noexcept { return data.crbegin(); }
        
        Dictionary<KeyT, ValueT>::reverse_iterator        rend()       { return data.rend(); }
        Dictionary<KeyT, ValueT>::const_reverse_iterator  rend() const { return data.rend(); }
        Dictionary<KeyT, ValueT>::const_reverse_iterator crend() const noexcept { return data.crend(); }
#endif

        std::unique_ptr<Interface> Clone() override
        {
            return std::make_unique<InterfaceModel>(data);
        }

        std::unique_ptr<Interface> Empty() override
        {
            return std::make_unique_for_overwrite<InterfaceModel>();
        }

        DictionaryType data;
    };

public:
    IDictionary() = delete;

    template <typename DictionaryType>
    IDictionary(DictionaryType &input)
      :
      m_pimple( std::make_unique<InterfaceModel<DictionaryType>>(input) )
    {
    }

    template <typename DictionaryType>
    IDictionary(DictionaryType &&input)
      :
      m_pimple( std::make_unique<InterfaceModel<DictionaryType>>( std::move(input) ) )
    {
    }

    IDictionary(const IDictionary &other)
      :
      m_pimple( other.m_pimple->Clone() )
    {
    }
    IDictionary(IDictionary &other)
      :
      m_pimple( other.m_pimple->Clone() )
    {
    }
    IDictionary(IDictionary &&other)
      :
      m_pimple( other.m_pimple->Empty() )
    {
        std::swap( m_pimple, other.m_pimple );
    }

    IDictionary &operator =(const IDictionary &other)
    {
        m_pimple = other.m_pimple->Clone();
        return *this;
    }

    IDictionary &operator =(IDictionary &&other) = delete;

    // Collection
    std::size_t Count() const      { return m_pimple->Count(); }
    bool        IsReadOnly() const { return m_pimple->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimple->IsReadOnly(); }
    bool        IsSynchronized() const { return m_pimple->IsSynchronized(); }

    void Add(const KeyValueType<KeyT, ValueT> &item)      { m_pimple->Add(item); }
    bool Remove(const KeyValueType<KeyT, ValueT> &item)   { return m_pimple->Remove(item); }
    void Clear()                 { m_pimple->Clear(); }
    bool Contains(const KeyValueType<KeyT, ValueT> &item) { return m_pimple->Contains(item); }

    // Dictionary
          ValueT &operator[](const KeyT &key)       { return m_pimple->operator [](key); }
    const ValueT &operator[](const KeyT &key) const { return m_pimple->operator [](key); }
          ValueT &at(const KeyT &key)       { return m_pimple->at(key); }
    const ValueT &at(const KeyT &key) const { return m_pimple->at(key); }

    void Add(const KeyT &key, const ValueT &value) { m_pimple->Add(key, value); }
    bool TryAdd(const KeyT &key, const ValueT &value) { return m_pimple->TryAdd(key, value); }
    bool Remove(const KeyT &key) const override { return m_pimple->Remove(key); }
    bool ContainsKey(const KeyT &key) const { return m_pimple->ContainsKey(key); }
    bool ContainsValue(const ValueT &value) const { return m_pimple->ContainsValue(value); }
    bool TryGetValue(const KeyT &key, const ValueT &value_out) const { return m_pimple->TryGetValue(key, value_out); }

    ICollection<KeyT>   Keys()   const { return m_pimple->Keys(); }
    ICollection<ValueT> Values() const { return m_pimple->Values(); }

#if 0
    // Range-for compatibility
          iterator  begin()       { return iterator{ _data.begin() }; }
    const_iterator  begin() const { return const_iterator{ _data.begin() }; }
    const_iterator cbegin() const noexcept { return const_iterator{ _data.cbegin() }; }

          iterator  end()        { return _data.end(); }
    const_iterator  end()  const { return _data.end(); }
    const_iterator cend() const noexcept { return _data.cend(); }

          reverse_iterator  rbegin()       { return _data.rbegin(); }
    const_reverse_iterator  rbegin() const { return _data.rbegin(); }
    const_reverse_iterator crbegin() const noexcept { return _data.crbegin(); }

          reverse_iterator  rend()       { return _data.rend(); }
    const_reverse_iterator  rend() const { return _data.rend(); }
    const_reverse_iterator crend() const noexcept { return _data.crend(); }
#endif
protected:
    std::unique_ptr<Interface> m_pimple;
};
}