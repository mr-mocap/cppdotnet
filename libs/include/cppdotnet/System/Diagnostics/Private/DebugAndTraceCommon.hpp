#pragma once

#include <cppdotnet/System/Diagnostics/TraceListenerCollection.hpp>
#include <cppdotnet/System/Diagnostics/DefaultTraceListener.hpp>
#include <set>
#include <string>
#include <string_view>
#include <mutex>
#include <memory>
#include <source_location>


namespace System::Diagnostics::Private
{

class ITracer
{
public:
    ITracer() = default;
    ITracer(std::string_view name)
        :
        _name(name)
    {
    }
    
    // No copying/moving
    ITracer(const ITracer &) = delete;
    ITracer operator =(const ITracer &) = delete;

    virtual ~ITracer() = default;
    
    TraceListenerCollection &Listeners() { return _listeners; }

    std::string_view Name() const { return _name; }

    virtual bool UseGlobalLock();
    virtual void UseGlobalLock(bool new_value);

    virtual int  IndentLevel() = 0;
    virtual void IndentLevel(int new_value) = 0;

    virtual int  IndentSize() = 0;
    virtual void IndentSize(int new_value) = 0;

    virtual void Indent() = 0;
    virtual void Unindent() = 0;

    virtual void Flush() = 0;
    virtual void Close() = 0;

    virtual bool AutoFlush() = 0;
    virtual void AutoFlush(bool new_value) = 0;

    virtual void Write(std::string_view message) = 0;
    virtual void Write(std::string_view message, std::string_view category) = 0;

    virtual void WriteLine(std::string_view message) = 0;
    virtual void WriteLine(std::string_view message, std::string_view category) = 0;

    void WriteIf(bool condition, std::string_view message);
    void WriteIf(bool condition, std::string_view message, std::string_view category);

    void WriteLineIf(bool condition, std::string_view message);
    void WriteLineIf(bool condition, std::string_view message, std::string_view category);

    virtual void Assert(bool condition, const std::source_location) = 0;
    virtual void Assert(bool condition, std::string_view message, const std::source_location) = 0;
    virtual void Assert(bool condition,
                        std::string_view message,
                        std::string_view detail_message,
                        const std::source_location) = 0;

    virtual void Fail(std::string_view message) = 0;
    virtual void Fail(std::string_view message, std::string_view category) = 0;
protected:
    TraceListenerCollection _listeners;
    std::string _name = "DefaultTracer";
    bool _useGlobalLock = true;
};

class GlobalTracer : public ITracer
{
public:
    GlobalTracer();
    GlobalTracer(std::string_view name);
    
    // No copying/moving
    GlobalTracer(const GlobalTracer &) = delete;
    GlobalTracer operator =(const GlobalTracer &) = delete;

   ~GlobalTracer() override = default;

    static ITracer &Instance();

    int  IndentLevel() override;
    void IndentLevel(int new_value) override;

    int  IndentSize() override;
    void IndentSize(int new_value) override;

    void Indent() override;
    void Unindent() override;

    void Flush() override;
    void Close() override;

    bool AutoFlush() override;
    void AutoFlush(bool new_value) override;

    void Write(std::string_view message) override;
    void Write(std::string_view message, std::string_view category) override;

    void WriteLine(std::string_view message) override;
    void WriteLine(std::string_view message, std::string_view category) override;

    void Assert(bool condition, const std::source_location) override;
    void Assert(bool condition, std::string_view message, const std::source_location) override;
    void Assert(bool condition,
                std::string_view message,
                std::string_view detail_message,
                const std::source_location) override;

    void Fail(std::string_view message) override;
    void Fail(std::string_view message, std::string_view category) override;
protected:
    int  _indentLevel = 0;
    int  _indentSize  = 4;
    bool _autoFlush   = false;
    std::string _indentString;

    bool NeedIndent();
};

}