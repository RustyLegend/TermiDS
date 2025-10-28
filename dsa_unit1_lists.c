#include "dsa_unit1_lists.h"
#include "dsa_common.h"

// --- Helper Functions (Internal to this file) ---

static struct DLL_Node* dll_create_node(int data);
static void dll_insert_front(struct DLL_List *list);
static void dll_insert_end(struct DLL_List *list);
static void dll_delete_node(struct DLL_List *list);
static void dll_free_list(struct DLL_List *list);
static void dll_insert_at_pos(struct DLL_List *list);
static void dll_delete_front(struct DLL_List *list);
static void dll_delete_end(struct DLL_List *list);
static void dll_delete_at_pos(struct DLL_List *list);

static struct DLL_Node* dcll_create_node(int data);
static void dcll_insert_front(struct DLL_List *list);
static void dcll_insert_end(struct DLL_List *list);
static void dcll_delete_node(struct DLL_List *list);
static void dcll_free_list(struct DLL_List *list);
static void dcll_insert_at_pos(struct DLL_List *list);
static void dcll_delete_front(struct DLL_List *list);
static void dcll_delete_end(struct DLL_List *list);
static void dcll_delete_at_pos(struct DLL_List *list);

/**
 * @brief (SLL) Displays the list.
 */
void sll_display(struct SLL_Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct SLL_Node *temp = head;

    // Vertical display
    printf("\n HEAD\n");
    printf("  |\n");
    printf("  v\n");
    printf("  "); // Indent to align with the 'v'

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/**
 * @brief (DLL) Displays the list from head to tail.
 */
static void dll_display_forward(struct DLL_List *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct DLL_Node *temp = list->head;

    // Vertical display
    printf("\n HEAD\n");
    printf("  |\n");
    printf("  v\n");
    printf("  "); // Indent to align

    while (temp != NULL) {
        printf("%d", temp->data);

        // Also explicitly label the tail node
        if (temp == list->tail) {
            printf(" (TAIL)");
        }

        if (temp->next != NULL) {
            printf(" <-> ");
        }
        temp = temp->next;
    }
    printf(" -> NULL\n");
}

/**
 * @brief (D-CLL) Displays the list from head to tail.
 */
static void dcll_display_forward(struct DLL_List *list) {
    if (list->head == NULL) {
        printf("Doubly CLL is empty.\n");
        return;
    }
    struct DLL_Node *temp = list->head;

    printf("\n HEAD\n");
    printf("  |\n");
    printf("  v\n");
    printf("  ");

    do {
        printf("%d", temp->data);
        if (temp == list->head) printf(" (HEAD)");
        if (temp == list->tail) printf(" (TAIL)");

        temp = temp->next; // Move to next node

        // Only print arrow if we are not at the end of the loop
        if (temp != list->head) {
            printf(" <-> ");
        }
    } while (temp != list->head);

    printf("(to HEAD)\n");
}

// (Add these inside dsa_unit1_lists.c, with the other SLL helpers)

/** @brief (SLL) Inserts a node at a specific position (1-based index). */
static struct SLL_Node* sll_insert_at_pos(struct SLL_Node *head) {
    int pos, data, k = 1;
    printf("Enter position (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return head; }
    clear_input_buffer();

    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
    if (!newNode) { printf("Memory allocation failed!\n"); return head; }
    newNode->data = data;
    newNode->next = NULL;

    // Case 1: Insert at the beginning
    if (pos == 1) {
        newNode->next = head;
        printf("Inserted %d at position %d (new head).\n", data, pos);
        return newNode;
    }

    // Case 2: Traverse to the node *before* the desired position
    struct SLL_Node *temp = head;
    while (temp != NULL && k < pos - 1) {
        temp = temp->next;
        k++;
    }

    // Case 3: Position is out of bounds (beyond the end + 1)
    if (temp == NULL) {
        printf("Position %d is out of bounds (List length: %d).\n", pos, k);
        free(newNode);
        return head;
    }

    // Case 4: Insert in the middle or at the end
    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", data, pos);
    return head;
}

/** @brief (SLL) Deletes the node at the beginning. */
static struct SLL_Node* sll_delete_front(struct SLL_Node *head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    struct SLL_Node *temp = head;
    head = head->next;
    printf("Deleted node with value %d (from head).\n", temp->data);
    free(temp);
    return head;
}

/** @brief (SLL) Deletes the node at the end. */
static struct SLL_Node* sll_delete_end(struct SLL_Node *head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    // Case 1: Only one node
    if (head->next == NULL) {
        printf("Deleted node with value %d (last node).\n", head->data);
        free(head);
        return NULL;
    }
    // Case 2: Traverse to the second-to-last node
    struct SLL_Node *temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    // Now temp points to the second-to-last node
    struct SLL_Node *lastNode = temp->next;
    temp->next = NULL; // Unlink the last node
    printf("Deleted node with value %d (from end).\n", lastNode->data);
    free(lastNode);
    return head;
}

/** @brief (SLL) Deletes the node at a specific position (1-based index). */
static struct SLL_Node* sll_delete_at_pos(struct SLL_Node *head) {
    int pos, k = 1;
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    printf("Enter position to delete (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return head; }
    clear_input_buffer();

    struct SLL_Node *temp = head, *prev = NULL;

    // Case 1: Delete the head node
    if (pos == 1) {
        head = temp->next;
        printf("Deleted node at position %d (value: %d).\n", pos, temp->data);
        free(temp);
        return head;
    }

    // Case 2: Traverse to find the node at position 'pos'
    while (temp != NULL && k < pos) {
        prev = temp;
        temp = temp->next;
        k++;
    }

    // Case 3: Position is out of bounds
    if (temp == NULL) {
        printf("Position %d is out of bounds (List length: %d).\n", pos, k-1);
        return head;
    }

    // Case 4: Unlink the node from the list
    prev->next = temp->next;
    printf("Deleted node at position %d (value: %d).\n", pos, temp->data);
    free(temp);
    return head;
}

// SLL: Insert at beginning
struct SLL_Node* sll_insert_front(struct SLL_Node *head) {
    int data;
    struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }
    printf("Enter data for new node: ");
    scanf("%d", &data);
    clear_input_buffer();
    
    newNode->data = data;
    newNode->next = head;
    printf("Inserted %d at the front.\n", data);
    return newNode; // New node is now the new head
}

// SLL: Insert at end
struct SLL_Node* sll_insert_end(struct SLL_Node *head) {
    int data;
    struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return head;
    }
    printf("Enter data for new node: ");
    scanf("%d", &data);
    clear_input_buffer();
    
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) { // List is empty
        printf("Inserted %d at the end (new head).\n", data);
        return newNode;
    }
    
    struct SLL_Node *temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
    printf("Inserted %d at the end.\n", data);
    return head;
}

