#pragma once

#include "System/Collections/Generic/KeyValuePair.hpp"
#include "System/Collections/Generic/ICollection.hpp"
#include <memory>
#include <iterator>

namespace System::Collections::Generic
{

template <typename KeyT, typename ValueT>
class IDictionary
{
    struct IteratorInterface;
    template <typename ModelT> class IteratorModel;
    
    struct ConstIteratorInterface;
    template <typename ModelT> class ConstIteratorModel;

public:
    using key_type    = KeyT;
    using mapped_type = ValueT;
    using value_type  = KeyValuePair<KeyT, ValueT>;
    using size_type   = std::size_t;
    using reference       =       value_type &;
    using const_reference = const value_type &;
    using pointer         =       KeyValuePair<KeyT, ValueT> *;
    using const_pointer   = const KeyValuePair<KeyT, ValueT> *;


    struct Iterator
    {
        using difference_type   = std::ptrdiff_t;
        using value_type        = KeyValuePair<KeyT, ValueT>;
        using pointer           = value_type *;
        using reference         = value_type &;
        using iterator_category = std::forward_iterator_tag;

        Iterator(std::unique_ptr<IteratorInterface> &&position)
            :
            m_pimpl( std::move(position) )
        {
        }

        Iterator(const Iterator &other)
          :
          m_pimpl( other.m_pimpl->Clone() )
        {
        }

        Iterator(Iterator &other)
          :
          m_pimpl( other.m_pimpl->Clone() )
        {
        }

        Iterator(Iterator &&other) = delete;

        Iterator &operator =(const Iterator &other)
        {
            m_pimpl = other.m_pimpl->Clone();
            return *this;
        }

        Iterator &operator =(Iterator &&other) = delete;

        reference operator *()  noexcept { return *(*m_pimpl); }

        reference  operator ->() noexcept { return m_pimpl->operator ->(); }

        Iterator &operator ++() noexcept
        {
            m_pimpl->operator ++();
            return *this;
        }

        Iterator operator ++(int dummy_value) noexcept
        {
            Iterator old = *this;

            m_pimpl = m_pimpl->post_increment();
            return old;
        }

        friend bool operator ==(const Iterator &left, const Iterator &right) noexcept
        {
            return *left.m_pimpl == *right.m_pimpl;
        }

        protected:
            std::unique_ptr<IteratorInterface> m_pimpl;

            Iterator() = default;
    };

    struct ConstIterator
    {
        using difference_type   = std::ptrdiff_t;
        using value_type        = KeyValuePair<KeyT, ValueT>;
        using pointer           = const value_type *;
        using reference         = const value_type &;
        using iterator_category = std::forward_iterator_tag;

        ConstIterator(std::unique_ptr<ConstIteratorInterface> &&position)
            :
            m_pimpl( std::move(position) )
        {
        }

        ConstIterator(const ConstIterator &other)
          :
          m_pimpl( other.m_pimpl->Clone() )
        {
        }

        ConstIterator(ConstIterator &other)
          :
          m_pimpl( other.m_pimpl->Clone() )
        {
        }

        ConstIterator(ConstIterator &&other) = delete;

        ConstIterator &operator =(const ConstIterator &other)
        {
            m_pimpl = other.m_pimpl->Clone();
            return *this;
        }

        ConstIterator &operator =(ConstIterator &&other) = delete;

        IDictionary::const_reference operator *()  noexcept { return *(*m_pimpl); }

        IDictionary::const_pointer   operator ->() noexcept { return m_pimpl->operator ->(); }

        ConstIterator &operator ++() noexcept
        {
            m_pimpl->operator ++();
            return *this;
        }

        Iterator operator ++(int dummy_value) noexcept
        {
            Iterator old = *this;

            m_pimpl = m_pimpl->post_increment();
            return old;
        }

