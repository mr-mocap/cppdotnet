module;

export module System:BitConverter;

import System:Exception;
export import <vector>;
export import <array>;
export import <span>;
import <type_traits>;
import <cstdint>;
export import <cstddef>;
import <cstring>;
import <bit>;

namespace System
{

export
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
        if ( (index + sizeof(bool)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToBoolean( { &bytes[index], sizeof(bool) } );
    }

    static constexpr bool ToBoolean(std::span<const std::byte> bytes)
    {
        return To<bool>( bytes );
    }

    static constexpr char ToChar(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );
        if ( (index + sizeof(char)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToChar( { &bytes[index], sizeof(char) } );
    }

    static constexpr char ToChar(std::span<const std::byte> bytes)
    {
        return To<char>( bytes );
    }

    static constexpr std::int16_t ToInt16(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );
        if ( (index + sizeof(std::int16_t)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToInt16( { &bytes[index], sizeof(std::int16_t) } );
    }
    static constexpr std::int16_t ToInt16(std::span<const std::byte> bytes)
    {
        return To<std::int16_t>( bytes );
    }

    static constexpr std::int32_t ToInt32(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );
        if ( (index + sizeof(std::int32_t)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToInt32( { &bytes[index], sizeof(std::int32_t) } );
    }
    static constexpr std::int32_t ToInt32(std::span<const std::byte> bytes)
    {
        return To<std::int32_t>( bytes );
    }

    static constexpr std::int64_t ToInt64(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );
        if ( (index + sizeof(std::int64_t)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToInt64( { &bytes[index], sizeof(std::int64_t) } );
    }
    static constexpr std::int64_t ToInt64(std::span<const std::byte> bytes)
    {
        return To<std::int64_t>( bytes );
    }

    static constexpr std::uint16_t ToUInt16(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );
        if ( (index + sizeof(std::uint16_t)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToUInt16( { &bytes[index], sizeof(std::uint16_t) } );
    }
    static constexpr std::uint16_t ToUInt16(std::span<const std::byte> bytes)
    {
        return To<std::uint16_t>( bytes );
    }

    static constexpr std::uint32_t ToUInt32(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );
        if ( (index + sizeof(std::uint32_t)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToUInt32( { &bytes[index], sizeof(std::uint32_t) } );
    }
    static constexpr std::uint32_t ToUInt32(std::span<const std::byte> bytes)
    {
        return To<std::uint32_t>( bytes );
    }

    static constexpr std::uint64_t ToUInt64(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );
        if ( (index + sizeof(std::uint64_t)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToUInt64( { &bytes[index], sizeof(std::uint64_t) } );
    }
    static constexpr std::uint64_t ToUInt64(std::span<const std::byte> bytes)
    {
        return To<std::uint64_t>( bytes );
    }

    static constexpr float ToFloat(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );
        if ( (index + sizeof(float)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToFloat( { &bytes[index], sizeof(float) } );
    }
    static constexpr float ToFloat(std::span<const std::byte> bytes)
    {
        return To<float>( bytes );
    }

    static constexpr double ToDouble(const std::vector<std::byte> &bytes, size_t index = 0)
    {
        if ( bytes.empty() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"bytes"} );
        if ( index > bytes.size() )
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );
        if ( (index + sizeof(double)) > bytes.size() ) // Do we have enough bytes to convert to the type?
            ThrowWithTarget( System::ArgumentOutOfRangeException{"index"} );

        return ToDouble( { &bytes[index], sizeof(double) } );
    }
    static constexpr double ToDouble(std::span<const std::byte> bytes)
    {
        return To<double>( bytes );
    }

    // Non-standard methods...
    static constexpr std::uint16_t ByteSwap(std::uint16_t input) noexcept
    {
        return ((input >> 8) & 0x00FF) | // 2nd byte to 1st

               ((input << 8) & 0xFF00);  // 1st byte to 2nd
    }

    static constexpr std::int16_t ByteSwap(std::int16_t input) noexcept
    {
        return std::bit_cast<std::int16_t>( ByteSwap( std::bit_cast<std::uint16_t>(input) ) );
    }

    static constexpr std::uint32_t ByteSwap(std::uint32_t input) noexcept
    {
        return ((input >> (3 * 8)) & 0x000000FF) | // 4th byte to 1st
               ((input >> (1 * 8)) & 0x0000FF00) | // 3rd byte to 2nd

               ((input << (1 * 8)) & 0x00FF0000) | // 2nd byte to 3rd
               ((input << (3 * 8)) & 0xFF000000);  // 1st byte to 4th
    }

    static constexpr std::int32_t ByteSwap(std::int32_t input) noexcept
    {
        return std::bit_cast<std::int32_t>( ByteSwap( std::bit_cast<std::uint32_t>(input) ) );
    }

    static constexpr std::uint64_t ByteSwap(std::uint64_t input) noexcept
    {
        return ((input >> (7 * 8)) & 0x00000000000000FF) | // 8th byte to 1st
               ((input >> (5 * 8)) & 0x000000000000FF00) | // 7th byte to 2nd
               ((input >> (3 * 8)) & 0x0000000000FF0000) | // 6th byte to 3rd
               ((input >> (1 * 8)) & 0x00000000FF000000) | // 5th byte to 4th

               ((input << (1 * 8)) & 0x000000FF00000000) | // 4th byte to 5th
               ((input << (3 * 8)) & 0x0000FF0000000000) | // 3rd byte to 6th
               ((input << (5 * 8)) & 0x00FF000000000000) | // 2nd byte to 7th
               ((input << (7 * 8)) & 0xFF00000000000000);  // 1st byte to 8th
    }

    static constexpr std::int64_t ByteSwap(std::int64_t input) noexcept
    {
        return std::bit_cast<std::int64_t>( ByteSwap( std::bit_cast<std::uint64_t>(input) ) );
    }

    static constexpr float ByteSwap(float input)
    {
        return std::bit_cast<float>( ByteSwap( std::bit_cast<std::uint32_t>(input) ) );
    }

    static constexpr double ByteSwap(double input)
    {
        return std::bit_cast<double>( ByteSwap( std::bit_cast<std::uint64_t>(input) ) );
    }

    template <class BasicType, std::endian Endian = std::endian::native>
        requires( std::is_arithmetic_v<BasicType> || std::is_enum_v<BasicType> )
    static constexpr BasicType To(std::span<const std::byte> bytes) noexcept
    {
        BasicType result; // We do this for memory alignment of the variable type

        std::memcpy( &result, bytes.data(), sizeof(BasicType) );

        if ( Endian != std::endian::native )
        {
            return ByteSwap( result );
        }

        return result;
    }
};

}