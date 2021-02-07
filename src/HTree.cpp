#include "HTree.h"
#include <queue>
#include <iostream>

HNode* HNodePtr::operator*(){

    return node;
}

bool HNodePtr::operator < (const HNodePtr& o) const{

    return this->node->count < o.node->count;
}

bool HNodePtr::operator > (const HNodePtr& o) const{

    return this->node->count > o.node->count;
}
HNodePtr::HNodePtr(HNode* node) : node(node) {}

HNodePtr::HNodePtr() {}

void HTree::create_code_table(CodeTable& code_table, std::vector<int> freq_table){

    construct_tree(freq_table);
    get_codes_from_tree(code_table);

}
void HTree::construct_tree(std::vector<int>& freq_table){

    std::priority_queue<HNodePtr, std::vector<HNodePtr>, std::greater<HNodePtr>> q;

    for(int i=0; i<freq_table.size(); i++){

        if(freq_table[i] > 0){

            byte* val = new byte;
            *val = i;
            
            q.push(HNodePtr(new HNode(freq_table[i], val)));
        }
    }

    while(q.size() > 1){

        HNodePtr top1_ptr = q.top();
        q.pop();
        HNodePtr top2_ptr = q.top();
        q.pop();

        HNode* top1 = *top1_ptr;
        HNode* top2 = *top2_ptr;
        int top1_count = (top1)->get_count();
        int top2_count = (top2)->get_count();


        HNodePtr merged = HNodePtr(new HNode(top1_count + top2_count, top1, top2));

        q.push(merged);   
    }

    this->root = q.top();

}

void HTree::visit_write_code(HNode*& node, CodeTable& code_table, Bitset code, int code_len){

    if(node == nullptr) return;
    if(node->right == nullptr && node->left == nullptr){

        std::cout << "Node name " << *node->val << " code len " << code.size() << std::endl;
        
        std::cout << "Code: " << (std::string)code << std::endl;
        code_table[*node->val] = code;
    }


    Bitset left = code;
    left.add(1);

    Bitset right = code;
    right.add(0);

    visit_write_code(node->left, code_table, left, code_len);
    visit_write_code(node->right, code_table, right, code_len);

}
void HTree::get_codes_from_tree(CodeTable& code_table){

    HNode* root = *(this->root);
    Bitset start;
    visit_write_code(root, code_table, start, 0);

}

void HTree::print_tree(HNode* root){

    if(root == nullptr) return;
    std::cout << "Node:" << std::endl;
    std::cout << "Count: " << root->get_count() << " ";
    if(root->get_value() != nullptr) std::cout << "Val: " << *root->get_value() << std::endl;
    if(root->left) std::cout << "Left: " << root->left->count << " ";
    if(root->right) std::cout << "Right: " << root->right->count << std::endl;
    print_tree(root->left);
    print_tree(root->right);
    std::cout << "--------------" << std::endl;
    
}