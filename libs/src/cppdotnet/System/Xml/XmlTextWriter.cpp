#include <cppdotnet/System/Xml/XmlTextWriter.hpp>
#include <cppdotnet/System/Private/private.hpp>

namespace System::Xml
{

XmlTextWriter::XmlTextWriter(std::unique_ptr<System::IO::TextWriter> &&text_writer)
    :
    _text_writer( std::move(text_writer) )
{
    INVARIANT( _text_writer );
}

const XmlWriterSettings &XmlTextWriter::Settings() const noexcept
{
    INVARIANT( _text_writer );

    return _settings;
}

XmlWriterSettings &XmlTextWriter::Settings() noexcept
{
    INVARIANT( _text_writer );

    return _settings;
}

void XmlTextWriter::WriteValue(std::string_view value)
{
    INVARIANT( _text_writer );

    _text_writer->Write( value );
}

void XmlTextWriter::WriteValue(bool value)
{
    INVARIANT( _text_writer );

    _text_writer->Write( value );
}

void XmlTextWriter::WriteValue(float value)
{
    INVARIANT( _text_writer );

    _text_writer->Write( value );
}

void XmlTextWriter::WriteValue(double value)
{
    INVARIANT( _text_writer );

    _text_writer->Write( value );
}

void XmlTextWriter::WriteValue(int32_t value)
{
    INVARIANT( _text_writer );

    _text_writer->Write( value );
}

void XmlTextWriter::WriteValue(int64_t value)
{
    INVARIANT( _text_writer );

    _text_writer->Write( value );
}

enum WriteState XmlTextWriter::WriteState() const
{
    INVARIANT( _text_writer );

    return _write_state;
}

void XmlTextWriter::Close()
{
    INVARIANT( _text_writer );

    if ( Settings().CloseOutput() )
        _text_writer->Close();
}
}