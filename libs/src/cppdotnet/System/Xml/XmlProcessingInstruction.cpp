#include <cppdotnet/System/Xml/XmlProcessingInstruction.hpp>
#include <cppdotnet/System/Xml/XmlWriter.hpp>
#include <cppdotnet/System/Xml/Private/DefaultNodeListImplementation.hpp>
#include <cppdotnet/System/Macros/Contracts.hpp>
#include <cppdotnet/System/Macros/Utils.hpp>

namespace System::Xml
{

XmlProcessingInstruction::XmlProcessingInstruction()
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() )
{
    INVARIANT( ChildNodes().Count() == 0 );
}

XmlProcessingInstruction::XmlProcessingInstruction(std::string_view target, std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _target( target ),
    _document( document )
{
    INVARIANT( ChildNodes().Count() == 0 );
}

XmlProcessingInstruction::XmlProcessingInstruction(std::string_view target,
                                                       std::string_view data,
                                                       std::shared_ptr<XmlDocument> document)
    :
    XmlLinkedNode( std::make_shared<Private::DefaultNodeListImplementation>() ),
    _target( target ),
    _data( data ),
    _document( document )
{
    INVARIANT( ChildNodes().Count() == 0 );
}

XmlProcessingInstruction::XmlProcessingInstruction(const XmlProcessingInstruction &other)
    :
    XmlLinkedNode( other._children->MemberwiseClone() ),
    _target( other._target ),
    _data( other._data ),
    _document( other._document )
{
    INVARIANT( ChildNodes().Count() == 0 );
}

XmlProcessingInstruction &XmlProcessingInstruction::operator =(const XmlProcessingInstruction &other)
{
    INVARIANT( ChildNodes().Count() == 0 );

    if (this != &other)
    {
        _target = other._target;
        _data   = other._data;
        _document = other._document;
        _children = other._children->MemberwiseClone();
    }
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

std::string_view XmlProcessingInstruction::LocalName() const
{
    INVARIANT( ChildNodes().Count() == 0 );

    return { };
}

std::string_view XmlProcessingInstruction::Name() const
{
    INVARIANT( ChildNodes().Count() == 0 );

    return { };
}

std::string_view XmlProcessingInstruction::NamespaceURI() const
{
    INVARIANT( ChildNodes().Count() == 0 );

    return { };
}

std::shared_ptr<XmlDocument> XmlProcessingInstruction::OwnerDocument() const
{
    INVARIANT( ChildNodes().Count() == 0 );

    return _document;
}

std::string_view XmlProcessingInstruction::Prefix() const
{
    INVARIANT( ChildNodes().Count() == 0 );

    return { };
}

void XmlProcessingInstruction::Prefix(std::string_view new_prefix)
{
    UNUSED( new_prefix );
    INVARIANT( ChildNodes().Count() == 0 );
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

    if ( Data().empty() )
    {
        std::string data = std::format("<?{}?>", Target() );

        xml_writer.WriteRaw( data );
    }
    else
    {
        std::string data = std::format("<?{} {}?>", Target(), Data());

        xml_writer.WriteRaw( data );
    }

    POSTCONDITION( xml_writer.WriteState() == current_state );
}

XmlNodeType XmlProcessingInstruction::_getNodeType() const
{
    return XmlNodeType::ProcessingInstruction;
}

}