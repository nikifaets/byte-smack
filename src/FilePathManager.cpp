#include "FilePathManager.h"
#include <filesystem>
#include <assert.h>
#include <iostream>
#include <vector>

// If input is a single file, save only its name, without the path
// If input is a directory, save the names of all file inside, including the path

void FilePathManager::process_filename(const std::vector<std::string>& filenames, std::vector<std::string>& out){

    for(const std::string& filename : filenames){

        assert(std::filesystem::exists(filename));
        assert(filename.find("..") == std::string::npos);
        if(std::filesystem::is_directory(filename)){

            std::filesystem::recursive_directory_iterator rdi(filename);
            for(const std::filesystem::__cxx11::directory_entry& p : rdi){

                if(std::filesystem::is_directory(p)) continue;
                out.push_back(p.path());
            }
        }
        else{

            std::filesystem::path p(filename);
            out.push_back(p.filename());
        }
    }
}

void FilePathManager::dirnames_to_readable_files(const std::vector<std::string>& filenames, std::vector<std::string>& out){

    for(const std::string& file : filenames){

        assert(file.find("..") == std::string::npos);
        if(std::filesystem::is_directory(file)){

            std::filesystem::recursive_directory_iterator rdi(file);
            for(const std::filesystem::__cxx11::directory_entry& p : rdi){

                if(std::filesystem::is_directory(p)) continue;
                out.push_back(p.path());
            }
        }

        else{

            out.push_back(file);
        
        }

        std::cout << "READABLE FILENAMES  \n";
        for(const std::string& f : out){
            std::cout << f << std::endl;
        }
    
    }
}