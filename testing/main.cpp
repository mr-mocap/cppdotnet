#include "Diagnostics.hpp"
#include "TestDefaultTraceListener.hpp"
#include "TestConsoleTraceListener.hpp"
#include "TestConsole.hpp"
#include "TestDebug.hpp"
#include "TestException.hpp"
#include "TestEnvironment.hpp"
#include "TestVersion.hpp"
#include "TestStringReader.hpp"
#include "TestStringWriter.hpp"
#include "TestEnum.hpp"
#include "TestBitConverter.hpp"
#include "TestConvert.hpp"
#include "TestSpan.hpp"
#include "TestStringBuilder.hpp"
#include "TestInt32.hpp"
#include <cstdlib>
#include <iostream>


int main(void)
{
    std::cout << "Running Unit Tests!\n";

    TestDebug::Run();
    TestException::Run();
    TestEnvironment::Run();
    TestVersion::Run();
    TestStringReader::Run();
    TestStringWriter::Run();
    TestConsole::Run();
    TestDefaultTraceListener::Run();
    TestConsoleTraceListener::Run();
    TestEnum::Run();
    TestBitConverter::Run();
    TestConvert::Run();
    TestSpan::Run();
    TestStringBuilder::Run();
    TestInt32::Run();

    std::cout << "All tests passed!\n";

    return EXIT_SUCCESS;
}
