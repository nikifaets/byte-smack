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

    template <typename T>
    void clear_kth_bit(T& code, int k){

        code &= ~(1ull << (num_bits(code) - k - 1));
    }

    template <typename T>
    void toggle_kth_bit(T& code, int k){

        code ^= (1ull << (num_bits(code) - k - 1));
    }

    template <typename T>
    void merge(T& code1, T& code2, int non_empty_space){

        code1 |= (code2 >> non_empty_space);
        code2 = code2 << (num_bits(code2)-non_empty_space);
    }

    template<typename T>
    void print_bits(T val){

        int bits = sizeof(T) * 8;
        for(int i=0; i<bits; i++){

            std::cout << utils::get_kth_bit(val, i);
        }
        std::cout << std::endl;
    }

    template<typename T>
    void to_char_array(T val, char*& res, int len){

        for(int i=0; i<len; i++){

            res[i] = val >> (len*8 - 8*i - 8);

        }
    }

    template<typename T>
    void from_char_array(T& val, char*& chars){
        
        val = (T)0;
        int num_bytes = sizeof(val);

        for(int i=0; i<num_bytes; i++){

            unsigned char unsigned_char = (unsigned char) 0 | chars[num_bytes-i-1];
            val |= ((T)unsigned_char << 8*i);
            //std::cout << "val on  " << i << "th iteration: ";
            //utils::print_bits(val);
            //std::cout << "last masked char: ";
            //utils::print_bits((T)unsigned_char << 8*i);
            
        }
    }
}

