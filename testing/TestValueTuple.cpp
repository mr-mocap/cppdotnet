#include <cppdotnet/System/Console.hpp>
#include <cppdotnet/System/ValueTuple.hpp>
#include <cppdotnet/System/Private/private.hpp>
#include <cppdotnet/System/IO/TextWriter.hpp>
#include <cassert>


namespace TestValueTuple
{

void DefaultConstructed()
{
    {
        System::ValueTuple<> t;

        UNUSED(t);
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
    DefaultConstructed();
}

}

int main(void)
{
    TestValueTuple::Run();

    return EXIT_SUCCESS;
}