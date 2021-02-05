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

            byte val1 = i;
            byte* val = new byte[2];
            *val = i;
            val[1] = '\0';
            
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

    print_tree(*(this->root));
}

void HTree::visit_write_code(HNode*& node, CodeTable& code_table, byte code, int code_len){

    if(node == nullptr) return;
    if(node->right == nullptr && node->left == nullptr){

        CodeLengthPair cl(code, code_len);
        code_table[*node->val] = cl;
    }


    byte leftmost_one = 0b10000000;
    byte next_code_left = (code | ( leftmost_one >> code_len));
    code_len++;
    
    byte next_code_right = code;

    visit_write_code(node->left, code_table, next_code_left, code_len);
    visit_write_code(node->right, code_table, next_code_right, code_len);

}
void HTree::get_codes_from_tree(CodeTable& code_table){

    HNode* root = *(this->root);
    visit_write_code(root, code_table, 0, 0);

}

void HTree::print_tree(HNode* root){

    if(root == nullptr) return;
    std::cout << "Node:" << std::endl;
    std::cout << "Count: " << root->get_count() << " ";
    if(root->get_value() != nullptr) std::cout << "Val: " << root->get_value() << std::endl;
    if(root->left) std::cout << "Left: " << root->left->count << " ";
    if(root->right) std::cout << "Right: " << root->right->count << std::endl;
    print_tree(root->left);
    print_tree(root->right);
    std::cout << "--------------" << std::endl;
    
}