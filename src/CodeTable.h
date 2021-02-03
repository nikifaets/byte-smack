#pragma once

#include <unordered_map>

class CodeTable{

    struct CodeLengthPair{

        char code;
        int length;

    };

    typedef CodeLengthPair code_len;

    std::unordered_map<char, code_len> table;
    void prefill_table();

    public:

    char get_code(char& orig) const;
    int get_code_len(char& orig) const;
};
