#ifndef DSA_COMMON_H
#define DSA_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

// Utility function prototypes
void _clear_screen();
void clear_input_buffer();
void _press_enter_to_continue();
void _display_content_placeholder(const char *topic_name);
void _loading_animation();
int* get_array(int *n);
int* get_positive_array(int *n);
void print_array(int arr[], int size);
int get_max(int arr[], int n);
struct BST_Node {
    int data;
    struct BST_Node *left;
    struct BST_Node *right;
};
struct BST_Node* g_tree_free(struct BST_Node *root);
void g_tree_print_ascii(struct BST_Node* root);
#endif // DSA_COMMON_H