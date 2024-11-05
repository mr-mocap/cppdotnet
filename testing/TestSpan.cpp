#include "System/Span.hpp"
#include "System/Span.hpp"
#include <iostream>
#include <cassert>
#include <format>


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

void MultipleObjectsFromBuiltInArray()
{
    std::cout << __func__ << std::endl;

    int builtin_array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    System::Span<int> span_of_items( builtin_array );

    assert( span_of_items.Length() == 10 );
    assert( span_of_items[0] == 1 );
    assert( span_of_items[1] == 2 );
    assert( span_of_items[2] == 3 );
    assert( span_of_items[3] == 4 );
    assert( span_of_items[4] == 5 );
    assert( span_of_items[5] == 6 );
    assert( span_of_items[6] == 7 );
    assert( span_of_items[7] == 8 );
    assert( span_of_items[8] == 9 );
    assert( span_of_items[9] == 10 );

    span_of_items[3] = 99;

    assert( span_of_items[3] == 99 );
}

void MultipleObjectsFromStdArray()
{
    std::cout << __func__ << std::endl;

    // Non-const
    {
        std::array<int, 6> a{ 1, 2, 3, 4, 5, 6 };
        System::Span<int> span_a( a );

        assert( span_a.Length() == 6 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
        assert( span_a[3] == 4 );
        assert( span_a[4] == 5 );
        assert( span_a[5] == 6 );
    }

    // Const std::array to Span of const items
    {
        const std::array<int, 3> a{ 1, 2, 3 };
        System::Span<const int> span_a( a );

        assert( span_a.Length() == 3 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
    }
#if 0
    // std::array of const items to const Span of items
    {
        std::array<const int, 3> a{ 1, 2, 3 };
        const System::Span<int> span_a( a );

        assert( span_a.Length() == 3 );
    }
#endif

    // std::array of const items to Span of const items
    {
        std::array<const int, 3> a{ 1, 2, 3 };
        System::Span<const int> span_a( a );

        assert( span_a.Length() == 3 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
    }
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

void Clear()
{
    std::cout << __func__ << std::endl;

    int a[] = { 1, 2, 3 };
    System::Span<int> span_a( a );

    assert( span_a[0] == 1 );
    assert( span_a[1] == 2 );
    assert( span_a[2] == 3 );

    span_a.Clear();

    assert( span_a[0] == 0 );
    assert( span_a[1] == 0 );
    assert( span_a[2] == 0 );
}

void Fill()
{
    std::cout << __func__ << std::endl;

    int a[] = { 1, 2, 3 };
    System::Span<int> span_a( a );

    assert( span_a[0] == 1 );
    assert( span_a[1] == 2 );
    assert( span_a[2] == 3 );

    span_a.Fill( 12 );

    assert( span_a[0] == 12 );
    assert( span_a[1] == 12 );
    assert( span_a[2] == 12 );
}

void Slice()
{
    std::cout << __func__ << std::endl;

    int a[] = { 1, 2, 3 };
    System::Span<int> span_a( a );

    assert( span_a[0] == 1 );
    assert( span_a[1] == 2 );
    assert( span_a[2] == 3 );

    {
        System::Span<int> span_b( span_a.Slice( 1 ) );

        assert( span_b.Length() == 2 );
        assert( span_b[0] == 2 );
        assert( span_b[1] == 3 );
    }
    
    try
    {
        System::Span<int> span_c( span_a.Slice( 99 ) );
    }
    catch (const System::ArgumentOutOfRangeException &e)
    {
        std::cout << std::format("{} at {}", e.Message(), e.TargetSite() ) << std::endl;
    }
    catch (...)
    {
        assert( false );
    }
}

void Run()
{
    std::cout << "Running Span Tests..." << std::endl;

    Empty();
    DefaultConstructedSpanIsEmpty();
    SingleObject();
    MultipleObjectsFromBuiltInArray();
    Assignment();
    Clear();
    Fill();
    Slice();

    std::cout << "PASSED!" << std::endl;
}

}