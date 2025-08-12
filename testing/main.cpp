import "Diagnostics.hpp";
import "TestDefaultTraceListener.hpp";
import "TestConsoleTraceListener.hpp";
import "TestConsole.hpp";
import "TestTrace.hpp";
import "TestDebug.hpp";
import "TestException.hpp";
import "TestEnvironment.hpp";
import "TestVersion.hpp";
import "TestStringReader.hpp";
import "TestStringWriter.hpp";
import "TestEnum.hpp";
import "TestBitConverter.hpp";
import "TestConvert.hpp";
import "TestSpan.hpp";
import "TestReadOnlySpan.hpp";
import "TestStringBuilder.hpp";
import "TestInt32.hpp";
import "TestNullable.hpp";
import "TestDelegates.hpp";
import "TestLinkedList.hpp";
import "TestList.hpp";
import "TestTimeSpan.hpp";
import "TestDateTime.hpp";
import "TestICollection.hpp";
import "TestIDictionary.hpp";
import "TestIList.hpp";
import "TestDictionary.hpp";
import "TestTimeOnly.hpp";
import "TestDateTimeOffset.hpp";
import "TestDateOnly.hpp";
import "TestStack.hpp";
import "TestPath.hpp";
import "TestValueTuple.hpp";
import "TestBinaryWriter.hpp";
import "TestStopwatch.hpp";
import "TestCounter.hpp";
import "TestGuid.hpp";
import <cstdlib>;
import <iostream>;


int main(void)
{
    std::cout << "Running Unit Tests!\n";

    TestDebug::Run();
    TestTrace::Run();
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
    TestIDictionary::Run();
    TestIList::Run();
    TestTimeOnly::Run();
    TestDateTimeOffset::Run();
    TestDateOnly::Run();
    TestStack::Run();
    TestPath::Run();
    TestValueTuple::Run();
    TestBinaryWriter::Run();
    TestStopwatch::Run();
    TestCounter::Run();
    TestGuid::Run();

    std::cout << "All tests passed!\n";

    return EXIT_SUCCESS;
}
