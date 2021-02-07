#pragma once
#include <string>
#include <fstream>
#include "Global.h"

class FileReader{

    bool validate_file(std::fstream f);
    public:
    void read_byte_sequence(int num_bytes, std::fstream& file, Bitset& res);
};