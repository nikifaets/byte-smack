#pragma once
#include "Bitset.h"
#include "Global.h"
#include "Encoder.h"

class Archiver{

    CodeTable code_table;
    Encoder encoder;
    
    public:

    void compress(const std::string& archive, const std::vector<std::string>& files);
    bool decompress(const std::string& archive, const std::string& out_dir, const std::vector<std::string>& files);
    void add_to_archive(const std::string& archive_name, const std::string& filename);
};