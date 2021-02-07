#pragma once
#include "Bitset.h"
#include "Global.h"
#include "Encoder.h"

class Archiver{

    CodeTable code_table;
    Encoder encoder;
    
    public:

    void compress(std::string& archive, std::vector<std::string>& files);
    bool decompress(std::string& archive, std::string& out_dir);
    void add_to_archive(std::string& archive_name, std::string& filename);
};