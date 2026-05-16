add_library(cppdotnet_base)

# The Guid class depends on this
# NOTE: How do we include the Copyright?
find_package(PkgConfig REQUIRED)
pkg_check_modules(UUID REQUIRED uuid)

target_include_directories(cppdotnet_base PUBLIC ${UUID_INCLUDE_DIRS})
target_link_libraries(cppdotnet_base ${UUID_LIBRARIES})

target_sources(cppdotnet_base
        PRIVATE
            src/cppdotnet/System/Action.cpp
            src/cppdotnet/System/Boolean.cpp
            src/cppdotnet/System/Byte.cpp
            src/cppdotnet/System/Comparison.cpp
            src/cppdotnet/System/Convert.cpp
            src/cppdotnet/System/Converter.cpp
            src/cppdotnet/System/DateOnly.cpp
            src/cppdotnet/System/DateTime.cpp
            src/cppdotnet/System/DateTimeOffset.cpp
            src/cppdotnet/System/Enum.cpp
            src/cppdotnet/System/Environment.cpp
            src/cppdotnet/System/EventHandler.cpp
            src/cppdotnet/System/Exception.cpp
            src/cppdotnet/System/Func.cpp
            src/cppdotnet/System/Guid.cpp
            src/cppdotnet/System/Int16.cpp
            src/cppdotnet/System/Int32.cpp
            src/cppdotnet/System/Int64.cpp
            src/cppdotnet/System/Nullable.cpp
            src/cppdotnet/System/OperatingSystem.cpp
            src/cppdotnet/System/Predicate.cpp
            src/cppdotnet/System/ReadOnlySpan.cpp
            src/cppdotnet/System/Span.cpp
            src/cppdotnet/System/TimeOnly.cpp
            src/cppdotnet/System/TimeSpan.cpp
            src/cppdotnet/System/UInt16.cpp
            src/cppdotnet/System/UInt32.cpp
            src/cppdotnet/System/UInt64.cpp
            src/cppdotnet/System/ValueTuple.cpp
            src/cppdotnet/System/Version.cpp
            src/cppdotnet/System/Text/StringBuilder.cpp
               
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS
            include
        FILES
            include/cppdotnet/System/Action.hpp
            include/cppdotnet/System/Base.hpp
            include/cppdotnet/System/Base64FormattingOptions.hpp
            include/cppdotnet/System/BitConverter.hpp
            include/cppdotnet/System/Boolean.hpp
            include/cppdotnet/System/Byte.hpp
            include/cppdotnet/System/Comparison.hpp
            include/cppdotnet/System/Concepts.hpp
            include/cppdotnet/System/Convert.hpp
            include/cppdotnet/System/Converter.hpp
            include/cppdotnet/System/DateOnly.hpp
            include/cppdotnet/System/DateTime.hpp
            include/cppdotnet/System/DateTimeKind.hpp
            include/cppdotnet/System/DateTimeOffset.hpp
            include/cppdotnet/System/DayOfWeek.hpp
            include/cppdotnet/System/Enum.hpp
            include/cppdotnet/System/Environment.hpp
            include/cppdotnet/System/EnvironmentVariableTarget.hpp
            include/cppdotnet/System/EventArgs.hpp
            include/cppdotnet/System/EventHandler.hpp
            include/cppdotnet/System/Exception.hpp
            include/cppdotnet/System/Func.hpp
            include/cppdotnet/System/Guid.hpp
            include/cppdotnet/System/IComparable.hpp
            include/cppdotnet/System/IConvertible.hpp
            include/cppdotnet/System/IDisposable.hpp
            include/cppdotnet/System/IEquatable.hpp
            include/cppdotnet/System/IFormattable.hpp
            include/cppdotnet/System/Int16.hpp
            include/cppdotnet/System/Int32.hpp
            include/cppdotnet/System/Int64.hpp
            include/cppdotnet/System/IObservable.hpp
            include/cppdotnet/System/IObserver.hpp
            include/cppdotnet/System/IProgress.hpp
            include/cppdotnet/System/Math.hpp
            include/cppdotnet/System/Nullable.hpp
            include/cppdotnet/System/Numerics.hpp
            include/cppdotnet/System/OperatingSystem.hpp 
            include/cppdotnet/System/PlatformID.hpp
            include/cppdotnet/System/Predicate.hpp
            include/cppdotnet/System/Progress.hpp
            include/cppdotnet/System/ReadOnlySpan.hpp
            include/cppdotnet/System/Span.hpp
            include/cppdotnet/System/Text.hpp
            include/cppdotnet/System/TimeOnly.hpp
            include/cppdotnet/System/TimeSpan.hpp
            include/cppdotnet/System/TypeCode.hpp
            include/cppdotnet/System/UInt16.hpp
            include/cppdotnet/System/UInt32.hpp
            include/cppdotnet/System/UInt64.hpp
            include/cppdotnet/System/ValueTuple.hpp
            include/cppdotnet/System/Version.hpp
            include/cppdotnet/System/Macros/Assert.hpp
            include/cppdotnet/System/Macros/Contracts.hpp
            include/cppdotnet/System/Macros/Utils.hpp
            include/cppdotnet/System/Numerics/INumber.hpp
            include/cppdotnet/System/Numerics/INumberBase.hpp
            include/cppdotnet/System/Private/Delegate.hpp
            include/cppdotnet/System/Private/enum.hpp
            include/cppdotnet/System/Private/IntCommon.hpp
            include/cppdotnet/System/Text/StringBuilder.hpp
)