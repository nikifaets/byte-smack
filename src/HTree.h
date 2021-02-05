#pragma once

#include "HNode.h"
#include <string>
#include <vector>
#include "CodeTable.h"

struct HNodePtr{

    HNode* node = nullptr;
    HNode* operator *();
    bool operator < (const HNodePtr& o) const;
    bool operator > (const HNodePtr& o) const;
    HNodePtr(HNode* node);
    HNodePtr();

};

class HTree{

    HNodePtr root;

    void visit_write_code(HNode*& node, CodeTable& code_table, char code, int code_len);
    public:

    void construct_tree(std::vector<int>& freq_table);
    void get_codes_from_tree(CodeTable& code_table);
    void print_tree(HNode* root);
};