#include "TestBinaryWriter.hpp"
#include "System/Console.hpp"
#include "System/IO/MemoryStream.hpp"
#include "System/IO/BinaryWriter.hpp"
#include "System/IO/TextWriter.hpp"
#include "System/ReadOnlySpan.hpp"
#include <cassert>


namespace TestBinaryWriter
{

void DefaultConstructedEatsDataWritten()
{
    System::Console::Out().WriteLine(__func__);

    System::IO::BinaryWriter bw;

    assert( bw.OutStream().Length() == 0 );

    bw.Write( true );

    assert( bw.OutStream().Length() == 0 );

    bw.Write(2.0);

    assert( bw.OutStream().Length() == 0 );
}

void WriteBoolIncreasesOutputStreamLengthByOne()
{
    System::Console::Out().WriteLine(__func__);

    std::shared_ptr<System::IO::MemoryStream> mem_stream{ std::make_shared<System::IO::MemoryStream>() };
    System::IO::BinaryWriter bw( mem_stream );

    assert( bw.OutStream().Length() == 0 );

    bw.Write( true );

    std::string data = mem_stream->ToArray();

    assert( bw.OutStream().Length() == 1 );

    assert( data.size() == 1 );
    assert( data[0] == 0x01 );
}

void WriteCharIncreasesOutputStreamLengthByOne()
{
    System::Console::Out().WriteLine(__func__);

    std::shared_ptr<System::IO::MemoryStream> mem_stream{ std::make_shared<System::IO::MemoryStream>() };
    System::IO::BinaryWriter bw( mem_stream );

    assert( bw.OutStream().Length() == 0 );

    bw.Write('a');

    std::string data = mem_stream->ToArray();

    assert( bw.OutStream().Length() == 1 );

    assert( data.size() == 1 );
    assert( data[0] == 'a' );
}

void WriteReadOnlySpanWritesThoseBytes()
{
    System::Console::Out().WriteLine(__func__);

    std::shared_ptr<System::IO::MemoryStream> mem_stream{ std::make_shared<System::IO::MemoryStream>() };
    System::IO::BinaryWriter bw( mem_stream );

    assert( bw.OutStream().Length() == 0 );

    std::byte data_array[] = { std::byte{0}, std::byte{1}, std::byte{2}, std::byte{10} };

    bw.Write(data_array);

    std::string data = mem_stream->ToArray();

    assert( bw.OutStream().Length() == 4 );

    assert( data.size() == 4 );
    assert( data[0] == 0 );
    assert( data[1] == 1 );
    assert( data[2] == 2 );
    assert( data[3] == 10 );
}

void Run()
{
    System::Console::Out().WriteLine("Running BinaryWriter Tests...");

    DefaultConstructedEatsDataWritten();
    WriteBoolIncreasesOutputStreamLengthByOne();
    WriteCharIncreasesOutputStreamLengthByOne();
    WriteReadOnlySpanWritesThoseBytes();

    System::Console::Out().WriteLine("PASSED!");
}

}