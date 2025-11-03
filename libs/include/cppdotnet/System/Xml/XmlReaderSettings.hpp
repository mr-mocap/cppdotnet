#pragma once

#include <cppdotnet/System/Xml/NameTable.hpp>

namespace System::Xml
{

class XmlReaderSettings
{
public:
    XmlReaderSettings() = default;
   ~XmlReaderSettings() = default;

    XmlReaderSettings(const XmlReaderSettings &other) = default;
    XmlReaderSettings &operator=(const XmlReaderSettings &other) = default;

    XmlReaderSettings(XmlReaderSettings &&other) = default;
    XmlReaderSettings &operator=(XmlReaderSettings &&other) = default;

    bool CloseInput() const noexcept { return _close_input; }
    void CloseInput(bool value) noexcept { _close_input = value; }

    bool IgnoreComments() const noexcept { return _ignore_comments; }
    void IgnoreComments(bool value) noexcept { _ignore_comments = value; }

    const XmlNameTable &NameTable() const noexcept { return _name_table; }
          XmlNameTable &NameTable()       noexcept { return _name_table; }
    
    void NameTable(const System::Xml::NameTable &value) noexcept { _name_table = value; }

    void Reset();
protected:
    System::Xml::NameTable _name_table;
    bool                   _close_input     = false;
    bool                   _ignore_comments = false;
};

}