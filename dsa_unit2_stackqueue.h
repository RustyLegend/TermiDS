#ifndef DSA_UNIT2_STACKQUEUE_H
#define DSA_UNIT2_STACKQUEUE_H

// --- Structs for Unit 2 ---

#define STACK_SIZE 10
struct Stack {
    int items[STACK_SIZE];
    int top;
};

#define QUEUE_SIZE 5
struct Queue {
    int items[QUEUE_SIZE];
    int front, rear, count;
};


// --- Function Prototypes for Unit 2 ---

// Topic: Sorts (from Unit 2 list)
void dsa_count_radix_sort();

// Topic: Stack Operations
void dsa_stack_operations();

// Topic: Queue Operations
void dsa_queue_operations();

// Topic: Infix to Postfix
void dsa_infix_to_postfix();

// Topic: String Reversal
void dsa_string_reversal_stack();

// Topic: Postfix Evaluation
void dsa_postfix_evaluation();

// Topic: Balancing Symbols
void dsa_balancing_symbols();


#endif // DSA_UNIT2_STACKQUEUE_H