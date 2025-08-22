#include <memory>
#include <iterator>

namespace System::Collections::Generic::Private
{

template <class T>
struct LegacyBidirectionalIteratorBase
{
    using difference_type   = std::ptrdiff_t;
    using size_type         = std::size_t;
    using value_type        = T;
    using pointer           =       value_type *;
    using reference         =       value_type &;
    using const_pointer     = const value_type *;
    using const_reference   = const value_type &;

    struct IteratorInterface;
    template <class ListType> class IteratorModel;
    
    struct ConstIteratorInterface;
    template <class ListType> class ConstIteratorModel;

    struct ReverseIteratorInterface;
    template <class ListType> class ReverseIteratorModel;

    struct ConstReverseIteratorInterface;
    template <class ListType> class ConstReverseIteratorModel;

    struct ConstIterator;
    struct ConstReverseIterator;

    struct Iterator : std::bidirectional_iterator_tag
    {
        using difference_type   = LegacyBidirectionalIteratorBase::difference_type;
        using value_type        = LegacyBidirectionalIteratorBase::value_type;
        using pointer           = LegacyBidirectionalIteratorBase::pointer;
        using reference         = LegacyBidirectionalIteratorBase::reference;
        using iterator_category = std::bidirectional_iterator_tag;

        Iterator() = default;
       ~Iterator() = default;

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

        Iterator(Iterator &&other)
            :
            m_pimpl( std::move(other.m_pimpl) )
        {
        }

        Iterator &operator =(const Iterator &other)
        {
            m_pimpl = other.m_pimpl->Clone();
            return *this;
        }

        Iterator &operator =(Iterator &&other)
        {
            m_pimpl = std::move(other.m_pimpl);
            return *this;
        }

        T &operator *()  { return *(*m_pimpl); }

        T *operator ->() { return m_pimpl->operator ->(); }

        Iterator &operator ++()
        {
            m_pimpl->operator ++();
            return *this;
        }

        Iterator operator ++(int)
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

        Iterator operator --(int) noexcept
        {
            Iterator old = *this;

            m_pimpl = m_pimpl->post_decrement();
            return old;
        }

        bool operator ==(const Iterator &other)
        {
            return *m_pimpl == *other.m_pimpl;
        }

        bool operator !=(const Iterator &other)
        {
            return *m_pimpl != *other.m_pimpl;
        }

        ConstIterator AsConst() const
        {
            return ConstIterator( m_pimpl->CloneAsConst() );
        }
    protected:
        std::unique_ptr<IteratorInterface> m_pimpl;
    };

    struct ConstIterator : std::bidirectional_iterator_tag
    {
        using difference_type   = LegacyBidirectionalIteratorBase::difference_type;
        using value_type        = LegacyBidirectionalIteratorBase::value_type;
        using pointer           = const LegacyBidirectionalIteratorBase::pointer;
        using reference         = const LegacyBidirectionalIteratorBase::reference;
        using iterator_category = std::bidirectional_iterator_tag;

        ConstIterator() = default;
       ~ConstIterator() = default;

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
            
        ConstIterator(ConstIterator &&other)
            :
            m_pimpl( std::move(other.m_pimpl) )
        {
        }

        ConstIterator &operator =(const ConstIterator &other)
        {
            m_pimpl = other.m_pimpl->Clone();
            return *this;
        }

        ConstIterator &operator =(ConstIterator &&other)
        {
            m_pimpl = std::move(other.m_pimpl);
            return *this;
        }

        const T &operator*() { return *(*m_pimpl); }

        const T *operator->() { return m_pimpl->operator ->(); }

        ConstIterator &operator++()
        {
            m_pimpl->operator ++();
            return *this;
        }

        ConstIterator operator ++(int)
        {
            ConstIterator old = *this;

            m_pimpl = m_pimpl->post_increment();
            return old;
        }

        ConstIterator &operator --() noexcept
        {
            m_pimpl->operator --();
            return *this;
        }

        ConstIterator operator --(int) noexcept
        {
            ConstIterator old = *this;

            m_pimpl = m_pimpl->post_decrement();
            return old;
        }

        bool operator ==(const ConstIterator &other)
        {
            return *m_pimpl == *other.m_pimpl;
        }

