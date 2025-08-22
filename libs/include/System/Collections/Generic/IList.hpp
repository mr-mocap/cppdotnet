#include "System/Collections/Generic/Private/LegacyBidirectionalIterator.hpp"
#include "System/Collections/Generic/Private/IListInterface.hpp"

namespace System::Collections::Generic
{

template <class T>
class IList : public Private::LegacyBidirectionalIteratorBase<T>
{
public:
    using IteratorBase = Private::LegacyBidirectionalIteratorBase<T>;

    using typename IteratorBase::difference_type;
    using typename IteratorBase::size_type;
    using typename IteratorBase::value_type;
    using typename IteratorBase::pointer;
    using typename IteratorBase::reference;
    using typename IteratorBase::iterator;
    using typename IteratorBase::const_iterator;
    using typename IteratorBase::reverse_iterator;
    using typename IteratorBase::const_reverse_iterator;

private:
    struct Policy
    {
        using value_type         = typename IteratorBase::value_type;
        using size_type          = typename IteratorBase::size_type;
        using IteratorType       = typename IteratorBase::iterator;
        using ConstIteratorType  = typename IteratorBase::const_iterator;
        using ReverseIteratorType       = typename IteratorBase::reverse_iterator;
        using ConstReverseIteratorType  = typename IteratorBase::const_reverse_iterator;
    };

    using Interface = Private::IListInterface<Policy>;

    template <class ListType>
    struct InterfaceModel : Interface
    {
        InterfaceModel() = default;
        InterfaceModel(const ListType  &input) : data( input ) { }
        InterfaceModel(ListType &&input) : data( std::move(input) ) { }
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

        void Add(const value_type &item) override { data.Add(item); }
        bool Remove(const value_type &item) override { return data.Remove(item); }
        void Clear() override { data.Clear(); }
        bool Contains(const value_type &item) override { return data.Contains(item); }

        const value_type &operator [](std::size_t index) const override { return Private::IListIndexer<ListType>::GetAt(data, index); }
              value_type &operator [](std::size_t index)       override { return Private::IListIndexer<ListType>::GetAt(data, index); }

        size_type IndexOf(const value_type &item) const { return data.IndexOf(item); }

        void Insert(std::size_t index, const value_type &item) override { data.Insert(index, item); }
        void RemoveAt(std::size_t index) override { data.RemoveAt(index); }

        std::unique_ptr<Interface> Clone() override { return std::make_unique<InterfaceModel<ListType>>(data); }

        std::unique_ptr<Interface> Empty() override { return std::make_unique_for_overwrite<InterfaceModel<ListType>>(); }

        // Range-for compatibility
              iterator  begin()       override { return iterator( std::make_unique<typename IteratorBase::IteratorModel<ListType>>( data.begin() ) ); }
        const_iterator  begin() const override { return const_iterator( std::make_unique<typename IteratorBase::ConstIteratorModel<ListType>>( data.begin() ) ); }
        const_iterator cbegin() const override { return const_iterator( std::make_unique<typename IteratorBase::ConstIteratorModel<ListType>>( data.cbegin() ) ); }

              iterator  end()       override { return iterator( std::make_unique<typename IteratorBase::IteratorModel<ListType>>( data.end() ) ); }
        const_iterator  end() const override { return const_iterator( std::make_unique<typename IteratorBase::ConstIteratorModel<ListType>>( data.end() ) ); }
        const_iterator cend() const override { return const_iterator( std::make_unique<typename IteratorBase::ConstIteratorModel<ListType>>( data.cend() ) ); }

              reverse_iterator  rbegin()       override { return reverse_iterator( std::make_unique<typename IteratorBase::ReverseIteratorModel<ListType>>( data.rbegin() ) ); }
        const_reverse_iterator  rbegin() const override { return const_reverse_iterator( std::make_unique<typename IteratorBase::ConstReverseIteratorModel<ListType>>( data.rbegin() ) ); }
        const_reverse_iterator crbegin() const override { return const_reverse_iterator( std::make_unique<typename IteratorBase::ConstReverseIteratorModel<ListType>>( data.crbegin() ) ); }

              reverse_iterator  rend()       override { return reverse_iterator( std::make_unique<typename IteratorBase::ReverseIteratorModel<ListType>>( data.rend() ) ); }
        const_reverse_iterator  rend() const override { return const_reverse_iterator( std::make_unique<typename IteratorBase::ConstReverseIteratorModel<ListType>>( data.rend() ) ); }
        const_reverse_iterator crend() const override { return const_reverse_iterator( std::make_unique<typename IteratorBase::ConstReverseIteratorModel<ListType>>( data.crend() ) ); }

        ListType data;
    };

public:
    IList() = delete;

    template <typename ListType>
    IList(ListType &input)
      :
      m_pimpl( std::make_unique<InterfaceModel<ListType>>(input) )
    {
    }

