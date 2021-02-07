#include "FileWriter.h"
#include <assert.h>
#include <fstream>
#include <vector>

void FileWriter::append_archive(std::fstream& archive, Bitset& bitset, bool last=true){

    assert(archive.good());

    const std::vector<unsigned long long>& longs = bitset.longs();

    for(int i=0; i<longs.size()-1; i++){

        archive << longs[i];
    }

    if(last){

        archive << longs[longs.size()-1];
    }
}

void FileWriter::write_file(std::string& archive_name, Bitset& filename, Bitset& bitset, Bitset& special){

    std::fstream archive(archive_name);
    assert(archive.good());

    append_archive(archive, filename);
    append_archive(archive, bitset);
    append_archive(archive, special);
    
}