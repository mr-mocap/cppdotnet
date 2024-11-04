#pragma once

#include <span>
#include <type_traits>

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
      using pointer                = Type*;
      using const_pointer          = const Type*;
      using reference              = element_type&;
      using const_reference        = const element_type&;
      using iterator               = std::span<Type, Extent>::iterator;
      using reverse_iterator       = std::span<Type, Extent>::reverse_iterator;

    constexpr Span() noexcept
        requires(Extent == std::dynamic_extent  ||  Extent == 0)
    {
    }
    
    // Single object span
    explicit constexpr Span(Type &object)
        requires (Extent == std::dynamic_extent  ||  Extent == 1)
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


    static constexpr Span<Type> Empty() { return Span<Type>(); }

    constexpr bool IsEmpty() const { return _data.empty(); }

    constexpr size_t Length() const { return _data.size(); }

    constexpr const Type &operator [](size_t index) const
    {
        return _data[index];
    }

    constexpr Type &operator [](size_t index)
    {
        return _data[index];
    }
protected:
    std::span<Type> _data;
};

// Deduction guides
template<typename Type>
Span(Type &) -> Span<Type, 1>;

template<typename Type, size_t Extent>
Span(Type (&)[Extent]) -> Span<Type, Extent>;

template<typename Type, size_t Extent>
Span(std::array<Type, Extent> &) -> Span<Type, Extent>;

template<typename Type, size_t Extent>
Span(const std::array<Type, Extent> &) -> Span<const Type, Extent>;

}