        bool operator !=(const ConstIterator &other)
        {
            return *m_pimpl != *other.m_pimpl;
        }
        protected:
            std::unique_ptr<ConstIteratorInterface> m_pimpl;
    };

    struct ReverseIterator : std::bidirectional_iterator_tag
    {
        using difference_type   = LegacyBidirectionalIteratorBase::difference_type;
        using value_type        = LegacyBidirectionalIteratorBase::value_type;
        using pointer           = LegacyBidirectionalIteratorBase::pointer;
        using reference         = LegacyBidirectionalIteratorBase::reference;
        using iterator_category = std::bidirectional_iterator_tag;

        ReverseIterator() = default;
       ~ReverseIterator() = default;

        ReverseIterator(std::unique_ptr<ReverseIteratorInterface> &&position)
            :
            m_pimpl( std::move(position) )
        {
        }

        ReverseIterator(const ReverseIterator &other)
            :
            m_pimpl( other.m_pimpl->Clone() )
        {
        }

        ReverseIterator(ReverseIterator &other)
            :
            m_pimpl( other.m_pimpl->Clone() )
        {
        }

        ReverseIterator(ReverseIterator &&other)
            :
            m_pimpl( std::move(other.m_pimpl) )
        {
        }

        ReverseIterator &operator =(const ReverseIterator &other)
        {
            m_pimpl = other.m_pimpl->Clone();
            return *this;
        }

        ReverseIterator &operator =(ReverseIterator &&other)
        {
            m_pimpl = std::move(other.m_pimpl);
            return *this;
        }

        T &operator *()  { return *(*m_pimpl); }

        T *operator ->() { return m_pimpl->operator ->(); }

        ReverseIterator &operator ++()
        {
            m_pimpl->operator ++();
            return *this;
        }

        ReverseIterator operator ++(int)
        {
            ReverseIterator old = *this;

            m_pimpl = m_pimpl->post_increment();
            return old;
        }

        ReverseIterator &operator --() noexcept
        {
            m_pimpl->operator --();
            return *this;
        }

        ReverseIterator operator --(int) noexcept
        {
            ReverseIterator old = *this;

            m_pimpl = m_pimpl->post_decrement();
            return old;
        }

        bool operator ==(const ReverseIterator &other)
        {
            return *m_pimpl == *other.m_pimpl;
        }

        bool operator !=(const ReverseIterator &other)
        {
            return *m_pimpl != *other.m_pimpl;
        }

        ConstReverseIterator AsConst() const
        {
            return ConstReverseIterator( m_pimpl->CloneAsConst() );
        }
    protected:
        std::unique_ptr<ReverseIteratorInterface> m_pimpl;
    };

    struct ConstReverseIterator : std::bidirectional_iterator_tag
    {
        using difference_type   = LegacyBidirectionalIteratorBase::difference_type;
        using value_type        = LegacyBidirectionalIteratorBase::value_type;
        using pointer           = const LegacyBidirectionalIteratorBase::pointer;
        using reference         = const LegacyBidirectionalIteratorBase::reference;
        using iterator_category = std::bidirectional_iterator_tag;

        ConstReverseIterator() = default;
       ~ConstReverseIterator() = default;

        ConstReverseIterator(std::unique_ptr<ConstReverseIteratorInterface> &&position)
            :
            m_pimpl( std::move(position) )
        {
        }

        ConstReverseIterator(const ConstReverseIterator &other)
          :
          m_pimpl( other.m_pimpl->Clone() )
        {
        }

        ConstReverseIterator(ConstReverseIterator &other)
          :
          m_pimpl( other.m_pimpl->Clone() )
        {
        }

        ConstReverseIterator(const ReverseIterator &other)
            :
            m_pimpl( std::move( other.AsConst().m_pimpl ) )
        {
        }
            
        ConstReverseIterator(ConstReverseIterator &&other)
            :
            m_pimpl( std::move(other.m_pimpl) )
        {
        }

        ConstReverseIterator &operator =(const ConstReverseIterator &other)
        {
            m_pimpl = other.m_pimpl->Clone();
            return *this;
        }

        ConstReverseIterator &operator =(ConstReverseIterator &&other)
        {
            m_pimpl = std::move(other.m_pimpl);
            return *this;
        }

        const T &operator*() { return *(*m_pimpl); }

        const T *operator->() { return m_pimpl->operator ->(); }

        ConstReverseIterator &operator++()
        {
            m_pimpl->operator ++();
            return *this;
        }

