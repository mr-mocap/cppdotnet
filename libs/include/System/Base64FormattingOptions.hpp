#pragma once


namespace System
{

enum class Base64FormattingOptions
{
    None,            ///@< Does not insert line breaks after every 76 characters in the string representation.
    InsertLineBreaks ///@< Inserts line breaks after every 76 characters in the string representation.
};

}