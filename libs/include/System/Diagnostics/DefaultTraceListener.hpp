#include "System/Diagnostics/TraceListener.hpp"
#include "System/IO/StreamWriter.hpp"


namespace System::Diagnostics
{

class DefaultTraceListener : public TraceListener
{
public:
    DefaultTraceListener();
   ~DefaultTraceListener();

    std::string_view LogFileName() const;
    void             LogFileName(std::string_view filename);

    void Close() override;
    void Flush() override;

    void Write(std::string_view message) override;
    void Write(std::string_view message, std::string_view category) override;

    void WriteLine(std::string_view message) override;
    void WriteLine(std::string_view message, std::string_view category) override;
    
    void Fail(std::string_view message) override;
    void Fail(std::string_view message, std::string_view detail) override;

    void WriteIndent() override;

    bool AssertUiEnabled() const { return _ui_enabled; }
    void AssertUiEnabled(bool new_value) { _ui_enabled = new_value; }

protected:
    std::string _logFileName;
    std::string _line_buffer;
    std::unique_ptr<System::IO::StreamWriter> _log_stream;
    bool        _ui_enabled = false;

    void WriteRaw(std::string_view data);
    void WriteLineRaw(std::string_view data);
};

}
