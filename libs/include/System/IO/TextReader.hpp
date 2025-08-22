#include <string>

namespace System::IO
{

class TextReader
{
public:
    TextReader();
    virtual ~TextReader() = 0;

    virtual void Close() = 0;

    virtual int Read() = 0;

    virtual std::string ReadLine() = 0;
};

}