// SLL: Delete a node by value
struct SLL_Node* sll_delete_node(struct SLL_Node *head) {
    int key;
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    
    printf("Enter data value to delete: ");
    scanf("%d", &key);
    clear_input_buffer();

    struct SLL_Node *temp = head, *prev = NULL;

    // Case 1: Head node holds the key
    if (temp != NULL && temp->data == key) {
        head = temp->next; // Changed head
        free(temp);        // free old head
        printf("Deleted node with value %d (from head).\n", key);
        return head;
    }

    // Case 2: Search for the key, keeping track of previous
    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // Case 3: Key not in list
    if (temp == NULL) {
        printf("Value %d not found in list.\n", key);
        return head;
    }

    // Case 4: Key found, unlink the node
    prev->next = temp->next;
    free(temp); // Free memory
    printf("Deleted node with value %d.\n", key);
    return head;
}

// SLL: Free the entire list (cleanup)
struct SLL_Node* sll_free_list(struct SLL_Node *head) {
    struct SLL_Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("List memory freed.\n");
    return NULL; // List is now empty
}


// --- Main Topic Functions (Called by Dispatcher) ---

/**
 * @brief Topic 1: Array Max/Min
 */
void dsa_array_max_min() {
    // This is the implementation from our previous session.
    int n, i, min, max;
    int *arr;

    _clear_screen();
    printf("==========================================\n");
    printf("| Array: Find Max/Min                     |\n");
    printf("==========================================\n");
    
    printf("Enter number of elements: ");
    if(scanf("%d", &n) != 1) { n = 0; }
    clear_input_buffer();

    if (n <= 0) {
        printf("Invalid size.\n");
        _press_enter_to_continue();
        return;
    }

    arr = (int*) malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        _press_enter_to_continue();
        return;
    }

    printf("Enter %d elements:\n", n);
    for (i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        if(scanf("%d", &arr[i]) != 1) { arr[i] = 0; }
        clear_input_buffer();
    }

    min = arr[0];
    max = arr[0];
    for (i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    printf("\n--- Results ---\n");
    printf("Minimum element: %d\n", min);
    printf("Maximum element: %d\n", max);

    free(arr); 
    _press_enter_to_continue();
}

/**
 * @brief Topic 2: Singly Linked List Sub-Menu
 */
void dsa_sll_operations() {
    struct SLL_Node *head = NULL; // Start with an empty list
    int choice;

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Singly Linked List Operations           |\n");
        printf("==========================================\n");
        sll_display(head); // Display happens automatically
        printf("------------------------------------------\n");
        printf(" 1. Insert at Front\n");
        printf(" 2. Insert at End\n");
        printf(" 3. Insert at Position\n");
        printf(" 4. Delete at Front\n");
        printf(" 5. Delete at End\n");
        printf(" 6. Delete at Position\n");
        printf(" 7. Delete by Value\n");
        // Removed "8. Display List"
        printf(" 8. Back to Topics Menu\n"); // Renumbered from 9
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1: head = sll_insert_front(head); break;
            case 2: head = sll_insert_end(head); break;
            case 3: head = sll_insert_at_pos(head); break;
            case 4: head = sll_delete_front(head); break;
            case 5: head = sll_delete_end(head); break;
            case 6: head = sll_delete_at_pos(head); break;
            case 7: head = sll_delete_node(head); break;
            // Removed case 8 (Display)
            case 8: head = sll_free_list(head); return; // Renumbered from 9
            default: printf("Invalid choice. Please try again.\n");
        }
        // Only pause if not going back
        if (choice != 8) { // Renumbered from 9
            _press_enter_to_continue();
        }
    } while (choice != 8); // Renumbered from 9
}

// (Add these inside dsa_unit1_lists.c, with the other DLL helpers)

