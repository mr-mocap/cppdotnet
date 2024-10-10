#include "TestException.hpp"
#include "System/Exception.hpp"
#include "System/Console.hpp"
#include "System/Diagnostics/Trace.hpp"
#include <iostream>
#include <cassert>

using namespace System;
using namespace std::literals;

namespace TestException
{

void DefaultConstruction()
{
    std::cout << __func__ << std::endl;

    ArgumentNullException e;

    assert( e.Message().empty() );
    assert( !e.InnerException() );
    assert( &e.GetBaseException() == &e );
}

void WithMessage()
{
    std::cout << __func__ << std::endl;

    // Message Automatically filled in
    {
        ArgumentNullException ex{ "parameter"sv };

        assert( !ex.Message().empty() );
        assert( !ex.InnerException() );
        assert( &ex.GetBaseException() == &ex );
    }

    {
        auto msg = "Some kind of error occurred"sv;
        ArgumentNullException ex{ "parameter"sv, msg };

        assert( !ex.Message().empty() );
        assert( ex.Message() == msg );
        assert( ex.ParamName() == "parameter"sv );
        assert( !ex.InnerException() );
        assert( &ex.GetBaseException() == &ex );
    }
}

void WithMessageAndInnerException()
{
    std::cout << __func__ << std::endl;

    auto msg = "Some Kind of Exception occurred"sv;
    auto msg_outer = "This is the outer Exception"sv;

    // Copy inner exception into outer
    {
        InvalidOperationException outer{ msg_outer, ArgumentNullException{ "field"sv, msg } };

        assert( !outer.Message().empty() );
        assert( outer.Message() == msg_outer );
        assert( outer.InnerException() );
        assert( &outer.GetBaseException() == outer.InnerException() );
        assert( outer.InnerException()->Message() == msg );

        System::Console::WriteLine( outer.ToString() );
    }
}

void Run()
{
    std::cout << "Running Exception Tests..." << std::endl;

    DefaultConstruction();
    WithMessage();
    WithMessageAndInnerException();

    std::cout << "PASSED!" << std::endl;
}

}