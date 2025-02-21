#pragma once

#include "System/IO/FileAccess.hpp"
#include "System/IO/FileMode.hpp"


namespace System::IO
{

class FileStreamOptions
{
public:

    const FileAccess &Access() const { return _access; }

    size_t BufferSize() const { return _buffer_size; }

    const FileMode &Mode() const { return _mode; }

#if 0
    const FileOptions &Options() const { return _options; }
#endif
protected:
    FileAccess _access;
    FileMode   _mode;
#if 0
    FileOptions _options;
#endif
    size_t     _buffer_size;
};

}