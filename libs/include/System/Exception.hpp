#pragma once

#include <exception>
#include <string>
#include <string_view>
#include <memory>
#include <source_location>
#include <format>

namespace System
{

class Exception : public std::exception
{
public:
    Exception() = default;

    Exception(const Exception &) = delete;
    Exception &operator =(const Exception &) = delete;

    // Move
    Exception(Exception &&other);
    Exception &operator =(Exception &&other);

    Exception(const std::string_view message);
    template <class ExceptionType>
    Exception(const std::string_view message, const ExceptionType &inner_exception) = delete;

    template <class ExceptionType>
    Exception(const std::string_view message, ExceptionType &&inner_exception)
        :
        _message{ message },
        _innerException{ std::make_unique<ExceptionType>( std::move(inner_exception) ) }
    {
    }

    virtual ~Exception();

    const std::string_view Message() const;

    const std::string_view TargetSite() const;
          void             TargetSite(const char *object_name);
          void             TargetSite(const std::string_view object_name);

    const Exception *InnerException() const { return _innerException.get(); }
    const Exception &GetBaseException() const;

    virtual std::string ToString() const;

    bool operator ==(const Exception &other) const;

    //const char *what() const override { return _message.c_str(); }

    virtual const std::string_view ClassName() const;
protected:
    std::string _message;
    std::string _targetSite;
    std::unique_ptr<Exception> _innerException;
};

class SystemException : public Exception
{
public:
    using Exception::Exception;

    SystemException() = default;

    SystemException(const SystemException &) = delete;
    SystemException &operator =(const SystemException &) = delete;

    // Move
    SystemException(SystemException &&other) : Exception( std::move(other) ) { }
    SystemException &operator =(SystemException &&other)
    {
        Exception::operator =( std::move(other) );
        return *this;
    }

    SystemException(const std::string_view message)
        :
        Exception( message )
    {
    }

    const std::string_view ClassName() const override;
};

class ArgumentException : public SystemException
{
public:
    using SystemException::SystemException;

    ArgumentException() = default;

    ArgumentException(const ArgumentException &) = delete;
    ArgumentException &operator =(const ArgumentException &) = delete;

    // Move
    ArgumentException(ArgumentException &&other)
        :
        SystemException( std::move(other) ),
        _paramName{ std::move(other._paramName) }
    {
    }
    ArgumentException &operator =(ArgumentException &&other)
    {
        SystemException::operator =( std::move(other) );
        _paramName = std::move(other._paramName);
        return *this;
    }

    ArgumentException(const std::string_view message) : SystemException( message ) { }
    ArgumentException(const std::string_view message, const std::string_view param_name)
        :
        SystemException( message ),
        _paramName{ param_name }
    {
    }
    ArgumentException(const std::string_view message,
                      const std::string_view param_name,
                      Exception &&inner_exception)
        :
        SystemException( message, std::move(inner_exception) ),
        _paramName{ param_name }
    {
    }

    const std::string_view ParamName() const { return _paramName; }

    const std::string_view ClassName() const override;
protected:
    std::string _paramName;
};

class ArgumentNullException : public ArgumentException
{
public:
    using ArgumentException::ArgumentException;

    ArgumentNullException() = default;

    ArgumentNullException(const ArgumentNullException &) = delete;
    ArgumentNullException &operator =(const ArgumentNullException &) = delete;

    // Move
    ArgumentNullException(ArgumentNullException &&other) : ArgumentException( std::move(other) ) { }
    ArgumentNullException &operator =(ArgumentNullException &&other)
    {
        ArgumentException::operator =( std::move(other) );
        return *this;
    }

    ArgumentNullException(const std::string_view param_name);
    ArgumentNullException(const std::string_view param_name, const std::string_view message)
        :
        ArgumentException( message, param_name )
    {
    }

    const std::string_view ClassName() const override;
};

class ArgumentOutOfRangeException : public ArgumentException
{
public:
    using ArgumentException::ArgumentException;

    ArgumentOutOfRangeException() = default;

    ArgumentOutOfRangeException(const ArgumentOutOfRangeException &) = delete;
    ArgumentOutOfRangeException &operator =(const ArgumentOutOfRangeException &) = delete;

    // Move
    ArgumentOutOfRangeException(ArgumentOutOfRangeException &&other) : ArgumentException( std::move(other) ) { }
    ArgumentOutOfRangeException &operator =(ArgumentOutOfRangeException &&other)
    {
        ArgumentException::operator =( std::move(other) );
        return *this;
    }

    ArgumentOutOfRangeException(const std::string_view param_name);
    ArgumentOutOfRangeException(const std::string_view param_name, const std::string_view message)
        :
        ArgumentException( message, param_name )
    {
    }

    const std::string_view ClassName() const override;
};

class NotSupportedException : public SystemException
{
public:
    using SystemException::SystemException;

    NotSupportedException() = default;

    NotSupportedException(const NotSupportedException &) = delete;
    NotSupportedException &operator =(const NotSupportedException &) = delete;

    // Move
    NotSupportedException(NotSupportedException &&other) : SystemException( std::move(other) ) { }
    NotSupportedException &operator =(NotSupportedException &&other)
    {
        SystemException::operator =( std::move(other) );
        return *this;
    }

    NotSupportedException(const std::string_view message) : SystemException( message ) { }

    const std::string_view ClassName() const override;
};

class InvalidOperationException : public SystemException
{
public:
    using SystemException::SystemException;

    InvalidOperationException() = default;

    InvalidOperationException(const InvalidOperationException &) = delete;
    InvalidOperationException &operator =(const InvalidOperationException &) = delete;

    // Move
    InvalidOperationException(InvalidOperationException &&other) : SystemException( std::move(other) ) { }
    InvalidOperationException &operator =(InvalidOperationException &&other)
    {
        SystemException::operator =( std::move(other) );
        return *this;
    }

    InvalidOperationException(const std::string_view message) : SystemException( message ) { }

    const std::string_view ClassName() const override;
};

class ObjectDisposedException : public InvalidOperationException
{
public:
    using InvalidOperationException::InvalidOperationException;

    ObjectDisposedException() = default;
    
    ObjectDisposedException(const ObjectDisposedException &) = delete;
    ObjectDisposedException &operator =(const ObjectDisposedException &) = delete;

    // Move
    ObjectDisposedException(ObjectDisposedException &&other)
        :
        InvalidOperationException( std::move(other) ),
        _objectName{ std::move(other._objectName) }
    {
    }
    ObjectDisposedException &operator =(ObjectDisposedException &&other)
    {
        InvalidOperationException::operator =( std::move(other) );
        _objectName = std::move(other._objectName);
        return *this;
    }

    ObjectDisposedException(const std::string_view disposed_object_name);
    ObjectDisposedException(const std::string_view disposed_object_name, const std::string_view message);

    const std::string ObjectName() const { return _objectName; }

    const std::string_view ClassName() const override;
protected:
    std::string _objectName;
};

template <class ExceptionType>
void ThrowWithTarget(ExceptionType &&exception_to_throw,
                             std::source_location sloc = std::source_location::current())
{
    ExceptionType e{ std::forward<ExceptionType>( exception_to_throw ) };
    
    e.TargetSite( sloc.function_name() );
    throw e;
}

}