#include "Encoder.h"
#include <queue>
#include <iostream>
#include "HTree.h"
#include <assert.h>

/*
    Класът Encoder служи като интерфейс между класовете от по-високо ниво, като Archiver например, и логиката около Хъфман кодирането.
    Предоставя функционалност за съставяне на таблица с кодове, таблица за декодиране, осигурява връзката със самите дървета на Хъфман и др.
*/
void Encoder::set_code_table(CodeTable code_table){

    this->code_table = code_table;
}
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

int Encoder::count_different_symbols(){

    int count = 0;
    for(int i=0; i<freq_table.size(); i++){

        if(freq_table[i] > 0) count ++;
    }

    return count;
}
void Encoder::update_freq_table(std::vector<byte>& bytes){

    for(int i=0; i<bytes.size(); i++){

        freq_table[bytes[i]] ++;
    }
}

void Encoder::create_codes(){
    
    HTree htree;

    htree.create_code_table(this->code_table, freq_table, special);
    fill_decode_table();
}

void Encoder::get_special(Bitset& res){

    res = special;
}

void Encoder::fill_decode_table(){


}
void Encoder::decode_table_from_code_table(DecodeTable& decode_table, CodeTable& code_table){

    CodeTable::iterator it = code_table.begin();

    for(it; it!=code_table.end(); ++it){

    
        int count = decode_table.count(it->second);
        if(count > 0){
            BitsetHash bh;
        }

        decode_table[it->second] = it->first;
    }
}
void Encoder::get_codes(CodeTable& res) const{

    res = code_table;
}

void Encoder::get_decode_table(DecodeTable& res) const{

    res = decode_table;
}

void Encoder::encode(const std::vector<byte>& bytes, Bitset& res) const{

    for(int i=0; i<bytes.size(); i++){

        //utils::print_bits(bytes[i]);
        assert(code_table.count(bytes[i]) > 0);

        res += code_table.at(bytes[i]);
    }
}

void Encoder::decode(std::vector<byte>& res, Bitset& codes){

    int codes_len = codes.size();
    Bitset reader;
    int num_bits = 0;
    
    for(int i=0; i<codes_len; i++){

        assert(num_bits <= MAX_CODE_LEN);

        reader.add(codes[i]);
        num_bits++;

        if(decode_table.count(reader) > 0){

            res.push_back(decode_table[reader]);
            
            Bitset new_reader;
            reader = new_reader;
            num_bits = 0;
        }
        
    }
}