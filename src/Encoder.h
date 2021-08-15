#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include "HNode.h"
#include <bitset>
#include "Global.h"
#include "Utils.h"
#include "Bitset.h"

/*
    Този клас служи като интерфейс между класовете от по-високо ниво, като например Archiver, и манипулацията на Хъфман кодове.
    Предоставя функционалността за създаване на Хъфман дърво, таблица с кодове, таблица с честота на срещания на байтове и др.
*/

class Encoder{

    static const int BYTES_COUNT = 256;


    std::vector<int> freq_table;
    CodeTable code_table;
    DecodeTable decode_table;
    Bitset special;

    void prefill_table();
    void fill_decode_table();

    public:

    void decode_table_from_code_table(DecodeTable& decode_table, const CodeTable& code_table) const;
    bool write_archive(std::string& buf, std::string& out);
    void get_freq_table(std::vector<int>& out) const;
    void update_freq_table(const std::vector<byte>& bytes);
    void create_codes();
    void get_codes(CodeTable& res) const;
    void get_decode_table(DecodeTable& res) const;
    void encode(const std::vector<byte>& bytes, Bitset& res) const;
    void decode(std::vector<byte>& res, Bitset& codes) const;
    int count_different_symbols() const;
    void get_special(Bitset& res) const;
    void set_code_table(const CodeTable code_table);
    Encoder();
};