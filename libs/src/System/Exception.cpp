#include "System/Exception.hpp"
#include <format>
#include <cstring>

namespace System
{

Exception::Exception(Exception &&other)
    :
    _message{ std::move(other._message) },
    _targetSite{ std::move(other._targetSite) },
    _innerException{ std::move(other._innerException) }
{
}

Exception::Exception(const std::string_view message)
    :
    _message{ message }
{
}

Exception::~Exception()
{
}

Exception &Exception::operator =(Exception &&other)
{
    if ( this != &other )
    {
        _message = std::move(other._message);
        _targetSite  = std::move(other._targetSite);
        _innerException.reset();
        _innerException.swap(other._innerException);
    }
    return *this;
}

const Exception &Exception::GetBaseException() const
{
    if ( _innerException )
        return _innerException->GetBaseException();
    else
        return *this;
}

const std::string_view Exception::Message() const
{
    return _message;
}

const std::string_view Exception::TargetSite() const
{
    return _targetSite;
}

void Exception::TargetSite(const char *object_name)
{
    TargetSite( std::string_view{
                              object_name,
                              strlen(object_name)
                                } );
}

void Exception::TargetSite(const std::string_view object_name)
{
    _targetSite = object_name;
}

std::string Exception::StackTrace() const
{
    return "NOT IMPLEMENTED";
}

std::string Exception::ToString() const
{
    std::string s{ std::format("{}: '{}'", ClassName(), _message) };

    if ( InnerException() )
    {
        s.append( "\n" );
        s.append( InnerException()->ToString() );
    }
    return s;
}

bool Exception::operator ==(const Exception &other) const
{
    // Use the early-exit method by checking for differences fist!
    if ( _message != other._message )
        return false;
    if ( _innerException != other._innerException )
        return false;
    if ( _innerException && other._innerException )
        return *_innerException == *other._innerException;
    return true;
}

const std::string_view Exception::ClassName() const
{
    using namespace std::literals;

    return "Exception"sv;
}

const std::string_view SystemException::ClassName() const
{
    using namespace std::literals;

    return "SytemException"sv;
}

const std::string_view ArgumentException::ClassName() const
{
    using namespace std::literals;

    return "ArgumentException"sv;
}

ArgumentNullException::ArgumentNullException(const std::string_view param_name)
    :
    ArgumentException( std::format("Argument '{}' is null", param_name) )
{
    _paramName = param_name;
}

const std::string_view ArgumentNullException::ClassName() const
{
    using namespace std::literals;

    return "ArgumentNullException"sv;
}

ArgumentOutOfRangeException::ArgumentOutOfRangeException(const std::string_view param_name)
    :
    ArgumentException( std::format("Argument '{}' is out-of-range", param_name) )
{
    _paramName = param_name;
}

const std::string_view ArgumentOutOfRangeException::ClassName() const
{
    using namespace std::literals;

    return "ArgumentOutOfRangeException"sv;
}

const std::string_view NotSupportedException::ClassName() const
{
    using namespace std::literals;

    return "NotSupportedException"sv;
}

const std::string_view InvalidOperationException::ClassName() const
{
    using namespace std::literals;

    return "InvalidOperationException"sv;
}

ObjectDisposedException::ObjectDisposedException(const std::string_view disposed_object_name)
    :
    InvalidOperationException( std::format("Object '{}' already disposed", disposed_object_name) ),
    _objectName{ disposed_object_name }
{
}

ObjectDisposedException::ObjectDisposedException(const std::string_view disposed_object_name,
                                                 const std::string_view message)
    :
    InvalidOperationException( message ),
    _objectName{ disposed_object_name }
{
}

const std::string_view ObjectDisposedException::ClassName() const
{
    using namespace std::literals;

    return "ObjectDisposedException"sv;
}

}