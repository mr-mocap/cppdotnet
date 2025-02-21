#pragma once

#include "System/IO/Stream.hpp"
#include "System/IO/FileMode.hpp"

namespace System::IO
{

class FileStream : public Stream
{
public:
    FileStream(const std::string_view filename);
    FileStream(const std::string_view filename, const FileMode mode);
   ~FileStream();

protected:
    void _close() override;
};

}