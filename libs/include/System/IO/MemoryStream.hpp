#pragma once

#include "System/IO/Stream.hpp"


namespace System::IO
{

class MemoryStream : public Stream
{
public:
    MemoryStream();

    virtual std::string ToArray() const;

protected:
    size_t _length() override;
    size_t _position() override;
};

}