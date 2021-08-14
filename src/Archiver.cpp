    #include "Archiver.h"
    #include <assert.h>
    #include <fstream>
    #include "FileReader.h"
    #include "FileWriter.h"
    #include <filesystem>
    #include <algorithm>
    #include "FilePathManager.h"
    void Archiver::compress(const std::string& archive_name, const std::vector<std::string>& files){


        FileWriter writer;
        FileReader reader;
        FilePathManager filepath_manager;
        std::ifstream f;
        
        std::vector<std::string> archive_filenames;
        filepath_manager.process_filename(files, archive_filenames);

        std::vector<std::string> readable_filenames;
        filepath_manager.dirnames_to_readable_files(files, readable_filenames);

        for(int i=0; i<files.size(); i++){

            std::string file = readable_filenames[i];
            f.open(file);
            assert(f.good());   

            std::vector<byte> bytes;
            bool success = true;
            while(success){

                std::cout << "Try to read file " << file << std::endl;
                success = reader.read_byte_sequence(f, bytes, 100);
                encoder.update_freq_table(bytes);
                bytes.clear();
            }
            f.close();
        }

        encoder.create_codes();
        Bitset special;
        encoder.get_special(special);
        CodeTable code_table;
        encoder.codes(code_table);
        std::ofstream of(archive_name);
        for(const std::pair<byte, Bitset>& code : code_table){
            of << "key: " << (byte) code.first << std::endl;
            of << "value: " << (std::string) code.second << std::endl;
        }
        std::ofstream archive(archive_name, std::ios::binary);
        assert(archive.good());

        writer.write_code_table(archive, code_table, special);
        writer.write_bytes(files.size(), archive);
        std::cout << "files num " << files.size() << std::endl;
        for(int i=0; i<readable_filenames.size(); i++){

            std::string file = readable_filenames[i];
            std::string archive_filename = archive_filenames[i];
            std::cout << "WRITE FILE TO ARCHIVE " << archive_filename << std::endl;

            std::cout << "Try to write file: " << file << std::endl;

            f.open(file);
            assert(f.good());
            int filename_size = archive_filename.size();
            std::cout << "FILE NAME SIZE " << filename_size << std::endl;
            writer.write_bytes((int)filename_size, archive);
            //assert(file != files[1]);
            writer.write_string(archive, archive_filename);
            writer.write_file(archive, f, encoder, special);
            f.close();
            
        }
        //write code table
        //write name
        //special
        //file
        //special
        //name
        //special
        //....

        std::cout << "Compression OK\n";
        std::cout << "Special " << (std::string) special << std::endl;
    }

    bool Archiver::decompress(const std::string& archive_name, const std::string& out_dir, const std::vector<std::string>& files){

        std::ifstream archive(archive_name, std::ios::binary);
        assert(archive.good());

        FileReader reader;
        FileWriter writer;

        Bitset special;
        CodeTable code_table;
        reader.read_code_table(archive, code_table, special);
        
        DecodeTable decode_table;
        encoder.decode_table_from_code(decode_table, code_table);

        size_t num_files;
        reader.read_bytes(num_files, archive);

        std::cout << "num files: " << num_files << std::endl;

        for(int i=0; i<num_files; i++){
            std::cout << "START FILE " << i << std::endl;
            int strlen=0;
            reader.read_bytes(strlen, archive);
            utils::print_bits(strlen);
            std::cout << "strlen " << strlen << std::endl;
            std::cout << "special " << (std::string) special << std::endl;
            //assert(i<1);
            std::string filename;
            reader.read_string(archive, filename, strlen);

            //std::cout << "working with file: " << filename << std::endl;

            std::vector<byte> bytes;
            bool success = true;
            
            std::string filepath = out_dir + "/" + filename;
            bool file_requested = (std::find(files.begin(), files.end(), files[i]) != std::end(files));
            std::filesystem::path p(filepath);

            std::filesystem::create_directories(p.parent_path());
            std::ofstream of(filepath);
            std::cout << "FILEPATH " << filepath << std::endl;
            while(success){

                success = reader.read_and_decode(archive, bytes, decode_table, special);
                if(file_requested) writer.append_bytes(of, bytes);
                bytes.clear();
            }
            of.close();
            std::cout << "file ready \n";

        }
    }