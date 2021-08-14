#pragma once
#include <string>
#include <vector>
class FilePathManager{

    public:

    void process_filename(const std::vector<std::string>& filenames, std::vector<std::string>& out);
    void dirnames_to_readable_files(const std::vector<std::string>& filenames, std::vector<std::string>& out);
};