#include "Encoder.h"
#include <queue>
#include <iostream>
#include "HTree.h"
#include <assert.h>

void Encoder::prefill_table(){

    for(int i=0; i<BYTES_COUNT; i++){

        freq_table[i] = 0;
    }
}

Encoder::Encoder(){

    freq_table.resize(BYTES_COUNT);
}

void Encoder::get_freq_table(std::vector<int>& out){

    for(int i=0; i<BYTES_COUNT; i++){

        out[i] = freq_table[i];
    }
}

void Encoder::update_freq_table(std::vector<byte> bytes){


    for(int i=0; i<bytes.size(); i++){

        freq_table[bytes[i]] ++;
    }
}

void Encoder::create_codes(){
    
    HTree htree;

    htree.create_code_table(this->code_table, freq_table);
    fill_decode_table();
}

void Encoder::fill_decode_table(){

    CodeTable::iterator it = code_table.begin();

    for(it; it!=code_table.end(); it++){

        Bitset bitset = it->second;
        decode_table[bitset] = it->first;
    }
}

void Encoder::codes(CodeTable& res) const{

    res = code_table;
}

void Encoder::encode(Bitset& res, std::vector<byte> bytes){

    for(int i=0; i<bytes.size(); i++){

        assert(code_table.count(bytes[i]) > 0);

        res += code_table[bytes[i]];
    }
}

void Encoder::decode(std::vector<byte>& res, Bitset& codes){

    int codes_len = codes.size();
    byte reader = 0;
    int num_bits = 0;
    
    for(int i=0; i<codes_len; i++){

        assert(num_bits < 9);

        reader |= ((codes[i] << (7-num_bits)));

        num_bits ++;

        Bitset bitset(reader, num_bits);

        if(decode_table.count(bitset) > 0){

            res.push_back(decode_table[bitset]);
            reader = 0;
            num_bits = 0;
        }
        
    }
}