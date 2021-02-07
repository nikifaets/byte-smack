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

int sum(int v){

    int res = 0;
    for(int i=0; i<=v; i++){

        res += i;
    }

    return res;
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
    string s = "1234567890-=!@#$%^&*()_+qwertyuiop[]QWERTYUIOP{}asdfghjkl;'ASDFGHJKL:\"zxcvbnm,./ZXCVBNM<>?";
    
    for(int i=40; i<190; i++){

        int summ = sum(i);
        
        for(int j=0; j<summ+5; j++){

            inp.push_back(i);
        }
    }

    Encoder enc;

    enc.update_freq_table(inp);
    cout << "different symbols " << enc.count_different_symbols() << endl;
    enc.create_codes();
    CodeTable codes;
    enc.codes(codes);

    cout << "a: " << (string)codes['a'] << endl;
    cout << "2: " << (string) codes['2'] << endl;
    cout << "c: " << (string) codes['c'] << endl;

    cout << "a len " << codes['a'].next_free_bit << endl;
    cout << "b len " << codes['b'].next_free_bit << endl;
    cout << "c len " << codes['c'].next_free_bit << endl;
    Bitset ab = codes['a'] + codes['b'];
    ab += codes['c'];

    Bitset res;

    cout << "SUM 190 " << sum(190) << endl;
    enc.encode(res, inp);

    //cout << (string) res << endl;

    vector<byte> decoded;
    enc.decode(decoded, res);
    cout << "encoded " << s << endl;

    cout << "decoded ";

    
    cout << decoded.size() << " " <<inp.size() << endl;
    for(int i=0; i<decoded.size(); i++){

        assert(decoded[i] == inp[i]);

        //cout << decoded[i];
        

    }
    cout << endl;
    //cout << (string) compressed << endl;

    return 0;

}