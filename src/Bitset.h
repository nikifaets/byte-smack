#pragma once

#include <vector>
#include <string>
#include "Utils.h"
#include <assert.h>
const int LL_BITS = 64;
typedef unsigned char byte;

class BitReference{

    friend class Bitset;

    unsigned long long dummy;
    unsigned long long& l = dummy;
    int bit;

    BitReference();
    BitReference(unsigned long long& l, int bit);

    public:
    
    BitReference& operator= (const bool val);
    bool operator!= (const BitReference& o) const;
    operator bool() const;
    unsigned long long& long_val();
};



class Bitset{

    std::vector<unsigned long long> bits;
    

    public:
    int next_free_bit = 0;
    Bitset();

    template <typename T>
    Bitset(T code, int len){

        assert(len <= sizeof(T) * 8);

        for(int i=0; i<len; i++){

            add(utils::get_kth_bit(code, i));
        }
    }

    void add(bool bit);
    void reserve(int len);
    operator std::string() const;
    operator byte() const;
    Bitset& operator+ (Bitset& o);
    Bitset& operator= (Bitset& o);
    Bitset& operator+= (Bitset& o);

    BitReference operator [] (int idx);
    bool operator== (Bitset& o) const;
    int size();
    const std::vector<unsigned long long>& longs() const;
    void clear();



};

struct BitsetHash{
    
    std::size_t operator() (const Bitset& b) const;
};