#pragma once

#include "System/Exception.hpp"
#include <vector>
#include <ranges>
#include <span>
#include <type_traits>
#include <cstddef>
#include <cstring>

namespace System
{

struct BitConverter final
{
    template <class BasicType>
    static constexpr std::vector<std::byte> GetBytes(BasicType value)
        requires( std::is_arithmetic_v<BasicType> || std::is_enum_v<BasicType> )
    {
        auto bytes = std::bit_cast< std::array<std::byte, sizeof(BasicType)> >(value);

        return { bytes.begin(), bytes.end() };
    }
    
    static constexpr bool ToBoolean(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<bool>( { &bytes[index], sizeof(bool) } );
    }

    static constexpr char ToChar(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<char>( { &bytes[index], sizeof(char) } );
    }

    static constexpr std::int16_t ToInt16(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<std::int16_t>( { &bytes[index], sizeof(std::int16_t) } );
    }

    static constexpr std::int32_t ToInt32(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<std::int32_t>( { &bytes[index], sizeof(std::int32_t) } );
    }

    static constexpr std::int64_t ToInt64(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<std::int64_t>( { &bytes[index], sizeof(std::int64_t) } );
    }

    static constexpr std::uint16_t ToUInt16(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<std::uint16_t>( { &bytes[index], sizeof(std::uint16_t) } );
    }

    static constexpr std::uint32_t ToUInt32(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<std::uint32_t>( { &bytes[index], sizeof(std::uint32_t) } );
    }

    static constexpr std::uint64_t ToUInt64(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<std::uint64_t>( { &bytes[index], sizeof(std::uint64_t) } );
    }

    static constexpr float ToFloat(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<float>( { &bytes[index], sizeof(float) } );
    }

    static constexpr double ToDouble(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return To<double>( { &bytes[index], sizeof(double) } );
    }

protected:
    template <class BasicType>
    static constexpr BasicType To(std::span<const std::byte> bytes) requires( std::is_arithmetic_v<BasicType> || std::is_enum_v<BasicType> )
    {
        BasicType result; // We do this for memory alignment of the variable type

        std::memcpy( &result, bytes.data(), sizeof(BasicType) );
        return result;
    }
};

}