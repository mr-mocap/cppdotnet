#include "TestValueTuple.hpp"
#include "System/Console.hpp"
#include "System/ValueTuple.hpp"
#include <cassert>


namespace TestValueTuple
{

void DefaultConstructed()
{
    System::Console::Out().WriteLine(__func__);

    {
        System::ValueTuple<> t;

    }
    {
        System::ValueTuple<int> t;

        assert( t.Item<0>() == 0 );
    }
    {
        System::ValueTuple<int, int> t;

        assert( t.Item<0>() == 0 );
        assert( t.Item<1>() == 0 );
    }
}

void Run()
{
    System::Console::Out().WriteLine("Running ValueTuple Tests...");

    DefaultConstructed();

    System::Console::Out().WriteLine("PASSED!");
}

}