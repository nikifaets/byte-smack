#include "Bitset.h"
#include "Utils.h"
#include <iostream>

void Bitset::add(bool bit){

    if(next_free_bit % LL_BITS == 0){

        bits.push_back(0);
        next_free_bit = 0;
    }

    int last_idx = bits.size() - 1;

    if(bit){

        std::cout << "set kth bit " << next_free_bit << std::endl;
        utils::set_kth_bit(bits[last_idx], next_free_bit);
    }
    
    next_free_bit ++;
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