import "System/IO/Stream.hpp";
import "System/IO/FileMode.hpp";

namespace System::IO
{

class FileStream : public Stream
{
public:
    FileStream(std::string_view filename);
    FileStream(std::string_view filename, const FileMode mode);
   ~FileStream();

protected:
    void _close() override;
};

}