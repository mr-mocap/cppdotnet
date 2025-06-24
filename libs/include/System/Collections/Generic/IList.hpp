#pragma once

#include <memory>
#include <iterator>


namespace System::Collections::Generic
{

template <class T>
class IList
{
    struct IteratorInterface;
    template <typename ModelT> class IteratorModel;
    
    struct ConstIteratorInterface;
    template <typename ModelT> class ConstIteratorModel;

public:
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type &;
    using const_reference = const value_type &;
    
    struct Iterator
    {
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T *;
        using reference         = T &;
        using iterator_category = std::random_access_iterator_tag;

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

        Iterator &operator --() noexcept
        {
            m_pimpl->operator --();
            return *this;
        }

        Iterator operator --(int dummy_value) noexcept
        {
            Iterator old = *this;

            m_pimpl = m_pimpl->post_decrement();
            return old;
        }

        Iterator operator +(difference_type n) const
        {
            return Iterator( m_pimpl->create_positive_offset(n) );
        }

        Iterator operator -(difference_type n) const
        {
            return Iterator( m_pimpl->create_negative_offset(n) );
        }

        Iterator &operator +=(difference_type n)
        {
            *m_pimpl += n;
            return *this;
        }

        Iterator &operator -=(difference_type n)
        {
            *m_pimpl -= n;
            return *this;
        }

