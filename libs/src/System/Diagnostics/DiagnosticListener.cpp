#include "System/Diagnostics/DiagnosticListener.hpp"
#include "System/Private/private.hpp"

namespace
{
#if 0
class Unsubscriber
{
public:
    Unsibscriber(Collections::Generic::List< IObserver<Collections::Generic::KeyValuePair<std::string, void *>> > &observers,
                 IObserver<Collections::Generic::KeyValuePair<std::string, void *>> &the_observer)
        :
        _observers( observers ),
        _the_observer( the_observer )
    {
    }

    void Dispose()
    {
        _observers.
    }

protected:
    Collections::Generic::List< IObserver<Collections::Generic::KeyValuePair<std::string, void *>> > &_observers;
    Collections::Generic::KeyValuePair<std::string, void *>> _the_observer
};
#endif
}

namespace System::Diagnostics
{

DiagnosticListener::DiagnosticListener(std::string_view name)
    :
    _name( name )
{
}

DiagnosticListener::~DiagnosticListener()
{
}

bool DiagnosticListener::IsEnabled() const
{
    return _observers.Count() > 0;
}

bool DiagnosticListener::IsEnabled(std::string_view name) const
{
    UNUSED( name );

    if ( !IsEnabled() )
        return false;

    return _observers.Exists(
        [&](const Collections::Generic::KeyValuePair<std::string, void *> &object)
        {
            return object.Key() == name;
        } );
}

IDisposable DiagnosticListener::Subscribe(IObserver<Collections::Generic::KeyValuePair<std::string, void *>> &observer)
{
    UNUSED( observer );

    return IDisposable( System::Private::EmptyDisposable() );
}

void DiagnosticListener::Dispose()
{
}

void DiagnosticListener::WritePayload(std::string_view payload)
{
    UNUSED( payload );
}

}