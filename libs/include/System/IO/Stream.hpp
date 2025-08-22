#include "System/IO/SeekOrigin.hpp"
#include "System/ReadOnlySpan.hpp"
#include <iosfwd>
#include <memory>
#include <string>
#include <cstdint>

namespace System::IO
{

class Stream
{
public:
    Stream(const Stream &) = delete;
    Stream(Stream &&);
    virtual ~Stream();

    Stream &operator =(const Stream &) = delete;
    Stream &operator =(Stream &&);

    static std::unique_ptr<Stream> Null();

    bool CanRead() const { return _canRead; }
    bool CanWrite() const { return _canWrite; }
    bool CanSeek() const { return _canSeek; }

    void Close();
    void Flush();

    size_t Length();
    size_t Position();

    virtual void Write(std::string_view bytes);
    virtual void Write(ReadOnlySpan<std::byte> bytes);
    virtual void WriteByte(std::byte value);
    virtual void WriteByte(uint8_t byte);

    virtual std::string Read(int number_of_bytes);
    virtual int         Read(Span<std::byte> buffer);
    virtual int         ReadByte();

    virtual long Seek(long offset, SeekOrigin origin);
protected:
    std::unique_ptr<std::iostream> _stream;
    bool _canRead = false;
    bool _canWrite = false;
    bool _canSeek  = false;

    Stream() = default;
    Stream(std::unique_ptr<std::iostream> &&stream, bool can_read, bool can_write, bool can_seek);

    virtual void   _close();
    virtual void   _flush();
    virtual size_t _length();
    virtual size_t _position();
};

}