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

int sum(int v){

    int res = 0;
    for(int i=0; i<=v; i++){

        res += i;
    }

    return res;
}

int main(){

    std::vector<byte> inp;

    Archiver archiver;

    std::string arch_name = "hhh";
    std::string fname1 = "CMakeFiles/3.21.1/";
    std::string fname3 = "CMakeFiles";
    std::string fname4 = "test/testrec";
    std::string fname5 = "test";
    //std::string fname2 = "../test/text_1"
    std::vector<std::string> files = {fname5, fname3};
    std::string out_dir = "out1";

    FilePathManager h;
    std::vector<std::string> out;
    std::vector<std::string> files_to_decompress = {fname5, fname3};

    h.process_filename(files_to_decompress, out);

    archiver.compress(arch_name, files);
    //assert(false);
    archiver.decompress(arch_name, out_dir, out, false);

    std::cout << "---------------------------------------------Decompressed\n";
    archiver.modify_archived_file(arch_name, "CMakeFiles/3.21.1/CompilerIdC/a.out", "testrec_modified");
    std::cout << "....................................." << "Added new file\n";
    archiver.decompress("temp", "out_temp", out, true);
    
    return 0;

}