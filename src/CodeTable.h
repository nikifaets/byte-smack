#pragma once

#include <unordered_map>
struct CodeLengthPair{

    char code;
    int length;

    CodeLengthPair();
    CodeLengthPair(char code, int length);

};

typedef CodeLengthPair code_len;

class CodeTable{



    std::unordered_map<char, code_len> table;
    void prefill_table();

    public:

    CodeTable();
    char get_code(char& orig) const;
    int get_code_len(char& orig) const;

    code_len& operator [] (const char& key);

};
