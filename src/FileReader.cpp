#include "FileReader.h"
#include <assert.h>
#include <iostream>

bool FileReader::validate_file(std::ifstream& f){

    return f.good();
}

bool FileReader::read_byte_sequence(std::ifstream& file, std::vector<byte>& res, int num_bytes){

    assert(file.good());

    int bytes_read = 0;
    char inp = 0;

    while(file.good() && file.get(inp) && bytes_read < num_bytes){
        
        //std::cout << "read sequence " << bytes_read << std::endl;
        bytes_read ++;
        res.push_back(inp);
        
    }

    //assert(!file.eof());
    std::cout << "end of read seq" << std::endl;
    return !file.eof();
    
}

bool FileReader::read_code_table(std::ifstream& archive, CodeTable& code_table, Bitset& special){
        
    assert(archive.good());


    //assert(false);

    read_code(archive, special);
    

    int table_len;
    read_bytes(table_len, archive);
    

    for(int i=0; i<table_len; i++){

        char symbol;
        archive.get(symbol);

        Bitset code;
        read_code(archive, code);

        std::cout << "symbol " << symbol << " " << (std::string) code << std::endl;
        code_table[symbol] = code;

        //assert(i < 100);
    }
   
}

bool FileReader::read_code(std::ifstream& archive, Bitset& res){

    const int LL_BYTES = sizeof(unsigned long long);

    int code_bits;
    read_bytes(code_bits, archive);

    int longs_num = code_bits / LL_BITS;
    if(code_bits % LL_BITS) longs_num ++;


    for(int j=0; j<longs_num; j++){
        
        
        int meaningful_bits = LL_BITS;

        if(j == longs_num -1){

            meaningful_bits = code_bits % LL_BITS;
        }

        unsigned long long code_long;
        read_bytes(code_long, archive);

        Bitset long_bitset(code_long, meaningful_bits);

        res += long_bitset;              
        //Bitset byte_bitset(code_byte, )
    }

}

bool FileReader::read_and_decode(std::ifstream& archive, std::vector<byte>& res, DecodeTable& decode_table, Bitset& special, int num_bytes){

    Bitset code_buf;

    byte inp;
    int decoded_bytes = 0;
    bool end_archive = false;


    while(read_bytes(inp, archive) && decoded_bytes <= num_bytes && !end_archive){

        //std::cout << "decode table size " << decode_table.size() << std::endl;
        Bitset inp_bitset(inp, sizeof(byte)*8);
        //std::cout << "buf " << (std::string) code_buf << std::endl;
        for(int bit=0; bit<inp_bitset.size(); bit++){

            code_buf.add(inp_bitset[bit]);

            int count = decode_table.count(code_buf);
            if(count > 0){

                std::cout << "got one " << std::endl;
                decoded_bytes ++;
                std::cout << decode_table[code_buf] << std::endl;
                res.push_back(decode_table[code_buf]);
                Bitset new_bitset;
                code_buf = new_bitset;
            }

            if(code_buf == special){

                
                end_archive = true;
            }
        }

    }

    if(!archive.good() || end_archive) return false;
    return true;

}

void FileReader::read_string(std::ifstream& f, std::string& str, int len){

    char* arr = new char[len];
    f.read(arr, len);


    for(int i=0; i<len; i++){

        str += arr[i];
    }


}