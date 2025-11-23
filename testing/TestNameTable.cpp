#include <cppdotnet/System/Xml/NameTable.hpp>
#include <cppdotnet/System/Exception.hpp>
#include <cstdlib>
#include <cassert>

namespace TestNameTable
{

void DefaultConstructedContainsNoNames()
{
    System::Xml::NameTable nameTable;

    assert( nameTable.Get( "example" ).empty() );
    assert( nameTable.Get( "stuff" ).empty() );
    assert( nameTable.Get( "we can never fully test this" ).empty() );
}

void AddedNamesCanBeRetrieved()
{
    System::Xml::NameTable nameTable;

    std::string_view name1 = nameTable.Add( "example" );
    std::string_view name2 = nameTable.Add( "stuff" );

    assert( nameTable.Get( "example" ) == name1 );
    assert( nameTable.Get( "stuff" )   == name2 );
}

void AddingAnEmptyStringThrowsAnArgumentNullException()
{
    System::Xml::NameTable nameTable;

    try
    {
        nameTable.Add( "" );
        assert( false ); // Should not reach here
    }
    catch ( const System::ArgumentNullException & )
    {
        // Expected
        assert( true );
    }
    assert( true );
}

void GettingAnEmptyStringThrowsAnArgumentNullException()
{
    System::Xml::NameTable nameTable;

    try
    {
        nameTable.Get( "" );
        assert( false ); // Should not reach here
    }
    catch ( const System::ArgumentNullException & )
    {
        // Expected
        assert( true );
    }
    assert( true );
}

void Run()
{
    DefaultConstructedContainsNoNames();
    AddedNamesCanBeRetrieved();
    AddingAnEmptyStringThrowsAnArgumentNullException();
    GettingAnEmptyStringThrowsAnArgumentNullException();
}

}

int main(void)
{
    TestNameTable::Run();

    return EXIT_SUCCESS;
}