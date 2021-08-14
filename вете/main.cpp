#include "filesystemIterator.h"
#include <iostream>
#include <vector>


int main(int argc, char const *argv[]) {
  	FilesystemIterator *fsi = new FilesystemIterator();
	
	std::vector<std::string> search_arguments;

	for (int i = 1; i < argc; i++) {
		search_arguments.push_back(argv[i]);
	}

  	std::vector<std::string> filenames = fsi->search(search_arguments);
  	
	for (auto x : filenames) {
		std::cout << x << std::endl;
	}

  	return 0;
}
