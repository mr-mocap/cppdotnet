#pragma once

#include "System/ConsoleKey.hpp"
#include "System/ConsoleModifiers.hpp"


namespace System
{

struct ConsoleKeyInfo
{
    ConsoleKeyInfo(char key_char, ConsoleKey k, bool shift, bool alt, bool ctrl)
        :
        Key{ k },
        KeyChar{ key_char },
        Modifiers{ int(alt) | (int(shift) << 1) | (int(ctrl) << 2) }
    {
    }

    ConsoleKey       Key = ConsoleKey::None;
    char             KeyChar = 0;
    ConsoleModifiers Modifiers;

    friend bool operator ==(const ConsoleKeyInfo &left, const ConsoleKeyInfo &right)
    {
        return (left.Key       == right.Key) &&
               (left.KeyChar   == right.KeyChar) &&
               (left.Modifiers == right.Modifiers);
    }
};

}