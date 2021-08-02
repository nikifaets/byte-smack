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

void HTree::create_code_table(CodeTable& code_table, std::vector<int> freq_table, Bitset& special){

    construct_tree(freq_table);
    get_codes_from_tree(code_table, special);

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

        
        code_table[*node->val] = code;
    }


    Bitset left = code;
    left.add(1);

    Bitset right = code;
    right.add(0);

    visit_write_code(node->left, code_table, left, code_len);
    visit_write_code(node->right, code_table, right, code_len);

}
void HTree::get_codes_from_tree(CodeTable& code_table, Bitset& special){

    HNode* root = *(this->root);
    HNode* furthest;
    find_furthest(furthest);
    Bitset start;
    visit_write_code(root, code_table, start, 0);

    special = code_table[*furthest->val];
    code_table[*furthest->val].add(0);
    special.add(1);



}

void HTree::find_furthest(HNode*& res){

    HNode* furthest = *root; 
    int max_distance = 0;
    visit_find_furthest(furthest, furthest, 0, max_distance);

    res = furthest;
    
}

void HTree::visit_find_furthest(HNode* node, HNode*& furthest, int distance, int& max_distance){

    if(node == nullptr) return;
    if(node->left == nullptr && node->left == nullptr){

        if(distance > max_distance){

             max_distance = distance;
             furthest = node;
        }
    }

    visit_find_furthest(node->left, furthest, ++distance, max_distance);
    visit_find_furthest(node->right, furthest, ++distance, max_distance);
    
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