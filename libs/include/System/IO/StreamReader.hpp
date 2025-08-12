#pragma once

import "System/IO/TextReader.hpp";
import "System/IO/Stream.hpp";
import <memory>;
import <utility>;
import <string_view>;

namespace System::IO
{

class StreamReader : public TextReader
{
public:
    StreamReader() = default;
    StreamReader(std::string_view filename);
    StreamReader(const StreamReader &) = delete;
    StreamReader(StreamReader &&) = default;
    StreamReader(std::unique_ptr<System::IO::Stream> stream)
        :
        _stream{ std::move(stream) }
    {
    }

    StreamReader &operator =(const StreamReader &) = delete;
    StreamReader &operator =(StreamReader &&) = default;

   ~StreamReader() override = default;

    void Close() override;

    int Read() override;

    std::string ReadLine() override;

    System::IO::Stream *BaseStream() const { return _stream.get(); }
protected:
    std::unique_ptr<System::IO::Stream> _stream;
};

}