#include "System/IO/TextWriter.hpp"
#include "System/Text/StringBuilder.hpp"

namespace System::IO
{

class StringWriter : public TextWriter
{
public:
    StringWriter();
   ~StringWriter();

    const System::Text::StringBuilder &GetStringBuilder() const { return _builder; }

    using TextWriter::Write;

    void Write(char value) override;
    void Write(std::string_view message) override;

protected:
    System::Text::StringBuilder _builder;
};

}