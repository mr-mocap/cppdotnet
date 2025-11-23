#include <cppdotnet/System/Xml/XmlTextWriter.hpp>
#include <cppdotnet/System/IO/StreamWriter.hpp>
#include <cppdotnet/System/Private/private.hpp>

namespace System::Xml
{

XmlTextWriter::XmlTextWriter(std::shared_ptr<System::IO::TextWriter> text_writer)
    :
    _text_writer( text_writer )
{
    INVARIANT( _text_writer );
}

XmlTextWriter::XmlTextWriter(std::unique_ptr<System::IO::TextWriter> &&text_writer)
    :
    _text_writer( std::move(text_writer) )
{
    INVARIANT( _text_writer );
}

XmlTextWriter::XmlTextWriter(std::unique_ptr<System::IO::Stream> &&stream)
    :
    _text_writer( std::make_unique<System::IO::StreamWriter>( std::move(stream) ) )
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

void XmlTextWriter::WriteString(std::string_view data)
{
    INVARIANT( _text_writer );

    // TODO: Don't forget to transform character sequences to standard format (&, <, and > to '&amp;', '&lt;', and '&gt;')

    _text_writer->Write( data );
}

void XmlTextWriter::WriteRaw(std::string_view data)
{
    INVARIANT( _text_writer );

    _text_writer->Write( data );
}

enum WriteState XmlTextWriter::WriteState() const
{
    INVARIANT( _text_writer );

    return _write_state;
}

void XmlTextWriter::WriteState(System::Xml::WriteState new_state)
{
    _write_state = new_state;
}

void XmlTextWriter::Close()
{
    INVARIANT( _text_writer );

    if ( Settings().CloseOutput() )
        _text_writer->Close();
}

System::IO::Stream *XmlTextWriter::BaseStream()
{
    System::IO::StreamWriter *more_derived_writer = dynamic_cast<System::IO::StreamWriter *>( _text_writer.get() );

    if ( more_derived_writer )
        return more_derived_writer->BaseStream();

    return nullptr;
}

}