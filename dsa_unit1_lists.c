#include "dsa_unit1_lists.h"
#include "dsa_common.h"

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

void sll_display(struct SLL_Node *head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct SLL_Node *temp = head;

    printf("\n HEAD\n");
    printf("  |\n");
    printf("  v\n");
    printf("  ");

    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

static void dll_display_forward(struct DLL_List *list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct DLL_Node *temp = list->head;

    printf("\n HEAD\n");
    printf("  |\n");
    printf("  v\n");
    printf("  ");

    while (temp != NULL) {
        printf("%d", temp->data);

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

        temp = temp->next;

        if (temp != list->head) {
            printf(" <-> ");
        }
    } while (temp != list->head);

    printf("(to HEAD)\n");
}

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

    if (pos == 1) {
        newNode->next = head;
        printf("Inserted %d at position %d (new head).\n", data, pos);
        return newNode;
    }

    struct SLL_Node *temp = head;
    while (temp != NULL && k < pos - 1) {
        temp = temp->next;
        k++;
    }

    if (temp == NULL) {
        printf("Position %d is out of bounds (List length: %d).\n", pos, k);
        free(newNode);
        return head;
    }

    newNode->next = temp->next;
    temp->next = newNode;
    printf("Inserted %d at position %d.\n", data, pos);
    return head;
}

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

static struct SLL_Node* sll_delete_end(struct SLL_Node *head) {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    if (head->next == NULL) {
        printf("Deleted node with value %d (last node).\n", head->data);
        free(head);
        return NULL;
    }
    struct SLL_Node *temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }
    struct SLL_Node *lastNode = temp->next;
    temp->next = NULL;
    printf("Deleted node with value %d (from end).\n", lastNode->data);
    free(lastNode);
    return head;
}

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

    if (pos == 1) {
        head = temp->next;
        printf("Deleted node at position %d (value: %d).\n", pos, temp->data);
        free(temp);
        return head;
    }

    while (temp != NULL && k < pos) {
        prev = temp;
        temp = temp->next;
        k++;
    }

    if (temp == NULL) {
        printf("Position %d is out of bounds (List length: %d).\n", pos, k-1);
        return head;
    }

    prev->next = temp->next;
    printf("Deleted node at position %d (value: %d).\n", pos, temp->data);
    free(temp);
    return head;
}

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
    return newNode;
}

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

    if (head == NULL) {
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

    if (temp != NULL && temp->data == key) {
        head = temp->next;
        free(temp);
        printf("Deleted node with value %d (from head).\n", key);
        return head;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value %d not found in list.\n", key);
        return head;
    }

    prev->next = temp->next;
    free(temp);
    printf("Deleted node with value %d.\n", key);
    return head;
}

struct SLL_Node* sll_free_list(struct SLL_Node *head) {
    struct SLL_Node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    printf("List memory freed.\n");
    return NULL;
}

void dsa_array_max_min() {
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

void dsa_sll_operations() {
    struct SLL_Node *head = NULL;
    int choice;

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Singly Linked List Operations           |\n");
        printf("==========================================\n");
        sll_display(head);
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
            case 1: head = sll_insert_front(head); break;
            case 2: head = sll_insert_end(head); break;
            case 3: head = sll_insert_at_pos(head); break;
            case 4: head = sll_delete_front(head); break;
            case 5: head = sll_delete_end(head); break;
            case 6: head = sll_delete_at_pos(head); break;
            case 7: head = sll_delete_node(head); break;
            case 8: head = sll_free_list(head); return;
            default: printf("Invalid choice. Please try again.\n");
        }
        if (choice != 8) {
            _press_enter_to_continue();
        }
    } while (choice != 8);
}

