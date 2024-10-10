#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <cstdint>

namespace System::IO
{

class Stream
{
public:
    virtual ~Stream() = default;

    bool CanRead() const { return _canRead; }
    bool CanWrite() const { return _canWrite; }

    virtual void Close();
    virtual void Flush();

    virtual void Write(const std::string_view bytes);
    virtual void WriteByte(const uint8_t byte);

    virtual std::string Read(int number_of_bytes);
    virtual int         ReadByte();

protected:
    std::unique_ptr<std::iostream> _stream;
    bool _canRead = false;
    bool _canWrite = false;

    Stream() = default;
    Stream(std::unique_ptr<std::iostream> &&stream, bool can_read, bool can_write);
};

}