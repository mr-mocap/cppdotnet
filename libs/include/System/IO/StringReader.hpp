#include "System/IO/TextReader.hpp"
#include <string>
#include <string_view>

namespace System::IO
{

class StringReader : public TextReader
{
public:
    StringReader() = delete;
    StringReader(std::string_view initial_value) : _data{ initial_value } { }
   ~StringReader();

    void Close() override;

    int Read() override;

    std::string ReadLine() override;

protected:
    std::string            _data;
    std::string::size_type _position = 0;
};
}