#include "CodeTable.h"
#include <limits>



char CodeTable::get_code(char& orig) const{

    return this->table.at(orig).code;
}

int CodeTable::get_code_len(char& orig) const{

    return this->table.at(orig).length;
}

CodeTable::CodeTable(){

    prefill_table();
}

CodeLengthPair::CodeLengthPair(char code, int length): code(code), length(length) {}
CodeLengthPair::CodeLengthPair(){}

void CodeTable::prefill_table(){

    for(int i=0; i<256; i++){
        
        code_len cl(i, 8);
        table[i] = cl;
    }
}

code_len& CodeTable::operator [] (const char& key){

    return table[key];
}