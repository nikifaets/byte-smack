#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

class CLIParser{

    const static std::string COMMAND_COMPRESS, COMMAND_DECOMPRESS, COMMAND_HELP, COMMAND_CHANGE_FILE, COMMAND_GET_INFO;
    static std::unordered_set<std::string> commands;
    void err_invalid_arguments() const;
    void err_invalid_file() const;
    bool is_filepath_valid(const std::string& filepath) const;

    public:
    void parse(int argc, char* argv[]) const;

    void compress(int argc, char* argv[]) const;
    void decompress(int argc, char* argv[]) const;
    void get_info(int argc, char* argv[]) const;
    void change_file(int argc, char* argv[]) const;
    void help() const;

};