#include "HNode.h"
#include <iostream>

/*
    Връх от дърво на Хъфман.
*/
bool HNode::operator < (const std::shared_ptr<HNode>& o){

    return this->count < o->count;
}

bool HNode::operator < (std::shared_ptr<HNode>& o){

    return this->count < o->count;
}

HNode::HNode(int count) : count(count) {}
HNode::HNode(int count, std::shared_ptr<byte>& val) : count(count), val(val) {}
HNode::HNode(int count, std::shared_ptr<HNode>& left, std::shared_ptr<HNode>& right) : count(count), left(left), right(right) {}

std::shared_ptr<byte> HNode::get_value() const{

    return val;
}

int HNode::get_count() const{

    return count;
}