        friend bool operator ==(const ConstIterator &left, const ConstIterator &right) noexcept
        {
            return *left.m_pimpl == *right.m_pimpl;
        }

        protected:
            std::unique_ptr<ConstIteratorInterface> m_pimpl;

            ConstIterator() = default;
    };

private:
    struct IteratorInterface
    {
        virtual ~IteratorInterface() { }

        virtual IDictionary::reference  operator*()  noexcept = 0;
        virtual IDictionary::pointer    operator->() noexcept = 0;
        virtual IteratorInterface      &operator++() noexcept = 0;

        virtual std::unique_ptr<IteratorInterface> post_increment() noexcept = 0;

        virtual bool EqualTo(const IteratorInterface &other) const = 0;

        friend bool operator==(const IteratorInterface &left, const IteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }
    };

    template <typename DictionaryType>
    struct IteratorModel : IteratorInterface
    {
        IteratorModel(DictionaryType::iterator i)
          :
          m_iterator( i )
        {
        }

       ~IteratorModel() override { }

        IDictionary::reference operator*() noexcept override
        {
            return *m_iterator;
        }

        IDictionary::pointer operator->() noexcept override
        {
            return m_iterator.operator ->();
        }

        IteratorInterface &operator++() noexcept override
        {
            ++m_iterator;
            return *this;
        }

        std::unique_ptr<IteratorInterface> post_increment() noexcept override
        {
            typename DictionaryType::iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<IteratorModel>(old);
        }

        bool EqualTo(const IteratorInterface &other) const override
        {
            const IteratorModel<DictionaryType> *p = dynamic_cast<const IteratorModel<DictionaryType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            DictionaryType::iterator m_iterator;
    };

    struct ConstIteratorInterface
    {
        virtual ~ConstIteratorInterface() { }

        virtual IDictionary::const_reference             operator*()  noexcept = 0;
        virtual IDictionary::const_pointer               operator->() noexcept = 0;
        virtual ConstIteratorInterface                  &operator++() noexcept = 0;
        virtual std::unique_ptr<ConstIteratorInterface>  post_increment() noexcept = 0;

        virtual bool EqualTo(const ConstIteratorInterface &other) const = 0;

        friend bool operator==(const ConstIteratorInterface &left, const ConstIteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }
    };

    template <typename DictionaryType>
    struct ConstIteratorModel : ConstIteratorInterface
    {
        ConstIteratorModel(DictionaryType::const_iterator i)
          :
          m_iterator( i )
        {
        }

       ~ConstIteratorModel() override { }

        IDictionary::const_reference operator*() noexcept override
        {
            return *m_iterator;
        }

        IDictionary::const_pointer operator->() noexcept override
        {
            return m_iterator.operator ->();
        }

        ConstIteratorInterface &operator++() noexcept override
        {
            ++m_iterator;
            return *this;
        }

        std::unique_ptr<ConstIteratorInterface> post_increment() noexcept override
        {
            typename DictionaryType::const_iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<ConstIteratorModel>(old);
        }

        bool EqualTo(const ConstIteratorInterface &other) const override
        {
            const ConstIteratorModel<DictionaryType> *p = dynamic_cast<const ConstIteratorModel<DictionaryType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            DictionaryType::const_iterator m_iterator;
    };

    struct Interface
    {
        virtual ~Interface() { }

        virtual std::size_t Count()      const = 0;
        virtual bool        IsReadOnly() const = 0;
        virtual bool        IsReadOnly()       = 0;
        virtual bool        IsSynchronized() const = 0;

        // Collection
        virtual void Add(const KeyValuePair<key_type, mapped_type> &item)      = 0;
        virtual bool Remove(const KeyValuePair<key_type, mapped_type> &item)   = 0;
        virtual void Clear() = 0;
        virtual bool Contains(const KeyValuePair<key_type, mapped_type> &item) = 0;

        // TODO: Add CopyTo() ?

