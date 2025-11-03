#pragma once

#include <cppdotnet/System/Xml/XmlNameTable.hpp>
#include <unordered_set>
#include <string>

namespace System::Xml
{

class NameTable : public XmlNameTable
{
  public:
    NameTable() = default;
   ~NameTable() override = default;

    NameTable(const NameTable &other);
    NameTable &operator=(const NameTable &other);

    NameTable(NameTable &&other);
    NameTable &operator=(NameTable &&other);

    /** Adds a name to the name table.
     *  
     *  @param name The name to add
     * 
     *  @return std::string_view The internal string_view representing the added name
     * 
     *  @exception System::ArgumentNullException Thrown if @p name is an empty string
     */
    std::string_view Add(std::string_view name) override;

    /** Retrieves a name from the name table.
     *   
     *   @param name The name to look up
     * 
     *   @return std::string_view The internal string_view if found, or an empty string_view if not found
     * 
     *   @exception System::ArgumentNullException Thrown if @p name is an empty string
     */
    std::string_view Get(std::string_view name) const override;

protected:
    /** @name Internal Helper Classes
     *  @{
     */
    struct TransparentHash
    {
        using is_transparent = void;

        std::size_t operator()(std::string_view sv) const noexcept
        {
            return std::hash<std::string_view>{}(sv);
        }

        std::size_t operator()(std::string &s) const noexcept
        {
            return std::hash<std::string>{}(s);
        }
    };

    struct TransparentEqual
    {
        using is_transparent = void;

        bool operator()(std::string_view lhs, std::string_view rhs) const noexcept
        {
            return lhs == rhs;
        }

        bool operator()(const std::string &lhs, const std::string &rhs) const noexcept
        {
            return lhs == rhs;
        }

        bool operator()(std::string_view lhs, const std::string &rhs) const noexcept
        {
            return lhs == rhs;
        }

        bool operator()(const std::string &lhs, std::string_view rhs) const noexcept
        {
            return lhs == rhs;
        }
    };
    /// @}

    std::unordered_set<std::string, TransparentHash, TransparentEqual> _names;
};

}