#include "System/Exception.hpp"


namespace System::Collections::Generic
{

class KeyNotFoundException : public SystemException
{
public:
    using SystemException::SystemException;

    KeyNotFoundException() = default;

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    KeyNotFoundException(const KeyNotFoundException &) = delete;
    KeyNotFoundException &operator =(const KeyNotFoundException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    KeyNotFoundException(KeyNotFoundException &&other)
        :
        SystemException( std::move(other) )
    {
    }
    KeyNotFoundException &operator =(KeyNotFoundException &&other)
    {
        SystemException::operator =( std::move(other) );
        return *this;
    }
    /// @}

    explicit KeyNotFoundException(const char *message) : KeyNotFoundException( std::string_view{message} ) { }
    explicit KeyNotFoundException(std::string_view message) : SystemException( message ) { }

    explicit KeyNotFoundException(const char *message,
                                  Exception &&inner_exception)
        :
        KeyNotFoundException( std::string_view{message}, std::move(inner_exception) )
    {
    }
    explicit KeyNotFoundException(std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, std::move(inner_exception) )
    {
    }

    std::string_view ClassName() const override;
};

}