        // Dictionary
        virtual       mapped_type &operator[](const key_type &key)       = 0;
        virtual       mapped_type &at(const key_type &key)       = 0;
        virtual const mapped_type &at(const key_type &key) const = 0;

        virtual void Add(const key_type &key, const mapped_type &value)             = 0;
        virtual bool TryAdd(const key_type &key, const mapped_type &value)          = 0;
        virtual bool Remove(const key_type &key)                                    = 0;
        virtual bool ContainsKey(const key_type &key)                         const = 0;
        virtual bool ContainsValue(const mapped_type &value)                  const = 0;
        virtual bool TryGetValue(const key_type &key, mapped_type &value_out) const = 0;

        virtual ICollection<key_type>    Keys()   const = 0;
        virtual ICollection<mapped_type> Values() const = 0;

        virtual Iterator       begin()       = 0;
        virtual ConstIterator  begin() const = 0;
        virtual ConstIterator cbegin() const noexcept = 0;

        virtual Iterator       end()                = 0;
        virtual ConstIterator  end() const          = 0;
        virtual ConstIterator cend() const noexcept = 0;

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

        Iterator       begin()                { return Iterator{ std::make_unique<IteratorModel<DictionaryType>>(data.begin()) }; }
        ConstIterator  begin() const          { return ConstIterator{ std::make_unique<ConstIteratorModel<DictionaryType>>(data.begin()) }; }
        ConstIterator cbegin() const noexcept { return ConstIterator{ std::make_unique<ConstIteratorModel<DictionaryType>>(data.cbegin()) }; }
        
        Iterator       end()                { return Iterator{ std::make_unique<IteratorModel<DictionaryType>>(data.end()) }; }
        ConstIterator  end() const          { return ConstIterator{ std::make_unique<ConstIteratorModel<DictionaryType>>(data.end()) }; }
        ConstIterator cend() const noexcept { return ConstIterator{ std::make_unique<ConstIteratorModel<DictionaryType>>(data.cend()) }; }

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
    using iterator               = Iterator;
    using const_iterator         = ConstIterator;
    using reverse_iterator       = std::reverse_iterator<Iterator>;
    using const_reverse_iterator = std::reverse_iterator<ConstIterator>;

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
    const mapped_type &at(const key_type &key)         const { return m_pimpl->at(key); }

    void Add(const key_type &key, const mapped_type &value)                   { m_pimpl->Add(key, value); }
    bool TryAdd(const key_type &key, const mapped_type &value)                { return m_pimpl->TryAdd(key, value); }
    bool Remove(const key_type &key)                                    const { return m_pimpl->Remove(key); }
    bool ContainsKey(const key_type &key)                               const { return m_pimpl->ContainsKey(key); }
    bool ContainsValue(const mapped_type &value)                        const { return m_pimpl->ContainsValue(value); }
    bool TryGetValue(const key_type &key, const mapped_type &value_out) const { return m_pimpl->TryGetValue(key, value_out); }

    ICollection<key_type>    Keys()   const { return m_pimpl->Keys(); }
    ICollection<mapped_type> Values() const { return m_pimpl->Values(); }

    // Range-for compatibility
          iterator  begin()                { return m_pimpl->begin(); }
    const_iterator  begin() const          { return const_cast<const Interface *>(m_pimpl.get())->begin(); } // We have to make the underlying object const here
    const_iterator cbegin() const noexcept { return m_pimpl->cbegin(); }

          iterator  end()                { return m_pimpl->end(); }
    const_iterator  end()  const         { return const_cast<const Interface *>(m_pimpl.get())->end(); }
    const_iterator cend() const noexcept { return m_pimpl->cend(); }

protected:
    std::unique_ptr<Interface> m_pimpl;
};

// Deduction Guides

template <class DictionaryType>
IDictionary(DictionaryType &input) -> IDictionary<typename DictionaryType::key_type, typename DictionaryType::mapped_type>;

}