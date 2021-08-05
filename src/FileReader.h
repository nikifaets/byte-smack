#pragma once
#include <string>
#include <fstream>
#include "Global.h"
#include <vector>
#include "Utils.h"

class FileReader{

    bool validate_file(std::ifstream& f);

    public:

    template <typename T>
    bool read_bytes(T& res, std::ifstream& f){

        int num_bytes = sizeof(T);
        char* bytes = new char(num_bytes);

        f.read(bytes, num_bytes);

        utils::from_char_array(res, bytes);

        return f.good();
    }
    void read_string(std::ifstream& f, std::string& str, int len);
    bool read_byte_sequence(std::ifstream& file, std::vector<byte>& res, int num_bytes=20000);
    bool read_code_table(std::ifstream& archive, CodeTable& code_table, Bitset& special);
    bool read_code(std::ifstream& archive, Bitset& res);
    bool read_and_decode(std::ifstream& archive, std::vector<byte>& res, DecodeTable& decode_table, Bitset& special, int num_bytes=10000);
};