        T &operator [](size_type index)
        {
            return (*m_pimpl)[index];
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
        using value_type        = T;
        using pointer           = const T *;
        using reference         = const T &;
        using iterator_category = std::random_access_iterator_tag;

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

        ConstIterator &operator--() noexcept
        {
            m_pimpl->operator --();
            return *this;
        }

        ConstIterator operator --(int dummy_value) noexcept
        {
            ConstIterator old = *this;

            m_pimpl = m_pimpl->post_decrement();
            return old;
        }

        ConstIterator operator +(difference_type n)
        {
            return ConstIterator( m_pimpl->create_positive_offset(n) );
        }

        ConstIterator operator -(difference_type n)
        {
            return ConstIterator( m_pimpl->create_negative_offset(n) );
        }

        ConstIterator &operator +=(difference_type n)
        {
            *m_pimpl += n;
            return *this;
        }

        ConstIterator &operator -=(difference_type n)
        {
            *m_pimpl -= n;
            return *this;
        }

        const T &operator [](size_type index)
        {
            return (*m_pimpl)[index];
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

        virtual T &operator*() noexcept = 0;

        virtual T *operator->() noexcept = 0;

        virtual IteratorInterface &operator++()     noexcept = 0;
        virtual IteratorInterface &operator--()     noexcept = 0;
        virtual std::unique_ptr<IteratorInterface> post_increment() noexcept = 0;
        virtual std::unique_ptr<IteratorInterface> post_decrement() noexcept = 0;
        virtual std::unique_ptr<IteratorInterface> create_positive_offset(difference_type n) = 0;
        virtual std::unique_ptr<IteratorInterface> create_negative_offset(difference_type n) = 0;
        virtual IteratorInterface &operator +=(difference_type n) = 0;
        virtual IteratorInterface &operator -=(difference_type n) = 0;
        virtual T &operator [](size_type index) = 0;

        friend bool operator ==(const IteratorInterface &left, const IteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }

        virtual std::unique_ptr<IteratorInterface> Clone() const = 0;

        virtual bool EqualTo(const IteratorInterface &other) const = 0;
    };

    template <typename ListType>
    struct IteratorModel : IteratorInterface
    {
        IteratorModel(ListType::iterator i)
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

        IteratorInterface &operator--() noexcept override
        {
            --m_iterator;
            return *this;
        }

        std::unique_ptr<IteratorInterface> post_increment() noexcept override
        {
            typename ListType::iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<IteratorModel>(old);
        }

        std::unique_ptr<IteratorInterface> post_decrement() noexcept override
        {
            typename ListType::iterator old = m_iterator;

            m_iterator--;
            return std::make_unique<IteratorModel>(old);
        }

        std::unique_ptr<IteratorInterface> create_positive_offset(difference_type n) override
        {
            return std::make_unique<IteratorModel>( m_iterator + n );
        }

        std::unique_ptr<IteratorInterface> create_negative_offset(difference_type n) override
        {
            return std::make_unique<IteratorModel>( m_iterator - n );
        }

        IteratorInterface &operator +=(difference_type n) override
        {
            m_iterator += n;
            return *this;
        }

        IteratorInterface &operator -=(difference_type n) override
        {
            m_iterator -= n;
            return *this;
        }

        T &operator [](size_type index) override
        {
            return m_iterator[index];;
        }

        std::unique_ptr<IteratorInterface> Clone() const override
        {
            return std::make_unique<IteratorModel>(m_iterator);
        }

        bool EqualTo(const IteratorInterface &other) const override
        {
            const IteratorModel<ListType> *p = dynamic_cast<const IteratorModel<ListType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            ListType::iterator m_iterator;
    };

    struct ConstIteratorInterface
    {
        virtual ~ConstIteratorInterface() { }

        virtual const T &operator*() noexcept = 0;

        virtual const T *operator->() noexcept = 0;

        virtual ConstIteratorInterface &operator++()    noexcept = 0;
        virtual ConstIteratorInterface &operator--()    noexcept = 0;
        virtual std::unique_ptr<ConstIteratorInterface> post_increment() noexcept = 0;
        virtual std::unique_ptr<ConstIteratorInterface> post_decrement() noexcept = 0;
        virtual std::unique_ptr<ConstIteratorInterface> create_positive_offset(difference_type n) = 0;
        virtual std::unique_ptr<ConstIteratorInterface> create_negative_offset(difference_type n) = 0;
        virtual ConstIteratorInterface &operator +=(difference_type n) = 0;
        virtual ConstIteratorInterface &operator -=(difference_type n) = 0;
        virtual const T &operator [](size_type index) = 0;

        friend bool operator ==(const ConstIteratorInterface &left, const ConstIteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }

        virtual std::unique_ptr<ConstIteratorInterface> Clone() const = 0;

        virtual bool EqualTo(const ConstIteratorInterface &other) const = 0;
    };

    template <typename ListType>
    struct ConstIteratorModel : ConstIteratorInterface
    {
        ConstIteratorModel(ListType::const_iterator i)
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

        ConstIteratorInterface &operator--() noexcept override
        {
            --m_iterator;
            return *this;
        }

        std::unique_ptr<ConstIteratorInterface> post_increment() noexcept override
        {
            typename ListType::const_iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<ConstIteratorModel>(old);
        }

        std::unique_ptr<ConstIteratorInterface> post_decrement() noexcept override
        {
            typename ListType::const_iterator old = m_iterator;

            m_iterator--;
            return std::make_unique<ConstIteratorModel>(old);
        }

        std::unique_ptr<ConstIteratorInterface> create_positive_offset(difference_type n) override
        {
            return std::make_unique<ConstIteratorModel>( m_iterator + n );
        }

        std::unique_ptr<ConstIteratorInterface> create_negative_offset(difference_type n) override
        {
            return std::make_unique<ConstIteratorModel>( m_iterator - n );
        }


        ConstIteratorInterface &operator +=(difference_type n) override
        {
            m_iterator += n;
            return *this;
        }

        ConstIteratorInterface &operator -=(difference_type n) override
        {
            m_iterator -= n;
            return *this;
        }

        const T &operator [](size_type index) override
        {
            return m_iterator[index];
        }

        std::unique_ptr<ConstIteratorInterface> Clone() const override
        {
            return std::make_unique<ConstIteratorModel>(m_iterator);
        }

        bool EqualTo(const ConstIteratorInterface &other) const override
        {
            const ConstIteratorModel<ListType> *p = dynamic_cast<const ConstIteratorModel<ListType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            ListType::const_iterator m_iterator;
    };

    struct Interface
    {
        virtual ~Interface() { }

        virtual size_type Count() const = 0;
        virtual bool      IsReadOnly() const = 0;
        virtual bool      IsReadOnly()       = 0;
        virtual bool      IsSynchronized() const = 0;

        virtual void Add(const T &item) = 0;
        virtual bool Remove(const T &item) = 0;
        virtual void Clear() = 0;
        virtual bool Contains(const T &item) = 0;

        // TODO: Add CopyTo() ?

        virtual const_reference operator [](size_type index) const = 0;
        virtual reference       operator [](size_type index)       = 0;

        virtual size_type IndexOf(const_reference item) const = 0;

        virtual void Insert(size_type index, const_reference item) = 0;
        virtual void RemoveAt(size_type index) = 0;

        virtual std::unique_ptr<Interface> Clone() = 0;
        virtual std::unique_ptr<Interface> Empty() = 0;

        // Range-for compatibility
        virtual      Iterator  begin()       = 0;
        virtual ConstIterator  begin() const = 0;
        virtual ConstIterator cbegin() const = 0;

        virtual      Iterator  end()       = 0;
        virtual ConstIterator  end() const = 0;
        virtual ConstIterator cend() const = 0;

        virtual      std::reverse_iterator<Iterator>  rbegin()       = 0;
        virtual std::reverse_iterator<ConstIterator>  rbegin() const = 0;
        virtual std::reverse_iterator<ConstIterator> crbegin() const = 0;

        virtual      std::reverse_iterator<Iterator>  rend()       = 0;
        virtual std::reverse_iterator<ConstIterator>  rend() const = 0;
        virtual std::reverse_iterator<ConstIterator> crend() const = 0;
    };

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

        void Add(const T &item) override { data.Add(item); }
        bool Remove(const T &item) override { return data.Remove(item); }
        void Clear() override { data.Clear(); }
        bool Contains(const T &item) override { return data.Contains(item); }

        const_reference operator [](size_type index) const override { return data[index]; }
        reference       operator [](size_type index)       override { return data[index]; }

        size_type IndexOf(const_reference item) const { return data.IndexOf(item); }

        void Insert(size_type index, const_reference item) override { data.Insert(index, item); }
        void RemoveAt(size_type index) override { data.RemoveAt(index); }

        std::unique_ptr<Interface> Clone() override { return std::make_unique<InterfaceModel>(data); }

        std::unique_ptr<Interface> Empty() override { return std::make_unique_for_overwrite<InterfaceModel>(); }

        // Range-for compatibility
             Iterator  begin()       override { return Iterator( std::make_unique<IteratorModel<ListType>>(data.begin()) ); }
        ConstIterator  begin() const override { return ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data.begin()) ); }
        ConstIterator cbegin() const override { return ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data.cbegin()) ); }

