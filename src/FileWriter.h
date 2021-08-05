#pragma once
#include <string>
#include "Global.h"
#include "Bitset.h"
#include "Encoder.h"
#include "Utils.h"
#include <iostream>

class FileWriter{

    public:

    template<typename T> 
    void write_bytes(T& val, std::ofstream& f){

        int num_bytes = sizeof(val);
        char* buf = new char[num_bytes];

        utils::to_char_array(val, buf, num_bytes);
        
        f.write(buf, num_bytes);

    }
    void write_string(std::ofstream& f, std::string& str);
    void append_archive(std::ofstream& archive_name, Bitset& bitset, bool last=true);
    void write_file(std::ofstream& archive, std::ifstream& f, Encoder& encoder, Bitset& special);
    void write_code_table(std::ofstream& archive, CodeTable& code_table, Bitset& special);
    void append_bytes(std::ofstream& f, std::vector<byte>& bytes);
    void append_bytes_text(std::ofstream& f, std::vector<byte>& bytes);
};