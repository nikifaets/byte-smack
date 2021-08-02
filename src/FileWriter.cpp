#include "FileWriter.h"
#include <assert.h>
#include <fstream>
#include <vector>
#include "FileReader.h"

void FileWriter::append_archive(std::ofstream& archive, Bitset& bitset, bool last){

    assert(archive.good());

    const std::vector<unsigned long long>& longs = bitset.longs();

    for(int i=0; i<longs.size()-1; i++){

        write_bytes(longs[i], archive);
    }

    if(last){

        unsigned long long last_long = longs[longs.size()-1];
        
        utils::print_bits(last_long);
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

void FileWriter::write_file(std::ofstream& archive, std::ifstream& f, Encoder& encoder){

    assert(archive.good());

    FileReader reader;
    std::vector<byte> bytes;

    bool success = false;
    
    do{

        success = reader.read_byte_sequence(f, bytes);
        Bitset encoded;
        encoder.encode(encoded, bytes);

        append_archive(archive, encoded);
        bytes.clear();

    } while(success);




}

void FileWriter::write_code_table(std::ofstream& archive, CodeTable& code_table, Bitset& special){


    //archive << special.size();
    int special_len = special.size();
    write_bytes(special_len, archive);

    append_archive(archive, special);

    int code_table_size = code_table.size();
    write_bytes(code_table_size, archive);
    
    CodeTable::iterator it = code_table.begin();
    for(it; it!=code_table.end(); ++it){

        byte symbol = it->first;
        Bitset& code = it->second;

        std::cout << "write symbol: \n";
        write_bytes(symbol, archive);

        int code_size = code.size();
        std::cout << "write code size: \n";
        write_bytes(code_size, archive);
        std::cout << "append code: \n";
        append_archive(archive, code);
    }

}

void FileWriter::write_string(std::ofstream& f, std::string& str){

    int strlen = str.size();

    for(int i=0; i<strlen; i++){

        write_bytes(str[i], f);
        
    }
}