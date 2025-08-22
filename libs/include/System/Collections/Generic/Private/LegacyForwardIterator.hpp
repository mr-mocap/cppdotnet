#include <memory>
#include <iterator>

namespace System::Collections::Generic::Private
{

template <class T>
struct LegacyForwardIteratorBase
{
    using value_type        = T;
    using size_type         = std::size_t;
    using difference_type   = std::ptrdiff_t;
    using pointer           =       value_type *;
    using reference         =       value_type &;
    using const_pointer     = const value_type *;
    using const_reference   = const value_type &;

    struct IteratorInterface;
    template <class CollectionType> class IteratorModel;
    
    struct ConstIteratorInterface;
    template <class CollectionType> class ConstIteratorModel;

    struct ConstIterator;

    struct Iterator : std::forward_iterator_tag
    {
        using difference_type   = LegacyForwardIteratorBase::difference_type;
        using value_type        = LegacyForwardIteratorBase::value_type;
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

        T &operator *()  { return *(*m_pimpl); }

        T  operator ->() { return m_pimpl->operator ->(); }

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

        Iterator() = default;
    };

    struct ConstIterator : std::forward_iterator_tag
    {
        using difference_type   = LegacyForwardIteratorBase::difference_type;
        using value_type        = LegacyForwardIteratorBase::value_type;
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

            ConstIterator() = default;
    };

    struct ConstIteratorInterface
    {
        virtual ~ConstIteratorInterface() { }

        virtual const T &operator*() = 0;
        virtual const T *operator->() = 0;
        virtual ConstIteratorInterface &operator++() = 0;

        virtual std::unique_ptr<ConstIteratorInterface> post_increment() = 0;

        virtual bool operator ==(const ConstIteratorInterface &other) const = 0;
        virtual bool operator !=(const ConstIteratorInterface &other) const = 0;

        virtual std::unique_ptr<ConstIteratorInterface> Clone() const = 0;
    };

    template <class CollectionType>
    struct ConstIteratorModel : ConstIteratorInterface
    {
        ConstIteratorModel(typename CollectionType::const_iterator i)
          :
          m_iterator( i )
        {
        }

        ConstIteratorModel(typename CollectionType::iterator i)
            :
            m_iterator( i )
        {
        }

       ~ConstIteratorModel() override { }

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

        std::unique_ptr<ConstIteratorInterface> post_increment() override
        {
            typename CollectionType::const_iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<ConstIteratorModel>(old);
        }

        std::unique_ptr<ConstIteratorInterface> Clone() const override
        {
            return std::make_unique<ConstIteratorModel>(m_iterator);
        }

        bool operator ==(const ConstIteratorInterface &other) const override
        {
            const ConstIteratorModel<CollectionType> *p = dynamic_cast<const ConstIteratorModel<CollectionType> *>(&other);

            if ( !p )
                return false;

            return m_iterator == p->m_iterator;
        }

        bool operator !=(const ConstIteratorInterface &other) const override
        {
            const ConstIteratorModel<CollectionType> *p = dynamic_cast<const ConstIteratorModel<CollectionType> *>(&other);

            if ( !p )
                return false;

            return m_iterator != p->m_iterator;
        }
        protected:
            CollectionType::const_iterator m_iterator;
    };

    struct IteratorInterface
    {
        virtual ~IteratorInterface() { }

        virtual T &operator*() = 0;
        virtual T *operator->() = 0;
        virtual IteratorInterface &operator++() = 0;

        virtual std::unique_ptr<IteratorInterface> post_increment() = 0;

        virtual bool operator ==(const IteratorInterface &other) const = 0;
        virtual bool operator !=(const IteratorInterface &other) const = 0;

        virtual std::unique_ptr<IteratorInterface> Clone() = 0;
        virtual std::unique_ptr<ConstIteratorInterface> CloneAsConst() const = 0;
    };

    template <class CollectionType>
    struct IteratorModel : IteratorInterface
    {
        IteratorModel(typename CollectionType::iterator i)
          :
          m_iterator( i )
        {
        }

       ~IteratorModel() override { }

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

        std::unique_ptr<IteratorInterface> post_increment() override
        {
            typename CollectionType::iterator old = m_iterator;

            m_iterator++;
            return std::make_unique<IteratorModel<CollectionType>>(old);
        }

        std::unique_ptr<IteratorInterface> Clone() override
        {
            return std::make_unique<IteratorModel<CollectionType>>(m_iterator);
        }

        std::unique_ptr<ConstIteratorInterface> CloneAsConst() const override
        {
            return std::make_unique<ConstIteratorModel<CollectionType>>(m_iterator);
        }

        bool operator ==(const IteratorInterface &other) const override
        {
            const IteratorModel<CollectionType> *p = dynamic_cast<const IteratorModel<CollectionType> *>(&other);

            if ( !p )
                return false;

            return m_iterator == p->m_iterator;
        }

        bool operator !=(const IteratorInterface &other) const override
        {
            const IteratorModel<CollectionType> *p = dynamic_cast<const IteratorModel<CollectionType> *>(&other);

            if ( !p )
                return true;

            return m_iterator != p->m_iterator;
        }
        protected:
            CollectionType::iterator m_iterator;
    };

    using iterator       = Iterator;
    using const_iterator = ConstIterator;
};

}