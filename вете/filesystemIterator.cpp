#include "filesystemIterator.h"
#include <filesystem>
#include <string>
#include <vector>
#include <regex>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

FilesystemIterator::FilesystemIterator() {}

FilesystemIterator::~FilesystemIterator() {}

void replace_all(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty()) return;
    int start = 0;

    while((start = str.find(from, start)) != std::string::npos) {
        str.replace(start, from.length(), to);
        start += to.length();
    }
}

void translate_to_regex(std::string& pattern) {
    replace_all(pattern, "(", "\\(");
    replace_all(pattern, ")", "\\)");
    replace_all(pattern, "[", "\\[");
    replace_all(pattern, "]", "\\]");
    replace_all(pattern, ".", "\\.");
    replace_all(pattern, "?", ".");
    replace_all(pattern, "*", "[^/]*");
    pattern += ".*";

    std::cout << pattern << std::endl;
}

std::string get_root_dir(std::string path) {

    std::string root_dir = "";
    for (char& c: path) {
        if (c == '/') break;
        root_dir += c;
    }
    root_dir += "/";

    return root_dir;
}

std::vector<std::string> FilesystemIterator::search(std::vector<std::string> args) {
    std::vector<std::string> result;

    for (auto pattern : args) {

        std::string root_dir = get_root_dir(pattern);
        translate_to_regex(pattern);
        std::regex re(pattern);

        for (const auto& dir : recursive_directory_iterator(root_dir)) {

            if (std::regex_match(dir.path().string(), re)) {
                std::string path = dir.path().string();
                std::error_code ec;

                if (ec) {
                    std::cerr << "Error: " << ec.message();
                }

                if (!std::filesystem::is_directory(path, ec)) {
                    result.push_back(dir.path().string());
                }
            }
        }
    }

    return result;
}
