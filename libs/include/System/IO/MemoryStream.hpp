#include "System/IO/Stream.hpp"


namespace System::IO
{

class MemoryStream : public Stream
{
public:
    MemoryStream();
    MemoryStream(const std::string &initial_buffer);
    MemoryStream(const std::string &initial_buffer, int index, int count, bool writable = true);
   ~MemoryStream() override;

    virtual int Capacity() const { return static_cast<int>( _capacity ); }

    virtual std::string ToArray() const;

protected:
    std::size_t _initial_capacity = 0;
    std::size_t _capacity = 0;

    size_t _length() override;
    size_t _position() override;
};

}