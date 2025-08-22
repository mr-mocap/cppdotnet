#include "System/IO/Stream.hpp"

namespace System::IO
{

class ConsoleStream : public Stream
{
public:
    enum Which { In, Out, Error, Log };

    ConsoleStream(Which which);
   ~ConsoleStream() override;

    Which Type() const { return _which; }
protected:
    Which _which;
};

}