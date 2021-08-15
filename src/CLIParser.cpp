#include "CLIParser.h"
#include <unordered_set>
#include <algorithm>
#include <filesystem>
#include "Archiver.h"

const std::string CLIParser::COMMAND_CHANGE_FILE = "change_file";
const std::string CLIParser::COMMAND_COMPRESS = "compress";
const std::string CLIParser::COMMAND_DECOMPRESS = "decompress";
const std::string CLIParser::COMMAND_HELP = "help";
const std::string CLIParser::COMMAND_GET_INFO = "info";


std::unordered_set<std::string> CLIParser::commands = {COMMAND_GET_INFO, COMMAND_COMPRESS, COMMAND_DECOMPRESS, COMMAND_CHANGE_FILE, COMMAND_HELP};
void CLIParser::parse(int argc, char* argv[]) const{


    if(argc < 2){
        std::cout << "Possible commands are:\n\n";
        for(const std::string& s : commands){
            std::cout <<"-" << s << "\n";
        }
        std::cout << std::endl;
        std::cout << "Enter 'help' for more info.\n";
        return;
    }

    std::string arg1 = argv[1];

    if(commands.count(arg1) < 1){

        std::cout << "Invalid command. Type 'help' for assistance.\n";
        return;
    }

    if(arg1 == COMMAND_COMPRESS){
        compress(argc, argv);
    }

    else if(arg1 == COMMAND_DECOMPRESS){
        decompress(argc, argv);
    }

    else if(arg1 == COMMAND_HELP){
        help();
    }

    else if(arg1 == COMMAND_GET_INFO){
        get_info(argc, argv);
    }

    else if(arg1 == COMMAND_CHANGE_FILE){
        change_file(argc, argv);
    }

}

void CLIParser::err_invalid_arguments() const{

    std::cout << "Invalid arguments. Type 'help' for more info.\n";
}

void CLIParser::err_invalid_file() const{

    std::cout << "Invalid filepath. Check again.\n";
}
bool CLIParser::is_filepath_valid(const std::string& filepath) const{

    return filepath.find("..") == std::string::npos && std::filesystem::exists(filepath);
}

void CLIParser::compress(int argc, char* argv[]) const{

    if(argc < 4){
        err_invalid_arguments();
        return;
    }

    std::vector<std::string> filepaths;

    if(std::string(argv[2]).find("..") != std::string::npos){
        err_invalid_file();
        return;
    }

    for(int i=3; i<argc; i++){
        if(!is_filepath_valid(argv[i])){
            err_invalid_file();
            return;
        }
        if(i>2) filepaths.push_back(argv[i]);
    }

    Archiver archiver;
    archiver.compress(argv[2], filepaths);

}
void CLIParser::decompress(int argc, char* argv[]) const{

    if(argc < 5){
        err_invalid_arguments();
        return;
    }

    // Archive name
    if(!is_filepath_valid(argv[2])){
        err_invalid_file();
        return;
    }

    std::vector<std::string> filepaths;
    for(int i=4; i<argc; i++){
        filepaths.push_back(argv[i]);
    }

    Archiver archiver;
    archiver.decompress(argv[2], argv[3], filepaths);

}
void CLIParser::change_file(int argc, char* argv[]) const{

    if(argc < 5){
        err_invalid_arguments();
        return;
    }


    // Existence of archive and target new file
    if(!std::filesystem::exists(argv[2]) || !std::filesystem::exists(argv[4])){
        err_invalid_file();
        return;
    }

    Archiver archiver;
    archiver.modify_archived_file(argv[2], argv[3], argv[4]);
    
}
void CLIParser::get_info(int argc, char* argv[]) const{

    if(argc < 3){
        err_invalid_arguments();
        return;
    }

    if(!std::filesystem::exists(argv[2])){
        err_invalid_file();
        return;
    }

    Archiver archiver;
    archiver.decompress(argv[2], "", {}, true);
}
void CLIParser::help() const{

    std::cout << "Commands:\n";
    std::cout << "compress [archive name] [input files]\n";
    std::cout << "decompress [archive name] [output name] [files to decompress] or type 'all' to decompress all files\n";
    std::cout << "change_file [archive name] [name of the target file as it is in the archive] [path to the new file]\n";
    std::cout << "info [archive name]\n";

}