#include "TestNullable.hpp"
#include "System/Nullable.hpp"
#include <iostream>
#include <cassert>


namespace TestNullable
{

void DefaultConstructsToNull()
{
    std::cout << __func__ << std::endl;

    System::Nullable<int> variable;

    assert( !variable.HasValue() );
}

void ConstructWithValueSetValueAndHasValueToTrue()
{
    std::cout << __func__ << std::endl;

    {
        System::Nullable<int> variable{ 6 };

        assert( variable.HasValue() );
        assert( variable.Value() == 6 );
    }
    {
        const System::Nullable<int> variable{ 6 };

        assert( variable.HasValue() );
        assert( variable.Value() == 6 );
        assert( 6 == variable.Value() );
    }
}

void AccessingValueWhenHasValueIsFalseThrowsException()
{
    std::cout << __func__ << std::endl;

    System::Nullable<int> variable;

    assert( !variable.HasValue() );

    try
    {
        variable.Value();
        assert( false );
    }
    catch(const System::InvalidOperationException &e)
    {
        std::cout << "Exception Caught: " << e.Message() << std::endl;
        assert( true );
    }
}

void AccessingValueWhenHasValueIsTrueDoesNotThrowException()
{
    std::cout << __func__ << std::endl;

    System::Nullable<int> variable{ 2 };

    assert( variable.HasValue() );
    assert( variable.Value() == 2 );
}

void GetValueOrDefaultReturnsDefaultWhenHasValueIsFalse()
{
    std::cout << __func__ << std::endl;

    System::Nullable<int> variable;

    assert( !variable.HasValue() );
    assert( variable.GetValueOrDefault( 6 ) == 6 );
}

void GetValueOrDefaultReturnsValueWhenHasValueIsTrue()
{
    std::cout << __func__ << std::endl;

    System::Nullable<int> variable{ 32768 };

    assert( variable.HasValue() );
    assert( variable.GetValueOrDefault( 6 ) == 32768 );
}

void GetValueOrDefaultWithNoParameters()
{
    std::cout << __func__ << std::endl;

    // Returns Default Value when !HasValue()
    {
        System::Nullable<int> variable;

        assert( !variable.HasValue() );
        assert( variable.GetValueOrDefault() == 0 );
    }

    // Returns Value when HasValue()
    {
        System::Nullable<int> variable{ 32768 };

        assert( variable.HasValue() );
        assert( variable.GetValueOrDefault() == 32768 );
    }
}

void ConversionOperator()
{
    std::cout << __func__ << std::endl;

    // Returns Default Value when !HasValue()
    {
        System::Nullable<int> variable;
        int x = variable;

        assert( !variable.HasValue() );
        assert( x == 0 );
    }

    // Returns Value when HasValue()
    {
        System::Nullable<int> variable{ 32768 };
        int x = variable;

        assert( variable.HasValue() );
        assert( x == 32768 );
    }

    {
        System::Nullable<int> variable{ 32768 };

        assert( variable.HasValue() );
        assert( variable == 32768 );
    }
}

void OperatorEquals()
{
    std::cout << __func__ << std::endl;

    System::Nullable<int> variable;

    // Assigning a value to an empty Nullable
    {
        assert( !variable.HasValue() );

        variable = 6;

        assert( variable.HasValue() );
        assert( variable == 6 );
    }

    // Returns Value when HasValue()
    {
        assert( variable.HasValue() );
        assert( variable != 9 );

        variable = 9;

        assert( variable.HasValue() );
        assert( variable == 9 );
    }

    {
        variable = 66;

        assert( variable.HasValue() );

        System::Nullable<int> other{ 128 };

        assert( variable != other );

        variable = other;

        assert( variable == other );
    }

    // Clearing a variable that has a value
    {
        variable = 1;

        assert( variable.HasValue() );

        variable = std::nullopt;

        assert( !variable.HasValue() );
    }

    // Clearing a variable that has NO value
    {
        assert( !variable.HasValue() );

        variable = std::nullopt;

        assert( !variable.HasValue() );
    }

    // Assigning an rvalue
    {
        assert( !variable.HasValue() );

        variable = System::Nullable<int>{33};

        assert( variable.HasValue() );
        assert( variable == 33 );
    }
}

void OperatorEqualsEquals()
{
    std::cout << __func__ << std::endl;

    // Both Null
    {
        System::Nullable<int> variable;
        System::Nullable<int> othervariable;

        assert( variable == othervariable );
    }

    // One is Null
    {
        System::Nullable<int> variable(2);
        System::Nullable<int> othervariable;

        assert( variable != othervariable );
    }
    {
        System::Nullable<int> variable;
        System::Nullable<int> othervariable(42);

        assert( variable != othervariable );
    }

    // Both with a value
    {
        System::Nullable<int> variable(6);
        System::Nullable<int> othervariable(6);

        assert( variable == othervariable );
    }
    {
        System::Nullable<int> variable(42);
        System::Nullable<int> othervariable(6);

        assert( variable != othervariable );
    }
}

void Run()
{
    std::cout << "Running Nullable Tests..." << std::endl;

    DefaultConstructsToNull();
    ConstructWithValueSetValueAndHasValueToTrue();
    AccessingValueWhenHasValueIsFalseThrowsException();
    AccessingValueWhenHasValueIsTrueDoesNotThrowException();
    GetValueOrDefaultReturnsDefaultWhenHasValueIsFalse();
    GetValueOrDefaultReturnsValueWhenHasValueIsTrue();
    GetValueOrDefaultWithNoParameters();
    ConversionOperator();
    OperatorEquals();
    OperatorEqualsEquals();

    std::cout << "PASSED!" << std::endl;
}

}