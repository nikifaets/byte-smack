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
    void write_bytes(const T& val, std::ofstream& f){
        
        assert(f.good());
        if(val == (byte)0) std::cout << "write remainder " << std::endl;
        int num_bytes = sizeof(val);
        char* buf = new char[num_bytes];

        //std::cout << "write bytes " << std::endl;

        utils::to_char_array(val, buf, num_bytes);
        for(int i=0; i<num_bytes; i++){
            //utils::print_bits(buf[i]);
        }
        //std::cout << buf[0] << std::endl;
        assert(f.write(buf, num_bytes).good());
        delete [] buf;

    }
    void write_string(std::ofstream& f, const std::string& str);
    void append_archive(std::ofstream& archive_name, Bitset& bitset, bool last=true);
    void write_file(std::ofstream& archive, std::ifstream& f, Encoder& encoder, Bitset& special);
    void write_code_table(std::ofstream& archive, CodeTable& code_table, Bitset& special);
    void append_bytes(std::ofstream& f, std::vector<byte>& bytes);
    void append_bytes_text(std::ofstream& f, std::vector<byte>& bytes);
};