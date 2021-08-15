#pragma once

#include "Global.h"
#include <memory>
class HNode{


    public:

    std::shared_ptr<HNode> left = nullptr;
    std::shared_ptr<HNode> right = nullptr;
    std::shared_ptr<byte> val =  nullptr;
    int count;
    HNode(int count);
    HNode(int count, std::shared_ptr<byte>& val);
    HNode(int count, std::shared_ptr<HNode>& left, std::shared_ptr<HNode>& right);
    
    std::shared_ptr<byte> get_value() const;
    int get_count() const;

    bool operator < (const std::shared_ptr<HNode>& o);
    bool operator < (std::shared_ptr<HNode>& o);


};

