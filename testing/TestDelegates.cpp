#include <cppdotnet/System/Action.hpp>
#include <cppdotnet/System/Func.hpp>
#include <iostream>
#include <cassert>

static int VariableToAffect = 0;

static void IncrementStaticVariable()
{
    ++VariableToAffect;
}

static int AlwaysReturns99()
{
    return 99;
}

namespace TestDelegates
{

void ActionDefaultConstructsToEmpty()
{
    System::Action example_action;
}

void ActionConstructWithFunction()
{
    System::Action example_action( IncrementStaticVariable );
}

void ActionConstructWithLambda()
{
    int a = 0;

    System::Action example_action( [&a]() { ++a; } );
}

void ActionAlwaysHasSingleTargetTrue()
{
    {
        System::Action example_action;

        assert( example_action.HasSingleTarget() );
    }

    {
        System::Action example_action( IncrementStaticVariable );

        assert( example_action.HasSingleTarget() );
    }
}

void ActionCalledCallsFunction()
{
    // Normal Function
    {
        System::Action example_action( IncrementStaticVariable );
        assert( VariableToAffect == 0 );

        example_action();

        assert( VariableToAffect == 1 );
    }

    // Using Lambda
    {
        int a = 0;
        System::Action example_action( [&a]() { ++a; } );

        assert( a == 0 );

        example_action();

        assert( a == 1 );
    }
}

void TestActions()
{
    ActionDefaultConstructsToEmpty();
    ActionConstructWithFunction();
    ActionConstructWithLambda();
    ActionAlwaysHasSingleTargetTrue();
    ActionCalledCallsFunction();
}

void FuncDefaultConstructsToEmpty()
{
    System::Func<int> example_func;
}

void FuncConstructWithFunction()
{
    {
        System::Func<int> example_func( AlwaysReturns99 );
    }
}

void FuncConstructWithLambda()
{
    System::Func<int> example_func( []() { return 800; }) ;
}

void FuncCalledCallsFunction()
{
    // Normal Function
    {
        System::Func<int> example_func( AlwaysReturns99 );

        assert( example_func() == 99 );
    }

    // Lambda
    {
        System::Func<int> example_func( []() { return 800;} );

        assert( example_func() == 800 );
    }
}

void TestFuncs()
{
    FuncDefaultConstructsToEmpty();
    FuncConstructWithFunction();
    FuncConstructWithLambda();
    FuncCalledCallsFunction();
}

void Run()
{
    TestActions();
}

}

int main(void)
{
    TestDelegates::Run();

    return EXIT_SUCCESS;
}