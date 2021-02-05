#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "HNode.h"
#include "CodeTable.h"
#include <bitset>
#include "Global.h"
class Encoder{

    static const int BYTES_COUNT = 256;


    std::vector<int> freq_table;
    CodeTable code_table;
    void prefill_table();
    void code_table_to_bitset(CodeTable& code_table);
    bool get_kth_bit(byte code, int k);
    public:

    bool write_archive(std::string& buf, std::string& out);
    void get_table(std::vector<int>& out);
    void update_table(std::string str);
    void create_codes();
    Encoder();
};