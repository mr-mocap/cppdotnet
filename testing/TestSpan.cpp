#include "System/Span.hpp"
#include "System/Span.hpp"
#include <iostream>
#include <cassert>


namespace TestSpan
{

void Empty()
{
    std::cout << __func__ << std::endl;

    assert( System::Span<int>::Empty().IsEmpty() );
    assert( System::Span<int>::Empty().Length() == 0 );
}

void DefaultConstructedSpanIsEmpty()
{
    std::cout << __func__ << std::endl;

    assert( System::Span<short>().IsEmpty() );
}

void SingleObject()
{
    std::cout << __func__ << std::endl;

    float var = 3.3;
    System::Span<float> one_item{ var };

    assert( !one_item.IsEmpty() );
    assert( one_item.Length() == 1 );
    assert( one_item[0] == var );
}

void Assignment()
{
    std::cout << __func__ << std::endl;

    float var = 6.6f;
    System::Span<float> one_item{ var };
    System::Span<float> new_item;

    assert( one_item.Length() == 1 );
    assert( one_item[0] == var );
    assert( new_item.IsEmpty() );

    new_item = one_item;

    // new_item now contains what one_item has...
    assert( !new_item.IsEmpty() );
    assert( new_item.Length() == 1 );
    assert( new_item[0] == var );

    // And the original source object still contains the data too
    assert( one_item.Length() == 1 );
    assert( one_item[0] == var );
}

void Run()
{
    std::cout << "Running Span Tests..." << std::endl;

    Empty();
    DefaultConstructedSpanIsEmpty();
    SingleObject();
    Assignment();

    std::cout << "PASSED!" << std::endl;
}

}