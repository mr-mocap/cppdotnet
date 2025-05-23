#pragma once

#include <memory>


namespace System::Collections::Generic
{

template <class T>
class ICollection
{
    struct InternalInterface
    {
        virtual ~InternalInterface() { }

        virtual std::size_t Count() const = 0;
        virtual bool        IsReadOnly() const = 0;
        virtual bool        IsReadOnly()       = 0;
        virtual bool        IsSynchronized() const = 0;

        virtual void Add(const T &item) = 0;
        virtual bool Remove(const T &item) = 0;
        virtual void Clear() = 0;
        virtual bool Contains(const T &item) = 0;

        // TODO: Add CopyTo() ?

        virtual std::unique_ptr<InternalInterface> Clone() = 0;
        virtual std::unique_ptr<InternalInterface> Empty() = 0;
    };

    template <typename DataType>
    struct GeneralizedInterface : InternalInterface
    {
        GeneralizedInterface() = default;
        GeneralizedInterface(DataType &input) : data( input ) { }
        GeneralizedInterface(DataType &&input) : data( std::move(input) ) { }
        ~GeneralizedInterface() override { }
          
        // Default copy and move
        GeneralizedInterface(const GeneralizedInterface &other) = default;
        GeneralizedInterface(GeneralizedInterface &&other) = default;

        GeneralizedInterface &operator =(const GeneralizedInterface &) = default;
        GeneralizedInterface &operator =(GeneralizedInterface &&) = default;

        std::size_t Count() const override { return data.Count(); }

        bool IsReadOnly() const override { return data.IsReadOnly(); }
        bool IsReadOnly()       override { return data.IsReadOnly(); }

        bool IsSynchronized() const { return data.IsSynchronized(); }

        void Add(const T &item) override { data.Add(item); }

        bool Remove(const T &item) override { return data.Remove(item); }

        void Clear() override { data.Clear(); }

        bool Contains(const T &item) override { return data.Contains(item); }

        std::unique_ptr<InternalInterface> Clone() override
        {
            return std::make_unique<GeneralizedInterface>(data);
        }

        std::unique_ptr<InternalInterface> Empty() override
        {
            return std::make_unique_for_overwrite<GeneralizedInterface>();
        }

        DataType data;
    };

public:
    ICollection() = delete;

    template <class DataType>
    ICollection(DataType &input)
      :
      _data( std::make_unique<GeneralizedInterface<DataType>>(input) )
    {
    }

    template <class DataType>
    ICollection(DataType &&input)
      :
      _data( std::make_unique<GeneralizedInterface<DataType>>( std::move(input) ) )
    {
    }

    ICollection(const ICollection &other)
      :
      _data( other._data->Clone() )
    {
    }
    ICollection(ICollection &other)
      :
      _data( other._data->Clone() )
    {
    }
    ICollection(ICollection &&other)
      :
      _data( other._data->Empty() )
    {
        std::swap( _data, other._data );
    }

    ICollection &operator =(const ICollection &other)
    {
        _data = other._data->Clone();
        return *this;
    }

    ICollection &operator =(ICollection &&other) = delete;

    std::size_t Count() const      { return _data->Count(); }
    bool        IsReadOnly() const { return _data->IsReadOnly(); }
    bool        IsReadOnly()       { return _data->IsReadOnly(); }
    bool        IsSynchronized() const { return _data->IsSynchronized(); }

    void Add(const T &item)      { _data->Add(item); }
    bool Remove(const T &item)   { return _data->Remove(item); }
    void Clear()                 { _data->Clear(); }
    bool Contains(const T &item) { return _data->Contains(item); }
protected:
    std::unique_ptr<InternalInterface> _data;
};


template <class T>
class ICollectionRef
{
    struct InternalInterface
    {
        virtual ~InternalInterface() { }

        virtual std::size_t Count() const = 0;
        virtual bool        IsReadOnly() const = 0;
        virtual bool        IsReadOnly()       = 0;
        virtual bool        IsSynchronized() const = 0;

        virtual void Add(const T &item) = 0;
        virtual bool Remove(const T &item) = 0;
        virtual void Clear() = 0;
        virtual bool Contains(const T &item) = 0;

        // TODO: Add CopyTo() ?

        virtual std::unique_ptr<InternalInterface> Clone() = 0;
    };

    template <typename DataType>
    struct GeneralizedInterfacePtr : InternalInterface
    {
        GeneralizedInterfacePtr() = delete;
        GeneralizedInterfacePtr(DataType *input) : data( input ) { } // For easily creating a copy
        ~GeneralizedInterfacePtr() override
        {
            data = nullptr;
        }
          
        // Default copy and move
        GeneralizedInterfacePtr(const GeneralizedInterfacePtr &other) = default;
        GeneralizedInterfacePtr(GeneralizedInterfacePtr &&other) = default;

        GeneralizedInterfacePtr &operator =(const GeneralizedInterfacePtr &) = default;
        GeneralizedInterfacePtr &operator =(GeneralizedInterfacePtr &&) = default;

        std::size_t Count() const override { return data->Count(); }

        bool IsReadOnly() const override { return data->IsReadOnly(); }
        bool IsReadOnly()       override { return data->IsReadOnly(); }

        bool IsSynchronized() const override { return data->IsSynchronized(); }

        void Add(const T &item) override { data->Add(item); }

        bool Remove(const T &item) override { return data->Remove(item); }

        void Clear() override { data->Clear(); }

        bool Contains(const T &item) override { return data->Contains(item); }

        std::unique_ptr<InternalInterface> Clone() override
        {
            return std::make_unique<GeneralizedInterfacePtr<DataType>>(data);
        }

        DataType *data = nullptr;
    };

public:
    ICollectionRef() = delete;

    template <class DataType>
    ICollectionRef(DataType *input)
      :
      _data( std::make_unique<GeneralizedInterfacePtr<DataType>>(input) )
    {
    }

    ICollectionRef(const ICollectionRef &other)
      :
      _data( other._data->Clone() )
    {
    }
    ICollectionRef(ICollectionRef &other)
      :
      _data( other._data->Clone() )
    {
    }
    ICollectionRef(ICollectionRef &&other) = default;

    std::size_t Count() const      { return _data->Count(); }
    bool        IsReadOnly() const { return _data->IsReadOnly(); }
    bool        IsReadOnly()       { return _data->IsReadOnly(); }
    bool        IsSynchronized() const { return _data->IsSynchronized(); }

    void Add(const T &item)      { _data->Add(item); }
    bool Remove(const T &item)   { return _data->Remove(item); }
    void Clear()                 { _data->Clear(); }
    bool Contains(const T &item) { return _data->Contains(item); }
protected:
    std::unique_ptr<InternalInterface> _data;
};

}