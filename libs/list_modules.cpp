#include <cstddef>
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <string_view>
#include <format>


struct ModulesReferenced {
    std::string module_name; // module name
    std::string kind; // implementation, interface
    std::string filename; // source file where the module is defined
};

std::ifstream OpenFile(const char *filename) {
    std::ifstream file(filename);

    if (!file) {
        throw std::runtime_error( std::format("Error opening file: {}", filename) );
    }
    return file;
}

ModulesReferenced Scan(std::istream &input, std::string_view filename) {
    std::regex pattern(R"(^(module|export module) ([a-zA-Z:_0-9-]+);)");
    std::string line;
    ModulesReferenced references;

    references.filename = filename;
    while (std::getline(input, line)) {
        std::smatch match;

        if (std::regex_search(line, match, pattern)) {
            std::string kind;

            if (match[1] == "module") {
                references.kind = "implementation";
            }
            else if (match[1] == "export module") {
                references.kind = "interface";
            }

            references.module_name = match[2];
        }
    }
    return references;
}

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        const char *filename = argv[i];

        try
        {
            std::ifstream     file       = OpenFile(filename);
            ModulesReferenced references = Scan(file, filename);

            std::cout << references.module_name << '\t' << references.kind << '\t' << references.filename << '\n';
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    return EXIT_SUCCESS;
}
