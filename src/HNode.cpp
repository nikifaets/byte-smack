#include "HNode.h"
#include <iostream>

bool HNode::operator < (const HNode*& o){

    return this->count < o->count;
}

bool HNode::operator < (HNode*& o){

    return this->count < o->count;
}

HNode::HNode(int count) : count(count) {}
HNode::HNode(int count, byte* val) : count(count), val(val) {}
HNode::HNode(int count, HNode*& left, HNode*& right) : count(count), left(left), right(right) {}

const byte* HNode::get_value() const{

    return val;
}

int HNode::get_count() const{

    return count;
}