    template <typename ListType>
    IList(const ListType &input)
      :
      m_pimpl( std::make_unique<const InterfaceModel<ListType>>(input) )
    {
    }

    template <typename ListType>
    IList(ListType &&input)
      :
      m_pimpl( std::make_unique<InterfaceModel<ListType>>( std::move(input) ) )
    {
    }

    IList(const IList &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    IList(IList &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    IList(IList &&other)
      :
      m_pimpl( other.m_pimpl->Empty() )
    {
        std::swap( m_pimpl, other.m_pimpl );
    }

    IList &operator =(const IList &other)
    {
        m_pimpl = other.m_pimpl->Clone();
        return *this;
    }

    IList &operator =(IList &&other) = delete;

    std::size_t Count() const      { return AsConst()->Count(); }
    bool        IsReadOnly() const { return AsConst()->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return AsConst()->IsSynchronized(); }

    void Add(const T &item)      { m_pimpl->Add(item); }
    bool Remove(const T &item)   { return m_pimpl->Remove(item); }
    void Clear()                 { m_pimpl->Clear(); }
    bool Contains(const T &item) { return m_pimpl->Contains(item); }

    const T &operator [](std::size_t index) const { return (*AsConst())[index]; }
          T &operator [](std::size_t index)       { return (*m_pimpl)[index]; }

    std::size_t IndexOf(const T &item) const { return AsConst()->IndexOf(item); }

    void Insert(std::size_t index, const T &item) { m_pimpl->Insert(index, item); }
    void RemoveAt(std::size_t index) { m_pimpl->RemoveAt(index); }

    // Range-for compatibility
          iterator  begin()       { return m_pimpl->begin();  }
    const_iterator  begin() const { return AsConst()->begin(); }
    const_iterator cbegin() const { return AsConst()->cbegin(); }

          iterator  end()       { return m_pimpl->end();  }
    const_iterator  end() const { return AsConst()->end(); }
    const_iterator cend() const { return AsConst()->cend(); }

          reverse_iterator  rbegin()       { return m_pimpl->rbegin();  }
    const_reverse_iterator  rbegin() const { return AsConst()->rbegin(); }
    const_reverse_iterator crbegin() const { return AsConst()->crbegin(); }

          reverse_iterator  rend()       { return m_pimpl->rend();  }
    const_reverse_iterator  rend() const { return AsConst()->rend(); }
    const_reverse_iterator crend() const { return AsConst()->crend(); }
protected:
    std::unique_ptr<Interface> m_pimpl;

    const Interface *AsConst() const
    {
        return m_pimpl.get();
    }
};

// Deduction Guides

template <class ListType>
IList(ListType &input) -> IList<typename ListType::value_type>;

template <class T>
class IListRef : public Private::LegacyBidirectionalIteratorBase<T>
{
public:
    using IteratorBase = Private::LegacyBidirectionalIteratorBase<T>;

    using typename IteratorBase::difference_type;
    using typename IteratorBase::size_type;
    using typename IteratorBase::value_type;
    using typename IteratorBase::pointer;
    using typename IteratorBase::reference;
    using typename IteratorBase::iterator;
    using typename IteratorBase::const_iterator;
    using typename IteratorBase::reverse_iterator;
    using typename IteratorBase::const_reverse_iterator;

private:
    struct Policy
    {
        using value_type         = typename IteratorBase::value_type;
        using size_type          = typename IteratorBase::size_type;
        using IteratorType       = typename IteratorBase::iterator;
        using ConstIteratorType  = typename IteratorBase::const_iterator;
        using ReverseIteratorType       = typename IteratorBase::reverse_iterator;
        using ConstReverseIteratorType  = typename IteratorBase::const_reverse_iterator;
    };

    using Interface = Private::IListInterface<Policy>;

    template <class ListType>
    struct InterfaceModelPtr : Interface
    {
        InterfaceModelPtr() = default;
        InterfaceModelPtr(ListType  *input) : data( input ) { }
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
               bool IsSynchronized() const { return data->IsSynchronized(); }

        void Add(const T &item) override { data->Add(item); }
        bool Remove(const T &item) override { return data->Remove(item); }
        void Clear() override { data->Clear(); }
        bool Contains(const T &item) override { return data->Contains(item); }

        const T &operator [](std::size_t index) const override { return Private::IListIndexer<ListType>::GetAt(data, index); }
              T &operator [](std::size_t index)       override { return Private::IListIndexer<ListType>::GetAt(data, index); }

        std::size_t IndexOf(const T &item) const { return data->IndexOf(item); }

        void Insert(std::size_t index, const T &item) override { data->Insert(index, item); }
        void RemoveAt(std::size_t index) override { data->RemoveAt(index); }

        std::unique_ptr<Interface> Clone() override { return std::make_unique<InterfaceModelPtr<ListType>>(data); }

        std::unique_ptr<Interface> Empty() override { return std::make_unique_for_overwrite<InterfaceModelPtr<ListType>>(); }

        // Range-for compatibility
              iterator  begin()       override { return iterator( std::make_unique<typename IteratorBase::IteratorModel<ListType>>( data->begin() ) ); }
        const_iterator  begin() const override { return const_iterator( std::make_unique<typename IteratorBase::ConstIteratorModel<ListType>>( data->begin() ) ); }
        const_iterator cbegin() const override { return const_iterator( std::make_unique<typename IteratorBase::ConstIteratorModel<ListType>>( data->cbegin() ) ); }

              iterator  end()       override { return iterator( std::make_unique<typename IteratorBase::IteratorModel<ListType>>( data->end() ) ); }
        const_iterator  end() const override { return const_iterator( std::make_unique<typename IteratorBase::ConstIteratorModel<ListType>>( data->end() ) ); }
        const_iterator cend() const override { return const_iterator( std::make_unique<typename IteratorBase::ConstIteratorModel<ListType>>( data->cend() ) ); }

              reverse_iterator  rbegin()       override { return reverse_iterator( std::make_unique<typename IteratorBase::ReverseIteratorModel<ListType>>( data->rbegin() ) ); }
        const_reverse_iterator  rbegin() const override { return const_reverse_iterator( std::make_unique<typename IteratorBase::ConstReverseIteratorModel<ListType>>( data->rbegin() ) ); }
        const_reverse_iterator crbegin() const override { return const_reverse_iterator( std::make_unique<typename IteratorBase::ConstReverseIteratorModel<ListType>>( data->crbegin() ) ); }

              reverse_iterator  rend()       override { return reverse_iterator( std::make_unique<typename IteratorBase::ReverseIteratorModel<ListType>>( data->rend() ) ); }
        const_reverse_iterator  rend() const override { return const_reverse_iterator( std::make_unique<typename IteratorBase::ConstReverseIteratorModel<ListType>>( data->rend() ) ); }
        const_reverse_iterator crend() const override { return const_reverse_iterator( std::make_unique<typename IteratorBase::ConstReverseIteratorModel<ListType>>( data->crend() ) ); }

        ListType *data = nullptr;
    };

public:
    IListRef() = delete;

    template <typename ListType>
    IListRef(ListType *input)
      :
      m_pimpl( std::make_unique<InterfaceModelPtr<ListType>>(input) )
    {
    }

    template <typename ListType>
    IListRef(const ListType *input)
      :
      m_pimpl( std::make_unique<const InterfaceModelPtr<ListType>>(input) )
    {
    }

    template <typename ListType>
    IListRef(ListType &&input) = delete;

    IListRef(const IListRef &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    IListRef(IListRef &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    IListRef(IListRef &&other)
      :
      m_pimpl( other.m_pimpl->Empty() )
    {
        std::swap( m_pimpl, other.m_pimpl );
    }

    IListRef &operator =(const IListRef &other)
    {
        m_pimpl = other.m_pimpl->Clone();
        return *this;
    }

    IListRef &operator =(IListRef &&other) = delete;

    std::size_t Count() const      { return AsConst()->Count(); }
    bool        IsReadOnly() const { return AsConst()->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return AsConst()->IsSynchronized(); }

    void Add(const T &item)      { m_pimpl->Add(item); }
    bool Remove(const T &item)   { return m_pimpl->Remove(item); }
    void Clear()                 { m_pimpl->Clear(); }
    bool Contains(const T &item) { return m_pimpl->Contains(item); }

    const T &operator [](std::size_t index) const { return (*AsConst())[index]; }
          T &operator [](std::size_t index)       { return (*m_pimpl)[index]; }

    std::size_t IndexOf(const T &item) const { return AsConst()->IndexOf(item); }

    void Insert(std::size_t index, const T &item) { m_pimpl->Insert(index, item); }
    void RemoveAt(std::size_t index) { m_pimpl->RemoveAt(index); }

    // Range-for compatibility
          iterator  begin()       { return m_pimpl->begin();  }
    const_iterator  begin() const { return AsConst()->begin(); }
    const_iterator cbegin() const { return AsConst()->cbegin(); }

          iterator  end()       { return m_pimpl->end();  }
    const_iterator  end() const { return AsConst()->end(); }
    const_iterator cend() const { return AsConst()->cend(); }

          reverse_iterator  rbegin()       { return m_pimpl->rbegin();  }
    const_reverse_iterator  rbegin() const { return AsConst()->rbegin(); }
    const_reverse_iterator crbegin() const { return AsConst()->crbegin(); }

          reverse_iterator  rend()       { return m_pimpl->rend();  }
    const_reverse_iterator  rend() const { return AsConst()->rend(); }
    const_reverse_iterator crend() const { return AsConst()->crend(); }
protected:
    std::unique_ptr<Interface> m_pimpl;

    const Interface *AsConst() const
    {
        return m_pimpl.get();
    }
};

}