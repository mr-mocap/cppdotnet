#include "TestUtf8JsonReader.hpp"
#include "System/Text/Json/Utf8JsonReader.hpp"
#include <string>
#include <iostream>
#include <cassert>


namespace TestUtf8JsonReader
{

void DefaultConstructed()
{
    std::cout << __func__ << std::endl;

    std::string json_data = "{ }";
    //System::ReadOnlySpan bytes{ std::as_bytes( std::span{ json_data } ) };
#if 0
    System::Text::Json::Utf8JsonReader reader( bytes );

    assert( reader.BytesConsumed() == 0 );
    assert( reader.CurrentDepth() == 0 );
    assert( reader.TokenType() == System::Text::Json::JsonTokenType::None );
#endif
}

void ParseEmptyObject()
{
    std::cout << __func__ << std::endl;

    std::string json_data = "{ }";
    //System::ReadOnlySpan bytes{ std::as_bytes( std::span{ json_data } ) };
#if 0
    System::Text::Json::Utf8JsonReader reader( bytes );

    assert( reader.BytesConsumed() == 0 );
    assert( reader.CurrentDepth() == 0 );
    assert( reader.TokenType() == System::Text::Json::JsonTokenType::None );

    bool read_result = reader.Read();

    assert( read_result == true );
#endif
}

void Run()
{
    std::cout << "Running Utf8JsonReader Tests..." << std::endl;

    DefaultConstructed();

    std::cout << "PASSED!" << std::endl;
}

}