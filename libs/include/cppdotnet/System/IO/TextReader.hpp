#pragma once

#include <string>

namespace System::IO
{

class TextReader
{
public:
    TextReader();
    virtual ~TextReader();

    virtual void Close() = 0;

    virtual int Read() = 0;

    virtual std::string ReadLine() = 0;
};

}