import "System/IO/Path.hpp";

namespace System::IO
{

std::string Path::Combine(const std::string &one, const std::string &two)
{
    using namespace std::filesystem;

    if ( (one.find(' ') != std::string::npos) ||
            (two.find(' ') != std::string::npos) )
    {
        return one + two;
    }

    return path( one ) / path( two );
}

std::string Path::Combine(const std::string &one,
                          const std::string &two,
                          const std::string &three)
{
    return Combine( Combine( one, two ), three );
}

std::string Path::Combine(const std::string &one,
                          const std::string &two,
                          const std::string &three,
                          const std::string &four)
{
    return Combine( Combine( Combine( one, two ), three ), four );
}

bool Path::EndsInDirectorySeparator(const std::string &path)
{
    return !path.empty() && (path.back() == DirectorySeparatorChar());
}

}