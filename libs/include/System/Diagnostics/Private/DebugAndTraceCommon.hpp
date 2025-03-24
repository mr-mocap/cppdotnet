#pragma once

#include "System/Diagnostics/TraceListenerCollection.hpp"
#include "System/Diagnostics/DefaultTraceListener.hpp"
#include "System/Diagnostics/Private/DebugAndTraceCommon.hpp"
#include <set>
#include <string>
#include <mutex>
#include <memory>
#include <source_location>


namespace System::Diagnostics::Private
{

class TraceListener;

class DebugAndTraceCommon
{
public:
    DebugAndTraceCommon();
   ~DebugAndTraceCommon();

    DebugAndTraceCommon(const DebugAndTraceCommon &) = delete;
    DebugAndTraceCommon operator =(const DebugAndTraceCommon &) = delete;
    DebugAndTraceCommon(DebugAndTraceCommon &&) = delete;
    DebugAndTraceCommon operator =(const DebugAndTraceCommon &&) = delete;

    static DebugAndTraceCommon &Instance();

    TraceListenerCollection &Listeners() { return _listeners; }

    bool UseGlobalLock();
    void UseGlobalLock(bool new_value);

    static int  IndentLevel();
    static void IndentLevel(int new_value);

    static int  IndentSize();
    static void IndentSize(int new_value);

    static void Indent();
    static void Unindent();

    static void Flush();
    static void Close();

    static bool AutoFlush();
    static void AutoFlush(bool new_value);

    static void Write(const std::string_view message);
    static void Write(const std::string_view message, const std::string_view category);

    static void WriteLine(const std::string_view message);
    static void WriteLine(const std::string_view message, const std::string_view category);

    static void WriteIf(bool condition, const std::string_view message);
    static void WriteIf(bool condition, const std::string_view message, const std::string_view category);

    static void WriteLineIf(bool condition, const std::string_view message);
    static void WriteLineIf(bool condition, const std::string_view message, const std::string_view category);

    static void Assert(bool condition, const std::source_location);
    static void Assert(bool condition, const std::string_view message, const std::source_location);
    static void Assert(bool condition,
                       const std::string_view message,
                       const std::string_view category,
                       const std::source_location);

    static void Fail(const std::string_view message);
    static void Fail(const std::string_view message, const std::string_view category);

    // Methods for Debug class
    static void Print(const std::string_view message);

    // Methods for Trace class
    static void TraceError(const std::string_view message);
    static void TraceWarning(const std::string_view message);
    static void TraceInformation(const std::string_view message);

protected:
    TraceListenerCollection _listeners;
    bool _useGlobalLock = true;

    static int  _indentLevel;
    static int  _indentSize;
    static bool _autoFlush;
    static std::string _indentString;

    static bool NeedIndent();
};

}