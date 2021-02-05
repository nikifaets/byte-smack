#pragma once

#include <vector>
#include <string>

class Bitset{

    const int LL_BITS = 64;
    std::vector<unsigned long long> bits;
    int next_free_bit=0;

    public:
    
    void add(bool bit);
    operator std::string();

};