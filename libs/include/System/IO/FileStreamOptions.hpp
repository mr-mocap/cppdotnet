#include "System/IO/FileAccess.hpp"
#include "System/IO/FileMode.hpp"
#include "System/Nullable.hpp"
#include "System/IO/UnixFileMode.hpp"


namespace System::IO
{

class FileStreamOptions
{
public:

    FileAccess Access() const { return _access; }

    size_t     BufferSize() const { return _buffer_size; }

    FileMode   Mode() const { return _mode; }

    Nullable<UnixFileMode> UnixCreateMode() const { return _unix_file_mode; }
    void UnixCreateMode(Nullable<UnixFileMode> ufm)
    {
        _unix_file_mode = ufm;
    }
#if 0
    const FileOptions &Options() const { return _options; }
#endif

    bool operator ==(const FileStreamOptions &other) const
    {
        return (_access == other._access) &&
               (_mode == other._mode) &&
               (_unix_file_mode == other._unix_file_mode);
    }
protected:
    size_t     _buffer_size = 0;
    FileAccess _access = FileAccess::ReadWrite;
    FileMode   _mode   = FileMode::Open;
    Nullable<UnixFileMode> _unix_file_mode;
#if 0
    FileOptions _options;
#endif

};

}