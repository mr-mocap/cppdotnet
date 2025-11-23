#include <cppdotnet/System/Xml/XmlDocument.hpp>
#include <cppdotnet/System/Xml/NameTable.hpp>
#include <cstdlib>
#include <cassert>


namespace TestXmlDocument
{

void DefaultConstructed()
{
    System::Xml::XmlDocument d;

    assert( d.NameTable().empty() );
}

void ConstructWithReferenceToExternalNameTableCopiesTheExternalTable()
{
    System::Xml::NameTable nt;

    nt.Add( "Name" );

    assert( !nt.empty() );
    assert( nt.Get( "Name" ) == "Name" ); // "Name" is in there

    System::Xml::XmlDocument d( nt );

    // Test if they both contain the same data in the two NameTables
    assert( !d.NameTable().empty() );
    assert( d.NameTable().Get( "Name" ) == "Name" );

    // Add a new name into the external NameTable;
    nt.Add( "Test" );
    assert( nt.Get( "Test" ) == "Test" );

    // Demonstrate that the Document's NameTable is unaffected
    assert( d.NameTable().Get( "Test" ).empty() );
}

void ConstructWithSharedPointerToExternalNameTableRefersToTheExternalNameTable()
{
    std::shared_ptr<System::Xml::XmlNameTable> external_name_table = std::make_shared<System::Xml::NameTable>();

    assert( external_name_table->empty() );

    System::Xml::XmlDocument d( external_name_table );

    assert( d.NameTable().empty() );

    // Now, let's add something to the external table
    external_name_table->Add( "Test" );

    // Demonstrate that it was added...
    assert( external_name_table->Get( "Test" ) == "Test" );

    // Demonstrate that the Document's NameTable is also changed.
    assert( d.NameTable().Get( "Test" ) == "Test" );
}

void Run()
{
    DefaultConstructed();
    ConstructWithReferenceToExternalNameTableCopiesTheExternalTable();
    ConstructWithSharedPointerToExternalNameTableRefersToTheExternalNameTable();
}

}

int main(void)
{
    TestXmlDocument::Run();
    return EXIT_SUCCESS;
}