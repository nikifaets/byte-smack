#include "FileReader.h"
#include <assert.h>

bool FileReader::validate_file(std::fstream f){

    return f.good();
}

void FileReader::read_byte_sequence(int num_bytes=20000, std::fstream& file, Bitset& res){

    assert(file.good());

    int bytes_read = 0;
    while(file.good() && bytes_read <= num_bytes){

        byte inp;
        assert(file >> inp);

        Bitset inp_bitset(inp, 8);
        res += inp_bitset;
    }

    
    


}