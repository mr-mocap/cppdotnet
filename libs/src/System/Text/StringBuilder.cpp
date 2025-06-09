#include "System/Text/StringBuilder.hpp"
#include "System/Convert.hpp"
#include "System/Environment.hpp"
#include <exception>


namespace System::Text
{

static size_t NumberOfTimesOccursIn(const std::string &origin, std::string_view substring)
{
    size_t occurrences = 0;
    size_t start_pos = 0;

    while (true)
    {
        size_t new_start_pos = origin.find( substring, start_pos );

        if ( new_start_pos == std::string::npos )
            break;
        start_pos = new_start_pos + substring.length();
        ++occurrences;
    }
    return occurrences;
}

StringBuilder &StringBuilder::Append(bool value)
{
    std::string_view string_value = System::Convert::ToString(value);

    if ( (Length() + string_value.length()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( System::Convert::ToString(value) );
    return *this;
}

StringBuilder &StringBuilder::Append(std::byte value)
{
    if ( (Length() + 1) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( System::Convert::ToString(value) );
    return *this;
}

StringBuilder &StringBuilder::Append(char value)
{
    if ( (Length() + 1) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.push_back( value );
    return *this;
}

StringBuilder &StringBuilder::Append(const char *value)
{
    return Append( std::string_view{value} );
}

StringBuilder &StringBuilder::Append(std::string_view value)
{
    if ( (Length() + value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( value );
    return *this;
}

StringBuilder &StringBuilder::Append(const std::string &value)
{
    if ( (Length() + value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( value );
    return *this;
}

StringBuilder &StringBuilder::Append(const StringBuilder &other_builder)
{
    if ( (Length() + other_builder.Length()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"other_builder", "Operation forces object to exceed MaxCapacity"} );

    _string.append( other_builder.ToString() );
    return *this;
}

StringBuilder &StringBuilder::Append(int16_t value)
{
    std::string str_value = System::Convert::ToString(value);

    if ( (Length() + str_value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( str_value );
    return *this;
}

StringBuilder &StringBuilder::Append(int32_t value)
{
    std::string str_value = System::Convert::ToString(value);

    if ( (Length() + str_value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( str_value );
    return *this;
}

StringBuilder &StringBuilder::Append(int64_t value)
{
    std::string str_value = System::Convert::ToString(value);

    if ( (Length() + str_value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( str_value );
    return *this;
}

StringBuilder &StringBuilder::Append(uint16_t value)
{
    std::string str_value = System::Convert::ToString(value);

    if ( (Length() + str_value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( str_value );
    return *this;
}

StringBuilder &StringBuilder::Append(uint32_t value)
{
    std::string str_value = System::Convert::ToString(value);

    if ( (Length() + str_value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( str_value );
    return *this;
}

StringBuilder &StringBuilder::Append(uint64_t value)
{
    std::string str_value = System::Convert::ToString(value);

    if ( (Length() + str_value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( str_value );
    return *this;
}

StringBuilder &StringBuilder::Append(float value)
{
    std::string str_value = System::Convert::ToString(value);

    if ( (Length() + str_value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( str_value );
    return *this;
}

StringBuilder &StringBuilder::Append(double value)
{
    std::string str_value = System::Convert::ToString(value);

    if ( (Length() + str_value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );

    _string.append( str_value );
    return *this;
}

StringBuilder &StringBuilder::Replace(std::string_view old_value, std::string_view new_value)
{
    if ( old_value.empty() )
        ThrowWithTarget( ArgumentException{"Argument is empty", "old_value"} );

    size_t how_many_times = NumberOfTimesOccursIn( _string, old_value );
    size_t original_length_without_old_substrings = _string.length() - how_many_times * old_value.length();
    size_t new_length = original_length_without_old_substrings + how_many_times * new_value.length();

    if ( new_length > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"this", "Object would exceed MaxCapacity"} );

    std::string temp;

    temp.reserve(new_length); // Adjust the new size to be the size of the resulting replacement

    // Now, just copy chunks
    {
        std::pair<size_t, size_t> chunk{0, 0}; // <start_pos, found_pos>

        while (true)
        {
            chunk.second = _string.find(old_value, chunk.first);

            if ( chunk.second == std::string::npos )
            {
                // We found the last chunk!
                temp.append( _string, chunk.first );
                break;
            }

            // The general case, where we need to search for the next chunk...
            
            // First, copy the common part of the original string...
            temp.append( _string, chunk.first, chunk.second - chunk.first );

            // And then insert the new value where the old value would have been...
            temp.append( new_value );

            // Finally, move the new write position into chunk.first...
            chunk.first = chunk.second + old_value.length();
        }
    }

    _string = temp;
    return *this;
}

StringBuilder &StringBuilder::AppendLine()
{
    std::string_view str_value = System::Environment::NewLine();

    if ( (Length() + str_value.size()) > MaxCapacity() )
        ThrowWithTarget( ArgumentOutOfRangeException{"<None>", "Operation forces object to exceed MaxCapacity"} );

    _string.append( str_value );
    return *this;
}

StringBuilder &StringBuilder::AppendLine(std::string_view value)
try
{
    return Append(value).AppendLine();
}
catch (const std::length_error &e)
{
    ThrowWithTarget( ArgumentOutOfRangeException{"value", "Operation forces object to exceed MaxCapacity"} );
    return *this;
}

}