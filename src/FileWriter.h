#pragma once
#include <string>
#include "Global.h"
#include "Bitset.h"

class FileWriter{

    public:

    void append_archive(std::fstream& archive_name, Bitset& bitset, bool last=true);
    void write_file(std::string& archive_name, Bitset& filename, Bitset& bitset, Bitset& special);
};