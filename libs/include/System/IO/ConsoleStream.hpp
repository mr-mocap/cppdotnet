#pragma once

#include "System/IO/Stream.hpp"
#include <string>

namespace System::IO
{

class ConsoleStream : public Stream
{
public:
    enum Which { In, Out, Error, Log };

    ConsoleStream(Which which);
   ~ConsoleStream();

    Which Type() const { return _which; }
protected:
    Which _which;
};

}