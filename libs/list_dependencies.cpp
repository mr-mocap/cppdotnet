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

    std::regex pattern(R"((import|#include)\s*([<"])([^">]+)[">])");
    std::string line;

    while (std::getline(file, line)) {
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            std::string kind = match[1];
            std::string bracket = match[2];
            std::string path = match[3];
            std::string type = (bracket == "<") ? "system" : "user";
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
