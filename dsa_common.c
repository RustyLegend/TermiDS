#include "dsa_common.h"

void _clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[2J\033[H");
    #endif
}

void _loading_animation() {
    _clear_screen();
    printf(">> Initializing TermiDS Engine...\n");
    printf("Establishing Senior-Junior Connection...\n");
    printf("Loading content...\n\n");
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void _press_enter_to_continue() {
    printf("------------------------------------------\n");
    printf("Press ENTER to return to the menu...\n");
    getchar();
}

void _display_content_placeholder(const char *topic_name) {
    _clear_screen();
    printf("====================================================\n");
    printf("| TERMID S: Content Viewer - %-20s |\n", topic_name);
    printf("====================================================\n");
    printf("Loading content... %s\n", topic_name);
    printf("\n\n                     +---------------------+\n");
    printf("                     | Still adding 'em!   |\n");
    printf("                     +---------------------+\n\n");
    _press_enter_to_continue();
}

int* get_array(int *n) {
    printf("Enter number of elements: ");
    if(scanf("%d", n) != 1) { *n = 0; }
    clear_input_buffer();

    if (*n <= 0) {
        printf("Invalid size.\n");
        return NULL;
    }

    int* arr = (int*) malloc(*n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    printf("Enter %d elements:\n", *n);
    for (int i = 0; i < *n; i++) {
        printf("Element %d: ", i + 1);
        if(scanf("%d", &arr[i]) != 1) { arr[i] = 0; }
        clear_input_buffer();
    }
    return arr;
}

void print_array(int arr[], int size) {
    printf("[ ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}

int* get_positive_array(int *n) {
    printf("Enter number of elements: ");
    if(scanf("%d", n) != 1) { *n = 0; }
    clear_input_buffer();

    if (*n <= 0) {
        printf("Invalid size.\n");
        return NULL;
    }

    int* arr = (int*) malloc(*n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    printf("Enter %d elements (must be 0 or greater):\n", *n);
    for (int i = 0; i < *n; i++) {
        printf("Element %d: ", i + 1);
        if(scanf("%d", &arr[i]) != 1 || arr[i] < 0) { 
            printf("Invalid input. Forcing to 0.\n");
            arr[i] = 0; 
        }
        clear_input_buffer();
    }
    return arr;
}

int get_max(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}

struct BST_Node* g_tree_free(struct BST_Node *root) {
    if (root == NULL) return NULL;
    g_tree_free(root->left);
    g_tree_free(root->right);
    free(root);
    return NULL;
}

static int g_tree_get_height(struct BST_Node* root) {
    if (root == NULL) {
        return 0;
    }
    int left_height = g_tree_get_height(root->left);
    int right_height = g_tree_get_height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}

static void g_tree_print_ascii_recursive(char** screen, struct BST_Node* root, 
                                          int level, int col_start, int col_end) {
    if (root == NULL || col_start > col_end) {
        return;
    }

    int col_mid = (col_start + col_end) / 2;
    int row = level * 2;

    char val_str[16];
    sprintf(val_str, "%d", root->data);
    int str_len = strlen(val_str);
    int draw_pos = col_mid - (str_len / 2);
    for (int i = 0; i < str_len; i++) {
        if (draw_pos + i < col_end) {
            screen[row][draw_pos + i] = val_str[i];
        }
    }

    if (root->left != NULL) {
        int line_pos = (col_start + col_mid - 1) / 2;
        screen[row + 1][line_pos] = '/';
        g_tree_print_ascii_recursive(screen, root->left, level + 1, col_start, col_mid - 1);
    }
    
    if (root->right != NULL) {
        int line_pos = (col_mid + 1 + col_end) / 2;
        screen[row + 1][line_pos] = '\\';
        g_tree_print_ascii_recursive(screen, root->right, level + 1, col_mid + 1, col_end);
    }
}

void g_tree_print_ascii(struct BST_Node* root) {
    printf("--- 2D Tree Representation ---\n");

    if (root == NULL) {
        printf("\nTree is empty.\n");
        printf("------------------------------\n");
        return;
    }

    int height = g_tree_get_height(root);
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

    g_tree_print_ascii_recursive(screen, root, 0, 0, width - 1);

    for (int i = 0; i < rows; i++) {
        printf("%s\n", screen[i]);
    }

    for (int i = 0; i < rows; i++) {
        free(screen[i]);
    }
    free(screen);
    printf("------------------------------\n");
}