static void dll_insert_at_pos(struct DLL_List *list) {
    int pos, data, k = 1;
    printf("Enter position (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return; }
    clear_input_buffer();

    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    if (pos == 1) {
        dll_insert_front(list);
        return;
    }

    struct DLL_Node *newNode = dll_create_node(data);
    if (!newNode) return;

    struct DLL_Node *temp = list->head;
    while (temp != NULL && k < pos - 1) {
        temp = temp->next;
        k++;
    }

    if (temp == NULL) {
        printf("Position %d is out of bounds (List length: %d).\n", pos, k);
        free(newNode);
        return;
    }

    if (temp->next == NULL) {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        printf("Inserted %d at position %d (new tail).\n", data, pos);
    }
    else {
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        printf("Inserted %d at position %d.\n", data, pos);
    }
}

static void dll_delete_front(struct DLL_List *list) {
    if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct DLL_Node *temp = list->head;
    list->head = list->head->next;

    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        list->tail = NULL;
    }
    printf("Deleted node with value %d (from head).\n", temp->data);
    free(temp);
}

static void dll_delete_end(struct DLL_List *list) {
    if (list->tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct DLL_Node *temp = list->tail;
    list->tail = list->tail->prev;

    if (list->tail != NULL) {
        list->tail->next = NULL;
    } else {
        list->head = NULL;
    }
    printf("Deleted node with value %d (from tail).\n", temp->data);
    free(temp);
}

static void dll_delete_at_pos(struct DLL_List *list) {
    int pos, k = 1;
     if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    printf("Enter position to delete (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return; }
    clear_input_buffer();

    if (pos == 1) {
        dll_delete_front(list);
        return;
    }

    struct DLL_Node *temp = list->head;
    while (temp != NULL && k < pos) {
        temp = temp->next;
        k++;
    }

    if (temp == NULL) {
        printf("Position %d is out of bounds (List length: %d).\n", pos, k-1);
        return;
    }

    temp->prev->next = temp->next;

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        list->tail = temp->prev;
    }

    printf("Deleted node at position %d (value: %d).\n", pos, temp->data);
    free(temp);
}

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

static void dll_insert_front(struct DLL_List *list) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct DLL_Node *newNode = dll_create_node(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head->prev = newNode;
        list->head = newNode;
    }
    printf("Inserted %d at the front.\n", data);
}

static void dll_insert_end(struct DLL_List *list) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct DLL_Node *newNode = dll_create_node(data);
    if (newNode == NULL) return;

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    printf("Inserted %d at the end.\n", data);
}

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

    while (temp != NULL && temp->data != key) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Value %d not found in list.\n", key);
        return;
    }

    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        list->head = temp->next;
    }

    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    } else {
        list->tail = temp->prev;
    }

    free(temp);
    printf("Deleted node with value %d.\n", key);
}

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

void dsa_dll_operations() {
    struct DLL_List list;
    list.head = NULL;
    list.tail = NULL;
    
    int choice;

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Doubly Linked List Operations           |\n");
        printf("==========================================\n");
        dll_display_forward(&list);
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
            case 8: dll_free_list(&list); return;
            default: printf("Invalid choice. Please try again.\n");
        }
        _press_enter_to_continue();
    } while (choice != 8);
}

