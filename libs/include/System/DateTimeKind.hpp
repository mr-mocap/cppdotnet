#pragma once


namespace System
{

enum class DateTimeKind
{
    Unspecified, ///@< The time represented is not specified as either local time or Coordinated Universal Time (UTC)
    Utc,         ///@< The time represents UTC
    Local        ///@< The time represented is local time
};

}