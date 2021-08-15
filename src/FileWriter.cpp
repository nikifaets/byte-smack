#include "FileWriter.h"
#include <assert.h>
#include <fstream>
#include <vector>
#include "FileReader.h"
#include <math.h>

/*
    Подобно на FileReader, но за писане.
*/

void FileWriter::append_archive(std::ofstream& archive, Bitset& bitset, bool last){

    assert(archive.good());
    const std::vector<unsigned long long>& longs = bitset.longs();
    for(int i=0; i<longs.size()-1; i++){

        write_bytes(archive, longs[i]);
    }

    if(last){

        unsigned long long last_long = longs[longs.size()-1];
        
        write_bytes(archive, last_long);
    }
}

void FileWriter::append_bytes(std::ofstream& f, std::vector<byte>& bytes){

    for(int i=0; i<bytes.size(); i++){

        write_bytes(f, bytes[i]);
    }
}

void FileWriter::append_bytes_text(std::ofstream& f, std::vector<byte>& bytes){

}

void FileWriter::write_file(std::ofstream& archive, std::ifstream& f, Encoder& encoder, Bitset& special){

    assert(archive.good());

    FileReader reader;
    std::vector<byte> bytes;

    bool success = false;
    Bitset encoded;

    do{

        success = reader.read_byte_sequence(f, bytes);
        
        encoder.encode(bytes, encoded);

        bytes.clear();

    } while(success);

    encoded += special;

    append_archive(archive, encoded);
    
    int ull_used_bytes = std::ceil(encoded.size() / 8.);
    int bytes_remainder = 8 - ull_used_bytes % 8;

    if(bytes_remainder == 8) bytes_remainder = 0;
    for(int i=0; i<8-bytes_remainder; i++){
        write_bytes(archive, (byte)0);
    }

}

void FileWriter::write_byte_remainder(std::ofstream& archive, const Bitset& encoded){
    
    int ull_used_bytes = std::ceil(encoded.size() / 8.);
    int bytes_remainder = 8 - ull_used_bytes % 8;

    if(bytes_remainder == 8) bytes_remainder = 0;
    for(int i=0; i<8-bytes_remainder; i++){
        write_bytes(archive, (byte)0);
    }
}

void FileWriter::write_code_table(std::ofstream& archive, CodeTable& code_table, Bitset& special){


    //archive << special.size();
    int special_len = special.size();

    write_bytes(archive, special_len);

    append_archive(archive, special);

    int code_table_size = code_table.size();
    
    write_bytes(archive, code_table_size);
    
    CodeTable::iterator it = code_table.begin();
    for(it; it!=code_table.end(); ++it){

        byte symbol = it->first;
        Bitset& code = it->second;

        write_bytes(archive, symbol);

        int code_size = code.size();        
        write_bytes(archive, code_size);
        append_archive(archive, code);
    }

}

void FileWriter::write_string(std::ofstream& f, const std::string& str){

    int strlen = str.size();
    //assert(str != "../test/test_text2");
    for(int i=0; i<strlen; i++){

        write_bytes(f, str[i]);
        
    }
}