             Iterator  end()       override { return Iterator( std::make_unique<IteratorModel<ListType>>(data.end()) ); }
        ConstIterator  end() const override { return ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data.end()) ); }
        ConstIterator cend() const override { return ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data.cend()) ); }

             std::reverse_iterator<Iterator>  rbegin()       { return std::make_reverse_iterator( Iterator( std::make_unique<IteratorModel<ListType>>(data.begin()) ) ); }
        std::reverse_iterator<ConstIterator>  rbegin() const { return std::make_reverse_iterator( ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data.begin()) ) ); }
        std::reverse_iterator<ConstIterator> crbegin() const noexcept { return std::make_reverse_iterator( ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data.cbegin()) ) ); }

             std::reverse_iterator<Iterator>  rend()       { return std::make_reverse_iterator( Iterator( std::make_unique<IteratorModel<ListType>>(data.end()) ) ); }
        std::reverse_iterator<ConstIterator>  rend() const { return std::make_reverse_iterator( ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data.end()) ) ); }
        std::reverse_iterator<ConstIterator> crend() const noexcept { return std::make_reverse_iterator( ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data.cend()) ) ); }

        ListType data;
    };

public:
    using iterator        = Iterator;
    using const_iterator  = ConstIterator;
    using reverse_iterator       = std::reverse_iterator<Iterator>;
    using const_reverse_iterator = std::reverse_iterator<ConstIterator>;

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

    std::size_t Count() const      { return m_pimpl->Count(); }
    bool        IsReadOnly() const { return const_cast<const Interface *>(m_pimpl.get())->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return m_pimpl->IsSynchronized(); }

    void Add(const T &item)      { m_pimpl->Add(item); }
    bool Remove(const T &item)   { return m_pimpl->Remove(item); }
    void Clear()                 { m_pimpl->Clear(); }
    bool Contains(const T &item) { return m_pimpl->Contains(item); }

    const_reference operator [](size_type index) const { return (* const_cast<const Interface *>(m_pimpl.get()))[index]; }
    reference       operator [](size_type index)       { return (*m_pimpl)[index]; }

    size_type IndexOf(const_reference item) const { return m_pimpl->IndexOf(item); }

    void Insert(size_type index, const_reference item) { m_pimpl->Insert(index, item); }
    void RemoveAt(size_type index) { m_pimpl->RemoveAt(index); }

    // Range-for compatibility
          iterator  begin()       { return m_pimpl->begin(); }
    const_iterator  begin() const { return const_cast<const Interface *>(m_pimpl.get())->begin(); } // We have to make the underlying object const here
    const_iterator cbegin() const { return m_pimpl->cbegin(); }

          iterator  end()       { return m_pimpl->end(); }
    const_iterator  end() const { return const_cast<const Interface *>(m_pimpl.get())->end(); } // We have to make the underlying object const here
    const_iterator cend() const { return m_pimpl->cend(); }

          reverse_iterator  rbegin()       { return m_pimpl->rbegin(); }
    const_reverse_iterator  rbegin() const { return const_cast<const Interface *>(m_pimpl.get())->rbegin(); } // We have to make the underlying object const here
    const_reverse_iterator crbegin() const { return m_pimpl->crbegin(); }

          reverse_iterator  rend()       { return m_pimpl->rend(); }
    const_reverse_iterator  rend() const { return const_cast<const Interface *>(m_pimpl.get())->rend(); } // We have to make the underlying object const here
    const_reverse_iterator crend() const { return m_pimpl->crend(); }
