#pragma once

#include <cppdotnet/System/Xml/XmlReader.hpp>

namespace System::Xml
{

class XmlNodeReader : public XmlReader
{
public:
    XmlNodeReader() = default;
   ~XmlNodeReader() override = default;

    const XmlReaderSettings &Settings() const noexcept override;
          XmlReaderSettings &Settings()       noexcept override;

    virtual bool Read() override;

protected:
    XmlReaderSettings _settings;
};

}