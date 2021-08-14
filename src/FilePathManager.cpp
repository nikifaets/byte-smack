#include "FilePathManager.h"
#include <filesystem>
#include <assert.h>
#include <iostream>
#include <vector>

void FilePathManager::process_filename(const std::vector<std::string>& filenames, std::vector<std::string>& out){

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

            std::filesystem::path p(file);
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