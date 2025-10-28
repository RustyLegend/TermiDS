#ifndef DSA_UNIT3_TREES_H
#define DSA_UNIT3_TREES_H

// --- Structs for Unit 3 ---

// Node for Binary Search Tree (BST)


struct ET_Node {
    char value; // Stores operands (a, b) or operators (+, *)
    struct ET_Node *left;
    struct ET_Node *right;
};

// --- Function Prototypes for Unit 3 ---

// Topic: Binary Tree
void dsa_binary_tree();

// Topic: Binary Search Tree (BST)
void dsa_bst_operations();

// Topic: Expression Tree
void dsa_expression_tree();


#endif // DSA_UNIT3_TREES_H