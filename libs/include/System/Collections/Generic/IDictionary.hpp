#include "System/Collections/Generic/Private/LegacyForwardIterator.hpp"
#include "System/Collections/Generic/Private/IDictionaryInterface.hpp"

namespace System::Collections::Generic
{

template <typename KeyT, typename ValueT>
class IDictionary : public Private::LegacyForwardIteratorBase<KeyValuePair<KeyT, ValueT>>
{
public:
    using IteratorBase = Private::LegacyForwardIteratorBase<KeyValuePair<KeyT, ValueT>>;

    using key_type    = KeyT;
    using mapped_type = ValueT;
    using typename IteratorBase::value_type;
    using typename IteratorBase::size_type;
    using typename IteratorBase::reference;
    using typename IteratorBase::const_reference;
    using typename IteratorBase::pointer;
    using typename IteratorBase::const_pointer;
    using typename IteratorBase::iterator;
    using typename IteratorBase::const_iterator;

private:
    struct Policy
    {
        using key_type    = KeyT;
        using mapped_type = ValueT;
        using value_type         = typename IteratorBase::value_type;
        using size_type          = typename IteratorBase::size_type;
        using IteratorType       = typename IteratorBase::iterator;
        using ConstIteratorType  = typename IteratorBase::const_iterator;
    };

    using Interface = Private::IDictionaryInterface<Policy>;

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

        void Add(const value_type &item)      override { data.Add(item); }
        bool Remove(const value_type &item)   override { return data.Remove(item); }
        void Clear()                          override { data.Clear(); }
        bool Contains(const value_type &item) override { return data.Contains(item); }

        // Dictionary
              mapped_type &operator[](const key_type &key)       override { return data[key]; }
        const mapped_type &at(const key_type &key)         const override { return data.at(key); }
              mapped_type &at(const key_type &key)               override { return data.at(key); }

        void Add(const key_type &key, const mapped_type &value)             override { data.Add(key, value); }
        bool Remove(const key_type &key)                                    override { return data.Remove(key); }
        bool ContainsKey(const key_type &key)                         const override { return data.ContainsKey(key); }
        bool TryGetValue(const key_type &key, mapped_type &value_out) const override { return data.TryGetValue(key, value_out); }

        ICollection<key_type>    Keys()   const override { return data.Keys(); }
        ICollection<mapped_type> Values() const override { return data.Values(); }

        iterator        begin()       override { return       iterator{ std::make_unique<typename IteratorBase::IteratorModel<DictionaryType>>( data.begin() ) }; }
        const_iterator  begin() const override { return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<DictionaryType>>( data.begin() ) }; }
        const_iterator cbegin() const override { return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<DictionaryType>>( data.cbegin() ) }; }
        
        iterator        end()       override { return       iterator{ std::make_unique<typename IteratorBase::IteratorModel<DictionaryType>>( data.end() ) }; }
        const_iterator  end() const override { return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<DictionaryType>>( data.end() ) }; }
        const_iterator cend() const override { return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<DictionaryType>>( data.cend() ) }; }

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
    std::size_t Count() const      { return AsConst()->Count(); }
    bool        IsReadOnly() const { return AsConst()->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return AsConst()->IsSynchronized(); }

    void Add(const KeyValuePair<key_type, mapped_type> &item)      { m_pimpl->Add(item); }
    bool Remove(const KeyValuePair<key_type, mapped_type> &item)   { return m_pimpl->Remove(item); }
    void Clear()                                                   { m_pimpl->Clear(); }
    bool Contains(const KeyValuePair<key_type, mapped_type> &item) { return m_pimpl->Contains(item); }

    // Dictionary
          mapped_type &operator[](const key_type &key)       { return m_pimpl->operator [](key); }
    const mapped_type &at(const key_type &key)         const { return AsConst()->at(key); }
          mapped_type &at(const key_type &key)               { return m_pimpl->at(key); }

    void Add(const key_type &key, const mapped_type &value)                   { m_pimpl->Add(key, value); }
    bool Remove(const key_type &key)                                          { return m_pimpl->Remove(key); }
    bool ContainsKey(const key_type &key)                               const { return AsConst()->ContainsKey(key); }
    bool TryGetValue(const key_type &key, const mapped_type &value_out) const { return AsConst()->TryGetValue(key, value_out); }

    ICollection<key_type>    Keys()   const { return AsConst()->Keys();   }
    ICollection<mapped_type> Values() const { return AsConst()->Values(); }

    // Range-for compatibility
          iterator  begin()       { return m_pimpl->begin();  }
    const_iterator  begin() const { return AsConst()->cbegin(); }
    const_iterator cbegin() const { return AsConst()->cbegin(); }

          iterator  end()       { return m_pimpl->end();  }
    const_iterator  end() const { return AsConst()->cend(); }
    const_iterator cend() const { return AsConst()->cend(); }

protected:
    std::unique_ptr<Interface> m_pimpl;

    const Interface *AsConst() const
    {
        return m_pimpl.get();
    }
};

// Deduction Guides

template <class DictionaryType>
IDictionary(DictionaryType &input) -> IDictionary<typename DictionaryType::key_type, typename DictionaryType::mapped_type>;

}