#include "TestDelegates.hpp"
#include "System/Action.hpp"
#include "System/Func.hpp"
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
    std::cout << __func__ << std::endl;

    System::Action example_action;
}

void ActionConstructWithFunction()
{
    std::cout << __func__ << std::endl;

    System::Action example_action( IncrementStaticVariable );
}

void ActionConstructWithLambda()
{
    std::cout << __func__ << std::endl;

    int a = 0;

    System::Action example_action( [&a]() { ++a; } );
}

void ActionAlwaysHasSingleTargetTrue()
{
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

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
    std::cout << __func__ << std::endl;

    System::Func<int> example_func;
}

void FuncConstructWithFunction()
{
    std::cout << __func__ << std::endl;

    {
        System::Func<int> example_func( AlwaysReturns99 );
    }
}

void FuncConstructWithLambda()
{
    std::cout << __func__ << std::endl;

    System::Func<int> example_func( []() { return 800; }) ;
}

void FuncCalledCallsFunction()
{
    std::cout << __func__ << std::endl;

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
    std::cout << "Running Delegate Tests..." << std::endl;

    TestActions();

    std::cout << "PASSED!" << std::endl;
}

}