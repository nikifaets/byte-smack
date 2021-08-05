#include "Archiver.h"
#include <assert.h>
#include <fstream>
#include "FileReader.h"
#include "FileWriter.h"
#include <filesystem>

void Archiver::compress(std::string& archive_name, std::vector<std::string>& files){


    FileWriter writer;
    FileReader reader;
    std::ifstream f;
    for(int i=0; i<files.size(); i++){

        std::string& file = files[i];

        f.open(file);
        assert(f.good());

        std::vector<byte> bytes;
        bool success = true;
        while(success){

            success = reader.read_byte_sequence(f, bytes, 100);
            encoder.update_freq_table(bytes);
            bytes.clear();
        }
        f.close();


    }
    
    
    encoder.create_codes();
    std::cout << "tree" << std::endl;
    Bitset special;
    encoder.get_special(special);
    std::cout << "special" << std::endl;
    std::cout << "special string " << (std::string) special << std::endl;
    CodeTable code_table;
    encoder.codes(code_table);
    std::cout << "codetable ready " << std::endl;
    std::ofstream of("codes");
    for(const auto& code : code_table){
        of << "key: " << (byte) code.first << std::endl;
        of << "value: " << (std::string) code.second << std::endl;
    }
    std::ofstream archive(archive_name, std::ios::binary);
    assert(archive.good());

    writer.write_code_table(archive, code_table, special);

    std::cout << "wrote table " << std::endl;
    
    for(int i=0; i<files.size(); i++){


        f.open(files[i]);
        
        int filename_size = files[i].size();
        writer.write_bytes(filename_size, archive);
        writer.write_string(archive, files[i]);
        writer.write_file(archive, f, encoder, special);
        
    }
    //write code table
    //write name
    //special
    //file
    //special
    //name
    //special
    //....
}

bool Archiver::decompress(std::string& archive_name, std::string& out_dir){

    std::ifstream archive(archive_name, std::ios::binary);
    assert(archive.good());

    FileReader reader;
    FileWriter writer;

    Bitset special;
    CodeTable code_table;
    reader.read_code_table(archive, code_table, special);
    //assert(false);
    std::cout << "READ CODE TABLE\n";
    /*for(const auto& code : code_table){

        std::cout << "key " << (byte) code.first << std::endl;
        std::cout << "val: " << (std::string) code.second << std::endl;
    } */
    std::cout << "SPECIAL " << (std::string) special << std::endl;

    
    DecodeTable decode_table;
    encoder.decode_table_from_code(decode_table, code_table);

    std::cout << "code table size " << code_table.size() << std::endl;
    std::cout << "decode table size " << decode_table.size() << std::endl;

    bool file_read = false;

    while(!file_read){

        int strlen;
        reader.read_bytes(strlen, archive);

        std::cout << "strlen " << strlen << std::endl;

        std::string filename;
        reader.read_string(archive, filename, strlen);
        std::cout << "first filename " << filename << std::endl;

        std::vector<byte> bytes;
        bool success = true;
        
        std::ofstream f("out", std::ios::app);

        while(success){

            success = reader.read_and_decode(archive, bytes, decode_table, special);
            writer.append_bytes(f, bytes);
            bytes.clear();
        }

        break;
    }
    
}