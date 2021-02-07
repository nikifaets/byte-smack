#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "HNode.h"
#include <bitset>
#include "Global.h"
#include "Utils.h"
#include "Bitset.h"

class Encoder{

    static const int BYTES_COUNT = 256;


    std::vector<int> freq_table;
    CodeTable code_table;
    DecodeTable decode_table;
    Bitset special;

    void prefill_table();
    void fill_decode_table();

    public:

    void decode_table_from_code(DecodeTable& decode_table, CodeTable& code_table);
    bool write_archive(std::string& buf, std::string& out);
    void get_freq_table(std::vector<int>& out);
    void update_freq_table(std::vector<byte>& bytes);
    void create_codes();
    void codes(CodeTable& res) const;
    void get_decode_table(DecodeTable& res) const;
    void encode(Bitset& res, std::vector<byte> bytes);
    void decode(std::vector<byte>& res, Bitset& codes);
    int count_different_symbols();
    void get_special(Bitset& res);
    Encoder();
};