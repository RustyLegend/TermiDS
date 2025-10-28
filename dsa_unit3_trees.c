#include "dsa_unit3_trees.h"
#include "dsa_common.h"
#include <math.h>

// --- BST Helper Functions ---

// Create a new BST node
struct BST_Node* bst_create_node(int data) {
    struct BST_Node *newNode = (struct BST_Node*) malloc(sizeof(struct BST_Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a node into the BST
struct BST_Node* bst_insert(struct BST_Node *root, int data) {
    // Base case: If the tree is empty, return a new node
    if (root == NULL) {
        return bst_create_node(data);
    }
    
    // Recursive step
    if (data < root->data) {
        root->left = bst_insert(root->left, data);
    } else if (data > root->data) {
        root->right = bst_insert(root->right, data);
    } else {
        printf("Value %d already exists in the BST.\n", data);
    }
    return root;
}

// Inorder Traversal (L-N-R)
void bst_inorder_traversal(struct BST_Node *root) {
    if (root != NULL) {
        bst_inorder_traversal(root->left);
        printf("%d ", root->data);
        bst_inorder_traversal(root->right);
    }
}

// Preorder Traversal (N-L-R)
void bst_preorder_traversal(struct BST_Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        bst_preorder_traversal(root->left);
        bst_preorder_traversal(root->right);
    }
}

// Postorder Traversal (L-R-N)
void bst_postorder_traversal(struct BST_Node *root) {
    if (root != NULL) {
        bst_postorder_traversal(root->left);
        bst_postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

// Free the entire tree
struct BST_Node* bst_free_tree(struct BST_Node *root) {
    if (root == NULL) return NULL;
    
    bst_free_tree(root->left);
    bst_free_tree(root->right);
    free(root);
    return NULL;
}


// --- Main Topic Functions (Called by Dispatcher) ---

// (This code goes into dsa_unit3_trees.c)
// ... (The BST helper functions like bst_create_node are already here) ...

// ====================================================================
// --- 1. Static Helper Functions for General Binary Tree (BT) ---
// ====================================================================
// We reuse the 'struct BST_Node' but name the functions 'bt_'
// to keep them logically separate from 'bst_'.

#define BT_PRINT_SPACE 10

/**
 * @brief (BT) Creates a new tree node.
 */
static struct BST_Node* bt_create_node(int data) {
    struct BST_Node *newNode = (struct BST_Node*) malloc(sizeof(struct BST_Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/**
 * @brief (BT) Frees all memory used by the tree.
 */
static struct BST_Node* bt_free_tree(struct BST_Node *root) {
    if (root == NULL) return NULL;
    bt_free_tree(root->left);
    bt_free_tree(root->right);
    free(root);
    return NULL;
}

/**
 * @brief (BT) Traversal helper: Inorder (LNR)
 */
static void bt_inorder_traversal(struct BST_Node *root) {
    if (root != NULL) {
        bt_inorder_traversal(root->left);
        printf("%d ", root->data);
        bt_inorder_traversal(root->right);
    }
}

/**
 * @brief (BT) Traversal helper: Preorder (NLR)
 */
static void bt_preorder_traversal(struct BST_Node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        bt_preorder_traversal(root->left);
        bt_preorder_traversal(root->right);
    }
}

/**
 * @brief (BT) Traversal helper: Postorder (LRN)
 */
static void bt_postorder_traversal(struct BST_Node *root) {
    if (root != NULL) {
        bt_postorder_traversal(root->left);
        bt_postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

/**
 * @brief (BT) Finds a node with a specific value (preorder search).
 */
static struct BST_Node* bt_find_node(struct BST_Node* root, int data) {
    if (root == NULL) {
        return NULL;
    }
    if (root->data == data) {
        return root;
    }
    // Search left subtree
    struct BST_Node* foundNode = bt_find_node(root->left, data);
    if (foundNode != NULL) {
        return foundNode;
    }
    // Search right subtree
    return bt_find_node(root->right, data);
}


// (This code goes into dsa_unit3_trees.c)

/**
 * @brief (BT) [NEW] Helper to get the height of the tree.
 */


/**
 * @brief (BT) The UI logic for adding a new child node.
 */
static void bt_insert_child(struct BST_Node* root) {
    int parentData, childData;
    char choice;

    if (root == NULL) {
        printf("Tree is empty. You must create a Root node first.\n");
        return;
    }

    printf("Enter parent node's value (where you want to insert): ");
    if(scanf("%d", &parentData) != 1) { parentData = 0; }
    clear_input_buffer();

    struct BST_Node* parent = bt_find_node(root, parentData);
    if (parent == NULL) {
        printf("Error: Parent node with value %d was not found!\n", parentData);
        return;
    }
    
    printf("Enter the new child node's value: ");
    if(scanf("%d", &childData) != 1) { childData = 0; }
    clear_input_buffer();

    printf("Insert as (L)eft or (R)ight child of %d?: ", parentData);
    if(scanf(" %c", &choice) != 1) { choice = ' '; }
    clear_input_buffer();

    if (choice == 'L' || choice == 'l') {
        if (parent->left != NULL) {
            printf("Error: Left child of %d already exists (value: %d)!\n", parentData, parent->left->data);
        } else {
            parent->left = bt_create_node(childData);
            printf("Inserted %d as LEFT child of %d.\n", childData, parentData);
        }
    } else if (choice == 'R' || choice == 'r') {
        if (parent->right != NULL) {
            printf("Error: Right child of %d already exists (value: %d)!\n", parentData, parent->right->data);
        } else {
            parent->right = bt_create_node(childData);
            printf("Inserted %d as RIGHT child of %d.\n", childData, parentData);
        }
    } else {
        printf("Invalid choice. Operation cancelled.\n");
    }
}


// ====================================================================
// --- 2. Main Binary Tree Topic Function ---
// ====================================================================

/**
 * @brief Topic 1: General Binary Tree
 * This is the main function called by the dispatcher.
 */
void dsa_binary_tree() {
    struct BST_Node *root = NULL;
    int choice, data;

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| General Binary Tree (BT) Operations     |\n");
        printf("==========================================\n");
        printf("Build your tree manually. Current root: %s\n", root ? "SET" : "NULL");
        printf("------------------------------------------\n");
        printf(" 1. Create / Overwrite Root Node\n");
        printf(" 2. Add Child Node\n");
        printf(" 3. Display Tree (2D Visualization)\n");
        printf(" 4. Display Traversals (In/Pre/Post-order)\n");
        printf(" 5. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                if (root != NULL) {
                    printf("This will erase the current tree. Are you sure? (y/n): ");
                    char confirm;
                    if(scanf(" %c", &confirm) != 1) { confirm = 'n'; }
                    clear_input_buffer();
                    if (confirm == 'y' || confirm == 'Y') {
                        root = bt_free_tree(root);
                    } else {
                        printf("Operation cancelled.\n");
                        _press_enter_to_continue();
                        break;
                    }
                }
                printf("Enter value for new root node: ");
                if (scanf("%d", &data) != 1) { data = 0; }
                clear_input_buffer();
                root = bt_create_node(data);
                printf("Root node with value %d created.\n", data);
                _press_enter_to_continue();
                break;
            
            case 2:
                bt_insert_child(root);
                _press_enter_to_continue();
                break;
                
            case 3:
                g_tree_print_ascii(root);
                _press_enter_to_continue();
                break;

            case 4:
                _clear_screen();
                printf("--- Traversals ---\n");
                printf("Inorder (LNR):   ");
                if (root) bt_inorder_traversal(root); else printf("Empty");
                printf("\n");
                printf("Preorder (NLR):  ");
                if (root) bt_preorder_traversal(root); else printf("Empty");
                printf("\n");
                printf("Postorder (LRN): ");
                if (root) bt_postorder_traversal(root); else printf("Empty");
                printf("\n");
                _press_enter_to_continue();
                break;
                
            case 5:
                root = g_tree_free(root); // Cleanup
                printf("Binary Tree memory freed.\n");
                return;
                
            default:
                printf("Invalid choice.\n");
                _press_enter_to_continue();
        }
    } while (choice != 5);
}


// ... (The rest of your dsa_unit3_trees.c file,
// e.g., dsa_bst_operations, dsa_expression_tree, etc.)

void dsa_bst_operations() {
    struct BST_Node *root = NULL;
    int choice, data;

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Binary Search Tree (BST) Operations     |\n");
        printf("==========================================\n");
        printf(" 1. Insert Node\n");
        printf(" 2. Display Inorder (Sorted)\n");
        printf(" 3. Display Preorder\n");
        printf(" 4. Display Postorder\n");
        printf(" 5. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                if (scanf("%d", &data) != 1) { data = 0; }
                clear_input_buffer();
                root = bst_insert(root, data);
                printf("Inserted %d.\n", data);
                _press_enter_to_continue();
                break;
            case 2:
                printf("Inorder Traversal (LNR): ");
                bst_inorder_traversal(root);
                if(root == NULL) printf("Tree is empty.");
                printf("\n");
                _press_enter_to_continue();
                break;
            case 3:
                printf("Preorder Traversal (NLR): ");
                bst_preorder_traversal(root);
                if(root == NULL) printf("Tree is empty.");
                printf("\n");
                _press_enter_to_continue();
                break;
            case 4:
                printf("Postorder Traversal (LRN): ");
                bst_postorder_traversal(root);
                if(root == NULL) printf("Tree is empty.");
                printf("\n");
                _press_enter_to_continue();
                break;
            case 5:
                root = g_tree_free(root); // Cleanup
                printf("BST memory freed.\n");
                return;
            default:
                printf("Invalid choice.\n");
                _press_enter_to_continue();
        }
    } while (choice != 5);
}

// (This code goes into dsa_unit3_trees.c)
// ... (All the Binary Tree and BST code is here) ...

// ====================================================================
// --- 3. Static Helpers for Expression Tree (ET) ---
// ====================================================================

// --- Stack for ET_Node pointers ---
#define ET_STACK_SIZE 100
static struct ET_Node* g_et_stack[ET_STACK_SIZE];
static int g_et_top = -1;

static void et_stack_init() { g_et_top = -1; }
static int et_stack_is_empty() { return g_et_top == -1; }
static int et_stack_is_full() { return g_et_top == ET_STACK_SIZE - 1; }

static void et_push(struct ET_Node* node) {
    if (!et_stack_is_full()) {
        g_et_stack[++g_et_top] = node;
    }
}

static struct ET_Node* et_pop() {
    if (!et_stack_is_empty()) {
        return g_et_stack[g_et_top--];
    }
    return NULL; // Error/empty
}

// --- ET Helper Functions ---

/**
 * @brief (ET) Creates a new expression tree node.
 */
static struct ET_Node* et_create_node(char value) {
    struct ET_Node *newNode = (struct ET_Node*) malloc(sizeof(struct ET_Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/**
 * @brief (ET) Checks if a character is an operator.
 */
static int et_is_operator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

/**
 * @brief (ET) Frees all memory used by the expression tree.
 */
static struct ET_Node* et_free_tree(struct ET_Node *root) {
    if (root == NULL) return NULL;
    et_free_tree(root->left);
    et_free_tree(root->right);
    free(root);
    return NULL;
}

/**
 * @brief (ET) Traversal helper: Inorder (LNR)
 * This traversal *recreates* the original infix expression (with parentheses).
 */
static void et_inorder_traversal(struct ET_Node *root) {
    if (root != NULL) {
        // If the child is an operator, add parentheses
        if (et_is_operator(root->value) && root->left != NULL) {
            printf("(");
        }
        et_inorder_traversal(root->left);
        
        printf("%c", root->value);
        
        et_inorder_traversal(root->right);
        if (et_is_operator(root->value) && root->right != NULL) {
            printf(")");
        }
    }
}

/**
 * @brief (ET) Traversal helper: Preorder (NLR) - (Polish Notation)
 */
static void et_preorder_traversal(struct ET_Node *root) {
    if (root != NULL) {
        printf("%c ", root->value);
        et_preorder_traversal(root->left);
        et_preorder_traversal(root->right);
    }
}

/**
 * @brief (ET) Traversal helper: Postorder (LRN) - (Original Postfix)
 */
static void et_postorder_traversal(struct ET_Node *root) {
    if (root != NULL) {
        et_postorder_traversal(root->left);
        et_postorder_traversal(root->right);
        printf("%c ", root->value);
    }
}

// --- ASCII 2D Print Functions (adapted for ET_Node) ---

static int et_get_height(struct ET_Node* root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = et_get_height(root->left);
    int right_height = et_get_height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

static void et_print_ascii_tree_recursive(char** screen, struct ET_Node* root, 
                                          int level, int col_start, int col_end) {
    if (root == NULL || col_start > col_end) {
        return;
    }

    int col_mid = (col_start + col_end) / 2;
    int row = level * 2; 

    // Draw the node's value
    screen[row][col_mid] = root->value;

    // Recurse for left child
    if (root->left != NULL) {
        int line_pos = (col_start + col_mid - 1) / 2;
        screen[row + 1][line_pos] = '/';
        et_print_ascii_tree_recursive(screen, root->left, level + 1, col_start, col_mid - 1);
    }
    
    // Recurse for right child
    if (root->right != NULL) {
        int line_pos = (col_mid + 1 + col_end) / 2;
        screen[row + 1][line_pos] = '\\';
        et_print_ascii_tree_recursive(screen, root->right, level + 1, col_mid + 1, col_end);
    }
}

static void et_print_ascii_tree(struct ET_Node* root) {
    printf("--- 2D Tree Representation ---\n");

    if (root == NULL) {
        printf("\nTree is empty.\n");
        printf("------------------------------\n");
        return;
    }

    int height = et_get_height(root);
    int width = pow(2, height) * 4; 
    int rows = height * 2;

    char** screen = (char**) malloc(rows * sizeof(char*));
    if (screen == NULL) { printf("Memory allocation failed!\n"); return; }
    for (int i = 0; i < rows; i++) {
        screen[i] = (char*) malloc(width * sizeof(char));
        if (screen[i] == NULL) { printf("Memory failed!\n"); return; }
        memset(screen[i], ' ', width - 1);
        screen[i][width - 1] = '\0';
    }

    et_print_ascii_tree_recursive(screen, root, 0, 0, width - 1);

    for (int i = 0; i < rows; i++) {
        printf("%s\n", screen[i]);
    }

    for (int i = 0; i < rows; i++) {
        free(screen[i]);
    }
    free(screen);
    printf("------------------------------\n");
}


// --- Main Topic Function (Called by Dispatcher) ---

/**
 * @brief Topic 3: Expression Tree
 * This is the main function called by the dispatcher.
 */
void dsa_expression_tree() {
    char postfix[ET_STACK_SIZE];
    struct ET_Node *root = NULL;
    int i;
    
    et_stack_init(); // Reset the ET_Node stack
    
    _clear_screen();
    printf("==========================================\n");
    printf("| Expression Tree Builder                 |\n");
    printf("==========================================\n");
    printf("Note: This tool builds a tree from a POSTFIX expression.\n");
    printf("Enter a postfix expression (e.g., ab+c* ):\n");
    
    if(scanf("%s", postfix) != 1) { strcpy(postfix, "ab+c*"); }
    clear_input_buffer();
    
    printf("\n--- Building Tree from: %s ---\n", postfix);

    // --- The Build Algorithm ---
    for (i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];
        printf("Reading: '%c'\n", ch);
        
        // Case 1: Operand
        if (!et_is_operator(ch)) {
            struct ET_Node *newNode = et_create_node(ch);
            et_push(newNode);
            printf("  Action: Operand. Pushed node '%c' to stack.\n", ch);
        }
        // Case 2: Operator
        else {
            struct ET_Node *newNode = et_create_node(ch);
            printf("  Action: Operator. Pushing node '%c' to stack.\n", ch);
            
            // Pop two operands
            newNode->right = et_pop();
            newNode->left = et_pop();
            
            if(newNode->left == NULL || newNode->right == NULL) {
                printf("  ERROR: Malformed expression! (Not enough operands for '%c')\n", ch);
                root = et_free_tree(root); // Free partial tree
                et_free_tree(newNode);
                goto cleanup; // Jump to end
            }
            
            printf("  Popped '%c' (set as left child).\n", newNode->left->value);
            printf("  Popped '%c' (set as right child).\n", newNode->right->value);
            
            et_push(newNode);
        }
    }
    
    // After loop, the stack should have exactly one item: the root
    root = et_pop();
    if (!et_stack_is_empty()) {
        printf("ERROR: Malformed expression! (Too many operands)\n");
        root = et_free_tree(root); // Free the root we popped
        // Free everything else on the stack
        while(!et_stack_is_empty()) {
            et_free_tree(et_pop());
        }
    }

cleanup: // Label to jump to on error
    printf("\n--- Build Complete ---\n\n");
    
    // --- Display Results ---
    et_print_ascii_tree(root);
    
    printf("\n--- Traversals ---\n");
    printf("Inorder (Infix):   ");
    if (root) et_inorder_traversal(root); else printf("Empty");
    printf("\n");
    
    printf("Preorder (Prefix): ");
    if (root) et_preorder_traversal(root); else printf("Empty");
    printf("\n");
    
    printf("Postorder (Postfix): ");
    if (root) et_postorder_traversal(root); else printf("Empty");
    printf("\n");

    if (root) root = et_free_tree(root); // Cleanup
    _press_enter_to_continue();
}