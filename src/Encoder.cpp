#include "Encoder.h"
#include <queue>
#include <iostream>

void Encoder::prefill_table(){

    for(int i=0; i<BYTES_COUNT; i++){

        freq_table[i] = 0;
    }
}

Encoder::Encoder(){

    //prefill_table();
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

void Encoder::codes_from_tree(HNode*& root){
    
    
}  