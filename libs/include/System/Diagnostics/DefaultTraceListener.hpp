#pragma once

#include "System/Diagnostics/TraceListener.hpp"


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
protected:
    std::string _logFileName;

    void WriteRaw(std::string_view data);
    void WriteLineRaw(std::string_view data);
};

}
