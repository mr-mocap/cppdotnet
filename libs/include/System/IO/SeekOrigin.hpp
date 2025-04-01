#pragma once

namespace System::IO
{

enum class SeekOrigin
{
    Begin,   ///@< Specifies the beginning of a stream
    Current, ///@< Specifies the current position within a stream
    End      ///@< Specifies the end of a stream
};

}