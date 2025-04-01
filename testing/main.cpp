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
#include "TestReadOnlySpan.hpp"
#include "TestStringBuilder.hpp"
#include "TestInt32.hpp"
#include "TestNullable.hpp"
#include "TestDelegates.hpp"
#include "TestLinkedList.hpp"
#include "TestList.hpp"
#include "TestTimeSpan.hpp"
#include "TestDateTime.hpp"
#include "TestICollection.hpp"
#include "TestDictionary.hpp"
#include "TestTimeOnly.hpp"
#include "TestDateTimeOffset.hpp"
#include "TestDateOnly.hpp"
#include "TestStack.hpp"
#include "TestPath.hpp"
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
    TestReadOnlySpan::Run();
    TestStringBuilder::Run();
    TestInt32::Run();
    TestNullable::Run();
    TestDelegates::Run();
    TestLinkedList::Run();
    TestList::Run();
    TestTimeSpan::Run();
    TestDateTime::Run();
    TestICollection::Run();
    TestDictionary::Run();
    TestTimeOnly::Run();
    TestDateTimeOffset::Run();
    TestDateOnly::Run();
    TestStack::Run();
    TestPath::Run();

    std::cout << "All tests passed!\n";

    return EXIT_SUCCESS;
}