static struct SLL_Node* scll_insert_at_pos(struct SLL_Node *tail) {
    int pos, data, k = 1;
    printf("Enter position (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return tail; }
    clear_input_buffer();

    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    if (tail == NULL) {
        if (pos == 1) {
            struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
            if (!newNode) { printf("Memory allocation failed!\n"); return NULL; }
            newNode->data = data;
            newNode->next = newNode;
            printf("Inserted %d at position 1 (list was empty).\n", data);
            return newNode;
        } else {
            printf("Position %d is out of bounds (List is empty).\n", pos);
            return NULL;
        }
    }

    if (pos == 1) {
        struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
        if (!newNode) { printf("Memory allocation failed!\n"); return tail; }
        newNode->data = data;
        newNode->next = tail->next;
        tail->next = newNode;
        printf("Inserted %d at position 1 (new head).\n", data);
        return tail;
    }

    struct SLL_Node *temp = tail->next;
    while (temp != tail && k < pos - 1) {
        temp = temp->next;
        k++;
    }

    if (k < pos - 1 || (temp == tail && k < pos - 1) ) {
         printf("Position %d is out of bounds.\n", pos);
         return tail;
    }

    struct SLL_Node *newNode = (struct SLL_Node*) malloc(sizeof(struct SLL_Node));
    if (!newNode) { printf("Memory allocation failed!\n"); return tail; }
    newNode->data = data;
    newNode->next = temp->next;
    temp->next = newNode;

    if (temp == tail) {
        tail = newNode;
        printf("Inserted %d at position %d (new tail).\n", data, pos);
    } else {
        printf("Inserted %d at position %d.\n", data, pos);
    }

    return tail;
}

static struct SLL_Node* scll_delete_front(struct SLL_Node *tail) {
    if (tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    struct SLL_Node *head = tail->next;
    printf("Deleted node with value %d (from head).\n", head->data);

    if (head == tail) {
        free(head);
        return NULL;
    } else {
        tail->next = head->next;
        free(head);
        return tail;
    }
}

static struct SLL_Node* scll_delete_end(struct SLL_Node *tail) {
    if (tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return NULL;
    }
    printf("Deleted node with value %d (from tail).\n", tail->data);

    if (tail->next == tail) {
        free(tail);
        return NULL;
    } else {
        struct SLL_Node *temp = tail->next;
        while (temp->next != tail) {
            temp = temp->next;
        }
        temp->next = tail->next;
        free(tail);
        return temp;
    }
}

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

    if (pos == 1) {
        return scll_delete_front(tail);
    }

    do {
        prev = curr;
        curr = curr->next;
        k++;
        if (curr == tail->next) break;
    } while (k < pos && curr != tail->next);

    if (k < pos) {
        printf("Position %d is out of bounds.\n", pos);
        return tail;
    }

    prev->next = curr->next;
    printf("Deleted node at position %d (value: %d).\n", pos, curr->data);

    if (curr == tail) {
        tail = prev;
    }
    free(curr);
    return tail;
}

static void scll_display(struct SLL_Node *tail) {
    if (tail == NULL) {
        printf("Singly CLL is empty.\n");
        return;
    }
    
    struct SLL_Node *temp = tail->next;
    
    printf("\n HEAD\n");
    printf("  |\n");
    printf("  v\n");
    printf("  ");

    do {
        printf("%d", temp->data);
        if (temp == tail) {
            printf(" (TAIL)");
        }

        temp = temp->next;
        
        if (temp != tail->next) {
            printf(" -> ");
        }
        
    } while (temp != tail->next);
    
    printf("(to HEAD)\n");
}

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

static void dsa_singly_cll_menu() {
    struct SLL_Node *tail = NULL;
    int choice;

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

static void dcll_insert_at_pos(struct DLL_List *list) {
    int pos, data, k = 1;
    printf("Enter position (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return; }
    clear_input_buffer();

    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    if (list->head == NULL) {
        if (pos == 1) {
            dcll_insert_front(list);
        } else {
            printf("Position %d is out of bounds (List is empty).\n", pos);
        }
        return;
    }

    if (pos == 1) {
        dcll_insert_front(list);
        return;
    }

    struct DLL_Node *newNode = dcll_create_node(data);
    if (!newNode) return;

    struct DLL_Node *temp = list->head;
    while (temp != list->tail && k < pos - 1) {
        temp = temp->next;
        k++;
    }

     if (k < pos - 1 || (temp == list->tail && k < pos - 1)) {
        printf("Position %d is out of bounds.\n", pos);
        free(newNode);
        return;
    }

    if (temp == list->tail && k == pos - 1) {
        newNode->next = list->head;
        newNode->prev = list->tail;
        list->head->prev = newNode;
        list->tail->next = newNode;
        list->tail = newNode;
        printf("Inserted %d at position %d (new tail).\n", data, pos);
    }
    else {
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        printf("Inserted %d at position %d.\n", data, pos);
    }
}

static void dcll_delete_front(struct DLL_List *list) {
    if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct DLL_Node *temp = list->head;
    printf("Deleted node with value %d (from head).\n", temp->data);

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = list->tail;
        list->tail->next = list->head;
    }
    free(temp);
}

static void dcll_delete_end(struct DLL_List *list) {
    if (list->tail == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    struct DLL_Node *temp = list->tail;
     printf("Deleted node with value %d (from tail).\n", temp->data);

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = list->head;
        list->head->prev = list->tail;
    }
    free(temp);
}

static void dcll_delete_at_pos(struct DLL_List *list) {
    int pos, k = 1;
    if (list->head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }
    printf("Enter position to delete (1-based): ");
    if(scanf("%d", &pos) != 1 || pos < 1) { printf("Invalid position.\n"); clear_input_buffer(); return; }
    clear_input_buffer();

    if (pos == 1) {
        dcll_delete_front(list);
        return;
    }

    struct DLL_Node *temp = list->head;
    do {
        temp = temp->next;
        k++;
        if (temp == list->head) break;
    } while (k < pos && temp != list->head);

    if (k < pos || temp == list->head) {
        printf("Position %d is out of bounds.\n", pos);
        return;
    }

    printf("Deleted node at position %d (value: %d).\n", pos, temp->data);
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;

    if (temp == list->tail) {
        list->tail = temp->prev;
    }
    free(temp);
}

static void dcll_insert_front(struct DLL_List *list) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct DLL_Node *newNode = dcll_create_node(data);
    if (newNode == NULL) return;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        newNode->next = list->head;
        newNode->prev = list->tail;
        list->head->prev = newNode;
        list->tail->next = newNode;
        list->head = newNode;
    }
    printf("Inserted %d at the front.\n", data);
}

