#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <string_view>
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <cstdlib>
#include <iterator>
#include <algorithm>


using Dependency = std::pair<std::string, std::vector<std::string>>;
using Dependencies = std::unordered_map<std::string, std::vector<std::string>>;
using StringList = std::vector<std::string>;

std::string_view IncludeDir = "include/";

void AddPrefix(std::string &filename)
{
    if ( !filename.starts_with( IncludeDir ) )
        filename.insert( 0, IncludeDir );
}

StringList AddPrefix(StringList &&list)
{
    for (std::string &i : list)
        AddPrefix( i );
    return list;
}

StringList ReadFileNamesFrom(std::istream &istream)
{
    StringList filenames;

    for (std::string line; std::getline(istream, line); )
    {
        std::istringstream iss( line );
        StringList words{ 
            std::istream_iterator<std::string>{ iss },
            std::istream_iterator<std::string>{}
        };

        std::ranges::copy( words, std::back_inserter( filenames ) );
    }

    return filenames;
}

StringList SearchFileForPattern(std::string &filename)
{
    std::ifstream input( filename );

    if ( !input.is_open() )
        return { };
    
    std::string line;
    StringList  valid_lines;

    while ( std::getline(input, line) )
    {
        if ( line.starts_with("import \"") && line.ends_with("\";") )
        {
            size_t first_quote = line.find('\"') + 1;

            valid_lines.emplace_back( line.substr( first_quote, line.size() - first_quote - 2) );
        }
    }
    return valid_lines;
}

Dependency GenerateDependency(std::string filename)
{
    return std::make_pair( filename, AddPrefix( SearchFileForPattern( filename ) ) );
}

Dependencies GenerateDependencies(const StringList &files_to_process)
{
    Dependencies dependencies;

    for (const std::string &filename : files_to_process)
    {
        Dependency d = GenerateDependency( filename );

        if ( !d.second.empty() )
        {
            Dependencies recursive_dependencies = GenerateDependencies( d.second );

            for (const Dependency &recursive_d : recursive_dependencies)
                dependencies.emplace( recursive_d );
        }

        dependencies.emplace( d );
    }

    return dependencies;
}

std::unordered_map<std::string, int> CalculateReferenceCounts(const Dependencies &dependencies)
{
    std::unordered_map<std::string, int> in_degree;

    for (const auto &[file, deps] : dependencies)
    {
        for (const auto &dep : deps)
            in_degree[dep]++;
    }
    return in_degree;
}

std::queue<std::string> FindHeadersWithNoDependencies(                  const Dependencies &dependencies,
                                                      std::unordered_map<std::string, int> &out_degrees)
{
    std::queue<std::string> ready;

    for (const auto &[file, _] : dependencies) {
        if ( out_degrees[file] == 0 ) {
            ready.emplace(file);
        }
    }
    return ready;
}

StringList CalculateBuildOrder(Dependencies                         &dependencies,
                               std::unordered_map<std::string, int> &degree,
                               std::queue<std::string>              &ready)
{
    StringList build_order;

    // Process the graph
    while (!ready.empty()) {
        std::string file = ready.front();
        
        ready.pop();
        build_order.insert( build_order.begin(), file );

        for (const auto &dep : dependencies[file]) {
            if ( --degree[dep] == 0 ) {
                ready.push( dep );
            }
        }
    }
    return build_order;
}

std::vector<std::string> RemoveDuplicates(std::vector<std::string> &&list)
{
    for (size_t i = 0; i < list.size(); ++i)
    {
        if ( list.size() > 1 )
        {
            auto new_end = std::remove( std::next( list.begin(), i + 1 ), list.end(), list[i] );

            if ( new_end != list.end() )
                list.erase( new_end, list.end() );
        }
    }
    return list;
}

int main(void)
{
    Dependencies dependencies = GenerateDependencies( AddPrefix( ReadFileNamesFrom( std::cin ) ) );
    std::unordered_map<std::string, int> in_degree = CalculateReferenceCounts( dependencies );
    std::queue<std::string>              ready = FindHeadersWithNoDependencies( dependencies, in_degree );

    StringList final_order = RemoveDuplicates( CalculateBuildOrder( dependencies, in_degree, ready ) );

    for (size_t i = 0; i < final_order.size(); ++i)
    {
        if ( i != 0 )
            std::cout << std::endl;
        std::cout << final_order[i];
    }
    return EXIT_SUCCESS;
}