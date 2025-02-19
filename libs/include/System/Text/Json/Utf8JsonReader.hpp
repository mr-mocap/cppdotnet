#pragma once

#include "System/Text/Json/JsonReaderState.hpp"
#include "System/Text/Json/JsonTokenType.hpp"
#include "System/ReadOnlySpan.hpp"
#include "System/Private/private.hpp"

#include <cstddef>


namespace System::Text::Json
{

class Utf8JsonReader
{
public:
#if 0
    constexpr explicit Utf8JsonReader(ReadOnlySpan<std::byte> jsonData, const JsonReaderOptions options = JsonReaderOptions())
        :
        _current_state{ options },
        _json_data{ jsonData }
    {
    }
#endif
#if 0
    constexpr explicit Utf8JsonReader(ReadOnlySpan<const std::byte> jsonData, const JsonReaderOptions options = JsonReaderOptions())
        :
        _current_state{ options },
        _json_data{ std::span<std::byte>{ const_cast<std::byte *>(jsonData.begin()), jsonData.Length() } }
    {
    }
#endif

    size_t BytesConsumed() const { return _bytes_consumed; }

    int CurrentDepth() const { return _current_depth; }

    const JsonReaderState &CurrentState() const { return _current_state; }

    /** Gets a value that indicates which Value property to use to get the token value
     */
    bool HasValueSequence();

    /** Gets a value that indicates whether all the JSON data was provided or there is more data to come
     */
    bool IsFinalBlock();

    /** Gets the current SequencePosition within the provided UTF-8 encoded input ReadOnlySequence<byte> or a default SequencePosition if the Utf8JsonReader struct was constructed with a ReadOnlySpan<byte>
     */
    //SequencePosition Position();

    /** Gets the index that the last processed JSON token starts at (within the given UTF-8 encoded input text), skipping any white space
     */
    size_t TokenStartIndex();

    /** The type of the last processed JSON token
     */
    JsonTokenType TokenType() const;

    /** A read-only span of bytes
     */
    ReadOnlySpan<std::byte> ValueSpan();

    /** Reads the next JSON token from the input source
     *  
     *  @return @c true if the token was read successfully;  otherwise, @c false
     * 
     *  @exception JsonException
     *             An invalid JSON token according to the JSON RFC is encountered
     *              OR
     *             The current depth exceeds the recursive limit set by the maximum depth.
     */
    bool Read();
protected:
    size_t _bytes_consumed = 0;
    int    _current_depth  = 0;
    JsonReaderState _current_state;
    ReadOnlySpan<std::byte> _json_data;
};

}