        ConstReverseIterator operator ++(int)
        {
            ConstReverseIterator old = *this;

            m_pimpl = m_pimpl->post_increment();
            return old;
        }

        ConstReverseIterator &operator --() noexcept
        {
            m_pimpl->operator --();
            return *this;
        }

        ConstReverseIterator operator --(int) noexcept
        {
            ConstReverseIterator old = *this;

            m_pimpl = m_pimpl->post_decrement();
            return old;
        }

        bool operator ==(const ConstReverseIterator &other)
        {
            return *m_pimpl == *other.m_pimpl;
        }

        bool operator !=(const ConstReverseIterator &other)
        {
            return *m_pimpl != *other.m_pimpl;
        }
        protected:
            std::unique_ptr<ConstReverseIteratorInterface> m_pimpl;
    };

    struct ConstIteratorInterface
    {
        virtual ~ConstIteratorInterface() { }

        virtual const T &operator*() = 0;
        virtual const T *operator->() = 0;
        virtual ConstIteratorInterface &operator++() = 0;
        virtual ConstIteratorInterface &operator--() = 0;

        virtual std::unique_ptr<ConstIteratorInterface> post_increment() = 0;
        virtual std::unique_ptr<ConstIteratorInterface> post_decrement() = 0;

        virtual std::unique_ptr<ConstIteratorInterface> Clone() const = 0;

        virtual bool operator ==(const ConstIteratorInterface &other) const = 0;
        virtual bool operator !=(const ConstIteratorInterface &other) const = 0;
    };

    template <class ListType>
    struct ConstIteratorModel : ConstIteratorInterface
    {
        ConstIteratorModel(typename ListType::const_iterator i)
          :
          m_iterator( i )
        {
        }

        ConstIteratorModel(typename ListType::iterator i)
            :
            m_iterator( i )
        {
        }

        ConstIteratorModel(const ConstIteratorModel<ListType> &other)
            :
            m_iterator( other.m_iterator )
        {
        }

        ConstIteratorModel(ConstIteratorModel<ListType> &&other)
            :
            m_iterator( std::move(other.m_iterator) )
        {
        }

       ~ConstIteratorModel() override { }

        ConstIteratorModel &operator =(const ConstIteratorModel  &other) = default;
        ConstIteratorModel &operator =(      ConstIteratorModel &&other) = default;

        const T &operator*() override
        {
            return *m_iterator;
        }

        const T *operator->() override
        {
            return m_iterator.operator ->();
        }

        ConstIteratorInterface &operator++() override
        {
            ++m_iterator;
            return *this;
        }

        ConstIteratorInterface &operator--() override
        {
            --m_iterator;
            return *this;
        }

        std::unique_ptr<ConstIteratorInterface> post_increment() override
        {
            typename ListType::const_iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<ConstIteratorModel>(old);
        }

        std::unique_ptr<ConstIteratorInterface> post_decrement() override
        {
            typename ListType::const_iterator old = m_iterator;

            m_iterator--;
            return std::make_unique<ConstIteratorModel>(old);
        }

        std::unique_ptr<ConstIteratorInterface> Clone() const override
        {
            return std::make_unique<ConstIteratorModel>(m_iterator);
        }

        bool operator ==(const ConstIteratorInterface &other) const override
        {
            const ConstIteratorModel<ListType> *p = dynamic_cast<const ConstIteratorModel<ListType> *>(&other);

            if ( !p )
                return false;

            return m_iterator == p->m_iterator;
        }

        bool operator !=(const ConstIteratorInterface &other) const override
        {
            const ConstIteratorModel<ListType> *p = dynamic_cast<const ConstIteratorModel<ListType> *>(&other);

            if ( !p )
                return false;

            return m_iterator != p->m_iterator;
        }
    protected:
        ListType::const_iterator m_iterator;
    };

    struct IteratorInterface
    {
        virtual ~IteratorInterface() { }

        virtual T &operator*() = 0;
        virtual T *operator->() = 0;
        virtual IteratorInterface &operator++() = 0;
        virtual IteratorInterface &operator--() = 0;

        virtual std::unique_ptr<IteratorInterface> post_increment() = 0;
        virtual std::unique_ptr<IteratorInterface> post_decrement() = 0;

