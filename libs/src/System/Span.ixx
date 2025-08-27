export module System:Span;

export import <span>;
export import <array>;
import <type_traits>;
import <algorithm>;
import System:Exception;

export
{

namespace System
{

template <typename Type, std::size_t Extent = std::dynamic_extent>
class Span
{
    template <typename To, typename From>
    using is_array_convertible = std::is_convertible<From (*)[], To (*)[]>;

    template <typename Tp, std::size_t ArrayExtent>
        requires (Extent == std::dynamic_extent || ArrayExtent == Extent)
	using is_compatible_array = is_array_convertible<Type, Tp>;
public:
    using element_type           = Type;
    using value_type             = std::remove_cv_t<Type>;
    using size_type              = std::size_t;
    using difference_type        = std::ptrdiff_t;
    using pointer                = Type *;
    using const_pointer          = const Type *;
    using reference              = element_type &;
    using const_reference        = const element_type &;
    using iterator               = std::span<Type, Extent>::iterator;
    using reverse_iterator       = std::span<Type, Extent>::reverse_iterator;
#if __cplusplus > 202002L
    using const_iterator         = std::span<Type, Extent>::const_iterator;
    using const_reverse_iterator = std::span<Type, Extent>::const_reverse_iterator;
#else
    using const_iterator         = std::span<const Type, Extent>::iterator;
    using const_reverse_iterator = std::span<const Type, Extent>::reverse_iterator;
#endif

    constexpr Span() noexcept
        requires(Extent == std::dynamic_extent  ||  Extent == 0) = default;
    
    // Single object span
    explicit constexpr Span(Type &object) noexcept
        requires ((Extent == std::dynamic_extent  ||  Extent == 1) &&
                  (std::is_arithmetic_v<Type> || std::is_enum_v<Type>))
        :
        _data{ &object, 1 }
    {
    }

    // Conversion from built-in arrays
    template <std::size_t ArrayExtent>
        requires (Extent == std::dynamic_extent  ||  ArrayExtent == Extent)
    constexpr Span(std::type_identity_t<Type> (&arr)[ArrayExtent]) noexcept
        :
        _data{ arr }
    {
    }

    template <typename Tp, std::size_t ArrayExtent>
        requires is_compatible_array<Tp, ArrayExtent>::value
    constexpr Span(std::array<Tp, ArrayExtent> &arr) noexcept
        :
        _data{ arr }
    {
    }

    template <typename Tp, std::size_t ArrayExtent>
        requires is_compatible_array<const Tp, ArrayExtent>::value
    constexpr Span(const std::array<Tp, ArrayExtent> &arr) noexcept
        :
        _data{ arr }
    {
    }

    Span(Type &&object) = delete;

    constexpr Span(std::span<Type, Extent> from) : _data{ from } { }

    template <std::size_t OtherExtent>
    constexpr Span(std::span<Type, OtherExtent> from) : _data{ from } { }

    static constexpr Span<Type> Empty() { return Span<Type>(); }

    constexpr bool IsEmpty() const { return _data.empty(); }

    constexpr size_type Length() const { return _data.size(); }

    constexpr void Clear() { Fill( Type{} ); }

    constexpr void Fill(const Type &value)
    {
        std::ranges::fill( _data, value );
    }

    Span Slice(std::size_t start, std::size_t length = std::dynamic_extent)
    {
        if ( start >= Length() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"start"} );
        if ( (length != std::dynamic_extent) && ((start + length) >= Length()) )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"length"} );

        return Span( _data.subspan( start, length ) );
    }

    void CopyTo(Span destination) const
    {
        if ( destination.Length() < Length() )
            ThrowWithTarget( System::ArgumentException{"Destination Span is shorter than the source Span", "destination"} );
        
        std::ranges::copy( _data, destination._data.begin() );
    }

    bool TryCopyTo(Span destination)
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

    constexpr reference operator [](size_t index)
    {
        return _data[index];
    }

    // C++ specific pleasantries
    constexpr const_pointer data() const { return _data.data(); }
    constexpr pointer       data()       { return _data.data(); }

    constexpr size_type size_bytes() const { return _data.size_bytes(); }

    Span<const std::byte>   as_bytes() const    { return Span<const std::byte>{ std::as_bytes( _data ) }; }
    Span<std::byte>         as_writable_bytes() { return Span<std::byte>{ std::as_writable_bytes( _data ) }; }

    // Make work with foreach
    constexpr const_iterator begin()  const noexcept { return _data.begin(); }
    constexpr iterator       begin()        noexcept { return _data.begin(); }
    constexpr const_iterator cbegin() const noexcept { return _data.cbegin(); }

    constexpr const_iterator end()  const noexcept { return _data.end();  }
    constexpr iterator       end()        noexcept { return _data.end();  }
    constexpr const_iterator cend() const noexcept { return _data.cend(); }

    constexpr const_iterator rbegin()  const noexcept { return _data.rbegin();  }
    constexpr iterator       rbegin()        noexcept { return _data.rbegin();  }
    constexpr const_iterator crbegin() const noexcept { return _data.crbegin(); }

    constexpr const_iterator rend()  const noexcept { return _data.rend();   }
    constexpr iterator       rend()        noexcept { return _data.rend();   }
    constexpr const_iterator crend() const noexcept { return _data.crend();  }
protected:
    std::span<Type, Extent> _data;

    template <class Tp, std::size_t N>
    friend class ReadOnlySpan;
};

// Deduction guides
template <typename Type>
Span(Type &) -> Span<Type, 1>;

template <typename Type, size_t Extent>
Span(Type (&)[Extent]) -> Span<Type, Extent>;

template <typename Type, size_t ArrayExtent>
Span(std::array<Type, ArrayExtent> &) -> Span<Type, ArrayExtent>;

template <typename Type, size_t ArrayExtent>
Span(const std::array<Type, ArrayExtent> &) -> Span<const Type, ArrayExtent>;

}

}