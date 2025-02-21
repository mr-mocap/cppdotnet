#pragma once


namespace System
{

enum class ConsoleKey
{
    None         = 0,
    Backspace    = 8,  ///@< The BACKSPACE key
    Tab          = 9,  ///@< The TAB key
    Clear        = 12, ///@< The CLEAR key
    Enter        = 13, ///@< The ENTER key
    Pause        = 19, ///@< The PAUSE key
    Escape       = 27, ///@< The ESC (ESCAPE) key
    Spacebar     = 32, ///@< The SPACEBAR key
    PageUp       = 33, ///@< The PAGE UP key
    PageDown     = 34, ///@< The PAGE DOWN key
    End          = 35, ///@< The END key
    Home         = 36, ///@< The HOME key
    LeftArrow    = 37, ///@< The LEFT ARROW key
    UpArrow      = 38, ///@< The UP ARROW key
    RightArrow   = 39, ///@< The RIGHT ARROW key
    DownArrow    = 40, ///@< The DOWN ARROW key
    Select       = 41, ///@< The SELECT key
    Print        = 42, ///@< The PRINT key
    Execute      = 43, ///@< The EXECUTE key
    PrintScreen  = 44, ///@< The PRINT SCREEN key
    Insert       = 45, ///@< The INS (INSERT) key
    Delete       = 46, ///@< The DEL (DELETE) key
    Help         = 47, ///@< The HELP key
    D0           = 48, ///@< The 0 key
    D1           = 49, ///@< The 1 key
    D2           = 50, ///@< The 2 key
    D3           = 51, ///@< The 3 key
    D4           = 52, ///@< The 4 key
    D5           = 53, ///@< The 5 key
    D6           = 54, ///@< The 6 key
    D7           = 55, ///@< The 7 key
    D8           = 56, ///@< The 8 key
    D9           = 57, ///@< The 9 key
    A            = 65, ///@< The A key
    B            = 66, ///@< The B key
    C            = 67, ///@< The C key
    D            = 68, ///@< The D key
    E            = 69, ///@< The E key
    F            = 70, ///@< The F key
    G            = 71, ///@< The G key
    H            = 72, ///@< The H key
    I            = 73, ///@< The I key
    J            = 74, ///@< The J key
    K            = 75, ///@< The K key
    L            = 76, ///@< The L key
    M            = 77, ///@< The M key
    N            = 78, ///@< The N key
    O            = 79, ///@< The O key
    P            = 80, ///@< The P key
    Q            = 81, ///@< The Q key
    R            = 82, ///@< The R key
    S            = 83, ///@< The S key
    T            = 84, ///@< The T key
    U            = 85, ///@< The U key
    V            = 86, ///@< The V key
    W            = 87, ///@< The W key
    X            = 88, ///@< The X key
    Y            = 89, ///@< The Y key
    Z            = 90, ///@< The Z key
    LeftWindows  = 91, ///@< The left Windows logo key (Microsoft Natural Keyboard)
    RightWindows = 92, ///@< The right Windows logo key (Microsoft Natural Keyboard)
    Applications = 93, ///@< The Application key (Microsoft Natural Keyboard)
    Sleep        = 95, ///@< The Computer Sleep key
    NumPad0      = 96, ///@< The 0 key on the numeric keypad
    NumPad1      = 97, ///@< The 1 key on the numeric keypad
    NumPad2      = 98, ///@< The 2 key on the numeric keypad
    NumPad3      = 99, ///@< The 3 key on the numeric keypad
    NumPad4      = 100, ///@< The 4 key on the numeric keypad
    NumPad5      = 101, ///@< The 5 key on the numeric keypad
    NumPad6      = 102, ///@< The 6 key on the numeric keypad
    NumPad7      = 103, ///@< The 7 key on the numeric keypad
    NumPad8      = 104, ///@< The 8 key on the numeric keypad
    NumPad9      = 105, ///@< The 9 key on the numeric keypad
    Multiply     = 106, ///@< The Multiply key (the multiplication key on the numeric keypad)
    Add          = 107, ///@< The Add key (the addition key on the numeric keypad)
    Separator    = 108, ///@< The Separator key
    Subtract     = 109, ///@< The Subtract key (the subtraction key on the numeric keypad)
    Decimal      = 110, ///@< The Decimal key (the decimal key on the numeric keypad)
    Divide       = 111, ///@< The Divide key (the division key on the numeric keypad)
    F1           = 112, ///@< The F1 key
    F2           = 113, ///@< The F2 key
    F3           = 114, ///@< The F3 key
    F4           = 115, ///@< The F4 key
    F5           = 116, ///@< The F5 key
    F6           = 117, ///@< The F6 key
    F7           = 118, ///@< The F7 key
    F8           = 119, ///@< The F8 key
    F9           = 120, ///@< The F9 key
    F10          = 121, ///@< The F10 key
    F11          = 122, ///@< The F11 key
    F12          = 123, ///@< The F12 key
    F13          = 124, ///@< The F13 key
    F14          = 125, ///@< The F14 key
    F15          = 126, ///@< The F15 key
    F16          = 127, ///@< The F16 key
    F17          = 128, ///@< The F17 key
    F18          = 129, ///@< The F18 key
    F19          = 130, ///@< The F19 key
    F20          = 131, ///@< The F20 key
    F21          = 132, ///@< The F21 key
    F22          = 133, ///@< The F22 key
    F23          = 134, ///@< The F23 key
    F24          = 135, ///@< The F24 key
    BrowserBack  = 166, ///@< The Browser Back key
    BrowserForward    = 167, ///@< The Browser Forward key
    BrowserRefresh    = 168, ///@< The Browser Refresh key
    BrowserStop       = 169, ///@< The Browser Stop key
    BrowserSearch     = 170, ///@< The Browser Search key
    BrowserFavorites  = 171, ///@< The Browser Favorites key
    BrowserHome       = 172, ///@< The Browser Home key
    VolumeMute        = 173, ///@< The Volume Mute key (Microsoft Natural Keyboard)
    VolumeDown        = 174, ///@< The Volume Down key (Microsoft Natural Keyboard)
    VolumeUp          = 175, ///@< The Volume Up key (Microsoft Natural Keyboard)
    MediaNext         = 176, ///@< The Media Next Track key
    MediaPrevious     = 177, ///@< The Media Previous Track key
    MediaStop         = 178, ///@< The Media Stop key
    MediaPlay         = 179, ///@< The Media Play/Pause key
    LaunchMail        = 180, ///@< The Start Mail key (Microsoft Natural Keyboard)
    LaunchMediaSelect = 181, ///@< The Select Media key (Microsoft Natural Keyboard)
    LaunchApp1        = 182, ///@< The Start Application 1 key (Microsoft Natural Keyboard)
    LaunchApp2        = 183, ///@< The Start Application 2 key (Microsoft Natural Keyboard)
    Oem1              = 186, ///@< The OEM 1 key (OEM specific)
    OemPlus           = 187, ///@< The OEM Plus key on any country/region keyboard
    OemComma          = 188, ///@< The OEM Comma key on any country/region keyboard
    OemMinus          = 189, ///@< The OEM Minus key on any country/region keyboard
    OemPeriod         = 190, ///@< The OEM Period key on any country/region keyboard
    Oem2              = 191, ///@< The OEM 2 key (OEM specific)
    Oem3              = 192, ///@< The OEM 3 key (OEM specific)
    Oem4              = 219, ///@< The OEM 4 key (OEM specific)
    Oem5              = 220, ///@< The OEM 5 (OEM specific)
    Oem6              = 221, ///@< The OEM 6 key (OEM specific)
    Oem7              = 222, ///@< The OEM 7 key (OEM specific)
    Oem8              = 223, ///@< The OEM 8 key (OEM specific)
    Oem102            = 226, ///@< The OEM 102 key (OEM specific)
    Process           = 229, ///@< The IME PROCESS key
    Packet            = 231, ///@< The PACKET key (used to pass Unicode characters with keystrokes)
    Attention         = 246, ///@< The ATTN key
    CrSel             = 247, ///@< The CRSEL (CURSOR SELECT) key
    ExSel             = 248, ///@< The EXSEL (EXTEND SELECTION) key
    EraseEndOfFile    = 249, ///@< The ERASE EOF key
    Play              = 250, ///@< The PLAY key
    Zoom              = 251, ///@< The ZOOM key
    NoName            = 252, ///@< A constant reserved for future use
    Pa1               = 253, ///@< The PA1 key
    OemClear          = 254, ///@< The CLEAR key (OEM specific)
};

}