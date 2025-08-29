export module System;

// Module Preamble: Imports

// Import Header Units...
//
// NOTE: These are ORDERED

// Things that depend on NOTHING...
export import :EventArgs;
export import :IComparable;

// Things that only depend on system-headers...
// export import :IDisposable;
export import :Exception;
// export import :Version;
export import :Delegate;
export import :Private_enum;
export import :ValueTuple;
// export import :TimeSpan;

// Depends on System/Private/Delegate.hpp...
export import :Action;
export import :Comparison;
export import :Converter;
export import :Func;
export import :Predicate;
export import :EventHandler;

// Depends on System/Private/enum.hpp...
export import :Base;
export import :Base64FormattingOptions;
export import :ConsoleColor;
export import :ConsoleModifiers;
export import :ConsoleKey;
export import :DateTimeKind;
export import :DayOfWeek;
export import :EnvironmentVariableTarget;
export import :PlatformID;
export import :TypeCode;

// Depends on Other System/. files...
// export import :BitConverter;
// export import "System/Convert.hpp";
// export import :ConsoleKeyInfo;
// export import :Span;
// export import :ReadOnlySpan;
// export import :Nullable;
// export import :Guid;
// export import :IConvertible;
// export import :Enum;
// export import :OperatingSystem;
// export import :IObserver;
// export import :IObservable;

// Not Included Yet!
//export import "Boolean.hpp";
//export import "Byte.hpp";
export import :Concepts;
//export import "Console.hpp";

// export import :TimeOnly;
// export import :DateOnly;
// export import :DateTime;
// export import :DateTimeOffset;

// export import :Environment;
//export import "Int16.hpp";
//export import "Int32.hpp";
//export import "Int64.hpp";

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