#pragma once
class HNode{



    public:

    HNode* left = nullptr;
    HNode* right = nullptr;
    char* val =  nullptr;
    int count;
    HNode(int count);
    HNode(int count, char* val);
    HNode(int count, HNode*& left, HNode*& right);
    
    const char* get_value() const;
    int get_count() const;

    bool operator < (const HNode*& o);
    bool operator < (HNode*& o);


};

