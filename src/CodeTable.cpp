#include "CodeTable.h"
#include <limits>



byte CodeTable::get_code(byte& orig) const{

    return this->table.at(orig).code;
}

int CodeTable::get_code_len(byte& orig) const{

    return this->table.at(orig).length;
}

CodeTable::CodeTable(){

    prefill_table();
}

CodeLengthPair::CodeLengthPair(byte code, int length): code(code), length(length) {}
CodeLengthPair::CodeLengthPair(){}

void CodeTable::prefill_table(){

    for(int i=0; i<256; i++){
        
        code_len cl(i, 8);
        table[i] = cl;
    }
}

code_len& CodeTable::operator [] (const byte& key){

    return table[key];
}