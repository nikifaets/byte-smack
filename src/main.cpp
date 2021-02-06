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


using namespace std;

void read_test(string filename){

    ifstream inp(filename, ios::binary);

    char f;
    while(inp.get(f)){

        cout << (int)f << endl;
    }

}



template <typename T>
void print_bits2(T val){

    while(val){

        cout << val%2;
        val /= 2;
    }

    cout << endl;
}
int main(){


    string s = "ccaaaabbb";
    Encoder enc;

    enc.update_table(s);
    std::vector<int> freq(500);
    enc.get_table(freq);



    CodeTable code_table;

    enc.create_codes();


    char start_val = 0b01000000;
    cout << "start " << (int)start_val << endl; 

    Bitset b1;
    Bitset b2;

    b1.reserve(64);
    for(int i=0; i<60; i++){

        b1.add(1);

    }

    for(int i=0; i<64; i++){

        b2.add(1);
    }

    cout << (string)b1 << endl;
    cout << (string)b2 << endl;

    b1 += b2;

    cout << "----------------------------------------------------------" << endl;
    cout << (string)b1 << endl;
    cout << (string)b2 << endl;

    return 0;
}