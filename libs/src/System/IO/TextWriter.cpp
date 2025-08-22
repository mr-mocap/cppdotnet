#include "System/IO/TextWriter.hpp"
#include "System/Convert.hpp"
#include <string_view>


namespace System::IO
{

TextWriter::~TextWriter()
{
}

void TextWriter::Close()
{
}

void TextWriter::Flush()
{
}

void TextWriter::Write(bool value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(int16_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(uint16_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(int32_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(uint32_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(int64_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(uint64_t value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(float value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::Write(double value)
{
    Write( Convert::ToString(value) );
}

void TextWriter::WriteLine(std::string_view message)
{
    Write( message );
    Write( NewLine() );
}

void TextWriter::WriteLine(bool value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(char value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(int16_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(uint16_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(int32_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(uint32_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(int64_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(uint64_t value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(float value)
{
    Write( value );
    Write( NewLine() );
}

void TextWriter::WriteLine(double value)
{
    Write( value );
    Write( NewLine() );
}

}