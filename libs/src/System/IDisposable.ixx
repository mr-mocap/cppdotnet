module;

export module System:IDisposable;

import <memory>;

namespace System
{

export
class IDisposable
{
    struct Interface
    {
        virtual ~Interface() { }

        virtual void Dispose() = 0;

        virtual std::unique_ptr<Interface> Clone() = 0;
        virtual std::unique_ptr<Interface> Empty() = 0;
    };

    template <typename DisposableType>
    struct InterfaceModel : Interface
    {
        InterfaceModel() = default;
        InterfaceModel(DisposableType &input) : data( input ) { }
        InterfaceModel(DisposableType &&input) : data( std::move(input) ) { }
        ~InterfaceModel() override { }
          
        // Default copy and move
        InterfaceModel(const InterfaceModel &other) = default;
        InterfaceModel(InterfaceModel &&other) = default;

        InterfaceModel &operator =(const InterfaceModel &) = default;
        InterfaceModel &operator =(InterfaceModel &&) = default;

        void Dispose() override { data.Dispose(); }

        std::unique_ptr<Interface> Clone() override
        {
            return std::make_unique<InterfaceModel>(data);
        }

        std::unique_ptr<Interface> Empty() override
        {
            return std::make_unique_for_overwrite<InterfaceModel>();
        }

        DisposableType data;
    };

public:
    IDisposable() = delete;

    template <class DisposableType>
    IDisposable(DisposableType &input)
      :
      m_pimple( std::make_unique<InterfaceModel<DisposableType>>(input) )
    {
    }

    template <class DisposableType>
    IDisposable(DisposableType &&input)
      :
      m_pimple( std::make_unique<InterfaceModel<DisposableType>>( std::move(input) ) )
    {
    }

    IDisposable(const IDisposable &other)
      :
      m_pimple( other.m_pimple->Clone() )
    {
    }
    IDisposable(IDisposable &other)
      :
      m_pimple( other.m_pimple->Clone() )
    {
    }
    IDisposable(IDisposable &&other)
      :
      m_pimple( other.m_pimple->Empty() )
    {
        std::swap( m_pimple, other.m_pimple );
    }

    IDisposable &operator =(const IDisposable &other)
    {
        m_pimple = other.m_pimple->Clone();
        return *this;
    }

    IDisposable &operator =(IDisposable &&other) = delete;

    void Dispose() { m_pimple->Dispose(); }
protected:
    std::unique_ptr<Interface> m_pimple;
};

}