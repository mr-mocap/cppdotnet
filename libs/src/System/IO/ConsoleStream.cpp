#include "System/IO/ConsoleStream.hpp"
#include <iostream>


namespace System::IO
{

ConsoleStream::ConsoleStream(Which which)
    :
    _which{ which }
{
    switch ( which )
    {
    case Which::In:
        _stream.reset( new std::iostream( std::cin.rdbuf() ) );
        _canRead = true;
        break;
    case Which::Out:
        _stream.reset( new std::iostream( std::cout.rdbuf() ) );
        _canWrite = true;
        break;
    case Which::Error:
        _stream.reset( new std::iostream( std::cerr.rdbuf() ) );
        _canWrite = true;
        break;
    case Which::Log:
        _stream.reset( new std::iostream( std::clog.rdbuf() ) );
        _canWrite = true;
        break;
    }
}

ConsoleStream::~ConsoleStream()
{
}

}