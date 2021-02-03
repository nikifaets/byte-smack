#include "HTree.h"
#include <queue>
#include <iostream>

HNode* HTree::construct_tree(std::vector<int>& freq_table){

    std::priority_queue<HNode*> q;

    for(int i=0; i<freq_table.size(); i++){

        if(freq_table[i] > 0){

            char val1 = i;
            char* val = new char[2];
            *val = i;
            val[1] = '\0';
            
            std::cout << "Creating queue; node with val " << val << " " << i << std::endl;
            q.push(new HNode(freq_table[i],  val));
        }
    }

    while(q.size() != 1){

        std::cout << "sdf" << std::endl;
        HNode* top1 = q.top();
        q.pop();
        HNode* top2 = q.top();
        q.pop();

        int top1_count = top1->get_count();
        int top2_count = top2->get_count();
        HNode* merged = new HNode(top1_count + top2_count, top2, top1);

        q.push(merged);   
    }

    HNode* root = q.top();

    print_tree(root);
    return root;
}

void HTree::print_tree(HNode* root){

    if(root == nullptr) return;
    std::cout << "Node:" << std::endl;
    std::cout << "Count: " << root->get_count() << " ";
    if(root->get_value() != nullptr) std::cout << root->get_value() << std::endl;
    if(root->left) std::cout << "Left: " << root->left->count << " ";
    if(root->right) std::cout << "Right: " << root->right->count << std::endl;
    print_tree(root->left);
    print_tree(root->right);
    std::cout << "--------------" << std::endl;
    
}