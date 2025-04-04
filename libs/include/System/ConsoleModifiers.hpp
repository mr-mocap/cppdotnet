#pragma once


namespace System
{

enum class ConsoleModifiers
{
    None    = 0,
    Alt     = 1, ///@< The left or right ALT modifier key
    Shift   = 2, ///@< The left or right SHIFT modifier key
    Control = 4  ///@< The left or right CTRL modifier key
};

}