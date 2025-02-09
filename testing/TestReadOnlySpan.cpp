#include "TestReadOnlySpan.hpp"
#include "System/ReadOnlySpan.hpp"
#include <iostream>
#include <cassert>


namespace TestReadOnlySpan
{

void Empty()
{
    std::cout << __func__ << std::endl;

    assert( System::ReadOnlySpan<int>::Empty().IsEmpty() );
    assert( System::ReadOnlySpan<int>::Empty().Length() == 0 );
}

void DefaultConstructedSpanIsEmpty()
{
    std::cout << __func__ << std::endl;

    assert( System::ReadOnlySpan<short>().IsEmpty() );
}

void SingleObject()
{
    std::cout << __func__ << std::endl;

    float var = 3.3;
    System::ReadOnlySpan<float> one_item{ var };

    assert( !one_item.IsEmpty() );
    assert( one_item.Length() == 1 );
    assert( one_item[0] == var );
}

void MultipleObjectsFromBuiltInArray()
{
    std::cout << __func__ << std::endl;

    int builtin_array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    System::ReadOnlySpan<int> span_of_items( builtin_array );

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

#if 0
    // This line should FAIL TO COMPILE!
    span_of_items[3] = 99;

    assert( span_of_items[3] == 99 );
#endif
}

void MultipleObjectsFromStdArray()
{
    std::cout << __func__ << std::endl;

    // Non-const
    {
        std::array<int, 6> a{ 1, 2, 3, 4, 5, 6 };
        System::ReadOnlySpan<int> span_a( a );

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
        System::ReadOnlySpan<const int> span_a( a );

        assert( span_a.Length() == 3 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
    }
#if 0
    // std::array of const items to const Span of items
    {
        std::array<const int, 3> a{ 1, 2, 3 };
        const System::ReadOnlySpan<int> span_a( a );

        assert( span_a.Length() == 3 );
    }
#endif

    // std::array of const items to Span of const items
    {
        std::array<const int, 3> a{ 1, 2, 3 };
        System::ReadOnlySpan<const int> span_a( a );

        assert( span_a.Length() == 3 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
    }

    // std::span of items to Span of items
    {
        std::array<int, 3> a{ 1, 2, 3 };
        std::span<int>     b{ a };
        System::ReadOnlySpan<int> span_a{ b };

        assert( span_a.Length() == 3 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
    }

    // std::span of const items to Span of const items
    {
        std::array<const int, 3> a{ 1, 2, 3 };
        std::span<const int> b{ a };
        System::ReadOnlySpan<const int> span_a{ b };

        assert( span_a.Length() == 3 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
    }

#if 0
    // std::span of const items to Span of const items
    {
        std::array<const int, 3> a{ 1, 2, 3 };
        std::span<const int> b{ a };
        const System::ReadOnlySpan<int> span_a( b );

        assert( span_a.Length() == 3 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
    }
#endif
}

void Assignment()
{
    std::cout << __func__ << std::endl;

    float var = 6.6f;
    System::ReadOnlySpan<float> one_item{ var };
    System::ReadOnlySpan<float> new_item;

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

void Slice()
{
    std::cout << __func__ << std::endl;

    int a[] = { 1, 2, 3 };
    System::ReadOnlySpan<int> span_a( a );

    assert( span_a[0] == 1 );
    assert( span_a[1] == 2 );
    assert( span_a[2] == 3 );

    {
        System::ReadOnlySpan<int> span_b( span_a.Slice( 1 ) );

        assert( span_b.Length() == 2 );
        assert( span_b[0] == 2 );
        assert( span_b[1] == 3 );
    }
    
    {
        System::ReadOnlySpan<int> span_b( span_a.Slice( 0, 2 ) );

        assert( span_b.Length() == 2 );
        assert( span_b[0] == 1 );
        assert( span_b[1] == 2 );
    }
    
    // Index past end
    try
    {
        System::ReadOnlySpan<int> span_c( span_a.Slice( 99 ) );
    }
    catch (const System::ArgumentOutOfRangeException &e)
    {
        std::cout << std::string(e.Message()).append(" at ").append(e.TargetSite()) << std::endl;
    }
    catch (...)
    {
        assert( false );
    }

    // Length past end
    try
    {
        System::ReadOnlySpan<int> span_d( span_a.Slice( 0, 99 ) );
    }
    catch (const System::ArgumentOutOfRangeException &e)
    {
        std::cout << std::string(e.Message()).append(" at ").append(e.TargetSite()) << std::endl;
    }
    catch (...)
    {
        assert( false );
    }
}

void CopyTo()
{
    std::cout << __func__ << std::endl;

    int a[] = { 1, 2, 3 };
    int b[] = { 5, 5, 5, 5, 5 };
    System::ReadOnlySpan<int> span_a( a );
    System::Span<int> span_b( b );

    assert( span_b[0] != span_a[0] );
    assert( span_b[1] != span_a[1] );
    assert( span_b[2] != span_a[2] );

    assert( span_b[0] == 5 );
    assert( span_b[1] == 5 );
    assert( span_b[2] == 5 );
    assert( span_b[3] == 5 );
    assert( span_b[4] == 5 );

    span_a.CopyTo(span_b);

    assert( span_b[0] == span_a[0] );
    assert( span_b[1] == span_a[1] );
    assert( span_b[2] == span_a[2] );

    assert( span_b[0] == 1 );
    assert( span_b[1] == 2 );
    assert( span_b[2] == 3 );
    assert( span_b[3] == 5 );
    assert( span_b[4] == 5 );

#if 0
    // This should FAIL TO COMPILE!
    try
    {
        span_b.CopyTo( span_a );
    }
    catch(const System::ArgumentException &e)
    {
        std::cout << std::string(e.Message()).append(" at ").append(e.TargetSite()) << std::endl;
    }
#endif 
}

void TryCopyTo()
{
    std::cout << __func__ << std::endl;

    int a[] = { 1, 2, 3 };
    int b[] = { 5, 5, 5, 5, 5 };
    System::ReadOnlySpan<int> span_a( a );
    System::Span<int> span_b( b );

    assert( span_b[0] != span_a[0] );
    assert( span_b[1] != span_a[1] );
    assert( span_b[2] != span_a[2] );

    assert( span_b[0] == 5 );
    assert( span_b[1] == 5 );
    assert( span_b[2] == 5 );
    assert( span_b[3] == 5 );
    assert( span_b[4] == 5 );

    assert( span_a.TryCopyTo(span_b) == true );

    assert( span_b[0] == span_a[0] );
    assert( span_b[1] == span_a[1] );
    assert( span_b[2] == span_a[2] );

    assert( span_b[0] == 1 );
    assert( span_b[1] == 2 );
    assert( span_b[2] == 3 );
    assert( span_b[3] == 5 );
    assert( span_b[4] == 5 );

#if 0
    // This should FAIL TO COMPILE!
    assert( span_b.TryCopyTo( span_a ) == false );
#endif
}


void Run()
{
    std::cout << "Running ReadOnlySpan Tests..." << std::endl;

    Empty();
    DefaultConstructedSpanIsEmpty();
    SingleObject();
    MultipleObjectsFromBuiltInArray();
    MultipleObjectsFromStdArray();
    Assignment();
    Slice();
    CopyTo();
    TryCopyTo();

    std::cout << "PASSED!" << std::endl;
}

}