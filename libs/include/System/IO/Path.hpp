#include <filesystem>


namespace System::IO
{

class Path
{
public:
    static constexpr std::filesystem::path::value_type PathSeparator()
    {
#if defined(_WIN32) && !defined(__CYGWIN__)
        return ';';
#else
        return ':';
#endif
    }

    static constexpr std::filesystem::path::value_type VolumeSeparatorChar()
    {
#if defined(_WIN32) && !defined(__CYGWIN__)
        return ':';
#else
        return '/';
#endif
    }

    static constexpr std::filesystem::path::value_type DirectorySeparatorChar()
    {
        return std::filesystem::path::preferred_separator;
    }

    static constexpr std::filesystem::path::value_type AltDirectorySeparatorChar()
    {
        return '/';
    }

    static std::string ChangeExtension(const std::string &path, const std::string &extension = std::string())
    {
        if ( path.empty() )
            return path;
        return std::filesystem::path( path ).replace_extension( extension );
    }

    static std::string Combine(const std::string &one, const std::string &two);
    static std::string Combine(const std::string &one, const std::string &two, const std::string &three);
    static std::string Combine(const std::string &one, const std::string &two, const std::string &three, const std::string &four);

    static bool EndsInDirectorySeparator(const std::string &path);

    static bool Exists(const std::string &path) { return std::filesystem::exists( path ); }

    static bool HasExtension(const std::string &path) { return std::filesystem::path(path).has_extension(); }
};

}