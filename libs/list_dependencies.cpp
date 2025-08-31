#include <cstddef>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <string_view>
#include <vector>
#include <format>

struct Dependency {
    std::string kind; // import, #include, export import
    std::string type; // system, user
    std::string path; // path to the dependency
};

std::ifstream OpenFile(const char *filename) {
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error( std::format("Error opening file: {}", filename) );
    }
    return file;
}

std::vector<Dependency> Scan(std::istream &input) {
    std::vector<Dependency> dependencies;
    std::regex pattern(R"(^(import|#include|export import)[[:space:]]+(["<][^">]+[">]|[a-zA-Z:_]+))");
    std::string line;

    while (std::getline(input, line)) {
        std::smatch match;

        if (std::regex_search(line, match, pattern)) {
            Dependency dep{ .kind = match[1], .type = "unknown", .path = "" };
            std::string bracket = match[2];

            if (bracket.empty())
                continue;

            if (bracket.front() == '<' && bracket.back() == '>')
                dep.type = "system";
            else if (bracket.front() == '\"' && bracket.back() == '\"')
                dep.type = "user";
            else
                dep.type = "module";

            if ( (bracket.front() == '<' && bracket.back() == '>') || (bracket.front() == '\"' && bracket.back() == '\"') ) {
                // Remove angle brackets/double quotes
                dep.path = bracket.substr(1, bracket.size() - 2);
            } else {
                dep.path = bracket;
            }

            dependencies.push_back(dep);
        }
    }
    return dependencies;
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        const char *filename = argv[i];

        try
        {
            std::ifstream input = OpenFile(filename);

            for (const auto &dep : Scan(input)) {
                std::cout << filename << '\t' << dep.kind << '\t' << dep.type << '\t' << dep.path << "\n";
            }
        }
        catch(const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return EXIT_SUCCESS;
}
