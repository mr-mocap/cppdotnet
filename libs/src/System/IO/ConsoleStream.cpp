import "System/IO/ConsoleStream.hpp";
import <iostream>;


namespace System::IO
{

ConsoleStream::ConsoleStream(Which which)
    :
    _which{ which }
{
    switch ( which )
    {
    case Which::In:
        _stream = std::make_unique<std::iostream>( std::cin.rdbuf() );
        _canRead = true;
        break;
    case Which::Out:
        _stream = std::make_unique<std::iostream>( std::cout.rdbuf() );
        _canWrite = true;
        break;
    case Which::Error:
        _stream = std::make_unique<std::iostream>( std::cerr.rdbuf() );
        _canWrite = true;
        break;
    case Which::Log:
        _stream = std::make_unique<std::iostream>( std::clog.rdbuf() );
        _canWrite = true;
        break;
    }
}

ConsoleStream::~ConsoleStream()
{
}

}