protected:
    std::unique_ptr<Interface> m_pimpl;
};

template <class T>
class IListRef
{
    struct IteratorInterface;
    template <typename ModelT> class IteratorModel;
    
    struct ConstIteratorInterface;
    template <typename ModelT> class ConstIteratorModel;

public:
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference       = value_type &;
    using const_reference = const value_type &;
    
    struct Iterator
    {
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T *;
        using reference         = T &;
        using iterator_category = std::random_access_iterator_tag;

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

        Iterator &operator --() noexcept
        {
            m_pimpl->operator --();
            return *this;
        }

        Iterator operator --(int dummy_value) noexcept
        {
            Iterator old = *this;

            m_pimpl = m_pimpl->post_decrement();
            return old;
        }

        Iterator operator +(difference_type n) const
        {
            return Iterator( m_pimpl->create_positive_offset(n) );
        }

        Iterator operator -(difference_type n) const
        {
            return Iterator( m_pimpl->create_negative_offset(n) );
        }

        Iterator &operator +=(difference_type n)
        {
            *m_pimpl += n;
            return *this;
        }

        Iterator &operator -=(difference_type n)
        {
            *m_pimpl -= n;
            return *this;
        }

        T &operator [](size_type index)
        {
            return (*m_pimpl)[index];
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
        using value_type        = T;
        using pointer           = const T *;
        using reference         = const T &;
        using iterator_category = std::random_access_iterator_tag;

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

        ConstIterator &operator--() noexcept
        {
            m_pimpl->operator --();
            return *this;
        }

        ConstIterator operator --(int dummy_value) noexcept
        {
            ConstIterator old = *this;

            m_pimpl = m_pimpl->post_decrement();
            return old;
        }

        ConstIterator operator +(difference_type n)
        {
            return ConstIterator( m_pimpl->create_positive_offset(n) );
        }

        ConstIterator operator -(difference_type n)
        {
            return ConstIterator( m_pimpl->create_negative_offset(n) );
        }

        ConstIterator &operator +=(difference_type n)
        {
            *m_pimpl += n;
            return *this;
        }

        ConstIterator &operator -=(difference_type n)
        {
            *m_pimpl -= n;
            return *this;
        }

        const T &operator [](size_type index)
        {
            return (*m_pimpl)[index];
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

        virtual T &operator*() noexcept = 0;

        virtual T *operator->() noexcept = 0;

        virtual IteratorInterface &operator++()     noexcept = 0;
        virtual IteratorInterface &operator--()     noexcept = 0;
        virtual std::unique_ptr<IteratorInterface> post_increment() noexcept = 0;
        virtual std::unique_ptr<IteratorInterface> post_decrement() noexcept = 0;
        virtual std::unique_ptr<IteratorInterface> create_positive_offset(difference_type n) = 0;
        virtual std::unique_ptr<IteratorInterface> create_negative_offset(difference_type n) = 0;
        virtual IteratorInterface &operator +=(difference_type n) = 0;
        virtual IteratorInterface &operator -=(difference_type n) = 0;
        virtual T &operator [](size_type index) = 0;

        friend bool operator ==(const IteratorInterface &left, const IteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }

        virtual std::unique_ptr<IteratorInterface> Clone() const = 0;

        virtual bool EqualTo(const IteratorInterface &other) const = 0;
    };

    template <typename ListType>
    struct IteratorModel : IteratorInterface
    {
        IteratorModel(ListType::iterator i)
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

        IteratorInterface &operator--() noexcept override
        {
            --m_iterator;
            return *this;
        }

        std::unique_ptr<IteratorInterface> post_increment() noexcept override
        {
            typename ListType::iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<IteratorModel>(old);
        }

        std::unique_ptr<IteratorInterface> post_decrement() noexcept override
        {
            typename ListType::iterator old = m_iterator;

            m_iterator--;
            return std::make_unique<IteratorModel>(old);
        }

        std::unique_ptr<IteratorInterface> create_positive_offset(difference_type n) override
        {
            return std::make_unique<IteratorModel>( m_iterator + n );
        }

        std::unique_ptr<IteratorInterface> create_negative_offset(difference_type n) override
        {
            return std::make_unique<IteratorModel>( m_iterator - n );
        }

        IteratorInterface &operator +=(difference_type n) override
        {
            m_iterator += n;
            return *this;
        }

        IteratorInterface &operator -=(difference_type n) override
        {
            m_iterator -= n;
            return *this;
        }

        T &operator [](size_type index) override
        {
            return m_iterator[index];;
        }

        std::unique_ptr<IteratorInterface> Clone() const override
        {
            return std::make_unique<IteratorModel>(m_iterator);
        }

        bool EqualTo(const IteratorInterface &other) const override
        {
            const IteratorModel<ListType> *p = dynamic_cast<const IteratorModel<ListType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            ListType::iterator m_iterator;
    };

    struct ConstIteratorInterface
    {
        virtual ~ConstIteratorInterface() { }

        virtual const T &operator*() noexcept = 0;

        virtual const T *operator->() noexcept = 0;

        virtual ConstIteratorInterface &operator++()    noexcept = 0;
        virtual ConstIteratorInterface &operator--()    noexcept = 0;
        virtual std::unique_ptr<ConstIteratorInterface> post_increment() noexcept = 0;
        virtual std::unique_ptr<ConstIteratorInterface> post_decrement() noexcept = 0;
        virtual std::unique_ptr<ConstIteratorInterface> create_positive_offset(difference_type n) = 0;
        virtual std::unique_ptr<ConstIteratorInterface> create_negative_offset(difference_type n) = 0;
        virtual ConstIteratorInterface &operator +=(difference_type n) = 0;
        virtual ConstIteratorInterface &operator -=(difference_type n) = 0;
        virtual const T &operator [](size_type index) = 0;

        friend bool operator ==(const ConstIteratorInterface &left, const ConstIteratorInterface &right) noexcept
        {
            return left.EqualTo(right);
        }

        virtual std::unique_ptr<ConstIteratorInterface> Clone() const = 0;

        virtual bool EqualTo(const ConstIteratorInterface &other) const = 0;
    };

    template <typename ListType>
    struct ConstIteratorModel : ConstIteratorInterface
    {
        ConstIteratorModel(ListType::const_iterator i)
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

        ConstIteratorInterface &operator--() noexcept override
        {
            --m_iterator;
            return *this;
        }

        std::unique_ptr<ConstIteratorInterface> post_increment() noexcept override
        {
            typename ListType::const_iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<ConstIteratorModel>(old);
        }

        std::unique_ptr<ConstIteratorInterface> post_decrement() noexcept override
        {
            typename ListType::const_iterator old = m_iterator;

            m_iterator--;
            return std::make_unique<ConstIteratorModel>(old);
        }

        std::unique_ptr<ConstIteratorInterface> create_positive_offset(difference_type n) override
        {
            return std::make_unique<ConstIteratorModel>( m_iterator + n );
        }

        std::unique_ptr<ConstIteratorInterface> create_negative_offset(difference_type n) override
        {
            return std::make_unique<ConstIteratorModel>( m_iterator - n );
        }


        ConstIteratorInterface &operator +=(difference_type n) override
        {
            m_iterator += n;
            return *this;
        }

        ConstIteratorInterface &operator -=(difference_type n) override
        {
            m_iterator -= n;
            return *this;
        }

        const T &operator [](size_type index) override
        {
            return m_iterator[index];
        }

        std::unique_ptr<ConstIteratorInterface> Clone() const override
        {
            return std::make_unique<ConstIteratorModel>(m_iterator);
        }

        bool EqualTo(const ConstIteratorInterface &other) const override
        {
            const ConstIteratorModel<ListType> *p = dynamic_cast<const ConstIteratorModel<ListType> *>(&other);

            if ( !p )
                return false;
            return m_iterator == p->m_iterator;
        }
        protected:
            ListType::const_iterator m_iterator;
    };

    struct Interface
    {
        virtual ~Interface() { }

        virtual size_type Count() const = 0;
        virtual bool      IsReadOnly() const = 0;
        virtual bool      IsReadOnly()       = 0;
        virtual bool      IsSynchronized() const = 0;

        virtual void Add(const T &item) = 0;
        virtual bool Remove(const T &item) = 0;
        virtual void Clear() = 0;
        virtual bool Contains(const T &item) = 0;

        // TODO: Add CopyTo() ?

        virtual const_reference operator [](size_type index) const = 0;
        virtual reference       operator [](size_type index)       = 0;

        virtual size_type IndexOf(const_reference item) const = 0;

        virtual void Insert(size_type index, const_reference item) = 0;
        virtual void RemoveAt(size_type index) = 0;

        virtual std::unique_ptr<Interface> Clone() = 0;

        // Range-for compatibility
        virtual      Iterator  begin()       = 0;
        virtual ConstIterator  begin() const = 0;
        virtual ConstIterator cbegin() const = 0;

        virtual      Iterator  end()       = 0;
        virtual ConstIterator  end() const = 0;
        virtual ConstIterator cend() const = 0;

        virtual      std::reverse_iterator<Iterator>  rbegin()       = 0;
        virtual std::reverse_iterator<ConstIterator>  rbegin() const = 0;
        virtual std::reverse_iterator<ConstIterator> crbegin() const = 0;

        virtual      std::reverse_iterator<Iterator>  rend()       = 0;
        virtual std::reverse_iterator<ConstIterator>  rend() const = 0;
        virtual std::reverse_iterator<ConstIterator> crend() const = 0;
    };

    template <class ListType>
    struct InterfaceModelPtr : Interface
    {
        InterfaceModelPtr() = delete;
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

        const_reference operator [](size_type index) const override { return (*data)[index]; }
        reference       operator [](size_type index)       override { return (*data)[index]; }

        size_type IndexOf(const_reference item) const { return data->IndexOf(item); }

        void Insert(size_type index, const_reference item) override { data->Insert(index, item); }
        void RemoveAt(size_type index) override { data->RemoveAt(index); }

        std::unique_ptr<Interface> Clone() override { return std::make_unique<InterfaceModelPtr>(data); }

        // Range-for compatibility
             Iterator  begin()       override { return Iterator( std::make_unique<IteratorModel<ListType>>(data->begin()) ); }
        ConstIterator  begin() const override { return ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data->begin()) ); }
        ConstIterator cbegin() const override { return ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data->cbegin()) ); }

