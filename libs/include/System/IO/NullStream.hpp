#include "System/IO/Stream.hpp"


namespace System::IO
{

class NullStream : public Stream
{
public:
    NullStream() = default;

    void Write(std::string_view bytes) override;
    void Write(ReadOnlySpan<std::byte> bytes) override;
    void WriteByte(std::byte byte) override;
    void WriteByte(uint8_t byte) override;

    std::string Read(int number_of_bytes) override;
    int         ReadByte() override;
protected:

    void   _close() override;
    void   _flush() override;
    size_t _length() override;
    size_t _position() override;
};

}