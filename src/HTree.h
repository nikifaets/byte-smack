#pragma once

#include "HNode.h"
#include <string>
#include <vector>

class HTree{

    
    public:

    HNode* construct_tree(std::vector<int>& freq_table);

    void print_tree(HNode* root);
};