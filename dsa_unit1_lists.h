#ifndef DSA_UNIT1_LISTS_H
#define DSA_UNIT1_LISTS_H

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

void dsa_array_max_min();
void dsa_sll_operations();
void dsa_dll_operations();
void dsa_cll_operations();
void dsa_poly_create();
void dsa_poly_add_sub();

#endif