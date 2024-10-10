#pragma once

#include "System/IO/TextWriter.hpp"

namespace System
{

class Console final
{
public:

    //static IO::TextReader &In();
    static IO::TextWriter &Out();
    static IO::TextWriter &Error();
    static IO::TextWriter &Log();

    static std::string ReadLine();

    static void Write(bool value);
    static void Write(const std::string_view data);

    static void WriteLine();
    static void WriteLine(bool value);
    static void WriteLine(const std::string_view line);
};

}
