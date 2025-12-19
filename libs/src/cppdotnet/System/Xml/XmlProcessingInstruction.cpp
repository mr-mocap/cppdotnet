#include <cppdotnet/System/Xml/XmlProcessingInstruction.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <cppdotnet/System/Macros/Utils.hpp>
#include <format>


namespace
{

std::string GenerateOuterXml(std::string_view target, std::string_view data)
{
    return std::format( "<?{} {}?>", target, data );
}

}

namespace System::Xml
{

XmlProcessingInstruction::XmlProcessingInstruction(std::string_view target, std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   NodeConstructionParameters{ .local_name     = target,
                                               .name           = target,
                                               .owner_document = document }
                 )
{
    _outer_xml = GenerateOuterXml( Target(), Data() );

    INVARIANT( ChildNodes().Count() == 0 );
}

XmlProcessingInstruction::XmlProcessingInstruction(std::string_view target,
                                                   std::string_view data,
                                                   std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>(),
                   NodeConstructionParameters{ .local_name     = target,
                                               .name           = target,
                                               .owner_document = document }
                 ),
    _data( data )
{
    _outer_xml = GenerateOuterXml( Target(), Data() );

    INVARIANT( ChildNodes().Count() == 0 );
}

XmlProcessingInstruction::XmlProcessingInstruction(const XmlProcessingInstruction &other)
    :
    XmlLinkedNode( other ),
    _data( other._data )
{
    INVARIANT( ChildNodes().Count() == 0 );
}

XmlProcessingInstruction &XmlProcessingInstruction::operator =(const XmlProcessingInstruction &other)
{
    INVARIANT( ChildNodes().Count() == 0 );

    XmlLinkedNode::operator =( other );
    if (this != &other)
    {
        _data = other._data;
    }

    INVARIANT( ChildNodes().Count() == 0 );

    return *this;
}

XmlProcessingInstruction &XmlProcessingInstruction::operator =(XmlProcessingInstruction &&other)
{
    INVARIANT( ChildNodes().Count() == 0 );

    XmlLinkedNode::operator =( std::move( other ) );
    if (this != &other)
    {
        _data = other._data;
    }

    INVARIANT( ChildNodes().Count() == 0 );

    return *this;
}

std::shared_ptr<XmlNode> XmlProcessingInstruction::CloneNode(bool deep) const
{
    INVARIANT( ChildNodes().Count() == 0 );

    // TODO: Implement properly!
    if ( deep )
        return std::make_shared<XmlProcessingInstruction>( *this );
    else
        return std::make_shared<XmlProcessingInstruction>( *this );
}

void XmlProcessingInstruction::Data(std::string_view new_data)
{
    _data = new_data;
    _outer_xml = GenerateOuterXml( Target(), Data() );
}

std::string_view XmlProcessingInstruction::Value() const
{
    return _data;
}

void XmlProcessingInstruction::RemoveAll()
{
    INVARIANT( ChildNodes().Count() == 0 );
}

std::shared_ptr<XmlNode> XmlProcessingInstruction::RemoveChild(std::shared_ptr<XmlNode> old_child)
{
    INVARIANT( ChildNodes().Count() == 0 );

    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->RemoveChild( old_child );
}

std::shared_ptr<XmlNode> XmlProcessingInstruction::ReplaceChild(std::shared_ptr<XmlNode> new_child, std::shared_ptr<XmlNode> old_child)
{
    INVARIANT( ChildNodes().Count() == 0 );

    std::shared_ptr<Private::DefaultNodeListImplementation> children_as_derived_type = std::static_pointer_cast<Private::DefaultNodeListImplementation>( _children );

    return children_as_derived_type->ReplaceChild( new_child, old_child );
}

void XmlProcessingInstruction::WriteTo(XmlWriter &xml_writer) const
{
    INVARIANT( ChildNodes().Count() == 0 );

    // Check for invalid state(s)
    if ( xml_writer.WriteState() == Xml::WriteState::Start )
        xml_writer.WriteStartDocument();

    if ( xml_writer.WriteState() != Xml::WriteState::Prolog &&
         xml_writer.WriteState() != Xml::WriteState::Content )
    {
        // TODO: Check for more cases where writing a ProcessingInstruction is invalid
        ThrowWithTarget( InvalidOperationException("Cannot write XML processing instruction node.  Invalid write state.") );
    }

    Xml::WriteState current_state = xml_writer.WriteState();

    ASSERT( xml_writer.WriteState() != Xml::WriteState::Start );

    xml_writer.WriteRaw( OuterXml() );

    POSTCONDITION( xml_writer.WriteState() == current_state );
}

XmlNodeType XmlProcessingInstruction::_getNodeType() const
{
    return XmlNodeType::ProcessingInstruction;
}

}