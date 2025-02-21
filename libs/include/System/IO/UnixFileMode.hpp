#pragma once


namespace System::IO
{

enum class UnixFileMode
{
    None          = 0,    ///@< No Permissions
    OtherExecute  = 1,    ///@< Execute permission for others
    OtherWrite    = 2,    ///@< Write permission for others
    OtherRead     = 4,    ///@< Read permission for others
    GroupExecute  = 8,    ///@< Execute permission for group
    GroupWrite    = 16,   ///@< Write permission for group
    GroupRead     = 32,   ///@< Read permission for group
    UserExecute   = 64,   ///@< Execute permission for user
    UserWrite     = 128,  ///@< Write permission for user
    UserRead      = 256,  ///@< Read permission for user
    StickyBit     = 512,  ///@< Sticky bit permission
    SetGroup      = 1024, ///@< Set group permission
    SetUser       = 2048  ///@< Set user permission
};

}