             Iterator  end()       override { return Iterator( std::make_unique<IteratorModel<ListType>>(data->end()) ); }
        ConstIterator  end() const override { return ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data->end()) ); }
        ConstIterator cend() const override { return ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data->cend()) ); }

             std::reverse_iterator<Iterator>  rbegin()       { return std::make_reverse_iterator( Iterator( std::make_unique<IteratorModel<ListType>>(data->begin()) ) ); }
        std::reverse_iterator<ConstIterator>  rbegin() const { return std::make_reverse_iterator( ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data->begin()) ) ); }
        std::reverse_iterator<ConstIterator> crbegin() const noexcept { return std::make_reverse_iterator( ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data->cbegin()) ) ); }

             std::reverse_iterator<Iterator>  rend()       { return std::make_reverse_iterator( Iterator( std::make_unique<IteratorModel<ListType>>(data->end()) ) ); }
        std::reverse_iterator<ConstIterator>  rend() const { return std::make_reverse_iterator( ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data->end()) ) ); }
        std::reverse_iterator<ConstIterator> crend() const noexcept { return std::make_reverse_iterator( ConstIterator( std::make_unique<ConstIteratorModel<ListType>>(data->cend()) ) ); }

        ListType *data = nullptr;
    };

public:
    using iterator        = Iterator;
    using const_iterator  = ConstIterator;
    using reverse_iterator       = std::reverse_iterator<Iterator>;
    using const_reverse_iterator = std::reverse_iterator<ConstIterator>;

    IListRef() = delete;

    template <typename ListType>
    IListRef(const ListType *input)
      :
      m_pimpl( std::make_unique<const InterfaceModelPtr<ListType>>(input) )
    {
    }

    template <typename ListType>
    IListRef(ListType *input)
      :
      m_pimpl( std::make_unique<InterfaceModelPtr<ListType>>(input) )
    {
    }

    IListRef(const IListRef &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }

    IListRef(IListRef &&other) = delete;

    IListRef &operator =(const IListRef &other)
    {
        m_pimpl = other.m_pimpl->Clone();
        return *this;
    }

    IListRef &operator =(IListRef &&other) = delete;

    std::size_t Count() const      { return m_pimpl->Count(); }
    bool        IsReadOnly() const { return const_cast<const Interface *>(m_pimpl.get())->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return m_pimpl->IsSynchronized(); }

    void Add(const T &item)      { m_pimpl->Add(item); }
    bool Remove(const T &item)   { return m_pimpl->Remove(item); }
    void Clear()                 { m_pimpl->Clear(); }
    bool Contains(const T &item) { return m_pimpl->Contains(item); }

    const_reference operator [](size_type index) const { return (* const_cast<const Interface *>(m_pimpl.get()))[index]; }
    reference       operator [](size_type index)       { return (*m_pimpl)[index]; }

    size_type IndexOf(const_reference item) const { return m_pimpl->IndexOf(item); }

    void Insert(size_type index, const_reference item) { m_pimpl->Insert(index, item); }
    void RemoveAt(size_type index) { m_pimpl->RemoveAt(index); }

    // Range-for compatibility
          iterator  begin()       { return m_pimpl->begin(); }
    const_iterator  begin() const { return const_cast<const Interface *>(m_pimpl.get())->begin(); } // We have to make the underlying object const here
    const_iterator cbegin() const { return m_pimpl->cbegin(); }

          iterator  end()       { return m_pimpl->end(); }
    const_iterator  end() const { return const_cast<const Interface *>(m_pimpl.get())->end(); } // We have to make the underlying object const here
    const_iterator cend() const { return m_pimpl->cend(); }

          reverse_iterator  rbegin()       { return m_pimpl->rbegin(); }
    const_reverse_iterator  rbegin() const { return const_cast<const Interface *>(m_pimpl.get())->rbegin(); } // We have to make the underlying object const here
    const_reverse_iterator crbegin() const { return m_pimpl->crbegin(); }

          reverse_iterator  rend()       { return m_pimpl->rend(); }
    const_reverse_iterator  rend() const { return const_cast<const Interface *>(m_pimpl.get())->rend(); } // We have to make the underlying object const here
    const_reverse_iterator crend() const { return m_pimpl->crend(); }
protected:
    std::unique_ptr<Interface> m_pimpl;
};

}