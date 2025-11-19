#include <cppdotnet/System/Xml/XmlLinkedNode.hpp>

namespace System::Xml
{

XmlLinkedNode::XmlLinkedNode(std::shared_ptr<XmlNodeList> specific_children_object)
    :
    XmlNode( specific_children_object )
{
}

}