#pragma once
#include <iostream>

namespace utils{


    template<typename T>
    int num_bits(T& var){

        return sizeof(T)*8;
    }

    template<typename T>
    T msb_for_type(T& var){
        
        T one = 1;
        return one << (num_bits(var) - 1);
    }
    
    template <typename T>
    bool get_kth_bit(T& code, int k){

        T msb = msb_for_type(code);
        int left_shift = num_bits(code) - k - 1;

        return ((code >> left_shift) & 1);
    }

    template <typename T>
    void set_kth_bit(T& code, int k){

        T msb = msb_for_type(code);
        code = code | (msb >> k);
    }
}