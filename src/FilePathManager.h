#pragma once
#include <string>
#include <vector>

/*
    Подробно описание в FilePathManager.cpp
*/
class FilePathManager{

    public:

    void filepaths_to_archive_names(const std::vector<std::string>& filenames, std::vector<std::string>& out) const;
    void filepaths_to_readable_files(const std::vector<std::string>& filenames, std::vector<std::string>& out) const;
};