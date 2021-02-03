#include <fstream>
#include <iostream>
#include <string>
#include "HTree.h"
#include <queue>
#include <cassert>
#include <unordered_map>
#include "Encoder.h"

using namespace std;

void read_test(string filename){

    ifstream inp(filename, ios::binary);

    char f;
    while(inp.get(f)){

        cout << (int)f << endl;
    }

}

int main(){


    string s = "aaaabbbccd";
    Encoder enc;

    cout << "before update" << endl;
    enc.update_table(s);
    std::vector<int> freq(500);
    cout << "initialized" << endl;
    enc.get_table(freq);

    
    HTree htree;
    htree.construct_tree(freq);


    return 0;
}