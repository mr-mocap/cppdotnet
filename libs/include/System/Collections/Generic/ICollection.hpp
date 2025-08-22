#include "System/Collections/Generic/Private/LegacyForwardIterator.hpp"
#include "System/Collections/Generic/Private/ICollectionInterface.hpp"


namespace System::Collections::Generic
{

template <typename T>
class ICollection : public Private::LegacyForwardIteratorBase<T>
{
public:
    using IteratorBase = Private::LegacyForwardIteratorBase<T>;

    using typename IteratorBase::value_type;
    using typename IteratorBase::size_type;
    using typename IteratorBase::difference_type;
    using typename IteratorBase::reference;
    using typename IteratorBase::const_reference;
    using typename IteratorBase::pointer;
    using typename IteratorBase::const_pointer;
    using typename IteratorBase::iterator;
    using typename IteratorBase::const_iterator;

private:
    struct Policy
    {
        using value_type         = typename IteratorBase::value_type;
        using size_type          = typename IteratorBase::size_type;
        using IteratorType       = typename IteratorBase::iterator;
        using ConstIteratorType  = typename IteratorBase::const_iterator;
    };

    using Interface = Private::ICollectionInterface<Policy>;

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
        iterator        begin()       override { return       iterator{ std::make_unique<typename IteratorBase::IteratorModel<CollectionType>>(data.begin()) }; }
        const_iterator  begin() const override { return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<CollectionType>>(data.begin()) }; }
        const_iterator cbegin() const override { return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<CollectionType>>(data.cbegin()) }; }

        iterator        end()       override { return       iterator{ std::make_unique<typename IteratorBase::IteratorModel<CollectionType>>(data.end()) }; }
        const_iterator  end() const override { return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<CollectionType>>(data.end()) }; }
        const_iterator cend() const override { return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<CollectionType>>(data.cend()) }; }

        CollectionType data;
    };

public:
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
      m_pimpl( std::make_unique<InterfaceModel<CollectionType>>(input) )
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

    std::size_t Count() const      { return AsConst()->Count(); }
    bool        IsReadOnly() const { return AsConst()->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return AsConst()->IsSynchronized(); }

    void Add(const T &item)      { m_pimpl->Add(item); }
    bool Remove(const T &item)   { return m_pimpl->Remove(item); }
    void Clear()                 { m_pimpl->Clear(); }
    bool Contains(const T &item) { return m_pimpl->Contains(item); }

    // Range-for compatibility
          iterator  begin()       { return m_pimpl->begin();    }
    const_iterator  begin() const { return AsConst()->cbegin(); }
    const_iterator cbegin() const { return AsConst()->cbegin(); }

          iterator  end()       { return m_pimpl->end();    }
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

template <class CollectionType>
ICollection(CollectionType &input) -> ICollection<typename CollectionType::value_type>;

template <typename T>
class ICollectionRef : public Private::LegacyForwardIteratorBase<T>
{
public:
    using IteratorBase = Private::LegacyForwardIteratorBase<T>;

    using typename IteratorBase::value_type;
    using typename IteratorBase::size_type;
    using typename IteratorBase::difference_type;
    using typename IteratorBase::reference;
    using typename IteratorBase::const_reference;
    using typename IteratorBase::pointer;
    using typename IteratorBase::const_pointer;
    using typename IteratorBase::iterator;
    using typename IteratorBase::const_iterator;

private:
    struct Policy
    {
        using value_type         = typename IteratorBase::value_type;
        using size_type          = typename IteratorBase::size_type;
        using IteratorType       = typename IteratorBase::iterator;
        using ConstIteratorType  = typename IteratorBase::const_iterator;
    };

    using Interface = Private::ICollectionInterface<Policy>;

    template <class CollectionType>
    struct InterfaceModelPtr : Interface
    {
        InterfaceModelPtr() = default;
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

        std::unique_ptr<Interface> Empty() override
        {
            return nullptr; // Cannot create an empty collection from a reference
        }

        // Range-for compatibility
        iterator  begin() override
        {
            return iterator{ std::make_unique<typename IteratorBase::IteratorModel<CollectionType>>( data->begin() ) };
        }
        const_iterator begin() const override
        {
            return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<CollectionType>>( data->begin() ) };
        }
        const_iterator cbegin() const override
        {
            return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<CollectionType>>( data->cbegin() ) };
        }

        iterator  end() override
        {
            return iterator{ std::make_unique<typename IteratorBase::IteratorModel<CollectionType>>( data->end() ) };
        }
        const_iterator end() const override
        {
            return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<CollectionType>>( data->end() ) };
        }
        const_iterator cend() const override
        {
            return const_iterator{ std::make_unique<typename IteratorBase::ConstIteratorModel<CollectionType>>( data->cend() ) };
        }

        CollectionType *data = nullptr;
    };

public:
    ICollectionRef() = delete;

    template <typename ConcreteCollectionType>
    ICollectionRef(const ConcreteCollectionType *input)
      :
      m_pimpl( std::make_unique<const InterfaceModelPtr<ConcreteCollectionType>>(input) )
    {
    }

    template <typename ConcreteCollectionType>
    ICollectionRef(ConcreteCollectionType *input)
      :
      m_pimpl( std::make_unique<InterfaceModelPtr<ConcreteCollectionType>>(input) )
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
    bool        IsReadOnly() const { return AsConst()->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return AsConst()->IsSynchronized(); }

    void Add(const T &item)      { m_pimpl->Add(item); }
    bool Remove(const T &item)   { return m_pimpl->Remove(item); }
    void Clear()                 { m_pimpl->Clear(); }
    bool Contains(const T &item) { return m_pimpl->Contains(item); }

    // Range-for compatibility
          iterator  begin()       { return m_pimpl->begin();  }
    const_iterator  begin() const { return AsConst()->begin(); }
    const_iterator cbegin() const { return AsConst()->cbegin(); }

          iterator  end()       { return m_pimpl->end();  }
    const_iterator  end() const { return AsConst()->end(); }
    const_iterator cend() const { return AsConst()->cend(); }
protected:
    std::unique_ptr<Interface> m_pimpl;

    const Interface *AsConst() const
    {
        return m_pimpl.get();
    }
};

}