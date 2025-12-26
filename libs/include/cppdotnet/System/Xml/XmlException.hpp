#pragma once

#include <System/Exception.hpp>


namespace System::Xml
{

class XmlException : public SystemException
{
public:
    using SystemException::SystemException;

    XmlException() = default;
    virtual ~XmlException() = default;

    XmlException(const XmlException &) = delete;
    XmlException &operator =(const XmlException &) = delete;

    XmlException(XmlException &&other) : SystemException( std::move(other) ) { }
    XmlException &operator =(XmlException &&other)
    {
        SystemException::operator =( std::move(other) );
        return *this;
    }

    XmlException(std::string_view message)
        :
        SystemException( message )
    {
    }

    template <class ExceptionType>
        requires (std::derived_from<ExceptionType, Exception>)
    XmlException(std::string_view message, ExceptionType &&e, int line_number, int line_position)
        :
        SystemException( message, std::move(e) ),
        _line_number( line_number ),
        _line_position( line_position )
    {
        INVARIANT( _line_number > 0 );
        INVARIANT( _line_position > 0 );
    }

    int LineNumber() const
    {
        return _line_number;
    }

    int LinePosition() const
    {
        return _line_position;
    }
protected:
    int _line_number   = 1;
    int _line_position = 1;
};

}