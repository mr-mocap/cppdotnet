#include <cppdotnet/System/Xml/XmlProcessingInstruction.hpp>
#include "UnitTesting.hpp"
#include "XmlNodeTestFixture.hpp"
#include <cstdlib>


namespace TestXmlProcessingInstruction
{

void XmlProcessingInstructionWithOnlyTarget()
{
    System::Xml::XmlProcessingInstruction node("target", nullptr);

    assert( node.Name() == "target" );
    assert( node.Value() == "" );
    assert( node.OuterXml() == "<?target ?>");
    assert( node.OwnerDocument() == nullptr );
}

void XmlProcessingInstructionWithTargetAndData()
{
    System::Xml::XmlProcessingInstruction node("target", "data", nullptr);

    assert( node.Name() == "target" );
    assert( node.Value() == "data" );
    assert( node.OuterXml() == "<?target data?>");
    assert( node.OwnerDocument() == nullptr );
}

void Run()
{
    XmlProcessingInstructionWithOnlyTarget();
    XmlProcessingInstructionWithTargetAndData();
}

}

int main(void)
{
    TestXmlProcessingInstruction::Run();
    return EXIT_SUCCESS;
}