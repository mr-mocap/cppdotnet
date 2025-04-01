#include "TestPath.hpp"
#include "System/IO/Path.hpp"
#include <iostream>
#include <cassert>


namespace TestPath
{

void ChangeExtension()
{
    std::cout << __func__ << std::endl;

    // Remove the extension
    assert( System::IO::Path::ChangeExtension("/this/is/a/path.txt") == "/this/is/a/path" );

    // Change it
    assert( System::IO::Path::ChangeExtension("/this/is/a/path.txt", ".pdf") == "/this/is/a/path.pdf" );
    assert( System::IO::Path::ChangeExtension("/this/is/a/path.txt", "pdf") == "/this/is/a/path.pdf" );

    // Edge Cases
    assert( System::IO::Path::ChangeExtension( "", "" ) == "" );
    assert( System::IO::Path::ChangeExtension( "", ".ext" ) == "" );
    assert( System::IO::Path::ChangeExtension( "some_path", ".ext" ) == "some_path.ext" );
    assert( System::IO::Path::ChangeExtension( "some_path", "ext" ) == "some_path.ext" );
}

void CombineTwo()
{
    using namespace System::IO;

    std::cout << __func__ << std::endl;

    assert( Path::Combine("a", "b") == "a/b");
    assert( Path::Combine("/a", "b") == "/a/b");

    // Path2 has a root, so Path2 is returned
    assert( Path::Combine("a", "/b") == "/b");
    assert( Path::Combine("/a", "/b") == "/b");

    // Path1 ends with a directory separator
    assert( Path::Combine("a/","b") == "a/b" );

    // Path1 ends with a directory separator
    assert( Path::Combine("a:","b") == "a:/b" );

    // Paths contain spaces
    assert( Path::Combine("a", " /b") == "a /b" );
    assert( Path::Combine("a ", "/b") == "a /b" );
    assert( Path::Combine(" a ", "/b") == " a /b" );
}

void EndsInDirectorySeparator()
{
    using namespace System::IO;

    std::cout << __func__ << std::endl;

    assert( Path::EndsInDirectorySeparator("a/") );
    assert( !Path::EndsInDirectorySeparator("a:") );
    assert( !Path::EndsInDirectorySeparator("a") );
    assert( !Path::EndsInDirectorySeparator("") );
}

void Run()
{
    std::cout << "Running Path Tests..." << std::endl;

    ChangeExtension();
    CombineTwo();
    EndsInDirectorySeparator();

    std::cout << "PASSED!" << std::endl;
}

}