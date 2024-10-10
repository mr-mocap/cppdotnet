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
#include <cstdlib>
#include <iostream>


int main(void)
{
    std::cout << "Running Unit Tests!\n";

#if 1
    TestDebug::Run();
    TestException::Run();
    TestEnvironment::Run();
    TestVersion::Run();
#endif
    TestStringReader::Run();
    TestStringWriter::Run();
#if 1
    TestConsole::Run();
    TestDefaultTraceListener::Run();
    TestConsoleTraceListener::Run();
#endif

    std::cout << "All tests passed!\n";

    return EXIT_SUCCESS;
}
