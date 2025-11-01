#pragma once

#include <cppdotnet/System/TypeCode.hpp>
#include <string>

namespace System::IO
{

class TextReader
{
public:
    TextReader();
    virtual ~TextReader();

    static constexpr TypeCode GetTypeCode() { return TypeCode::Object; }

    virtual void Close() = 0;

    virtual int Read() = 0;

    virtual std::string ReadLine() = 0;
};

}