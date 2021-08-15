#include "FileReader.h"
#include <assert.h>
#include "Utils.h"
#include <iostream>
#include "Global.h"
#include <math.h>

/*
    Различни помощни методи за четене на файл, на Bitset, на байт, на CodeTable и др.
    Дизайнът е измислен, така че да позволява четене на файлове без да се зареждат наведнъж целите. Това е с цел пестене на памет. При работа
    с големи файлове е по-разумно файлът да се чете постепенно, на малки групи от байтове, вместо да се зарежда целия в паметта.
*/

bool FileReader::validate_file(std::ifstream& f){

    return f.good();
}

bool FileReader::read_byte_sequence(std::ifstream& file, std::vector<byte>& res, int num_bytes){

    
    assert(file.good());

    int bytes_read = 0;
    char inp = 0;

    while(file.good() && file.get(inp) && bytes_read < num_bytes){
        
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

    int table_len;
    read_bytes(table_len, archive);
    

    for(int i=0; i<table_len; i++){

        char symbol;
        archive.get(symbol);

        Bitset code;
        read_code(archive, code);

        code_table[symbol] = code;

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

        if(j == longs_num - 1){

            meaningful_bits = code_bits % LL_BITS;
        }

        unsigned long long code_long;
        read_bytes(code_long, archive);
        Bitset long_bitset(code_long, meaningful_bits);

        res += long_bitset;
    }

}

bool FileReader::read_and_decode(std::ifstream& archive, std::vector<byte>& res, const DecodeTable& decode_table, Bitset& special, const int num_bytes){

    Bitset code_buf;

    byte inp;
    int decoded_bytes = 0;
    bool end_archive = false;

    std::ofstream log("logs");
    while(decoded_bytes <= num_bytes && !end_archive && read_bytes(inp, archive)){

        Bitset inp_bitset(inp, sizeof(byte)*8);
        for(int bit=0; bit<inp_bitset.size(); bit++){
            log << "code buf " << (std::string) code_buf << std::endl;
            code_buf.add(inp_bitset[bit]);

            int count = decode_table.count(code_buf);
            if(count > 0){

                decoded_bytes ++;
                res.push_back(decode_table.at(code_buf));
                code_buf.clear();

            }

            if(code_buf == special){

                unsigned long long h;
                read_bytes(h, archive);
                end_archive = true;
                break;
            }

        }

    }

    if(!archive.good() || end_archive) return false;
    return true;

}

void FileReader::read_string(std::string& str, const int len, std::ifstream& f){

    char* arr = new char[len];
    f.read(arr, len);


    for(int i=0; i<len; i++){

        str += arr[i];
    }

    delete [] arr;


}