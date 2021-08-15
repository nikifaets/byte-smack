#include "FilePathManager.h"
#include <filesystem>
#include <assert.h>
#include <iostream>
#include <vector>

/* 
    Този клас предоставя два метода за обработка на вектори с пътища до файлове и директории.
    filepaths_to_archive_names преобразува пълно име на файл (включително релативен път до него) до името, с което той ще стои в архивния файл.
    Например dir/gosho/pepi.txt ще бъде pepi.txt в архивния файл, понеже е индивидуален файл, а не директория.
    dir/dir2 ще се преобразува до dir/dir2/a.txt, dir/dir2/b.txt и т.н. с всички файлове, които се съдържат под зададената директория. Работи рекурсивно.
    filepaths_to_readble_files връща преобразувани имена, така че да могат да бъдат усвоени от std::fstream.
    dir1/dir2 отново ще се разгърне до списък с всички файлове под dir2, а самостоятелни файлове ще си останат с релативни пътища, за да могат да бъдат прочетени.
    На този етап се поддържат само пълни пътища без wildcards и символи за навигиране директория нагоре "..". 
*/

void FilePathManager::filepaths_to_archive_names(const std::vector<std::string>& filenames, std::vector<std::string>& out) const{

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

void FilePathManager::filepaths_to_readable_files(const std::vector<std::string>& filenames, std::vector<std::string>& out) const{

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
    
    }
}