/** @brief (DLL) Inserts a node at a specific position (1-based index). */
static void dll_insert_at_pos(struct DLL_List *list) {
    int pos, data, k = 1;
    printf("Enter position (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return; }
    clear_input_buffer();

    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    // Handle insertion at beginning separately (more efficient)
    if (pos == 1) {
        dll_insert_front(list); // Reuse existing function
        return;
    }

    struct DLL_Node *newNode = dll_create_node(data);
    if (!newNode) return;

    // Traverse to the node *before* the desired position
    struct DLL_Node *temp = list->head;
    while (temp != NULL && k < pos - 1) {
        temp = temp->next;
        k++;
    }

    // Case 1: Position is out of bounds
    if (temp == NULL) {
        printf("Position %d is out of bounds (List length: %d).\n", pos, k);
        free(newNode);
        return;
    }

    // Case 2: Insert at the end (temp points to the second-to-last node)
    if (temp->next == NULL) {
        // Can reuse insert_end logic slightly modified
        newNode->prev = list->tail; // Should be same as temp
        list->tail->next = newNode;
        list->tail = newNode;
        printf("Inserted %d at position %d (new tail).\n", data, pos);
    }
    // Case 3: Insert in the middle
    else {
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        printf("Inserted %d at position %d.\n", data, pos);
    }
}

/** @brief (DLL) Deletes the node at the beginning. */
static void dll_delete_front(struct DLL_List *list) {
    if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct DLL_Node *temp = list->head;
    list->head = list->head->next;

    if (list->head != NULL) {
        list->head->prev = NULL; // Update new head's prev
    } else {
        list->tail = NULL; // List became empty
    }
    printf("Deleted node with value %d (from head).\n", temp->data);
    free(temp);
}

/** @brief (DLL) Deletes the node at the end. */
static void dll_delete_end(struct DLL_List *list) {
    if (list->tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct DLL_Node *temp = list->tail;
    list->tail = list->tail->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL; // Update new tail's next
    } else {
        list->head = NULL; // List became empty
    }
    printf("Deleted node with value %d (from tail).\n", temp->data);
    free(temp);
}

/** @brief (DLL) Deletes the node at a specific position (1-based index). */
static void dll_delete_at_pos(struct DLL_List *list) {
    int pos, k = 1;
     if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    printf("Enter position to delete (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return; }
    clear_input_buffer();

    // Handle delete front separately
    if (pos == 1) {
        dll_delete_front(list);
        return;
    }

    // Traverse to find the node at position 'pos'
    struct DLL_Node *temp = list->head;
    while (temp != NULL && k < pos) {
        temp = temp->next;
        k++;
    }

    // Case 1: Position is out of bounds
    if (temp == NULL) {
        printf("Position %d is out of bounds (List length: %d).\n", pos, k-1);
        return;
    }

    // Case 2: Unlink the node (temp is the node to delete)
    temp->prev->next = temp->next;

    // Handle deleting the tail node
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        list->tail = temp->prev; // Update tail pointer
    }

    printf("Deleted node at position %d (value: %d).\n", pos, temp->data);
    free(temp);
}

/**
 * @brief Topic 3: Doubly Linked List (Stub)
 */
static struct DLL_Node* dll_create_node(int data) {
    struct DLL_Node *newNode = (struct DLL_Node*) malloc(sizeof(struct DLL_Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

/**
 * @brief (DLL) Inserts a new node at the front (head) of the list.
 */
static void dll_insert_front(struct DLL_List *list) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct DLL_Node *newNode = dll_create_node(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        // List is empty
        list->head = newNode;
        list->tail = newNode;
    } else {
        // List is not empty
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    printf("Inserted %d at the front.\n", data);
}

/**
 * @brief (DLL) Inserts a new node at the end (tail) of the list.
 */
static void dll_insert_end(struct DLL_List *list) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct DLL_Node *newNode = dll_create_node(data);
    if (newNode == NULL) return;

    if (list->tail == NULL) {
        // List is empty
        list->head = newNode;
        list->tail = newNode;
    } else {
        // List is not empty
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    printf("Inserted %d at the end.\n", data);
}

/**
 * @brief (DLL) Deletes a node by its data value.
 */
static void dll_delete_node(struct DLL_List *list) {
    int key;
    if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    
    printf("Enter data value to delete: ");
    if(scanf("%d", &key) != 1) { key = 0; }
    clear_input_buffer();

    struct DLL_Node *temp = list->head;

    // Find the node
    while (temp != NULL && temp->data != key) {
        temp = temp->next;
    }

    // Case 1: Node not found
    if (temp == NULL) {
        printf("Value %d not found in list.\n", key);
        return;
    }

    // Case 2: Node is found (temp is the node to delete)

    // Fix the 'next' pointer of the *previous* node
    if (temp->prev != NULL) {
        // It's not the head node
        temp->prev->next = temp->next;
    } else {
        // It *is* the head node
        list->head = temp->next;
    }

    // Fix the 'prev' pointer of the *next* node
    if (temp->next != NULL) {
        // It's not the tail node
        temp->next->prev = temp->prev;
    } else {
        // It *is* the tail node
        list->tail = temp->prev;
    }

    free(temp); // Free the memory
    printf("Deleted node with value %d.\n", key);
}

/**
 * @brief (DLL) Frees all memory used by the list.
 */
static void dll_free_list(struct DLL_List *list) {
    struct DLL_Node *temp = list->head;
    struct DLL_Node *next;
    
    while (temp != NULL) {
        next = temp->next;
        free(temp);
        temp = next;
    }
    
    list->head = NULL;
    list->tail = NULL;
    printf("Doubly Linked List memory freed.\n");
}

/**
 * @brief Topic 3: Doubly Linked List Sub-Menu
 * This is the main function called by the dispatcher.
 */
void dsa_dll_operations() {
    // Create the list manager on the stack
    struct DLL_List list;
    list.head = NULL;
    list.tail = NULL;
    
    int choice;

    // (Replace the do-while loop inside dsa_dll_operations)
    // (Replace the do-while loop inside dsa_dll_operations)
    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Doubly Linked List Operations           |\n");
        printf("==========================================\n");
        dll_display_forward(&list); // Display happens automatically
        printf("------------------------------------------\n");
        printf(" 1. Insert at Front\n");
        printf(" 2. Insert at End\n");
        printf(" 3. Insert at Position\n");
        printf(" 4. Delete at Front\n");
        printf(" 5. Delete at End\n");
        printf(" 6. Delete at Position\n");
        printf(" 7. Delete by Value\n");
        printf(" 8. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1: dll_insert_front(&list); break;
            case 2: dll_insert_end(&list); break;
            case 3: dll_insert_at_pos(&list); break;
            case 4: dll_delete_front(&list); break;
            case 5: dll_delete_end(&list); break;
            case 6: dll_delete_at_pos(&list); break;
            case 7: dll_delete_node(&list); break;
            case 8: dll_free_list(&list); return; // Renumbered from 10
            default: printf("Invalid choice. Please try again.\n");
        }
        _press_enter_to_continue(); // Pause after each operation (except exit)
    } while (choice != 8); // Renumbered from 10
}

/**
 * @brief Topic 4: Circular Linked List (Stub)
 */
// (This code goes into dsa_unit1_lists.c)

// ====================================================================
// --- 1. Helper Functions for Singly Circular Linked List (CLL) ---
// ====================================================================
// (This is the code I gave you last time, just renamed)

/**
 * @brief (S-CLL) Displays the list.
 */

// (Add these inside dsa_unit1_lists.c, with the other S-CLL helpers)

/** @brief (S-CLL) Inserts a node at a specific position (1-based index). */
static struct SLL_Node* scll_insert_at_pos(struct SLL_Node *tail) {
    int pos, data, k = 1;
    printf("Enter position (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return tail; }
    clear_input_buffer();

    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    // Handle empty list case separately
    if (tail == NULL) {
        if (pos == 1) {
            struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
            if (!newNode) { printf("Memory allocation failed!\n"); return NULL; }
            newNode->data = data;
            newNode->next = newNode; // Points to itself
            printf("Inserted %d at position 1 (list was empty).\n", data);
            return newNode; // Becomes the new tail
        } else {
            printf("Position %d is out of bounds (List is empty).\n", pos);
            return NULL;
        }
    }

    // Handle insert at front (position 1)
    if (pos == 1) {
        struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
        if (!newNode) { printf("Memory allocation failed!\n"); return tail; }
        newNode->data = data;
        newNode->next = tail->next; // Point to old head
        tail->next = newNode;       // Tail points to new head
        printf("Inserted %d at position 1 (new head).\n", data);
        return tail; // Tail doesn't change
    }

    // Traverse to find the node *before* the desired position
    struct SLL_Node *temp = tail->next; // Start at head
    while (temp != tail && k < pos - 1) { // Stop before reaching tail unless it's the target spot
        temp = temp->next;
        k++;
    }

    // Check if position is valid
    // We need k == pos - 1. If temp == tail and k is still less, pos is too large.
    if (k < pos - 1 || (temp == tail && k < pos - 1) ) {
         printf("Position %d is out of bounds.\n", pos);
         return tail;
    }

    // Insert the new node
    struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
    if (!newNode) { printf("Memory allocation failed!\n"); return tail; }
    newNode->data = data;
    newNode->next = temp->next;
    temp->next = newNode;

    // Handle insertion *after* the current tail (making it the new tail)
    if (temp == tail) {
        tail = newNode;
        printf("Inserted %d at position %d (new tail).\n", data, pos);
    } else {
        printf("Inserted %d at position %d.\n", data, pos);
    }

    return tail;
}


/** @brief (S-CLL) Deletes the node at the beginning (head). */
static struct SLL_Node* scll_delete_front(struct SLL_Node *tail) {
    if (tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    struct SLL_Node *head = tail->next;
    printf("Deleted node with value %d (from head).\n", head->data);

    if (head == tail) { // Only one node in the list
        free(head);
        return NULL; // List is now empty
    } else {
        tail->next = head->next; // Tail points to the new head
        free(head);
        return tail; // Tail remains the same
    }
}

/** @brief (S-CLL) Deletes the node at the end (tail). */
static struct SLL_Node* scll_delete_end(struct SLL_Node *tail) {
    if (tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    printf("Deleted node with value %d (from tail).\n", tail->data);

    if (tail->next == tail) { // Only one node
        free(tail);
        return NULL; // List is now empty
    } else {
        // Traverse to the node *before* the tail
        struct SLL_Node *temp = tail->next; // Start at head
        while (temp->next != tail) {
            temp = temp->next;
        }
        // temp is now the node before tail
        temp->next = tail->next; // Point to head
        free(tail);
        return temp; // The node before the old tail is the new tail
    }
}

/** @brief (S-CLL) Deletes the node at a specific position (1-based index). */
static struct SLL_Node* scll_delete_at_pos(struct SLL_Node *tail) {
     int pos, k = 1;
    if (tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    printf("Enter position to delete (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return tail; }
    clear_input_buffer();

    struct SLL_Node *curr = tail->next, *prev = tail;

    // Handle delete head (position 1)
    if (pos == 1) {
        return scll_delete_front(tail); // Reuse the delete front logic
    }

    // Traverse to find the node at position 'pos'
    do {
        prev = curr;
        curr = curr->next;
        k++;
        if (curr == tail->next) break; // Reached start again
    } while (k < pos && curr != tail->next);


    // Case 1: Position is out of bounds
    if (k < pos) {
        printf("Position %d is out of bounds.\n", pos);
        return tail;
    }

    // Case 2: Unlink the node (curr is the node to delete)
    prev->next = curr->next;
    printf("Deleted node at position %d (value: %d).\n", pos, curr->data);

    // Handle deleting the tail node
    if (curr == tail) {
        tail = prev; // Update tail pointer
    }
    free(curr);
    return tail;
}

static void scll_display(struct SLL_Node *tail) {
    if (tail == NULL) {
        printf("Singly CLL is empty.\n");
        return;
    }
    
    struct SLL_Node *temp = tail->next; // Start at the head
    
    printf("\n HEAD\n");
    printf("  |\n");
    printf("  v\n");
    printf("  ");

    do {
        printf("%d", temp->data);
        if (temp == tail) {
            printf(" (TAIL)");
        }

        temp = temp->next; // Move to next node
        
        // Only print arrow if we are not at the end of the loop
        if (temp != tail->next) {
            printf(" -> ");
        }
        
    } while (temp != tail->next);
    
    printf("(to HEAD)\n");
}

/**
 * @brief (S-CLL) Inserts a new node at the front.
 */
static struct SLL_Node* scll_insert_front(struct SLL_Node *tail) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
    if(newNode == NULL) {
        printf("Memory allocation failed!\n");
        return tail;
    }
    newNode->data = data;

    if (tail == NULL) {
        tail = newNode;
        tail->next = tail; 
    } else {
        newNode->next = tail->next; 
        tail->next = newNode;      
    }
    
    printf("Inserted %d at the front.\n", data);
    return tail;
}

/**
 * @brief (S-CLL) Inserts a new node at the end.
 */
static struct SLL_Node* scll_insert_end(struct SLL_Node *tail) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
    if(newNode == NULL) {
        printf("Memory allocation failed!\n");
        return tail;
    }
    newNode->data = data;

    if (tail == NULL) {
        tail = newNode;
        tail->next = tail; 
    } else {
        newNode->next = tail->next; 
        tail->next = newNode;      
        tail = newNode;            
    }
    
    printf("Inserted %d at the end.\n", data);
    return tail; 
}

/**
 * @brief (S-CLL) Deletes a node by its data value.
 */
static struct SLL_Node* scll_delete_node(struct SLL_Node *tail) {
    int key;
    if (tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    
    printf("Enter data value to delete: ");
    if(scanf("%d", &key) != 1) { key = 0; }
    clear_input_buffer();

    struct SLL_Node *curr = tail->next, *prev = tail;

    if (curr == tail && curr->data == key) {
        free(curr);
        printf("Deleted node %d. List is now empty.\n", key);
        return NULL;
    }

    do {
        if (curr->data == key) {
            prev->next = curr->next;
            if (curr == tail) {
                tail = prev;
            }
            free(curr);
            printf("Deleted node %d.\n", key);
            return tail;
        }
        prev = curr;
        curr = curr->next;
    } while (curr != tail->next); 

    printf("Value %d not found in list.\n", key);
    return tail;
}

/**
 * @brief (S-CLL) Frees all memory used by the list.
 */
static struct SLL_Node* scll_free_list(struct SLL_Node *tail) {
    if (tail == NULL) {
        return NULL;
    }
    
    struct SLL_Node *curr = tail->next; 
    tail->next = NULL; 
    
    while (curr != NULL) {
        struct SLL_Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    
    printf("Singly Circular Linked List memory freed.\n");
    return NULL;
}

/**
 * @brief (S-CLL) The main sub-menu for Singly CLL.
 */
static void dsa_singly_cll_menu() {
    struct SLL_Node *tail = NULL;
    int choice;

    // (Replace the do-while loop inside dsa_singly_cll_menu)
    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Singly Circular Linked List (SLL) Ops   |\n");
        printf("==========================================\n");
        scll_display(tail);
        printf("------------------------------------------\n");
        printf(" 1. Insert at Front\n");
        printf(" 2. Insert at End\n");
        printf(" 3. Insert at Position\n");
        printf(" 4. Delete at Front\n");
        printf(" 5. Delete at End\n");
        printf(" 6. Delete at Position\n");
        printf(" 7. Delete by Value\n");
        printf(" 8. Back to CLL Type Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1: tail = scll_insert_front(tail); break;
            case 2: tail = scll_insert_end(tail); break;
            case 3: tail = scll_insert_at_pos(tail); break;
            case 4: tail = scll_delete_front(tail); break;
            case 5: tail = scll_delete_end(tail); break;
            case 6: tail = scll_delete_at_pos(tail); break;
            case 7: tail = scll_delete_node(tail); break;
            case 8: tail = scll_free_list(tail); return;
            default: printf("Invalid choice. Please try again.\n");
        }
        _press_enter_to_continue();
    } while (choice != 8);
}


// ====================================================================
// --- 2. Helper Functions for Doubly Circular Linked List (DCLL) ---
// ====================================================================
// (This is all new code)

/**
 * @brief (D-CLL) Creates a new node.
 */
static struct DLL_Node* dcll_create_node(int data) {
    struct DLL_Node *newNode = (struct DLL_Node*) malloc(sizeof(struct DLL_Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// (Add these inside dsa_unit1_lists.c, with the other D-CLL helpers)

/** @brief (D-CLL) Inserts a node at a specific position (1-based index). */
static void dcll_insert_at_pos(struct DLL_List *list) {
    int pos, data, k = 1;
    printf("Enter position (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return; }
    clear_input_buffer();

    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    // Handle empty list case separately
    if (list->head == NULL) {
        if (pos == 1) {
            dcll_insert_front(list); // Reuse insert front for empty list
        } else {
            printf("Position %d is out of bounds (List is empty).\n", pos);
        }
        return;
    }

    // Handle insertion at beginning
    if (pos == 1) {
        dcll_insert_front(list); // Reuse insert front
        return;
    }

    struct DLL_Node *newNode = dcll_create_node(data);
    if (!newNode) return;

    // Traverse to the node *before* the desired position
    struct DLL_Node *temp = list->head;
    while (temp != list->tail && k < pos - 1) {
        temp = temp->next;
        k++;
    }

    // Case 1: Position is out of bounds (beyond the end + 1)
    // If temp is tail AND we still haven't reached pos-1, it's out of bounds
    // OR if k is still less than pos-1 (means we stopped early but not at tail)
     if (k < pos - 1 || (temp == list->tail && k < pos - 1)) {
        printf("Position %d is out of bounds.\n", pos);
        free(newNode);
        return;
    }

    // Case 2: Insert after the tail (new tail)
    if (temp == list->tail && k == pos - 1) {
        newNode->next = list->head;
        newNode->prev = list->tail;
        list->head->prev = newNode;
        list->tail->next = newNode;
        list->tail = newNode;
        printf("Inserted %d at position %d (new tail).\n", data, pos);
    }
    // Case 3: Insert in the middle
    else {
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        printf("Inserted %d at position %d.\n", data, pos);
    }
}


/** @brief (D-CLL) Deletes the node at the beginning. */
static void dcll_delete_front(struct DLL_List *list) {
    if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct DLL_Node *temp = list->head;
    printf("Deleted node with value %d (from head).\n", temp->data);

    if (list->head == list->tail) { // Only one node
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = list->tail; // New head points back to tail
        list->tail->next = list->head; // Tail points forward to new head
    }
    free(temp);
}

/** @brief (D-CLL) Deletes the node at the end. */
static void dcll_delete_end(struct DLL_List *list) {
    if (list->tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct DLL_Node *temp = list->tail;
     printf("Deleted node with value %d (from tail).\n", temp->data);

    if (list->head == list->tail) { // Only one node
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = list->head; // New tail points forward to head
        list->head->prev = list->tail; // Head points back to new tail
    }
    free(temp);
}

/** @brief (D-CLL) Deletes the node at a specific position (1-based index). */
static void dcll_delete_at_pos(struct DLL_List *list) {
    int pos, k = 1;
    if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    printf("Enter position to delete (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return; }
    clear_input_buffer();

    // Handle delete front
    if (pos == 1) {
        dcll_delete_front(list);
        return;
    }

    // Traverse to find the node at position 'pos'
    struct DLL_Node *temp = list->head;
    do {
        temp = temp->next;
        k++;
        if (temp == list->head) break; // Reached start again
    } while (k < pos && temp != list->head);

    // Case 1: Position is out of bounds
    if (k < pos || temp == list->head) { // If we wrapped around without finding it
        printf("Position %d is out of bounds.\n", pos);
        return;
    }

    // Case 2: Unlink the node (temp is the node to delete)
    printf("Deleted node at position %d (value: %d).\n", pos, temp->data);
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    // Handle deleting the tail node
    if (temp == list->tail) {
        list->tail = temp->prev; // Update tail pointer
    }
    free(temp);
}

/**
 * @brief (D-CLL) Inserts a new node at the front (head).
 */
static void dcll_insert_front(struct DLL_List *list) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct DLL_Node *newNode = dcll_create_node(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        // List is empty
        list->head = newNode;
        list->tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        // List is not empty
        newNode->next = list->head;
        newNode->prev = list->tail;
        list->head->prev = newNode;
        list->tail->next = newNode;
        list->head = newNode;
    }
    printf("Inserted %d at the front.\n", data);
}

/**
 * @brief (D-CLL) Inserts a new node at the end (tail).
 */
static void dcll_insert_end(struct DLL_List *list) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct DLL_Node *newNode = dcll_create_node(data);
    if (newNode == NULL) return;

    if (list->tail == NULL) {
        // List is empty
        list->head = newNode;
        list->tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        // List is not empty
        newNode->next = list->head;
        newNode->prev = list->tail;
        list->head->prev = newNode;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    printf("Inserted %d at the end.\n", data);
}

/**
 * @brief (D-CLL) Deletes a node by its data value.
 */
static void dcll_delete_node(struct DLL_List *list) {
    int key;
    if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    
    printf("Enter data value to delete: ");
    if(scanf("%d", &key) != 1) { key = 0; }
    clear_input_buffer();

    struct DLL_Node *temp = list->head;

    // Search for the node
    do {
        if (temp->data == key) {
            break; // Node found
        }
        temp = temp->next;
    } while (temp != list->head);

    // Case 1: Node not found
    if (temp->data != key) {
        printf("Value %d not found in list.\n", key);
        return;
    }
    
    // Case 2: Node is found (temp is the node to delete)
    // Handle Case 2a: Deleting the *only* node
    if (temp->next == temp) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        // Case 2b: Deleting from a list with >1 node
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        
        // Handle Case 2c: Deleting the head node
        if (temp == list->head) {
            list->head = temp->next;
        }
        // Handle Case 2d: Deleting the tail node
        if (temp == list->tail) {
            list->tail = temp->prev;
        }
    }

    free(temp); // Free the memory
    printf("Deleted node with value %d.\n", key);
}

/**
 * @brief (D-CLL) Frees all memory used by the list.
 */
static void dcll_free_list(struct DLL_List *list) {
    if (list->head == NULL) return;
    
    struct DLL_Node *curr = list->head;
    list->tail->next = NULL; // Break the circular link
    
    while (curr != NULL) {
        struct DLL_Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    
    list->head = NULL;
    list->tail = NULL;
    printf("Doubly Circular Linked List memory freed.\n");
}

/**
 * @brief (D-CLL) The main sub-menu for Doubly CLL.
 */
static void dsa_doubly_cll_menu() {
    struct DLL_List list;
    list.head = NULL;
    list.tail = NULL;
    int choice;

    // (Replace the do-while loop inside dsa_doubly_cll_menu)
    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Doubly Circular Linked List (DLL) Ops   |\n");
        printf("==========================================\n");
        dcll_display_forward(&list); // Display happens automatically
        printf("------------------------------------------\n");
        printf(" 1. Insert at Front\n");
        printf(" 2. Insert at End\n");
        printf(" 3. Insert at Position\n");
        printf(" 4. Delete at Front\n");
        printf(" 5. Delete at End\n");
        printf(" 6. Delete at Position\n");
        printf(" 7. Delete by Value\n");
        // Removed display options
        printf(" 8. Back to CLL Type Menu\n"); // Renumbered
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1: dcll_insert_front(&list); break;
            case 2: dcll_insert_end(&list); break;
            case 3: dcll_insert_at_pos(&list); break;
            case 4: dcll_delete_front(&list); break;
            case 5: dcll_delete_end(&list); break;
            case 6: dcll_delete_at_pos(&list); break;
            case 7: dcll_delete_node(&list); break;
            // Removed display cases
            case 8: dcll_free_list(&list); return; // Renumbered
            default: printf("Invalid choice. Please try again.\n");
        }
        _press_enter_to_continue();
    } while (choice != 8); // Renumbered
}

void dsa_cll_operations() {
    int choice;
    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Circular Linked List (CLL) Ops          |\n");
        printf("==========================================\n");
        printf("Select the type of Circular List:\n");
        printf("------------------------------------------\n");
        printf(" 1. Singly Circular Linked List\n");
        printf(" 2. Doubly Circular Linked List\n");
        printf(" 3. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                dsa_singly_cll_menu();
                break;
            case 2:
                dsa_doubly_cll_menu();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 3);
}

// (This code goes into dsa_unit1_lists.c)

// --- Helper Functions for Polynomial Linked List ---

/**
 * @brief (POLY) Creates a new polynomial term node.
 */
static struct Poly_Node* poly_create_node(int coeff, int exp) {
    struct Poly_Node *newNode = (struct Poly_Node*) malloc(sizeof(struct Poly_Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->coefficient = coeff;
    newNode->exponent = exp;
    newNode->next = NULL;
    return newNode;
}

/**
 * @brief (POLY) Frees all memory used by the polynomial list.
 */
static struct Poly_Node* poly_free_list(struct Poly_Node *head) {
    struct Poly_Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("Polynomial memory freed.\n");
    return NULL;
}

/**
 * @brief (POLY) Displays the polynomial in a pretty format.
 */
static void poly_display(struct Poly_Node *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    
    struct Poly_Node *temp = head;
    
    int isFirstTerm = 1;
    while (temp != NULL) {
        // 1. Handle the sign ( + or - )
        if (!isFirstTerm) {
            printf(temp->coefficient < 0 ? " - " : " + ");
        } else if (temp->coefficient < 0) {
            printf("-"); // Handle negative first term
        }
        
        int coeff = abs(temp->coefficient);

        // 2. Print coefficient (if not 1 or if exponent is 0)
        if (coeff != 1 || temp->exponent == 0) {
            printf("%d", coeff);
        }

        // 3. Print 'x' and exponent
        if (temp->exponent > 0) {
            printf("x");
            if (temp->exponent > 1) {
                printf("^%d", temp->exponent);
            }
        }
        
        isFirstTerm = 0;
        temp = temp->next;
    }
    printf("\n");
}

/**
 * @brief (POLY) Inserts a new term, sorted by exponent, and combines like terms.
 */
static struct Poly_Node* poly_insert_term(struct Poly_Node *head) {
    int coeff, exp;
    printf("Enter coefficient: ");
    if(scanf("%d", &coeff) != 1) { coeff = 0; }
    clear_input_buffer();

    printf("Enter exponent: ");
    if(scanf("%d", &exp) != 1) { exp = 0; }
    clear_input_buffer();

    if (coeff == 0) {
        printf("Coefficient is zero, term not added.\n");
        return head;
    }

    struct Poly_Node *newNode = poly_create_node(coeff, exp);
    if (newNode == NULL) return head;

    // Case 1: List is empty or new term has highest exponent
    if (head == NULL || exp > head->exponent) {
        newNode->next = head;
        printf("Inserted term %dx^%d\n", coeff, exp);
        return newNode; // New node is the new head
    }

    // Case 2: Traverse to find correct position
    struct Poly_Node *curr = head;
    while (curr->next != NULL && curr->next->exponent > exp) {
        curr = curr->next;
    }

    // Case 3: Found a term with the *same* exponent
    if (curr->exponent == exp) {
        curr->coefficient += coeff;
        printf("Exponent %d exists. Coeffs combined: %dx^%d\n", exp, curr->coefficient, exp);
        free(newNode); // Don't need the new node
    }
    // Check the next node as well (if loop terminated early)
    else if (curr->next != NULL && curr->next->exponent == exp) {
        curr->next->coefficient += coeff;
        printf("Exponent %d exists. Coeffs combined: %dx^%d\n", exp, curr->next->coefficient, exp);
        free(newNode); // Don't need the new node
    }
    // Case 4: Insert new term in the middle or at the end
    else {
        newNode->next = curr->next;
        curr->next = newNode;
        printf("Inserted term %dx^%d\n", coeff, exp);
    }

    // Cleanup: Check if a coefficient became zero after addition
    // (This is advanced, but good practice - e.g., 5x^2 + (-5x^2) = 0)
    // We'll skip this for brevity, but a full implementation would check for
    // nodes with coeff == 0 and delete them.
    
    return head;
}


// (This code goes into dsa_unit1_lists.c)

/**
 * @brief (POLY) [HELPER] A sub-menu to create one polynomial.
 * This is the refactored logic from the old dsa_poly_create.
 * It's now a helper so dsa_poly_add_sub can use it.
 */
static struct Poly_Node* poly_create_helper(const char* poly_name) {
    struct Poly_Node *head = NULL;
    int choice;

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Creating Polynomial: %s            |\n", poly_name);
        printf("==========================================\n");
        // Pass the head pointer to display
        printf("P(x) = ");
        poly_display(head ? head : NULL); // Pass NULL if head is NULL
        printf("------------------------------------------\n");
        printf(" 1. Add/Combine Term\n");
        printf(" 2. Done Creating This Polynomial\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                head = poly_insert_term(head);
                _press_enter_to_continue();
                break;
            case 2:
                printf("Polynomial %s created.\n", poly_name);
                return head; // Return the finished list
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 2);
    
    return head; // Should be reached by case 2
}

/**
 * @brief Topic 5: Polynomial Creation
 * This function now just calls the helper and cleans up.
 */
void dsa_poly_create() {
    // Call the helper to create a list
    struct Poly_Node *head = poly_create_helper("P(x)");
    
    // The menu is just for "creation," so we display it
    // one last time and then free it.
    _clear_screen();
    printf("==========================================\n");
    printf("| Polynomial Creation Complete            |\n");
    printf("==========================================\n");
    printf("You created the following polynomial:\n");
    printf("P(x) = ");
    poly_display(head);
    _press_enter_to_continue();

    head = poly_free_list(head); // Cleanup
}

/**
 * @brief Topic 6: Polynomial Add/Sub (Stub)
 */
// (This code goes into dsa_unit1_lists.c)

/**
 * @brief (POLY) [HELPER] The core logic for adding two polynomials.
 * @param p1 Head of first polynomial.
 * @param p2 Head of second polynomial.
 * @param isSubtraction 0 for addition, 1 for subtraction.
 * @return Head of a new result polynomial.
 */
static struct Poly_Node* poly_add(struct Poly_Node *p1, struct Poly_Node *p2, int isSubtraction) {
    struct Poly_Node *result_head = NULL;
    struct Poly_Node *result_tail = NULL;

    // We'll iterate as long as either list has terms
    while (p1 != NULL || p2 != NULL) {
        int coeff, exp;
        
        // Case 1: p1 is done, only p2 remains
        if (p1 == NULL) {
            coeff = isSubtraction ? -p2->coefficient : p2->coefficient;
            exp = p2->exponent;
            p2 = p2->next;
        }
        // Case 2: p2 is done, only p1 remains
        else if (p2 == NULL) {
            coeff = p1->coefficient;
            exp = p1->exponent;
            p1 = p1->next;
        }
        // Case 3: p1's exponent is higher
        else if (p1->exponent > p2->exponent) {
            coeff = p1->coefficient;
            exp = p1->exponent;
            p1 = p1->next;
        }
        // Case 4: p2's exponent is higher
        else if (p2->exponent > p1->exponent) {
            coeff = isSubtraction ? -p2->coefficient : p2->coefficient;
            exp = p2->exponent;
            p2 = p2->next;
        }
        // Case 5: Exponents are equal
        else {
            coeff = p1->coefficient + (isSubtraction ? -p2->coefficient : p2->coefficient);
            exp = p1->exponent;
            p1 = p1->next;
            p2 = p2->next;
            
            // If coeffs cancel out, skip adding this term
            if (coeff == 0) continue;
        }

        // Add the new term to our result list (efficient O(1) append)
        struct Poly_Node *newNode = poly_create_node(coeff, exp);
        if (result_head == NULL) {
            result_head = newNode;
            result_tail = newNode;
        } else {
            result_tail->next = newNode;
            result_tail = newNode;
        }
    }
    
    return result_head;
}

/**
 * @brief Topic 6: Polynomial Add/Sub Sub-Menu
 * This is the main function called by the dispatcher.
 */
void dsa_poly_add_sub() {
    struct Poly_Node *p1 = NULL;
    struct Poly_Node *p2 = NULL;
    struct Poly_Node *result = NULL;
    int choice;

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Polynomial Addition & Subtraction       |\n");
        printf("==========================================\n");
        printf("P1(x) = "); poly_display(p1);
        printf("P2(x) = "); poly_display(p2);
        printf("\nResult:\n");
        printf("R(x) = "); poly_display(result);
        printf("------------------------------------------\n");
        printf(" 1. Create/Edit Polynomial P1\n");
        printf(" 2. Create/Edit Polynomial P2\n");
        printf(" 3. Perform Addition (R = P1 + P2)\n");
        printf(" 4. Perform Subtraction (R = P1 - P2)\n");
        printf(" 5. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                if (p1) p1 = poly_free_list(p1); // Free old P1
                p1 = poly_create_helper("P1(x)");
                break;
            case 2:
                if (p2) p2 = poly_free_list(p2); // Free old P2
                p2 = poly_create_helper("P2(x)");
                break;
            case 3:
                if (result) result = poly_free_list(result); // Free old result
                result = poly_add(p1, p2, 0); // 0 = isSubtraction = false
                printf("Addition complete.\n");
                _press_enter_to_continue();
                break;
            case 4:
                if (result) result = poly_free_list(result); // Free old result
                result = poly_add(p1, p2, 1); // 1 = isSubtraction = true
                printf("Subtraction complete.\n");
                _press_enter_to_continue();
                break;
            case 5:
                // Cleanup all lists before leaving
                if (p1) p1 = poly_free_list(p1);
                if (p2) p2 = poly_free_list(p2);
                if (result) result = poly_free_list(result);
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 5);
}