        virtual std::unique_ptr<IteratorInterface> Clone() = 0;
        virtual std::unique_ptr<ConstIteratorInterface> CloneAsConst() const = 0;

        virtual bool operator ==(const IteratorInterface &other) const = 0;
        virtual bool operator !=(const IteratorInterface &other) const = 0;
    };

    template <class ListType>
    struct IteratorModel : IteratorInterface
    {
        IteratorModel(typename ListType::iterator i)
          :
          m_iterator( i )
        {
        }

       ~IteratorModel() override { }

        IteratorModel &operator =(const IteratorModel &other) = default;
        IteratorModel &operator =(IteratorModel &&other) = default;

        T &operator*() override
        {
            return *m_iterator;
        }

        T *operator->() override
        {
            return m_iterator.operator ->();
        }

        IteratorInterface &operator++() override
        {
            ++m_iterator;
            return *this;
        }

        IteratorInterface &operator--() override
        {
            --m_iterator;
            return *this;
        }

        std::unique_ptr<IteratorInterface> post_increment() override
        {
            typename ListType::iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<IteratorModel<ListType>>(old);
        }

        std::unique_ptr<IteratorInterface> post_decrement() override
        {
            typename ListType::iterator old = m_iterator;

            m_iterator--;
            return std::make_unique<IteratorModel<ListType>>(old);
        }

        std::unique_ptr<IteratorInterface> Clone() override
        {
            return std::make_unique<IteratorModel<ListType>>(m_iterator);
        }

        std::unique_ptr<ConstIteratorInterface> CloneAsConst() const override
        {
            return std::make_unique<ConstIteratorModel<ListType>>(m_iterator);
        }

        bool operator ==(const IteratorInterface &other) const override
        {
            const IteratorModel<ListType> *p = dynamic_cast<const IteratorModel<ListType> *>(&other);

            if ( !p )
                return false;

            return m_iterator == p->m_iterator;
        }

        bool operator !=(const IteratorInterface &other) const override
        {
            const IteratorModel<ListType> *p = dynamic_cast<const IteratorModel<ListType> *>(&other);

            if ( !p )
                return true;

            return m_iterator != p->m_iterator;
        }
    protected:
        ListType::iterator m_iterator;
    };

    struct ConstReverseIteratorInterface
    {
        virtual ~ConstReverseIteratorInterface() { }

        virtual const T &operator*() = 0;
        virtual const T *operator->() = 0;
        virtual ConstReverseIteratorInterface &operator++() = 0;
        virtual ConstReverseIteratorInterface &operator--() = 0;

        virtual std::unique_ptr<ConstReverseIteratorInterface> post_increment() = 0;
        virtual std::unique_ptr<ConstReverseIteratorInterface> post_decrement() = 0;

        virtual std::unique_ptr<ConstReverseIteratorInterface> Clone() const = 0;

        virtual bool operator ==(const ConstReverseIteratorInterface &other) const = 0;
        virtual bool operator !=(const ConstReverseIteratorInterface &other) const = 0;
    };

    template <class ListType>
    struct ConstReverseIteratorModel : ConstReverseIteratorInterface
    {
        ConstReverseIteratorModel(typename ListType::const_reverse_iterator i)
          :
          m_iterator( i )
        {
        }

        ConstReverseIteratorModel(const ConstReverseIteratorModel<ListType> &other)
            :
            m_iterator( other.m_iterator )
        {
        }

        ConstReverseIteratorModel(ConstReverseIteratorModel<ListType> &&other)
            :
            m_iterator( std::move(other.m_iterator) )
        {
        }

       ~ConstReverseIteratorModel() override { }

        ConstReverseIteratorModel &operator =(const ConstReverseIteratorModel  &other) = default;
        ConstReverseIteratorModel &operator =(      ConstReverseIteratorModel &&other) = default;

        const T &operator*() override
        {
            return *m_iterator;
        }

        const T *operator->() override
        {
            return m_iterator.operator ->();
        }

        ConstReverseIteratorInterface &operator++() override
        {
            ++m_iterator;
            return *this;
        }

        ConstReverseIteratorInterface &operator--() override
        {
            --m_iterator;
            return *this;
        }

        std::unique_ptr<ConstReverseIteratorInterface> post_increment() override
        {
            typename ListType::const_reverse_iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<ConstReverseIteratorModel>(old);
        }

