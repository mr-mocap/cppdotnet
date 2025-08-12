#pragma once

import <exception>;
import <string>;
import <string_view>;
import <memory>;
import <source_location>;
import <concepts>;

namespace System
{

/** The base exception class in .NET
 *
 *  @note You shouldn't use this OR SystemException.  Use one of the classes
 *        derived from those.
 */
class Exception : public std::exception
{
public:
    Exception() = default;

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    Exception(const Exception &) = delete;
    Exception &operator =(const Exception &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    Exception(Exception &&other);
    Exception &operator =(Exception &&other);
    /// @}

    Exception(std::string_view message);

    /** 
     *
     *  @note This pattern allows for only move of Exception classes into the InnerException()
     *        since we need to copy the entire Exception object and not just this base class slice.
     *
     *  @{
     */
    template <class ExceptionType>
        requires std::derived_from<ExceptionType, Exception>
    Exception(std::string_view message, const ExceptionType &inner_exception) = delete;

    template <class ExceptionType>
        requires std::derived_from<ExceptionType, Exception>
    Exception(std::string_view message, ExceptionType &&inner_exception)
        :
        _message{ message },
        _innerException{ std::make_unique<ExceptionType>( std::move(inner_exception) ) }
    {
    }
    /// @}

    virtual ~Exception();

    std::string_view Message() const;

    std::string_view TargetSite() const;
          void             TargetSite(const char *object_name);
          void             TargetSite(std::string_view object_name);

    const Exception *InnerException() const { return _innerException.get(); }
    const Exception &GetBaseException() const;

    virtual std::string StackTrace() const;

    virtual std::string ToString() const;

    bool operator ==(const Exception &other) const;

    //const char *what() const override { return _message.c_str(); }

    virtual std::string_view ClassName() const;
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
    virtual ~SystemException() = default;

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    SystemException(const SystemException &) = delete;
    SystemException &operator =(const SystemException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    SystemException(SystemException &&other) : Exception( std::move(other) ) { }
    SystemException &operator =(SystemException &&other)
    {
        Exception::operator =( std::move(other) );
        return *this;
    }
    /// @}

    SystemException(std::string_view message)
        :
        Exception( message )
    {
    }

    std::string_view ClassName() const override;
};

class ArgumentException : public SystemException
{
public:
    using SystemException::SystemException;

    ArgumentException() = default;
    virtual ~ArgumentException() = default;

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    ArgumentException(const ArgumentException &) = delete;
    ArgumentException &operator =(const ArgumentException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
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
    /// @}

    explicit ArgumentException(std::string_view message) : SystemException( message ) { }

    explicit ArgumentException(std::string_view message, std::string_view param_name)
        :
        SystemException( message ),
        _paramName{ param_name }
    {
    }
    explicit ArgumentException(std::string_view message,
                               std::string_view param_name,
                               Exception &&inner_exception)
        :
        SystemException( message, std::move(inner_exception) ),
        _paramName{ param_name }
    {
    }

    std::string_view ParamName() const { return _paramName; }

    std::string_view ClassName() const override;
protected:
    std::string _paramName;
};

class ArgumentNullException : public ArgumentException
{
public:
    using ArgumentException::ArgumentException;

    ArgumentNullException() = default;
   ~ArgumentNullException() = default;

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    ArgumentNullException(const ArgumentNullException &) = delete;
    ArgumentNullException &operator =(const ArgumentNullException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    ArgumentNullException(ArgumentNullException &&other) : ArgumentException( std::move(other) ) { }
    ArgumentNullException &operator =(ArgumentNullException &&other)
    {
        ArgumentException::operator =( std::move(other) );
        return *this;
    }
    /// @}

    ArgumentNullException(std::string_view param_name);

    ArgumentNullException(std::string_view param_name, std::string_view message)
        :
        ArgumentException( message, param_name )
    {
    }

    std::string_view ClassName() const override;
};

class ArgumentOutOfRangeException : public ArgumentException
{
public:
    using ArgumentException::ArgumentException;

    ArgumentOutOfRangeException() = default;
   ~ArgumentOutOfRangeException() = default;

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    ArgumentOutOfRangeException(const ArgumentOutOfRangeException &) = delete;
    ArgumentOutOfRangeException &operator =(const ArgumentOutOfRangeException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    ArgumentOutOfRangeException(ArgumentOutOfRangeException &&other) : ArgumentException( std::move(other) ) { }
    ArgumentOutOfRangeException &operator =(ArgumentOutOfRangeException &&other)
    {
        ArgumentException::operator =( std::move(other) );
        return *this;
    }
    /// @}

    ArgumentOutOfRangeException(std::string_view param_name);

    ArgumentOutOfRangeException(std::string_view param_name, std::string_view message)
        :
        ArgumentException( message, param_name )
    {
    }

    std::string_view ClassName() const override;
};

class NotSupportedException : public SystemException
{
public:
    using SystemException::SystemException;

    NotSupportedException() = default;
   ~NotSupportedException() = default;

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    NotSupportedException(const NotSupportedException &) = delete;
    NotSupportedException &operator =(const NotSupportedException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    NotSupportedException(NotSupportedException &&other) : SystemException( std::move(other) ) { }
    NotSupportedException &operator =(NotSupportedException &&other)
    {
        SystemException::operator =( std::move(other) );
        return *this;
    }
    /// @}

    NotSupportedException(std::string_view message) : SystemException( message ) { }

    std::string_view ClassName() const override;
};

class InvalidOperationException : public SystemException
{
public:
    using SystemException::SystemException;

    InvalidOperationException() = default;
    virtual ~InvalidOperationException() = default;

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    InvalidOperationException(const InvalidOperationException &) = delete;
    InvalidOperationException &operator =(const InvalidOperationException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    InvalidOperationException(InvalidOperationException &&other) : SystemException( std::move(other) ) { }
    InvalidOperationException &operator =(InvalidOperationException &&other)
    {
        SystemException::operator =( std::move(other) );
        return *this;
    }
    /// @}

    InvalidOperationException(std::string_view message) : SystemException( message ) { }

    std::string_view ClassName() const override;
};

class ObjectDisposedException : public InvalidOperationException
{
public:
    using InvalidOperationException::InvalidOperationException;

    ObjectDisposedException() = default;
   ~ObjectDisposedException() = default;
    
    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    ObjectDisposedException(const ObjectDisposedException &) = delete;
    ObjectDisposedException &operator =(const ObjectDisposedException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
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
    /// @}

    ObjectDisposedException(std::string_view disposed_object_name);

    ObjectDisposedException(std::string_view disposed_object_name, std::string_view message);

    std::string_view ObjectName() const { return _objectName; }

    std::string_view ClassName() const override;
protected:
    std::string _objectName;
};

class FormatException : public SystemException
{
public:
    using SystemException::SystemException;

    FormatException() = default;
   ~FormatException() = default;

    explicit FormatException(std::string_view message) : SystemException( message ) { }

    explicit FormatException(std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, std::move(inner_exception) )
    {
    }

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    FormatException(const FormatException &) = delete;
    FormatException &operator =(const FormatException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    FormatException(FormatException &&other) = default;
    FormatException &operator =(FormatException &&other) = default;
    /// @}

    std::string_view ClassName() const override;
};

class ArithmeticException : public SystemException
{
public:
    using SystemException::SystemException;

    ArithmeticException() = default;
   ~ArithmeticException() = default;

    explicit ArithmeticException(std::string_view message) : SystemException( message ) { }

    explicit ArithmeticException(std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, std::move(inner_exception) )
    {
    }

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    ArithmeticException(const ArithmeticException &) = delete;
    ArithmeticException &operator =(const ArithmeticException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    ArithmeticException(ArithmeticException &&other) = default;
    ArithmeticException &operator =(ArithmeticException &&other) = default;
    /// @}

    std::string_view ClassName() const override;
};

class OverflowException : public SystemException
{
public:
    using SystemException::SystemException;

    OverflowException() = default;
   ~OverflowException() = default;

    explicit OverflowException(std::string_view message) : SystemException( message ) { }

    explicit OverflowException(std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, std::move(inner_exception) )
    {
    }

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    OverflowException(const OverflowException &) = delete;
    OverflowException &operator =(const OverflowException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    OverflowException(OverflowException &&other) = default;
    OverflowException &operator =(OverflowException &&other) = default;
    /// @}

    std::string_view ClassName() const override;
};

/** Throws the given exception and fills in the TargetSite()
 *
 *  @param exception_to_throw
 *
 *  @note The second parameter is boilerplate for C++ to acquire
 *        the information about the call-site of the function call.
 */ 
template <class ExceptionType>
[[noreturn]] void ThrowWithTarget(ExceptionType        &&exception_to_throw,
                                  std::source_location   sloc = std::source_location::current())
{
    ExceptionType e{ std::forward<ExceptionType>( exception_to_throw ) };
    
    e.TargetSite( sloc.function_name() );
    throw e;
}

}
