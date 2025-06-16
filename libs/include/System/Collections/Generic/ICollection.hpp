#pragma once

#include <memory>


namespace System::Collections::Generic
{

template <class T>
class ICollection
{
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
    };

    template <typename DataType>
    struct InterfaceModel : Interface
    {
        InterfaceModel() = default;
        InterfaceModel(DataType &input) : data( input ) { }
        InterfaceModel(DataType &&input) : data( std::move(input) ) { }
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

        DataType data;
    };

public:
    ICollection() = delete;

    template <class DataType>
    ICollection(DataType &input)
      :
      m_pimple( std::make_unique<InterfaceModel<DataType>>(input) )
    {
    }

    template <class DataType>
    ICollection(DataType &&input)
      :
      m_pimple( std::make_unique<InterfaceModel<DataType>>( std::move(input) ) )
    {
    }

    ICollection(const ICollection &other)
      :
      m_pimple( other.m_pimple->Clone() )
    {
    }
    ICollection(ICollection &other)
      :
      m_pimple( other.m_pimple->Clone() )
    {
    }
    ICollection(ICollection &&other)
      :
      m_pimple( other.m_pimple->Empty() )
    {
        std::swap( m_pimple, other.m_pimple );
    }

    ICollection &operator =(const ICollection &other)
    {
        m_pimple = other.m_pimple->Clone();
        return *this;
    }

    ICollection &operator =(ICollection &&other) = delete;

    std::size_t Count() const      { return m_pimple->Count(); }
    bool        IsReadOnly() const { return m_pimple->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimple->IsReadOnly(); }
    bool        IsSynchronized() const { return m_pimple->IsSynchronized(); }

    void Add(const T &item)      { m_pimple->Add(item); }
    bool Remove(const T &item)   { return m_pimple->Remove(item); }
    void Clear()                 { m_pimple->Clear(); }
    bool Contains(const T &item) { return m_pimple->Contains(item); }
protected:
    std::unique_ptr<Interface> m_pimple;
};


template <class T>
class ICollectionRef
{
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
    };

    template <typename DataType>
    struct InterfaceModelPtr : Interface
    {
        InterfaceModelPtr() = delete;
        InterfaceModelPtr(DataType *input) : data( input ) { } // For easily creating a copy
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
            return std::make_unique<InterfaceModelPtr<DataType>>(data);
        }

        DataType *data = nullptr;
    };

public:
    ICollectionRef() = delete;

    template <class DataType>
    ICollectionRef(DataType *input)
      :
      m_pimpl( std::make_unique<InterfaceModelPtr<DataType>>(input) )
    {
    }

    ICollectionRef(const ICollectionRef &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    ICollectionRef(ICollectionRef &other)
      :
      m_pimpl( other.m_pimpl->Clone() )
    {
    }
    ICollectionRef(ICollectionRef &&other) = default;

    std::size_t Count() const      { return m_pimpl->Count(); }
    bool        IsReadOnly() const { return m_pimpl->IsReadOnly(); }
    bool        IsReadOnly()       { return m_pimpl->IsReadOnly(); }
    bool        IsSynchronized() const { return m_pimpl->IsSynchronized(); }

    void Add(const T &item)      { m_pimpl->Add(item); }
    bool Remove(const T &item)   { return m_pimpl->Remove(item); }
    void Clear()                 { m_pimpl->Clear(); }
    bool Contains(const T &item) { return m_pimpl->Contains(item); }
protected:
    std::unique_ptr<Interface> m_pimpl;
};

}