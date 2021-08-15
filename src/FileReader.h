#pragma once
#include <string>
#include <fstream>
#include "Global.h"
#include <vector>
#include "Utils.h"

class FileReader{

    bool validate_file(std::ifstream& f) const;

    public:

    template <typename T>
    bool read_bytes(T& res, std::ifstream& f){

        int num_bytes = sizeof(T);
        char* bytes = new char(num_bytes);
        //std::cout << "num bytes " << num_bytes << std::endl;
        
        f.read(bytes, num_bytes);
        for(int i=0; i<num_bytes; i++){
            //utils::print_bits(bytes[i]);
        }
        utils::from_char_array(res, bytes);

        return f.good();
    }
    void read_string(std::string& str, const int len, std::ifstream& f);
    bool read_byte_sequence(std::ifstream& file, std::vector<byte>& res, int num_bytes=2000000);
    bool read_code_table(std::ifstream& archive, CodeTable& code_table, Bitset& special);
    bool read_code(std::ifstream& archive, Bitset& res);
    bool read_and_decode(std::ifstream& archive, std::vector<byte>& res, const DecodeTable& decode_table, const Bitset& special, const int num_bytes=1000000);
};