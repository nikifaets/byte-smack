#include <fstream>
#include <iostream>
#include <string>
#include "HTree.h"
#include <queue>
#include <cassert>
#include <unordered_map>
#include "Encoder.h"
#include "Bitset.h"
#include "Utils.h"
#include "FileReader.h"
#include "Archiver.h"
#include "FilePathManager.h"
#include "CLIParser.h"

/* 
    Командният интерфейс не е напълно завършен. Има проблем с метода за обновяване на файл. Може да се направи тест като се закоментират ред 19-21 включително и
    се разкоментират другите.

    Предоставена функционалност: Всичко описано в заданието освен възможността за използване на wildcards като * и ?, и проверката дали
    в архива има проблем.
*/

/*
    Тествайте командния интерфейс като пуснете програмата и дадете help като CLI аргумент.
*/

int main(int argc, char* argv[]){

    /*CLIParser parser;
    parser.parse(argc, argv);
    std::vector<byte> inp;*/

    // Разкоментирайте за тест, който не е през командния интерфейс.
    Archiver archiver;

    std::string arch_name = "archive";
    std::string fname1 = "/home/nikifaets/Documents/vaccination";
    std::string fname2 = "/home/nikifaets/Documents/fmi_io";
    std::vector<std::string> files = {fname1, fname2};
    std::string out_dir = "decompressed";

    FilePathManager path_manager;
    std::vector<std::string> out;
    std::vector<std::string> files_to_decompress = {fname1, fname2}; // Това са файловете или директориите, които ще се компресират

    path_manager.filepaths_to_readable_files(files_to_decompress, out);

    archiver.compress(arch_name, files); // Компресия във файл "archive"
    archiver.decompress(arch_name, out_dir, out, true); // Декомпресия в директория "decompressed"

    std::cout << "---------------------------------------------Decompressed\n";

    archiver.modify_archived_file(arch_name, "/home/nikifaets/Documents/fmi_io/io_kontr.ods", "testrec_modified"); // Промяна на даден файл от архива. Попълнете файл от архива в левите кавички и случаен файл в десните. 
                                                    // За десните, моля, използвайте абсолютен път в машината.

    std::cout << "....................................." << "Added new file\n";
    archiver.decompress(arch_name, "decompressed_changed", out, false);
    
    return 0;

}