#include "Encoder.h"
#include <queue>
#include <iostream>
#include "HTree.h"

void Encoder::prefill_table(){

    for(int i=0; i<BYTES_COUNT; i++){

        freq_table[i] = 0;
    }
}

Encoder::Encoder(){

    freq_table.resize(BYTES_COUNT);
}

void Encoder::get_table(std::vector<int>& out){

    for(int i=0; i<BYTES_COUNT; i++){

        out[i] = freq_table[i];
    }
}

void Encoder::update_table(std::string str){

    int strlen = str.size();

    for(int i=0; i<strlen; i++){

        freq_table[str[i]] ++;
    }
}

void Encoder::create_codes(){
    
    HTree htree;

    htree.create_code_table(this->code_table, freq_table);
}  

bool Encoder::get_kth_bit(char code, int k){

    char leftmost_one = 0b10000000;

    return (code & ( leftmost_one >> k )) >> k;
}
void Encoder::code_table_to_bitset(CodeTable& code_table){

    size_t bitset_len = 0;
    //loop once to calculate the size of the bitset
    for(int i=0; i<freq_table.size(); i++){

        if(freq_table[i] < 1) continue;

        char orig = freq_table[i];

        int len = code_table[orig].length;
        bitset_len += len;
        
    }
    
}