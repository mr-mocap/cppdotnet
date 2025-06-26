#pragma once

#include <memory>
#include <iterator>


namespace System::Collections::Generic
{

template <typename T>
class ICollection
{
    struct IteratorInterface;
    template <typename ModelT> class IteratorModel;
    
    struct ConstIteratorInterface;
    template <typename ModelT> class ConstIteratorModel;

public:
    struct ConstIterator;

    struct Iterator
    {
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
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

        T &operator *()  noexcept { return *(*m_pimpl); }

        T  operator ->() noexcept { return m_pimpl->operator ->(); }

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

        ConstIterator AsConst() const
        {
            return ConstIterator( m_pimpl->CloneAsConst() );
        }

        protected:
            std::unique_ptr<IteratorInterface> m_pimpl;

            Iterator() = default;
    };

    struct ConstIterator
    {
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
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

        ConstIterator(const Iterator &other)
            :
            m_pimpl( std::move( other.AsConst().m_pimpl ) )
        {
        }
            
        ConstIterator(ConstIterator &&other) = delete;

        ConstIterator &operator =(const ConstIterator &other)
        {
            m_pimpl = other.m_pimpl->Clone();
            return *this;
        }

        ConstIterator &operator =(ConstIterator &&other) = delete;

        const T &operator*() noexcept { return *(*m_pimpl); }

        const T *operator->() noexcept  { return m_pimpl->operator ->(); }

        ConstIterator &operator++() noexcept
        {
            m_pimpl->operator ++();
            return *this;
        }

