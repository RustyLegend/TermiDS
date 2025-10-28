#ifndef DSA_UNIT1_LISTS_H
#define DSA_UNIT1_LISTS_H

// --- Structs for Unit 1 ---

// Node for Singly Linked List (SLL)
struct SLL_Node {
    int data;
    struct SLL_Node *next;
};

struct DLL_Node {
    int data;
    struct DLL_Node *next;
    struct DLL_Node *prev;
};

struct DLL_List {
    struct DLL_Node *head;
    struct DLL_Node *tail;
};

struct Poly_Node {
    int coefficient;
    int exponent;
    struct Poly_Node *next;
};


// --- Function Prototypes for Unit 1 ---

// Topic: Array Max/Min
void dsa_array_max_min();

// Topic: Singly Linked List (SLL)
void dsa_sll_operations();

// Topic: Doubly Linked List (DLL)
void dsa_dll_operations();

// Topic: Circular Linked List (CLL)
void dsa_cll_operations();

// Topic: Polynomial Creation
void dsa_poly_create();

// Topic: Polynomial Add/Sub
void dsa_poly_add_sub();


#endif // DSA_UNIT1_LISTS_H