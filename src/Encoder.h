#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "HNode.h"

typedef unsigned char uchar;

class Encoder{

    static const int BYTES_COUNT = 256;


    std::vector<int> freq_table;
    void prefill_table();
    void codes_from_tree(HNode*& root);
    public:

    bool write_archive(std::string& buf, std::string& out);
    void get_table(std::vector<int>& out);
    void update_table(std::string str);
    Encoder();
};