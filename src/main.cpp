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

    Bitset b;
    b.reserve(8);
    b[0] = 1;
    b[7] = 1;
    cout << (string) b << endl;

    byte t = b;
    utils::print_bits(t);

    vector<byte> inp;
    string s = "aaaasdgfdgfdfgfdgfdgfdgfdfdgfdgfdgfdgfddgfdggfdgdafgfadhgjutyiuyjbfdsghfgdhfg5453thjpoesdfsdsdsffdabababaccc";
    
    for(int i=0; i<s.size(); i++){

        inp.push_back(s[i]);
    }

    Encoder enc;

    enc.update_freq_table(inp);
    enc.create_codes();
    CodeTable codes;
    enc.codes(codes);

    cout << "a: " << (string)codes['a'] << endl;
    cout << "b: " << (string) codes['b'] << endl;
    cout << "c: " << (string) codes['c'] << endl;

    cout << "a len " << codes['a'].next_free_bit << endl;
    cout << "b len " << codes['b'].next_free_bit << endl;
    cout << "c len " << codes['c'].next_free_bit << endl;
    Bitset ab = codes['a'] + codes['b'];
    ab += codes['c'];

    Bitset res;

    enc.encode(res, inp);

    cout << (string) res << endl;

    vector<byte> decoded;
    enc.decode(decoded, res);
    cout << "encoded " << s << endl;

    cout << "decoded ";
    for(int i=0; i<decoded.size(); i++){

        cout << decoded[i];
        

    }
    cout << endl;
    //cout << (string) compressed << endl;

    return 0;

}