#pragma once

#include <string_view>
#include <memory>

namespace System::Xml
{

class XmlNameTable
{
  public:
    virtual ~XmlNameTable() = default;

    virtual std::string_view Add(std::string_view name) = 0;
    virtual std::string_view Get(std::string_view name) const = 0;

    virtual bool empty() const = 0; // C++-ism

    virtual std::shared_ptr<XmlNameTable> MemberwiseClone() const = 0;
};

}