static void dcll_insert_end(struct DLL_List *list) {
    int data;
    printf("Enter data for new node: ");
    if(scanf("%d", &data) != 1) { data = 0; }
    clear_input_buffer();

    struct DLL_Node *newNode = dcll_create_node(data);
    if (newNode == NULL) return;

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        newNode->next = list->head;
        newNode->prev = list->tail;
        list->head->prev = newNode;
        list->tail->next = newNode;
        list->tail = newNode;
    }
    printf("Inserted %d at the end.\n", data);
}

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

    do {
        if (temp->data == key) {
            break;
        }
        temp = temp->next;
    } while (temp != list->head);

    if (temp->data != key) {
        printf("Value %d not found in list.\n", key);
        return;
    }
    
    if (temp->next == temp) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        
        if (temp == list->head) {
            list->head = temp->next;
        }
        if (temp == list->tail) {
            list->tail = temp->prev;
        }
    }

    free(temp);
    printf("Deleted node with value %d.\n", key);
}

static void dcll_free_list(struct DLL_List *list) {
    if (list->head == NULL) return;
    
    struct DLL_Node *curr = list->head;
    list->tail->next = NULL;
    
    while (curr != NULL) {
        struct DLL_Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    
    list->head = NULL;
    list->tail = NULL;
    printf("Doubly Circular Linked List memory freed.\n");
}

static void dsa_doubly_cll_menu() {
    struct DLL_List list;
    list.head = NULL;
    list.tail = NULL;
    int choice;

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Doubly Circular Linked List (DLL) Ops   |\n");
        printf("==========================================\n");
        dcll_display_forward(&list);
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
            case 1: dcll_insert_front(&list); break;
            case 2: dcll_insert_end(&list); break;
            case 3: dcll_insert_at_pos(&list); break;
            case 4: dcll_delete_front(&list); break;
            case 5: dcll_delete_end(&list); break;
            case 6: dcll_delete_at_pos(&list); break;
            case 7: dcll_delete_node(&list); break;
            case 8: dcll_free_list(&list); return;
            default: printf("Invalid choice. Please try again.\n");
        }
        _press_enter_to_continue();
    } while (choice != 8);
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

