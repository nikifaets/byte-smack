#include "FileWriter.h"
#include <assert.h>
#include <fstream>
#include <vector>
#include "FileReader.h"
#include <math.h>

void FileWriter::append_archive(std::ofstream& archive, Bitset& bitset, bool last){

    assert(archive.good());
    std::cout << "append " << (std::string) bitset << std::endl;
    const std::vector<unsigned long long>& longs = bitset.longs();
    for(int i=0; i<longs.size()-1; i++){

        write_bytes(longs[i], archive);
    }

    if(last){

        std::cout << "last \n";
        unsigned long long last_long = longs[longs.size()-1];
        
        write_bytes(last_long, archive);
    }
}

void FileWriter::append_bytes(std::ofstream& f, std::vector<byte>& bytes){

    for(int i=0; i<bytes.size(); i++){

        write_bytes(bytes[i], f);
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
        
        encoder.encode(encoded, bytes);

        bytes.clear();

    } while(success);

    //std::cout << "encoded before add sepcial " << (std::string) encoded << std::endl;
    encoded += special;
    std::cout << "write encoded " << encoded.size() << std::endl;
    std::cout << "longs used " << encoded.longs().size() << std::endl;
    if(encoded.size() < 100) std::cout << (std::string) encoded << std::endl;
    append_archive(archive, encoded);
    int ull_used_bytes = std::ceil(encoded.size() / 8.);
    int bytes_remainder = 8 - ull_used_bytes % 8;

    std::cout << "APPEND REMAINDER NULL BYTES " << 8 - bytes_remainder << std::endl;
    for(int i=0; i<8-bytes_remainder; i++){
        write_bytes((byte)0, archive);
    }

    //std::cout << "encoded " << (std::string) encoded << std::endl;
}

void FileWriter::write_code_table(std::ofstream& archive, CodeTable& code_table, Bitset& special){


    //archive << special.size();
    int special_len = special.size();
    std::cout << "write special len\n";
    utils::print_bits(special_len);
    write_bytes(special_len, archive);

    append_archive(archive, special);

    int code_table_size = code_table.size();
    
    write_bytes(code_table_size, archive);
    
    CodeTable::iterator it = code_table.begin();
    for(it; it!=code_table.end(); ++it){

        byte symbol = it->first;
        Bitset& code = it->second;

        write_bytes(symbol, archive);

        int code_size = code.size();        
        write_bytes(code_size, archive);
        append_archive(archive, code);
    }

}

void FileWriter::write_string(std::ofstream& f, const std::string& str){

    int strlen = str.size();
    //assert(str != "../test/test_text2");
    std::cout << "write string " << str << std::endl;
    for(int i=0; i<strlen; i++){

        write_bytes(str[i], f);
        
    }
}