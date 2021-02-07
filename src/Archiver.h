#pragma once
#include "Bitset.h"
#include "Global.h"


class Archiver{

    CodeTable code_table;
    
    public:

    void compress(std::string archive, std::vector<std::string> files);
    void add_to_archive(std::string archive, std::string filename);
};