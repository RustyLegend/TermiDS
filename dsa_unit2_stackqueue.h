#ifndef DSA_UNIT2_STACKQUEUE_H
#define DSA_UNIT2_STACKQUEUE_H

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

void dsa_count_radix_sort();

void dsa_stack_operations();

void dsa_queue_operations();

void dsa_infix_to_postfix();

void dsa_string_reversal_stack();

void dsa_postfix_evaluation();

void dsa_balancing_symbols();


#endif