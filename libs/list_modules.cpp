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

    std::regex pattern(R"(^(module|export module) ([a-zA-Z:_]+);)");
    std::string line;

    while (std::getline(file, line)) {
        std::smatch match;

        if (std::regex_search(line, match, pattern)) {
            std::string kind;

            if (match[1] == "module") {
                kind = "implementation";
            }
            else if (match[1] == "export module") {
                kind = "interface";
            }

            std::string module_name = match[2];

            std::cout << module_name << '\t' << kind << '\t' << filename << '\n';
        }
    }
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        scan_file(argv[i]);
    }
    return EXIT_SUCCESS;
}
