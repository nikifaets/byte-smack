#pragma once

#include "HNode.h"
#include <string>
#include <vector>
#include "Global.h"
#include <memory>

struct HNodePtr{

    std::shared_ptr<HNode> node = nullptr;
    std::shared_ptr<HNode> operator *();
    bool operator < (const HNodePtr& o) const;
    bool operator > (const HNodePtr& o) const;
    HNodePtr(std::shared_ptr<HNode> node);
    HNodePtr();

};

class HTree{

    HNodePtr root;

    void visit_write_code(std::shared_ptr<HNode>& node, CodeTable& code_table, Bitset code, int code_len);
    void find_furthest(std::shared_ptr<HNode>& res);
    void visit_find_furthest(std::shared_ptr<HNode>& node, std::shared_ptr<HNode>& furthest, int distance, int& max_distance) const;
    public:

    void construct_tree(std::vector<int>& freq_table);
    void get_codes_from_tree(CodeTable& code_table, Bitset& special);
    void print_tree(const std::shared_ptr<HNode>& root) const;
    void create_code_table(CodeTable& code_table, std::vector<int> freq_table, Bitset& special);
};