        ConstIterator operator ++(int dummy_value) noexcept
        {
            ConstIterator old = *this;

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
    struct ConstIteratorInterface;

    struct IteratorInterface
    {
        virtual ~IteratorInterface() { }

        virtual T &operator*() noexcept = 0;

        virtual T *operator->() noexcept = 0;

        virtual IteratorInterface &operator++() noexcept = 0;

        virtual std::unique_ptr<IteratorInterface> post_increment() noexcept = 0;

        friend bool operator ==(const IteratorInterface &left, const IteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }

        virtual std::unique_ptr<IteratorInterface> Clone() = 0;
        virtual std::unique_ptr<ConstIteratorInterface> CloneAsConst() = 0;

        virtual bool EqualTo(const IteratorInterface &other) const = 0;
    };

    template <typename CollectionType>
    struct IteratorModel : IteratorInterface
    {
        IteratorModel(CollectionType::iterator i)
          :
          m_iterator( i )
        {
        }

       ~IteratorModel() override { }

        T &operator*() noexcept override
        {
            return *m_iterator;
        }

        T *operator->() noexcept override
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
            typename CollectionType::iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<IteratorModel>(old);
        }

        std::unique_ptr<IteratorInterface> Clone() override
        {
            return std::make_unique<IteratorModel>(m_iterator);
        }

        std::unique_ptr<ConstIteratorInterface> CloneAsConst() override;

        bool EqualTo(const IteratorInterface &other) const override
        {
            const IteratorModel<CollectionType> *p = dynamic_cast<const IteratorModel<CollectionType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            CollectionType::iterator m_iterator;
    };

    struct ConstIteratorInterface
    {
        virtual ~ConstIteratorInterface() { }

        virtual const T &operator*() noexcept = 0;

        virtual const T *operator->() noexcept = 0;

        virtual ConstIteratorInterface &operator++() noexcept = 0;

        virtual std::unique_ptr<ConstIteratorInterface> post_increment() noexcept = 0;

        friend bool operator ==(const ConstIteratorInterface &left, const ConstIteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }

        virtual std::unique_ptr<ConstIteratorInterface> Clone() const = 0;

        virtual bool EqualTo(const ConstIteratorInterface &other) const = 0;
    };

    template <typename CollectionType>
    struct ConstIteratorModel : ConstIteratorInterface
    {
        ConstIteratorModel(CollectionType::const_iterator i)
          :
          m_iterator( i )
        {
        }

        ConstIteratorModel(CollectionType::iterator i)
            :
            m_iterator( i )
        {
        }

       ~ConstIteratorModel() override { }

        const T &operator*() noexcept override
        {
            return *m_iterator;
        }

        const T *operator->() noexcept override
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
            typename CollectionType::const_iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<ConstIteratorModel>(old);
        }

        std::unique_ptr<ConstIteratorInterface> Clone() const override
        {
            return std::make_unique<ConstIteratorModel>(m_iterator);
        }

        bool EqualTo(const ConstIteratorInterface &other) const override
        {
            const ConstIteratorModel<CollectionType> *p = dynamic_cast<const ConstIteratorModel<CollectionType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            CollectionType::const_iterator m_iterator;
    };

    struct Interface
    {
        virtual ~Interface() { }

        virtual std::size_t Count() const = 0;
        virtual bool        IsReadOnly() const = 0;
        virtual bool        IsReadOnly()       = 0;
        virtual bool        IsSynchronized() const = 0;

        virtual void Add(const T &item) = 0;
        virtual bool Remove(const T &item) = 0;
        virtual void Clear() = 0;
        virtual bool Contains(const T &item) = 0;

        // TODO: Add CopyTo() ?

        virtual std::unique_ptr<Interface> Clone() = 0;
        virtual std::unique_ptr<Interface> Empty() = 0;

        // Range-for compatibility
        virtual      Iterator  begin()       = 0;
        virtual ConstIterator cbegin() const = 0;

        virtual      Iterator  end()       = 0;
        virtual ConstIterator cend() const = 0;
    };

    template <class CollectionType>
    struct InterfaceModel : Interface
    {
        InterfaceModel() = default;
        InterfaceModel(const CollectionType  &input) : data( input ) { }
        InterfaceModel(CollectionType &&input) : data( std::move(input) ) { }
        ~InterfaceModel() override { }
          
        // Default copy and move
        InterfaceModel(const InterfaceModel &other) = default;
        InterfaceModel(InterfaceModel &&other) = default;

        InterfaceModel &operator =(const InterfaceModel &) = default;
        InterfaceModel &operator =(InterfaceModel &&) = default;

        std::size_t Count() const override { return data.Count(); }

        bool IsReadOnly() const override { return data.IsReadOnly(); }
        bool IsReadOnly()       override { return data.IsReadOnly(); }

        bool IsSynchronized() const { return data.IsSynchronized(); }

        void Add(const T &item) override { data.Add(item); }

        bool Remove(const T &item) override { return data.Remove(item); }

        void Clear() override { data.Clear(); }

        bool Contains(const T &item) override { return data.Contains(item); }

        std::unique_ptr<Interface> Clone() override
        {
            return std::make_unique<InterfaceModel>(data);
        }

        std::unique_ptr<Interface> Empty() override
        {
            return std::make_unique_for_overwrite<InterfaceModel>();
        }

        // Range-for compatibility
             Iterator  begin()       override { return Iterator( std::make_unique<IteratorModel<CollectionType>>(data.begin()) ); }
        ConstIterator cbegin() const override { return ConstIterator( std::make_unique<ConstIteratorModel<CollectionType>>(data.cbegin()) ); }

             Iterator  end()       override { return Iterator( std::make_unique<IteratorModel<CollectionType>>(data.end()) ); }
        ConstIterator cend() const override { return ConstIterator( std::make_unique<ConstIteratorModel<CollectionType>>(data.cend()) ); }

        CollectionType data;
    };

public:
    using value_type  = T;
    using size_type   = std::size_t;
    using reference       =       value_type &;
    using const_reference = const value_type &;
    using pointer         =       value_type *;
    using const_pointer   = const value_type *;

    using iterator        = Iterator;
    using const_iterator  = ConstIterator;


    ICollection() = delete;

    template <typename CollectionType>
    ICollection(CollectionType &input)
      :
      m_pimpl( std::make_unique<InterfaceModel<CollectionType>>(input) )
    {
    }

    template <typename CollectionType>
    ICollection(const CollectionType &input)
      :
      m_pimpl( std::make_unique<const InterfaceModel<CollectionType>>(input) )
    {
    }

    template <typename CollectionType>
    ICollection(CollectionType &&input)
      :
      m_pimpl( std::make_unique<InterfaceModel<CollectionType>>( std::move(input) ) )
    {
    }

    ICollection(const ICollection &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    ICollection(ICollection &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    ICollection(ICollection &&other)
      :
      m_pimpl( other.m_pimpl->Empty() )
    {
        std::swap( m_pimpl, other.m_pimpl );
    }

    ICollection &operator =(const ICollection &other)
    {
        m_pimpl = other.m_pimpl->Clone();
        return *this;
    }

    ICollection &operator =(ICollection &&other) = delete;

    std::size_t Count() const      { return m_pimpl->Count(); }
    bool        IsReadOnly() const { return m_pimpl->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return m_pimpl->IsSynchronized(); }

    void Add(const T &item)      { m_pimpl->Add(item); }
    bool Remove(const T &item)   { return m_pimpl->Remove(item); }
    void Clear()                 { m_pimpl->Clear(); }
    bool Contains(const T &item) { return m_pimpl->Contains(item); }

    // Range-for compatibility
          iterator  begin()       { return m_pimpl->begin(); }
    const_iterator  begin() const { return m_pimpl->cbegin(); }
    const_iterator cbegin() const { return m_pimpl->cbegin(); }

          iterator  end()       { return m_pimpl->end(); }
    const_iterator  end() const { return m_pimpl->cend(); }
    const_iterator cend() const { return m_pimpl->cend(); }
protected:
    std::unique_ptr<Interface> m_pimpl;
};

template <class CollectionType>
template <class Specialization>
auto ICollection<CollectionType>::IteratorModel<Specialization>::CloneAsConst() -> std::unique_ptr<typename ICollection<CollectionType>::ConstIteratorInterface>
{
    return std::make_unique<ICollection<CollectionType>::ConstIteratorModel<Specialization>>(m_iterator);
}

// Deduction Guides

template <typename CollectionType>
ICollection(CollectionType &input) -> ICollection<typename CollectionType::value_type>;


template <typename T>
class ICollectionRef
{
    struct IteratorInterface;
    template <typename ModelT> class IteratorModel;
    
    struct ConstIteratorInterface;
    template <typename ModelT> class ConstIteratorModel;

public:
    struct ConstIterator;

    struct Iterator
    {
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
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

        T &operator *()  noexcept { return *(*m_pimpl); }

        T  operator ->() noexcept { return m_pimpl->operator ->(); }

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

        ConstIterator AsConst() const
        {
            return ConstIterator( m_pimpl->CloneAsConst() );
        }

        protected:
            std::unique_ptr<IteratorInterface> m_pimpl;

            Iterator() = default;
    };

    struct ConstIterator
    {
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
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

        ConstIterator(const Iterator &other)
            :
            m_pimpl( std::move( other.AsConst().m_pimpl ) )
        {
        }
            
        ConstIterator(ConstIterator &&other) = delete;

        ConstIterator &operator =(const ConstIterator &other)
        {
            m_pimpl = other.m_pimpl->Clone();
            return *this;
        }

        ConstIterator &operator =(ConstIterator &&other) = delete;

        const T &operator*() noexcept { return *(*m_pimpl); }

        const T *operator->() noexcept  { return m_pimpl->operator ->(); }

        ConstIterator &operator++() noexcept
        {
            m_pimpl->operator ++();
            return *this;
        }

        ConstIterator operator ++(int dummy_value) noexcept
        {
            ConstIterator old = *this;

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
    struct ConstIteratorInterface;

    struct IteratorInterface
    {
        virtual ~IteratorInterface() { }

        virtual T &operator*() noexcept = 0;

        virtual T *operator->() noexcept = 0;

        virtual IteratorInterface &operator++() noexcept = 0;

        virtual std::unique_ptr<IteratorInterface> post_increment() noexcept = 0;

        friend bool operator ==(const IteratorInterface &left, const IteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }

        virtual std::unique_ptr<IteratorInterface> Clone() = 0;
        virtual std::unique_ptr<ConstIteratorInterface> CloneAsConst() = 0;

        virtual bool EqualTo(const IteratorInterface &other) const = 0;
    };

    template <typename CollectionType>
    struct IteratorModel : IteratorInterface
    {
        IteratorModel(CollectionType::iterator i)
          :
          m_iterator( i )
        {
        }

       ~IteratorModel() override { }

        T &operator*() noexcept override
        {
            return *m_iterator;
        }

        T *operator->() noexcept override
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
            typename CollectionType::iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<IteratorModel>(old);
        }

        std::unique_ptr<IteratorInterface> Clone() override
        {
            return std::make_unique<IteratorModel>(m_iterator);
        }

        std::unique_ptr<ConstIteratorInterface> CloneAsConst() override;
        
        bool EqualTo(const IteratorInterface &other) const override
        {
            const IteratorModel<CollectionType> *p = dynamic_cast<const IteratorModel<CollectionType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            CollectionType::iterator m_iterator;
    };

    struct ConstIteratorInterface
    {
        virtual ~ConstIteratorInterface() { }

        virtual const T &operator*() noexcept = 0;

        virtual const T *operator->() noexcept = 0;

        virtual ConstIteratorInterface &operator++() noexcept = 0;

        virtual std::unique_ptr<ConstIteratorInterface> post_increment() noexcept = 0;

        friend bool operator ==(const ConstIteratorInterface &left, const ConstIteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }

        virtual std::unique_ptr<ConstIteratorInterface> Clone() const = 0;

        virtual bool EqualTo(const ConstIteratorInterface &other) const = 0;
    };

    template <typename CollectionType>
    struct ConstIteratorModel : ConstIteratorInterface
    {
        ConstIteratorModel(CollectionType::const_iterator i)
          :
          m_iterator( i )
        {
        }

       ~ConstIteratorModel() override { }

        const T &operator*() noexcept override
        {
            return *m_iterator;
        }

        const T *operator->() noexcept override
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
            typename CollectionType::const_iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<ConstIteratorModel>(old);
        }

        std::unique_ptr<ConstIteratorInterface> Clone() const override
        {
            return std::make_unique<ConstIteratorModel>(m_iterator);
        }

        bool EqualTo(const ConstIteratorInterface &other) const override
        {
            const ConstIteratorModel<CollectionType> *p = dynamic_cast<const ConstIteratorModel<CollectionType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            CollectionType::const_iterator m_iterator;
    };

    struct Interface
    {
        virtual ~Interface() { }

        virtual std::size_t Count() const = 0;
        virtual bool        IsReadOnly() const = 0;
        virtual bool        IsReadOnly()       = 0;
        virtual bool        IsSynchronized() const = 0;

        virtual void Add(const T &item) = 0;
        virtual bool Remove(const T &item) = 0;
        virtual void Clear() = 0;
        virtual bool Contains(const T &item) = 0;

        // TODO: Add CopyTo() ?

        virtual std::unique_ptr<Interface> Clone() = 0;

        // Range-for compatibility
        virtual      Iterator  begin()       = 0;
        virtual ConstIterator cbegin() const = 0;

        virtual      Iterator  end()       = 0;
        virtual ConstIterator cend() const = 0;
    };

    template <class CollectionType>
    struct InterfaceModelPtr : Interface
    {
        InterfaceModelPtr() = delete;
        InterfaceModelPtr(CollectionType *input) : data( input ) { } // For easily creating a copy
       ~InterfaceModelPtr() override
        {
            data = nullptr;
        }
          
        // Default copy and move
        InterfaceModelPtr(const InterfaceModelPtr &other) = default;
        InterfaceModelPtr(InterfaceModelPtr &&other) = default;

        InterfaceModelPtr &operator =(const InterfaceModelPtr &) = default;
        InterfaceModelPtr &operator =(InterfaceModelPtr &&) = default;

        std::size_t Count() const override { return data->Count(); }

        bool IsReadOnly() const override { return data->IsReadOnly(); }
        bool IsReadOnly()       override { return data->IsReadOnly(); }

        bool IsSynchronized() const override { return data->IsSynchronized(); }

        void Add(const T &item) override { data->Add(item); }

        bool Remove(const T &item) override { return data->Remove(item); }

        void Clear() override { data->Clear(); }

        bool Contains(const T &item) override { return data->Contains(item); }

        std::unique_ptr<Interface> Clone() override
        {
            return std::make_unique<InterfaceModelPtr<CollectionType>>(data);
        }

        // Range-for compatibility
             Iterator  begin()       override { return Iterator( std::make_unique<IteratorModel<CollectionType>>(data->begin()) ); }
        ConstIterator cbegin() const override { return ConstIterator( std::make_unique<ConstIteratorModel<CollectionType>>(data->cbegin()) ); }

             Iterator  end()       override { return Iterator( std::make_unique<IteratorModel<CollectionType>>(data->end()) ); }
        ConstIterator cend() const override { return ConstIterator( std::make_unique<ConstIteratorModel<CollectionType>>(data->cend()) ); }

        CollectionType *data = nullptr;
    };

public:
    using value_type  = T;
    using size_type   = std::size_t;
    using reference       =       value_type &;
    using const_reference = const value_type &;
    using pointer         =       value_type *;
    using const_pointer   = const value_type *;

    using iterator        = Iterator;
    using const_iterator  = ConstIterator;


    ICollectionRef() = delete;

    template <typename CollectionType>
    ICollectionRef(const CollectionType *input)
      :
      m_pimpl( std::make_unique<const InterfaceModelPtr<CollectionType>>(input) )
    {
    }

    template <typename CollectionType>
    ICollectionRef(CollectionType *input)
      :
      m_pimpl( std::make_unique<InterfaceModelPtr<CollectionType>>(input) )
    {
    }

    ICollectionRef(const ICollectionRef &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    ICollectionRef(ICollectionRef &&other) = delete;

    ICollectionRef &operator =(const ICollectionRef &other)
    {
        m_pimpl = other.m_pimpl->Clone();
        return *this;
    }

    ICollectionRef &operator =(ICollectionRef &&other) = delete;

    std::size_t Count() const      { return m_pimpl->Count(); }
    bool        IsReadOnly() const { return m_pimpl->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return m_pimpl->IsSynchronized(); }

    void Add(const T &item)      { m_pimpl->Add(item); }
    bool Remove(const T &item)   { return m_pimpl->Remove(item); }
    void Clear()                 { m_pimpl->Clear(); }
    bool Contains(const T &item) { return m_pimpl->Contains(item); }

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

template <class CollectionType>
template <class Specialization>
auto ICollectionRef<CollectionType>::IteratorModel<Specialization>::CloneAsConst() -> std::unique_ptr<typename ICollectionRef<CollectionType>::ConstIteratorInterface>
{
    return std::make_unique<ICollectionRef<CollectionType>::ConstIteratorModel<Specialization>>(m_iterator);
}

}