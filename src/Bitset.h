#pragma once

#include <vector>
#include <string>

class BitReference{

    friend class Bitset;

    unsigned long long dummy;
    unsigned long long& l = dummy;
    int bit;

    BitReference();
    BitReference(unsigned long long& l, int bit);

    public:
    
    BitReference& operator= (const bool val);
    operator bool() const;
    unsigned long long& long_val();
};
class Bitset{

    const int LL_BITS = 64;
    std::vector<unsigned long long> bits;
    int next_free_bit=0;

    public:
    
    void add(bool bit);
    void reserve(int len);
    operator std::string();
    Bitset();
    Bitset& operator+ (Bitset& o);
    Bitset& operator= (Bitset& o);
    Bitset& operator+= (Bitset& o);
    BitReference operator [] (int idx);

};