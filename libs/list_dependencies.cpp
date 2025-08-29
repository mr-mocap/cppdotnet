#include <cstddef>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>

void scan_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening " << filename << "\n";
        return;
    }

    std::regex pattern(R"(^(import|#include|export import)[[:space:]]+(["<][^">]+[">]|[a-zA-Z:_]+))");
    std::string line;

    while (std::getline(file, line)) {
        std::smatch match;

        if (std::regex_search(line, match, pattern)) {
            std::string kind = match[1];
            std::string bracket = match[2];

            if (bracket.empty())
                continue;

            std::string type = "unknown";;

            if (bracket.front() == '<' && bracket.back() == '>')
                type = "system";
            else if (bracket.front() == '\"' && bracket.back() == '\"')
                type = "user";
            else
                type = "user";

            std::string path;

            if ( (bracket.front() == '<' && bracket.back() == '>') || (bracket.front() == '\"' && bracket.back() == '\"') ) {
                // Remove angle brackets/double quotes
                path = bracket.substr(1, bracket.size() - 2);
            } else {
                path = bracket;
            }

            std::cout << filename << '\t' << kind << '\t' << type << '\t' << path << "\n";
        }
    }
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        scan_file(argv[i]);
    }
    return EXIT_SUCCESS;
}
