#include "FileReader.h"
#include <assert.h>
#include "Utils.h"
#include <iostream>
#include "Global.h"

bool FileReader::validate_file(std::ifstream& f){

    return f.good();
}

bool FileReader::read_byte_sequence(std::ifstream& file, std::vector<byte>& res, int num_bytes){

    assert(file.good());

    int bytes_read = 0;
    char inp = 0;

    while(file.good() && file.get(inp) && bytes_read < num_bytes){
        
        //std::cout << " loop " << std::endl;
        bytes_read ++;
        res.push_back(inp);
        
    }

    //assert(!file.eof());
    return !file.eof();
    
}

bool FileReader::read_code_table(std::ifstream& archive, CodeTable& code_table, Bitset& special){
        
    assert(archive.good());


    //assert(false);

    read_code(archive, special);
    std::cout << "Special: \n";
    std::cout << special << std::endl;

    int table_len;
    read_bytes(table_len, archive);
    

    for(int i=0; i<table_len; i++){

        char symbol;
        archive.get(symbol);

        //std::cout << "read symbol " << symbol << std::endl;
        Bitset code;
        read_code(archive, code);

        //std::cout << "key: " << symbol << " " << (std::string) code << std::endl;

        code_table[symbol] = code;

        //assert(i < 5);
    }
   
}

bool FileReader::read_code(std::ifstream& archive, Bitset& res){

    const int LL_BYTES = sizeof(unsigned long long);

    int code_bits;
    read_bytes(code_bits, archive);
    //std::cout << "code bits " << code_bits << std::endl;
    int longs_num = code_bits / LL_BITS;
    if(code_bits % LL_BITS) longs_num ++;

    //std::cout << "longs num " << longs_num << std::endl;

    for(int j=0; j<longs_num; j++){
        
        int meaningful_bits = LL_BITS;

        if(j == longs_num - 1){

            meaningful_bits = code_bits % LL_BITS;
        }

        unsigned long long code_long;
        read_bytes(code_long, archive);
        //std::cout << "code_long: ";
        //utils::print_bits(code_long);
        Bitset long_bitset(code_long, meaningful_bits);

        res += long_bitset;
        //std::cout << "temp res bitset " << (std::string) res << std::endl;          
        //Bitset byte_bitset(code_byte, )
    }

}

bool FileReader::read_and_decode(std::ifstream& archive, std::vector<byte>& res, DecodeTable& decode_table, Bitset& special, int num_bytes){

    Bitset code_buf;

    byte inp;
    int decoded_bytes = 0;
    bool end_archive = false;

    std::ofstream log("logs");
    while(read_bytes(inp, archive) && decoded_bytes <= num_bytes && !end_archive){

        Bitset inp_bitset(inp, sizeof(byte)*8);
        for(int bit=0; bit<inp_bitset.size(); bit++){
            log << "code buf " << (std::string) code_buf << std::endl;
            code_buf.add(inp_bitset[bit]);

            int count = decode_table.count(code_buf);
            if(count > 0){

                //  std::cout << "found code " << decode_table[code_buf] << std::endl;
                decoded_bytes ++;
                res.push_back(decode_table[code_buf]);
                code_buf.clear();

            }

            if(code_buf == special){

                std::cout << "read special " << std::endl;
                end_archive = true;
                break;
            }

            else{

                //utils::print_bits(inp);
                //std::cout  << " CHARACTER NOT IN DECODE TABLE \n";
                //std::cout << "int inp " << (int) inp << std::endl;
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