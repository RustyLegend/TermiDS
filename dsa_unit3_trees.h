#ifndef DSA_UNIT3_TREES_H
#define DSA_UNIT3_TREES_H


struct ET_Node {
    char value;
    struct ET_Node *left;
    struct ET_Node *right;
};


void dsa_binary_tree();

void dsa_bst_operations();

void dsa_expression_tree();


#endif