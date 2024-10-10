#pragma once

#include "System/Diagnostics/TraceListener.hpp"


namespace System::Diagnostics
{

class DefaultTraceListener : public TraceListener
{
public:
    DefaultTraceListener();
   ~DefaultTraceListener();

    const std::string_view LogFileName() const;
          void             LogFileName(const std::string_view filename);

    void Close() override;
    void Flush() override;

    void Write(const std::string_view message) override;
    void Write(const std::string_view message, const std::string_view category) override;

    void WriteLine(const std::string_view message) override;
    void WriteLine(const std::string_view message, const std::string_view category) override;
    
    void Fail(const std::string_view message) override;
    void Fail(const std::string_view message, const std::string_view detail) override;

    void WriteIndent() override;
protected:
    std::string _logFileName;

    void WriteRaw(const std::string_view data);
    void WriteLineRaw(const std::string_view data);
};

}
