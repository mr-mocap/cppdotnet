#include "System/IO/SeekOrigin.hpp"
#include "System/ReadOnlySpan.hpp"
#include <memory>
#include <utility>
#include <cstddef>


namespace System::IO
{

class Stream;

class BinaryWriter
{
public:
    BinaryWriter();
    BinaryWriter(std::unique_ptr<Stream> output) : _stream( std::move(output) ) { }
    BinaryWriter(std::shared_ptr<Stream> p) : _stream( p ) { }
    BinaryWriter(const BinaryWriter &other) = default;
    virtual ~BinaryWriter() = default;

    BinaryWriter &operator =(const BinaryWriter &other) = default;

    static BinaryWriter Null() { return BinaryWriter(); }

    const System::IO::Stream &OutStream() const { return *_stream; }
          System::IO::Stream &OutStream()       { return *_stream; }

    virtual void Close();

    virtual void Flush();

    virtual long Seek(long offset, SeekOrigin origin);

    virtual void Write(std::byte value);

    // @{
    virtual void Write(ReadOnlySpan<std::byte> values);

    template <std::size_t ArrayExtent>
    void Write(std::byte (&arr)[ArrayExtent])
    {
        Write( ReadOnlySpan<std::byte>( arr ) );
    }
    // @}

    virtual void Write(char value);
    virtual void Write(bool value);

    virtual void Write(std::int16_t value);
    virtual void Write(std::int32_t value);
    virtual void Write(std::int64_t value);

    virtual void Write(std::uint16_t value);
    virtual void Write(std::uint32_t value);
    virtual void Write(std::uint64_t value);

    virtual void Write(float value);
    virtual void Write(double value);
protected:
    std::shared_ptr<System::IO::Stream> _stream;
};

}