        std::unique_ptr<ConstReverseIteratorInterface> post_decrement() override
        {
            typename ListType::const_reverse_iterator old = m_iterator;

            m_iterator--;
            return std::make_unique<ConstReverseIteratorModel>(old);
        }

        std::unique_ptr<ConstReverseIteratorInterface> Clone() const override
        {
            return std::make_unique<ConstReverseIteratorModel>(m_iterator);
        }

        bool operator ==(const ConstReverseIteratorInterface &other) const override
        {
            const ConstReverseIteratorModel<ListType> *p = dynamic_cast<const ConstReverseIteratorModel<ListType> *>(&other);

            if ( !p )
                return false;

            return m_iterator == p->m_iterator;
        }

        bool operator !=(const ConstReverseIteratorInterface &other) const override
        {
            const ConstReverseIteratorModel<ListType> *p = dynamic_cast<const ConstReverseIteratorModel<ListType> *>(&other);

            if ( !p )
                return false;

            return m_iterator != p->m_iterator;
        }
    protected:
        ListType::const_reverse_iterator m_iterator;
    };

    struct ReverseIteratorInterface
    {
        virtual ~ReverseIteratorInterface() { }

        virtual T &operator*() = 0;
        virtual T *operator->() = 0;
        virtual ReverseIteratorInterface &operator++() = 0;
        virtual ReverseIteratorInterface &operator--() = 0;

        virtual std::unique_ptr<ReverseIteratorInterface> post_increment() = 0;
        virtual std::unique_ptr<ReverseIteratorInterface> post_decrement() = 0;

        virtual std::unique_ptr<ReverseIteratorInterface> Clone() = 0;
        virtual std::unique_ptr<ConstReverseIteratorInterface> CloneAsConst() const = 0;

        virtual bool operator ==(const ReverseIteratorInterface &other) const = 0;
        virtual bool operator !=(const ReverseIteratorInterface &other) const = 0;
    };

    template <class ListType>
    struct ReverseIteratorModel : ReverseIteratorInterface
    {
        ReverseIteratorModel(typename ListType::reverse_iterator i)
          :
          m_iterator( i )
        {
        }

       ~ReverseIteratorModel() override { }

        ReverseIteratorModel &operator =(const ReverseIteratorModel &other) = default;
        ReverseIteratorModel &operator =(ReverseIteratorModel &&other) = default;

        T &operator*() override
        {
            return *m_iterator;
        }

        T *operator->() override
        {
            return m_iterator.operator ->();
        }

        ReverseIteratorInterface &operator++() override
        {
            ++m_iterator;
            return *this;
        }

        ReverseIteratorInterface &operator--() override
        {
            --m_iterator;
            return *this;
        }

        std::unique_ptr<ReverseIteratorInterface> post_increment() override
        {
            typename ListType::reverse_iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<ReverseIteratorModel<ListType>>(old);
        }

        std::unique_ptr<ReverseIteratorInterface> post_decrement() override
        {
            typename ListType::reverse_iterator old = m_iterator;

            m_iterator--;
            return std::make_unique<ReverseIteratorModel<ListType>>(old);
        }

        std::unique_ptr<ReverseIteratorInterface> Clone() override
        {
            return std::make_unique<ReverseIteratorModel<ListType>>(m_iterator);
        }

        std::unique_ptr<ConstReverseIteratorInterface> CloneAsConst() const override
        {
            return std::make_unique<ConstReverseIteratorModel<ListType>>( typename ListType::const_reverse_iterator(m_iterator) );
        }

        bool operator ==(const ReverseIteratorInterface &other) const override
        {
            const ReverseIteratorModel<ListType> *p = dynamic_cast<const ReverseIteratorModel<ListType> *>(&other);

            if ( !p )
                return false;

            return m_iterator == p->m_iterator;
        }

        bool operator !=(const ReverseIteratorInterface &other) const override
        {
            const ReverseIteratorModel<ListType> *p = dynamic_cast<const ReverseIteratorModel<ListType> *>(&other);

            if ( !p )
                return true;

            return m_iterator != p->m_iterator;
        }
    protected:
        typename ListType::reverse_iterator m_iterator;
    };

    using iterator       = Iterator;
    using const_iterator = ConstIterator;
    using reverse_iterator       = ReverseIterator;
    using const_reverse_iterator = ConstReverseIterator;
};

}