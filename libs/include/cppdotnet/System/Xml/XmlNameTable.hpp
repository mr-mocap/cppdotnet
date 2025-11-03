#pragma once

#include <string_view>

namespace System::Xml
{

class XmlNameTable
{
  public:
    virtual ~XmlNameTable() = default;

    virtual std::string_view Add(std::string_view name) = 0;
    virtual std::string_view Get(std::string_view name) const = 0;
};

}