static void poly_display(struct Poly_Node *head) {
    if (head == NULL) {
        printf("0\n");
        return;
    }
    
    struct Poly_Node *temp = head;
    
    int isFirstTerm = 1;
    while (temp != NULL) {
        if (!isFirstTerm) {
            printf(temp->coefficient < 0 ? " - " : " + ");
        } else if (temp->coefficient < 0) {
            printf("-");
        }
        
        int coeff = abs(temp->coefficient);

        if (coeff != 1 || temp->exponent == 0) {
            printf("%d", coeff);
        }

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

    if (head == NULL || exp > head->exponent) {
        newNode->next = head;
        printf("Inserted term %dx^%d\n", coeff, exp);
        return newNode;
    }

    struct Poly_Node *curr = head;
    while (curr->next != NULL && curr->next->exponent > exp) {
        curr = curr->next;
    }

    if (curr->exponent == exp) {
        curr->coefficient += coeff;
        printf("Exponent %d exists. Coeffs combined: %dx^%d\n", exp, curr->coefficient, exp);
        free(newNode);
    }
    else if (curr->next != NULL && curr->next->exponent == exp) {
        curr->next->coefficient += coeff;
        printf("Exponent %d exists. Coeffs combined: %dx^%d\n", exp, curr->next->coefficient, exp);
        free(newNode);
    }
    else {
        newNode->next = curr->next;
        curr->next = newNode;
        printf("Inserted term %dx^%d\n", coeff, exp);
    }
    
    return head;
}

static struct Poly_Node* poly_create_helper(const char* poly_name) {
    struct Poly_Node *head = NULL;
    int choice;

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Creating Polynomial: %s            |\n", poly_name);
        printf("==========================================\n");
        printf("P(x) = ");
        poly_display(head ? head : NULL);
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
                return head;
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 2);
    
    return head;
}

void dsa_poly_create() {
    struct Poly_Node *head = poly_create_helper("P(x)");
    
    _clear_screen();
    printf("==========================================\n");
    printf("| Polynomial Creation Complete            |\n");
    printf("==========================================\n");
    printf("You created the following polynomial:\n");
    printf("P(x) = ");
    poly_display(head);
    _press_enter_to_continue();

    head = poly_free_list(head);
}

static struct Poly_Node* poly_add(struct Poly_Node *p1, struct Poly_Node *p2, int isSubtraction) {
    struct Poly_Node *result_head = NULL;
    struct Poly_Node *result_tail = NULL;

    while (p1 != NULL || p2 != NULL) {
        int coeff, exp;
        
        if (p1 == NULL) {
            coeff = isSubtraction ? -p2->coefficient : p2->coefficient;
            exp = p2->exponent;
            p2 = p2->next;
        }
        else if (p2 == NULL) {
            coeff = p1->coefficient;
            exp = p1->exponent;
            p1 = p1->next;
        }
        else if (p1->exponent > p2->exponent) {
            coeff = p1->coefficient;
            exp = p1->exponent;
            p1 = p1->next;
        }
        else if (p2->exponent > p1->exponent) {
            coeff = isSubtraction ? -p2->coefficient : p2->coefficient;
            exp = p2->exponent;
            p2 = p2->next;
        }
        else {
            coeff = p1->coefficient + (isSubtraction ? -p2->coefficient : p2->coefficient);
            exp = p1->exponent;
            p1 = p1->next;
            p2 = p2->next;
            
            if (coeff == 0) continue;
        }

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
                if (p1) p1 = poly_free_list(p1);
                p1 = poly_create_helper("P1(x)");
                break;
            case 2:
                if (p2) p2 = poly_free_list(p2);
                p2 = poly_create_helper("P2(x)");
                break;
            case 3:
                if (result) result = poly_free_list(result);
                result = poly_add(p1, p2, 0);
                printf("Addition complete.\n");
                _press_enter_to_continue();
                break;
            case 4:
                if (result) result = poly_free_list(result);
                result = poly_add(p1, p2, 1);
                printf("Subtraction complete.\n");
                _press_enter_to_continue();
                break;
            case 5:
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