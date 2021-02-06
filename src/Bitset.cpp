#include "Bitset.h"
#include "Utils.h"
#include <iostream>
#include <assert.h>
#include <bitset>


BitReference::BitReference() {}
BitReference::BitReference(unsigned long long& l, int bit) : l(l), bit(bit) {}

BitReference::operator bool() const{

    return utils::get_kth_bit(l, bit);
}

BitReference& BitReference::operator=(const bool val){

    if(utils::get_kth_bit(l, bit) != val){
        utils::toggle_kth_bit(l, bit);
    }

    return *this;
    
}

unsigned long long& BitReference::long_val(){

    return l;
}

Bitset::Bitset() {}

void Bitset::add(bool bit){

    if(next_free_bit % LL_BITS == 0){

        bits.push_back(0);
        next_free_bit = 0;
    }

    int last_idx = bits.size() - 1;

    if(bit){

        utils::set_kth_bit(bits[last_idx], next_free_bit);
    }
    
    next_free_bit ++;
}

void Bitset::reserve(int len){

    int new_longs = (len / LL_BITS) + 1;

    for(int i=0; i<new_longs; i++){

        bits.push_back(0);
    }

    next_free_bit += len;
    next_free_bit %= LL_BITS;
}

Bitset::operator std::string(){

    std::string res;

    for(int i=0; i<bits.size(); i++){

        for(int bit_idx=0; bit_idx<LL_BITS; bit_idx++){

            std::string curr_bit = std::to_string((int)utils::get_kth_bit(bits[i], bit_idx));
            res += curr_bit;
        }
    }
    return res;
}

Bitset& Bitset::operator= (Bitset& o){

    this->bits = o.bits;
    return *this;
}
Bitset& Bitset::operator+ (Bitset& o){

    if(next_free_bit == 0){

        for(int i=0; i<o.bits.size(); i++){

            bits.push_back(o.bits[i]);
        }
    }


    else{
        

        int non_empty_space = next_free_bit;
        for(int i=0; i<o.bits.size(); i++){
            
            unsigned long long& last_long = bits[bits.size()-1];
            utils::merge(last_long, o.bits[i], non_empty_space);
            non_empty_space = LL_BITS - non_empty_space;
            bits.push_back(o.bits[i]);
        }
        

    }

    return *this;
}

Bitset& Bitset::operator+= (Bitset& o){

    *this = *this + o;
    return *this;
}

BitReference Bitset::operator[] (int idx){

    assert(idx < bits.size() * LL_BITS + next_free_bit);

    int long_idx = idx / LL_BITS;
    int bit_idx = idx % LL_BITS ;


    return BitReference(bits[long_idx], bit_idx);
}