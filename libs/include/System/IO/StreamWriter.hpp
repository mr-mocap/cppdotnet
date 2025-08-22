#include "System/IO/TextWriter.hpp"
#include "System/IO/Stream.hpp"
#include <memory>
#include <concepts>

namespace System::IO
{

class StreamWriter : public TextWriter
{
public:
    StreamWriter() = default;
    StreamWriter(std::string_view filename);
    StreamWriter(std::unique_ptr<Stream> stream)
        :
        _stream{ std::move(stream) }
    {
    }

   ~StreamWriter();

    void Close() override;
    void Flush() override;

    void Write(char value) override;
    void Write(std::string_view message) override;

    Stream *BaseStream() const { return _stream.get(); }
protected:
    std::unique_ptr<Stream> _stream;
};

}