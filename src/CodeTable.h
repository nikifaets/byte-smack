#pragma once

#include <unordered_map>
#include "Global.h"

struct CodeLengthPair{

    byte code;
    int length;

    CodeLengthPair();
    CodeLengthPair(byte code, int length);

};

typedef CodeLengthPair code_len;

class CodeTable{



    std::unordered_map<byte, code_len> table;
    void prefill_table();

    public:

    CodeTable();
    byte get_code(byte& orig) const;
    int get_code_len(byte& orig) const;

    code_len& operator [] (const byte& key);

};
