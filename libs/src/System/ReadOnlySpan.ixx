module;

export module System:ReadOnlySpan;

import <cstddef>;
import <type_traits>;
export import System:Span;

export
{

namespace System
{

template <typename Type, std::size_t Extent = std::dynamic_extent>
class ReadOnlySpan
{
    template <typename To, typename From>
    using is_array_convertible = std::is_convertible<From (*)[], To (*)[]>;

    template <typename Tp, std::size_t ArrayExtent>
        requires (Extent == std::dynamic_extent || ArrayExtent == Extent)
	using is_compatible_array = is_array_convertible<const Type, Tp>;
public:
      using element_type           = const Type;
      using value_type             = std::remove_cv_t<Type>;
      using size_type              = std::size_t;
      using difference_type        = std::ptrdiff_t;
      using const_pointer          = const Type *;
      using const_reference        = const element_type &;
      using const_iterator         = std::span<Type, Extent>::const_iterator;
      using const_reverse_iterator = std::span<Type, Extent>::const_reverse_iterator;

    constexpr ReadOnlySpan() noexcept
        requires(Extent == std::dynamic_extent  ||  Extent == 0) = default;
    
    // Single object span
    explicit constexpr ReadOnlySpan(Type &object) noexcept
        requires ((Extent == std::dynamic_extent  ||  Extent == 1) &&
                  (std::is_arithmetic_v<Type> || std::is_enum_v<Type>))
        :
        _data{ &object, 1 }
    {
    }

    // Conversion from built-in arrays
    template <std::size_t ArrayExtent>
        requires (Extent == std::dynamic_extent  ||  ArrayExtent == Extent)
    constexpr ReadOnlySpan(std::type_identity_t<Type> (&arr)[ArrayExtent]) noexcept
        :
        _data{ arr }
    {
    }

    template <typename Tp, size_t ArrayExtent>
        requires (is_compatible_array<Tp, ArrayExtent>::value)
    constexpr ReadOnlySpan(std::array<Tp, ArrayExtent> &arr) noexcept
        :
        _data{ arr }
    {
    }

    template <typename Tp, size_t ArrayExtent>
        requires (is_compatible_array<const Tp, ArrayExtent>::value)
    explicit constexpr ReadOnlySpan(const std::array<Tp, ArrayExtent> &arr) noexcept
        :
        _data{ arr }
    {
    }

    constexpr ReadOnlySpan(std::span<Type, Extent> from)
        :
        _data{ from }
    {
    }

    constexpr ReadOnlySpan(std::span<const Type, Extent> from)
        :
        _data{ from }
    {
    }

    ReadOnlySpan(Type &&object) = delete;

    static constexpr size_t extent = std::span<Type, Extent>::extent;

    static constexpr ReadOnlySpan<Type> Empty() { return ReadOnlySpan<Type>(); }

    constexpr bool IsEmpty() const { return _data.empty(); }

    constexpr size_t Length() const { return _data.size(); }

    ReadOnlySpan Slice(std::size_t start, std::size_t length = std::dynamic_extent)
    {
        if ( start >= Length() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"start"} );
        if ( (length != std::dynamic_extent) && ((start + length) >= Length()) )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"length"} );

        return ReadOnlySpan( _data.subspan( start, length ) );
    }

    void CopyTo(Span<Type> destination) const
    {
        if ( destination.Length() < Length() )
            ThrowWithTarget( System::ArgumentException{"Destination Span is shorter than the source ReadOnlySpan", "destination"} );
        
        std::ranges::copy( _data, destination._data.begin() );
    }

    bool TryCopyTo(Span<Type> destination)
    {
        if ( destination.Length() < Length() )
            return false;
        
        std::ranges::copy( _data, destination._data.begin() );
        return true;
    }

    constexpr const_reference operator [](size_t index) const
    {
        return _data[index];
    }

    // C++ specific pleasantries
    constexpr const_pointer data() const { return _data.data(); }
    constexpr size_type size_bytes() const { return _data.size_bytes(); }

    ReadOnlySpan<std::byte> as_bytes() const { return ReadOnlySpan<std::byte>{ std::as_bytes( _data ) }; }

    // Make work with foreach
    constexpr const_iterator begin()  const noexcept { return _data.begin(); }
    constexpr const_iterator cbegin() const noexcept { return _data.cbegin(); }

    constexpr const_iterator end()   const noexcept { return _data.end();   }
    constexpr const_iterator cend()  const noexcept { return _data.cend();   }

    constexpr const_iterator rbegin()  const noexcept { return _data.rbegin(); }
    constexpr const_iterator crbegin() const noexcept { return _data.crbegin(); }

    constexpr const_iterator rend()  const noexcept { return _data.rend();   }
    constexpr const_iterator crend() const noexcept { return _data.crend();   }
protected:
    std::span<const Type, Extent> _data;
};

template <typename SpecializedType, std::size_t Extent>
class ReadOnlySpan<const SpecializedType, Extent> : public ReadOnlySpan<SpecializedType, Extent>
{
public:
    using ReadOnlySpan<SpecializedType, Extent>::ReadOnlySpan;
};


// Deduction guides
template <typename Type>
ReadOnlySpan(Type &) -> ReadOnlySpan<Type, 1>;

template <typename Type, size_t Extent>
ReadOnlySpan(Type (&)[Extent]) -> ReadOnlySpan<Type, Extent>;

template <typename Type, size_t ArrayExtent>
ReadOnlySpan(std::array<Type, ArrayExtent> &) -> ReadOnlySpan<Type, ArrayExtent>;

template <typename Type, size_t ArrayExtent>
ReadOnlySpan(const std::array<Type, ArrayExtent> &) -> ReadOnlySpan<Type, ArrayExtent>;

}

}