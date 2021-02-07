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
    std::string fname = "../test/test_text";
    std::vector<std::string> files = {fname};
    std::string out_dir = "out";

    archiver.compress(arch_name, files);
    archiver.decompress(arch_name, out_dir);
    
    return 0;


}