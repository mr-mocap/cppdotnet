#include <cppdotnet/System/Span.hpp>
#include <iostream>
#include <cassert>


namespace TestSpan
{

void Empty()
{
    assert( System::Span<int>::Empty().IsEmpty() );
    assert( System::Span<int>::Empty().Length() == 0 );
}

void DefaultConstructedSpanIsEmpty()
{
    assert( System::Span<short>().IsEmpty() );
}

void SingleObject()
{
    float var = 3.3;
    System::Span<float> one_item{ var };

    assert( !one_item.IsEmpty() );
    assert( one_item.Length() == 1 );
    assert( one_item[0] == var );
}

void MultipleObjectsFromBuiltInArray()
{
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

    // std::span of items to Span of items
    {
        std::array<int, 3> a{ 1, 2, 3 };
        std::span<int>     b{ a };
        System::Span<int> span_a{ b };

        assert( span_a.Length() == 3 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
    }

    // std::span of const items to Span of const items
    {
        std::array<const int, 3> a{ 1, 2, 3 };
        std::span<const int> b{ a };
        System::Span<const int> span_a{ b };

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
        const System::Span<int> span_a( b );

        assert( span_a.Length() == 3 );
        assert( span_a[0] == 1 );
        assert( span_a[1] == 2 );
        assert( span_a[2] == 3 );
    }
#endif
}

void Assignment()
{
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
    
    {
        System::Span<int> span_b( span_a.Slice( 0, 2 ) );

        assert( span_b.Length() == 2 );
        assert( span_b[0] == 1 );
        assert( span_b[1] == 2 );
    }
    
    // Index past end
    try
    {
        System::Span<int> span_c( span_a.Slice( 99 ) );
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
        System::Span<int> span_d( span_a.Slice( 0, 99 ) );
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
    int a[] = { 1, 2, 3 };
    int b[] = { 5, 5, 5, 5, 5 };
    System::Span<int> span_a( a );
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

    try
    {
        span_b.CopyTo( span_a );
    }
    catch(const System::ArgumentException &e)
    {
        std::cout << std::string(e.Message()).append(" at ").append(e.TargetSite()) << std::endl;
    }
    
}

void TryCopyTo()
{
    int a[] = { 1, 2, 3 };
    int b[] = { 5, 5, 5, 5, 5 };
    System::Span<int> span_a( a );
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

    assert( span_b.TryCopyTo( span_a ) == false );
}

void Run()
{
    Empty();
    DefaultConstructedSpanIsEmpty();
    SingleObject();
    MultipleObjectsFromBuiltInArray();
    MultipleObjectsFromStdArray();
    Assignment();
    Clear();
    Fill();
    Slice();
    CopyTo();
    TryCopyTo();
}

}

int main(void)
{
    TestSpan::Run();

    return EXIT_SUCCESS;
}