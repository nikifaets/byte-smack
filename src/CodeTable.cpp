#include "CodeTable.h"
#include <limits>



char CodeTable::get_code(char& orig) const{

    return this->table.at(orig).code;
}

int CodeTable::get_code_len(char& orig) const{

    return this->table.at(orig).length;
}