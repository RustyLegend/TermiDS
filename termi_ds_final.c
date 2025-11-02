#include "dsa_common.h"
#include "dsa_unit1_lists.h"
#include "dsa_unit2_stackqueue.h"
#include "dsa_unit3_trees.h"
#include "dsa_unit4_searchsort.h"
#include "dsa_unit5_graphs.h"

const char *const sessional_topics_map[2][6][10] = {
    {
        {"Array Max/Min", "Single Linked List (All Ops)", "Double Linked List (All Ops)", "Circular Linked List (All Ops)", "Polynomial Linked List Creation", "Polynomial Add/Sub", NULL},
        {"Count Sort and Radix Sort", "Stack Operations", "Queue Operations", "Infix to Postfix Conversion", "String Reversal using Stack", "Postfix Evaluation", "Balancing Symbols", NULL},
        {NULL}
    },
    {
        {"Binary Tree", "Binary Search Tree", "Expression Tree", NULL},
        {"Hash Table (Insert/Delete)", "Linear Search", "Binary Search", "Insertion Sort", "Quick Sort", "Merge Sort", "Heap Sort", NULL},
        {"Depth First Search (DFS)", "Breadth First Search (BFS)", "Dijkstra's Shortest Path", NULL}
    }
};

void _display_main_menu();
void _handle_sessional(int sessional_num);
void _handle_unit_topics(int sessional_idx, int unit_rel_idx, const char *unit_name);
void _dispatch_topic(const char *topic_name);

int main() {
    int choice;
    _loading_animation();

    do {
        _display_main_menu();
        if (scanf("%d", &choice) != 1) {
            choice = -1;
        }
        clear_input_buffer();

        switch (choice) {
            case 1:
            case 2:
                _handle_sessional(choice);
                break;
            case 0:
                printf("Thank you for using TermiDS! Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please select 1, 2, or 0. \n");
                _press_enter_to_continue();
                break;
        }
    } while (choice != 0);

    return 0;
}

void _display_main_menu() {
    _clear_screen();
    printf("==========================================\n");
    printf("| WELCOME TO TERMID S             |\n");
    printf("| C-DSA Logic Guide (Senior View) |\n");
    printf("==========================================\n");
    printf(" 1. Sessional 1 (Units 1 & 2)\n");
    printf(" 2. Sessional 2 (Units 3, 4 & 5)\n");
    printf("------------------------------------------\n");
    printf(" 0. Exit TermiDS\n");
    printf("Enter your choice: ");
}

void _handle_sessional(int sessional_num) {
    int choice;
    int sessional_idx = sessional_num - 1;

    const char *unit_names[3] = {NULL};
    if (sessional_num == 1) {
        unit_names[0] = "Introduction to Lists";
        unit_names[1] = "Stacks and Queues";
    } else {
        unit_names[0] = "Trees";
        unit_names[1] = "Hashing, Searching, Sorting";
        unit_names[2] = "Graphs";
    }

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("> Sessional %d - Units Selection < \n", sessional_num);
        printf("------------------------------------------\n");
        
        if (sessional_num == 1) {
            printf(" 1. Unit 1: %s\n", unit_names[0]);
            printf(" 2. Unit 2: %s\n", unit_names[1]);
        } else {
            printf(" 1. Unit 3: %s\n", unit_names[0]);
            printf(" 2. Unit 4: %s\n", unit_names[1]);
            printf(" 3. Unit 5: %s\n", unit_names[2]);
        }
        
        printf(" 9. Back to Main Menu\n");
        printf(" 0. Exit TermiDS\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        if (sessional_num == 1) {
            if (choice == 1) _handle_unit_topics(sessional_idx, 0, unit_names[0]);
            else if (choice == 2) _handle_unit_topics(sessional_idx, 1, unit_names[1]);
            else if (choice == 9) return;
            else if (choice == 0) exit(0);
            else { printf("Invalid choice.\n"); _press_enter_to_continue(); }
        } else {
            if (choice >= 1 && choice <= 3) { _handle_unit_topics(sessional_idx, choice - 1, unit_names[choice - 1]); }
            else if (choice == 9) return;
            else if (choice == 0) exit(0);
            else { printf("Invalid choice.\n"); _press_enter_to_continue(); }
        }
    } while (1);
}

