#include <iostream>
#include <vector>
#include <string>

class FilesystemIterator
{
public:
    FilesystemIterator();
    ~FilesystemIterator();
    std::vector<std::string> search(std::vector<std::string> args);
};


