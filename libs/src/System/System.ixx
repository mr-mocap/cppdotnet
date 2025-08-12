module;
// Global Module Fragment: #include, preprocessor directives

export module System;

// Module Preamble: Imports

// Import Header Units...
//
// NOTE: These are ORDERED

// Things that depend on NOTHING...
export import "System/EventArgs.hpp";

// Things that only depend on system-headers...
export import "System/IDisposable.hpp";
export import "System/Exception.hpp";
export import "System/Version.hpp";
export import "System/ValueTuple.hpp";
export import "System/Private/Delegate.hpp";
export import "System/Private/enum.hpp";
export import "System/TimeSpan.hpp";

// Depends on System/Private/Delegate.hpp...
export import "System/Action.hpp";
export import "System/Comparison.hpp";
export import "System/Converter.hpp";
export import "System/Func.hpp";
export import "System/Predicate.hpp";

// Depends on System/Private/enum.hpp...
export import "System/Base.hpp";
export import "System/Base64FormattingOptions.hpp";
export import "System/ConsoleColor.hpp";
export import "System/ConsoleKey.hpp";
export import "System/ConsoleModifiers.hpp";
export import "System/DateTimeKind.hpp";
export import "System/DayOfWeek.hpp";
export import "System/EnvironmentVariableTarget.hpp";
export import "System/EventHandler.hpp";
export import "System/PlatformID.hpp";
export import "System/TypeCode.hpp";

// Depends on Other System/. files...
export import "System/BitConverter.hpp";
export import "System/Convert.hpp";
export import "System/ConsoleKeyInfo.hpp";
export import "System/Span.hpp";
export import "System/ReadOnlySpan.hpp";
export import "System/Nullable.hpp";
export import "System/Guid.hpp";
export import "System/Enum.hpp";
export import "System/OperatingSystem.hpp";
export import "System/IObserver.hpp";
export import "System/IObservable.hpp";
export import "System/TimeOnly.hpp";

// Not Included Yet!
//export import "Boolean.hpp";
//export import "Byte.hpp";
//export import "Concepts.hpp";
//export import "Console.hpp";
//export import "Convert.hpp";
//export import "DateOnly.hpp";
//export import "DateTime.hpp";
//export import "DateTimeOffset.hpp";
//export import "Environment.hpp";
//export import "Int16.hpp";
//export import "Int32.hpp";
//export import "Int64.hpp";
//export import "Math.hpp";
//export import "TimeCode.hpp";

//export import "IO/BinaryWriter.hpp";
//export import "IO/ConsoleStream.hpp";
//export import "IO/FileAccess.hpp";
//export import "IO/FileMode.hpp";
//export import "IO/FileStream.hpp";
//export import "IO/FileStreamOptions.hpp";
//export import "IO/IOException.hpp";
//export import "IO/MatchCasing.hpp";
//export import "IO/MatchType.hpp";
//export import "IO/MemoryStream.hpp";
//export import "IO/NullStream.hpp";
//export import "IO/Path.hpp";
//export import "IO/SeekOrigin.hpp";
//export import "IO/Stream.hpp";
//export import "IO/StreamReader.hpp";
//export import "IO/StreamWriter.hpp";
//export import "IO/StringReader.hpp";
//export import "IO/StringWriter.hpp";
//export import "IO/TextReader.hpp";
//export import "IO/TextWriter.hpp";
//export import "IO/UnixFileMode.hpp";

//export import "Diagnostics/Activity.hpp";
//export import "Diagnostics/ActivityListener.hpp";
//export import "Diagnostics/ActivitySamplingResult.hpp";
//export import "Diagnostics/ActivitySource.hpp";
//export import "Diagnostics/ActivitySpanId.hpp";
//export import "Diagnostics/ActivityTraceId.hpp";
//export import "Diagnostics/BooleanSwitch.hpp";
//export import "Diagnostics/ConsoleTraceListener.hpp";
//export import "Diagnostics/Debug.hpp";
//export import "Diagnostics/Debugger.hpp";
//export import "Diagnostics/DefaultTraceListener.hpp";
//export import "Diagnostics/DiagnosticListener.hpp";
//export import "Diagnostics/DiagnosticSource.hpp";
//export import "Diagnostics/EventTypeFilter.hpp";
//export import "Diagnostics/SampleActivity.hpp";
//export import "Diagnostics/SourceFilter.hpp";
//export import "Diagnostics/SourceLevels.hpp";
//export import "Diagnostics/SourceSwitch.hpp";
//export import "Diagnostics/Stopwatch.hpp";
//export import "Diagnostics/Switch.hpp";
//export import "Diagnostics/TextWriterTraceListener.hpp";
//export import "Diagnostics/Trace.hpp";
//export import "Diagnostics/TraceEventCache.hpp";
//export import "Diagnostics/TraceEventType.hpp";
//export import "Diagnostics/TraceFilter.hpp";
//export import "Diagnostics/TraceLevel.hpp";
//export import "Diagnostics/TraceListener.hpp";
//export import "Diagnostics/TraceListenerCollection.hpp";
//export import "Diagnostics/TraceOptions.hpp";
//export import "Diagnostics/TraceSource.hpp";
//export import "Diagnostics/TraceSwitch.hpp";
//export import "Diagnostics/Private/DebugAndTraceCommon.hpp";