void _handle_unit_topics(int sessional_idx, int unit_rel_idx, const char *unit_name) {
    int choice;
    const char *const *topics = sessional_topics_map[sessional_idx][unit_rel_idx];
    int topic_count = 0;
    for (topic_count = 0; topics[topic_count] != NULL; ++topic_count);

    do {
        _clear_screen();
        printf("====================================================\n");
        printf("| TERMID S: Content Viewer - %-20s |\n", unit_name);
        printf("====================================================\n");
        printf(" | UNIT %d: %-30s|\n", (sessional_idx * 2) + unit_rel_idx + 1, unit_name);
        printf("----------------------------------------------------\n");

        for (int i = 0; i < topic_count; ++i) {
            printf("|%2d. %-35s |\n", i + 1, topics[i]);
        }

        printf("| 9. Back to Sessional Menu              |\n");
        printf("| 0. Exit TermiDS                        |\n");
        printf("+----------------------------------------+\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        if (choice >= 1 && choice <= topic_count) {
            _dispatch_topic(topics[choice - 1]);
        } else if (choice == 9) {
            return;
        } else if (choice == 0) {
            printf("Thank you for using TermiDS! Exiting...\n");
            exit(0);
        } else {
            printf("Invalid choice.\n");
            _press_enter_to_continue();
        }
    } while (1);
}

void _dispatch_topic(const char *topic_name) {
    
    if (strcmp(topic_name, "Array Max/Min") == 0) {
        dsa_array_max_min();
    } else if (strcmp(topic_name, "Single Linked List (All Ops)") == 0) {
        dsa_sll_operations();
    } else if (strcmp(topic_name, "Double Linked List (All Ops)") == 0) {
        dsa_dll_operations();
    } else if (strcmp(topic_name, "Circular Linked List (All Ops)") == 0) {
        dsa_cll_operations();
    } else if (strcmp(topic_name, "Polynomial Linked List Creation") == 0) {
        dsa_poly_create();
    } else if (strcmp(topic_name, "Polynomial Add/Sub") == 0) {
        dsa_poly_add_sub();
    } 
    
    else if (strcmp(topic_name, "Count Sort and Radix Sort") == 0) {
        dsa_count_radix_sort();
    } else if (strcmp(topic_name, "Stack Operations") == 0) {
        dsa_stack_operations();
    } else if (strcmp(topic_name, "Queue Operations") == 0) {
        dsa_queue_operations();
    } else if (strcmp(topic_name, "Infix to Postfix Conversion") == 0) {
        dsa_infix_to_postfix();
    } else if (strcmp(topic_name, "String Reversal using Stack") == 0) {
        dsa_string_reversal_stack();
    } else if (strcmp(topic_name, "Postfix Evaluation") == 0) {
        dsa_postfix_evaluation();
    } else if (strcmp(topic_name, "Balancing Symbols") == 0) {
        dsa_balancing_symbols();
    } 
    
    else if (strcmp(topic_name, "Binary Tree") == 0) {
        dsa_binary_tree();
    } else if (strcmp(topic_name, "Binary Search Tree") == 0) {
        dsa_bst_operations();
    } else if (strcmp(topic_name, "Expression Tree") == 0) {
        dsa_expression_tree();
    } 
    
    else if (strcmp(topic_name, "Hash Table (Insert/Delete)") == 0) {
        dsa_hash_table();
    } else if (strcmp(topic_name, "Linear Search") == 0) {
        dsa_linear_search();
    } else if (strcmp(topic_name, "Binary Search") == 0) {
        dsa_binary_search();
    } else if (strcmp(topic_name, "Insertion Sort") == 0) {
        dsa_insertion_sort();
    } else if (strcmp(topic_name, "Quick Sort") == 0) {
        dsa_quick_sort();
    } else if (strcmp(topic_name, "Merge Sort") == 0) {
        dsa_merge_sort();
    } else if (strcmp(topic_name, "Heap Sort") == 0) {
        dsa_heap_sort();
    } 
    
    else if (strcmp(topic_name, "Depth First Search (DFS)") == 0) {
        dsa_dfs();
    } else if (strcmp(topic_name, "Breadth First Search (BFS)") == 0) {
        dsa_bfs();
    } else if (strcmp(topic_name, "Dijkstra's Shortest Path") == 0) {
        dsa_dijkstra();
    }
    
    else {
        _display_content_placeholder(topic_name);
    }
}