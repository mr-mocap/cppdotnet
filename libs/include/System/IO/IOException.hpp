#include "System/Exception.hpp"


namespace System::IO
{

class IOException : public SystemException
{
public:
    using SystemException::SystemException;

    IOException() = default;

    /** Remove the ability to copy objects of this class
     *
     *  @{
     */
    IOException(const IOException &) = delete;
    IOException &operator =(const IOException &) = delete;
    /// @}

    /** Define the ability to move objects of this class
     *
     *  @{
     */
    IOException(IOException &&other)
        :
        SystemException( std::move(other) )
    {
    }
    IOException &operator =(IOException &&other)
    {
        SystemException::operator =( std::move(other) );
        return *this;
    }
    /// @}

    explicit IOException(const char *message) : IOException( std::string_view{message} ) { }
    explicit IOException(std::string_view message) : SystemException( message ) { }

    explicit IOException(const char *message,
                         Exception &&inner_exception)
        :
        IOException( std::string_view{message}, std::move(inner_exception) )
    {
    }
    explicit IOException(std::string_view message, Exception &&inner_exception)
        :
        SystemException( message, std::move(inner_exception) )
    {
    }

    std::string_view ClassName() const override;
};

}