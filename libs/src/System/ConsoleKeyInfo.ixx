module;

export module System:ConsoleKeyInfo;

export import System:ConsoleKey;
export import System:ConsoleModifiers;


namespace System
{

export
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