#pragma once

#include "Global.h"
class HNode{



    public:

    HNode* left = nullptr;
    HNode* right = nullptr;
    byte* val =  nullptr;
    int count;
    HNode(int count);
    HNode(int count, byte* val);
    HNode(int count, HNode*& left, HNode*& right);
    
    const byte* get_value() const;
    int get_count() const;

    bool operator < (const HNode*& o);
    bool operator < (HNode*& o);


};

