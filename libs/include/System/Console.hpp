#pragma once

#include "System/IO/TextWriter.hpp"
#include "System/IO/TextReader.hpp"
#include "System/IO/ConsoleStream.hpp"
#include <memory>

namespace System
{

class Console final
{
public:

    static IO::TextReader &In();
    static IO::TextWriter &Out();
    static IO::TextWriter &Error();
    static IO::TextWriter &Log();

    static void SetIn(std::unique_ptr<IO::TextReader> &&new_input_reader);
    static void SetOut(std::unique_ptr<IO::TextWriter> &&new_input_writer);
    static void SetError(std::unique_ptr<IO::TextWriter> &&new_input_writer);
    static void SetLog(std::unique_ptr<IO::TextWriter> &&new_input_writer);

    static std::unique_ptr<IO::ConsoleStream> OpenStandardInput();
    static std::unique_ptr<IO::ConsoleStream> OpenStandardOutput();
    static std::unique_ptr<IO::ConsoleStream> OpenStandardError();
    static std::unique_ptr<IO::ConsoleStream> OpenStandardLog();

    static std::string ReadLine();

    static void Write(bool value);
    static void Write(char value);
    static void Write(int32_t value);
    static void Write(uint32_t value);
    static void Write(int64_t value);
    static void Write(uint64_t value);
    static void Write(float value);
    static void Write(double value);
    static void Write(const std::string_view data);

    static void WriteLine();
    static void WriteLine(bool value);
    static void WriteLine(char value);
    static void WriteLine(int32_t value);
    static void WriteLine(uint32_t value);
    static void WriteLine(int64_t value);
    static void WriteLine(uint64_t value);
    static void WriteLine(float value);
    static void WriteLine(double value);
    static void WriteLine(const std::string_view line);
};

}
