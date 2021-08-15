#pragma once
#include "Bitset.h"
#include "Global.h"
#include "Encoder.h"

class Archiver{

    CodeTable code_table;
    Encoder encoder;
    
    public:

    void compress(const std::string& archive, const std::vector<std::string>& files);
    bool decompress(const std::string& archive, const std::string& out_dir, const std::vector<std::string>& files, bool get_info=false);
    void modify_archived_file(const std::string& archive_filepath, const std::string& filename, const std::string& modified_filepath);
    void print_info(const int arch_size, const int sum_files_sizes, const std::vector<std::string>& files_in_archive);
};