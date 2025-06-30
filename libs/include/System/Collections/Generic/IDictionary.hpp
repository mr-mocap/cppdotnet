#pragma once

#include "System/Collections/Generic/Private/LegacyForwardIterator.hpp"
#include "System/Collections/Generic/Private/IDictionaryInterface.hpp"

namespace System::Collections::Generic
{

template <typename KeyT, typename ValueT>
class IDictionary : public Private::LegacyForwardIteratorBase<KeyValuePair<KeyT, ValueT>>
{
public:
    using key_type    = KeyT;
    using mapped_type = ValueT;
    using value_type  = KeyValuePair<KeyT, ValueT>;
    using size_type   = std::size_t;
    using reference       =       value_type &;
    using const_reference = const value_type &;
    using pointer         =       KeyValuePair<KeyT, ValueT> *;
    using const_pointer   = const KeyValuePair<KeyT, ValueT> *;
    using iterator        = Private::LegacyForwardIteratorBase<KeyValuePair<KeyT, ValueT>>::Iterator;
    using const_iterator  = Private::LegacyForwardIteratorBase<KeyValuePair<KeyT, ValueT>>::ConstIterator;

private:
    using Interface = Private::IDictionaryInterface<KeyT, ValueT, iterator, const_iterator>;

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

        void Add(const KeyValuePair<KeyT, ValueT> &item)      override { data.Add(item); }
        bool Remove(const KeyValuePair<KeyT, ValueT> &item)   override { return data.Remove(item); }
        void Clear()                                          override { data.Clear(); }
        bool Contains(const KeyValuePair<KeyT, ValueT> &item) override { return data.Contains(item); }

        // Dictionary
              mapped_type &operator[](const key_type &key)       override { return data[key]; }
              mapped_type &at(const key_type &key)               override { return data.at(key); }
        const mapped_type &at(const key_type &key)         const override { return data.at(key); }

        void Add(const key_type &key, const mapped_type &value)             override { data.Add(key, value); }
        bool TryAdd(const key_type &key, const mapped_type &value)          override { return data.TryAdd(key, value); }
        bool Remove(const key_type &key)                                    override { return data.Remove(key); }
        bool ContainsKey(const key_type &key)                         const override { return data.ContainsKey(key); }
        bool ContainsValue(const mapped_type &value)                  const override { return data.ContainsValue(value); }
        bool TryGetValue(const key_type &key, mapped_type &value_out) const override { return data.TryGetValue(key, value_out); }

        ICollection<key_type>    Keys()   const override { return data.Keys(); }
        ICollection<mapped_type> Values() const override { return data.Values(); }

        iterator        begin() override { return       iterator{ std::make_unique<typename Private::LegacyForwardIteratorBase<KeyValuePair<KeyT, ValueT>>::IteratorModel<DictionaryType>>( data.begin() ) }; }
        const_iterator cbegin() override { return const_iterator{ std::make_unique<typename Private::LegacyForwardIteratorBase<KeyValuePair<KeyT, ValueT>>::ConstIteratorModel<DictionaryType>>( data.cbegin() ) }; }
        
        iterator        end() override { return       iterator{ std::make_unique<typename Private::LegacyForwardIteratorBase<KeyValuePair<KeyT, ValueT>>::IteratorModel<DictionaryType>>( data.end() ) }; }
        const_iterator cend() override { return const_iterator{ std::make_unique<typename Private::LegacyForwardIteratorBase<KeyValuePair<KeyT, ValueT>>::ConstIteratorModel<DictionaryType>>( data.cend() ) }; }

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

    template <class DictionaryType>
    IDictionary(DictionaryType &input)
      :
      m_pimpl( std::make_unique<InterfaceModel<DictionaryType>>(input) )
    {
    }

    template <class DictionaryType>
    IDictionary(DictionaryType &&input)
      :
      m_pimpl( std::make_unique<InterfaceModel<DictionaryType>>( std::move(input) ) )
    {
    }

    IDictionary(const IDictionary &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    IDictionary(IDictionary &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    IDictionary(IDictionary &&other)
      :
      m_pimpl( other.m_pimpl->Empty() )
    {
        std::swap( m_pimpl, other.m_pimpl );
    }

    IDictionary &operator =(const IDictionary &other)
    {
        m_pimpl = other.m_pimpl->Clone();
        return *this;
    }

    IDictionary &operator =(IDictionary &&other) = delete;

    // Collection
    std::size_t Count() const      { return m_pimpl->Count(); }
    bool        IsReadOnly() const { return m_pimpl->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return m_pimpl->IsSynchronized(); }

    void Add(const KeyValuePair<key_type, mapped_type> &item)      { m_pimpl->Add(item); }
    bool Remove(const KeyValuePair<key_type, mapped_type> &item)   { return m_pimpl->Remove(item); }
    void Clear()                                                   { m_pimpl->Clear(); }
    bool Contains(const KeyValuePair<key_type, mapped_type> &item) { return m_pimpl->Contains(item); }

    // Dictionary
          mapped_type &operator[](const key_type &key)       { return m_pimpl->operator [](key); }
          mapped_type &at(const key_type &key)               { return m_pimpl->at(key); }
    const mapped_type &at(const key_type &key)         const { return const_cast<const Interface *>(m_pimpl.get())->at(key); }

    void Add(const key_type &key, const mapped_type &value)                   { m_pimpl->Add(key, value); }
    bool TryAdd(const key_type &key, const mapped_type &value)                { return m_pimpl->TryAdd(key, value); }
    bool Remove(const key_type &key)                                          { return m_pimpl->Remove(key); }
    bool ContainsKey(const key_type &key)                               const { return m_pimpl->ContainsKey(key); }
    bool ContainsValue(const mapped_type &value)                        const { return m_pimpl->ContainsValue(value); }
    bool TryGetValue(const key_type &key, const mapped_type &value_out) const { return m_pimpl->TryGetValue(key, value_out); }

    ICollection<key_type>    Keys()   const { return m_pimpl->Keys();   }
    ICollection<mapped_type> Values() const { return m_pimpl->Values(); }

    // Range-for compatibility
          iterator  begin()       { return m_pimpl->begin();  }
    const_iterator  begin() const { return m_pimpl->cbegin(); }
    const_iterator cbegin() const { return m_pimpl->cbegin(); }

          iterator  end()       { return m_pimpl->end();  }
    const_iterator  end() const { return m_pimpl->cend(); }
    const_iterator cend() const { return m_pimpl->cend(); }

protected:
    std::unique_ptr<Interface> m_pimpl;
};

// Deduction Guides

template <class DictionaryType>
IDictionary(DictionaryType &input) -> IDictionary<typename DictionaryType::key_type, typename DictionaryType::mapped_type>;

}