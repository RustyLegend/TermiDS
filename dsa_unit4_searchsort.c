#include "dsa_unit4_searchsort.h"
#include "dsa_common.h"
#define HASH_TABLE_SIZE 10

struct Hash_Node {
    int key;
    struct Hash_Node *next;
}; 

struct HashTable {
    struct Hash_Node* table[HASH_TABLE_SIZE];
};

static struct HashTable g_hash_table;

static void hash_init() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        g_hash_table.table[i] = NULL;
    }
}

static int hash_function(int key) {
    int index = key % HASH_TABLE_SIZE;
    return (index < 0) ? index + HASH_TABLE_SIZE : index;
}

static void hash_free_all() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        struct Hash_Node* curr = g_hash_table.table[i];
        while (curr != NULL) {
            struct Hash_Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        g_hash_table.table[i] = NULL;
    }
    printf("Hash table memory freed.\n");
}

static void hash_print_table() {
    printf("--- Hash Table State (Size %d) ---\n", HASH_TABLE_SIZE);
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        printf("Index [%2d]: ", i);
        struct Hash_Node* temp = g_hash_table.table[i];
        if (temp == NULL) {
            printf("NULL\n");
            continue;
        }
        while (temp != NULL) {
            printf("-> %d ", temp->key);
            temp = temp->next;
        }
        printf("-> NULL\n");
    }
    printf("------------------------------------\n");
}

static void hash_insert() {
    int key;
    printf("Enter key to insert (int): ");
    if(scanf("%d", &key) != 1) { key = 0; }
    clear_input_buffer();
    
    int index = hash_function(key);
    printf("  Hash(%d) = %d. Inserting at Index [%d].\n", key, index, index);

    struct Hash_Node* temp = g_hash_table.table[index];
    while (temp != NULL) {
        if (temp->key == key) {
            printf("  Error: Key %d already exists. Duplicates not allowed.\n", key);
            return;
        }
        temp = temp->next;
    }

    struct Hash_Node* newNode = (struct Hash_Node*) malloc(sizeof(struct Hash_Node));
    if (newNode == NULL) {
        printf("  Memory allocation failed!\n");
        return;
    }
    newNode->key = key;

    newNode->next = g_hash_table.table[index];
    g_hash_table.table[index] = newNode;
    
    printf("  Successfully inserted %d.\n", key);
}

static void hash_search() {
    int key;
    printf("Enter key to search for (int): ");
    if(scanf("%d", &key) != 1) { key = 0; }
    clear_input_buffer();

    int index = hash_function(key);
    printf("  Hash(%d) = %d. Searching at Index [%d].\n", key, index, index);

    struct Hash_Node* temp = g_hash_table.table[index];
    while (temp != NULL) {
        if (temp->key == key) {
            printf("  Result: Found key %d at Index [%d].\n", key, index);
            return;
        }
        temp = temp->next;
    }

    printf("  Result: Key %d was not found.\n", key);
}

static void hash_delete() {
    int key;
    printf("Enter key to delete (int): ");
    if(scanf("%d", &key) != 1) { key = 0; }
    clear_input_buffer();

    int index = hash_function(key);
    printf("  Hash(%d) = %d. Searching at Index [%d] for deletion.\n", key, index, index);

    struct Hash_Node* curr = g_hash_table.table[index];
    struct Hash_Node* prev = NULL;

    while (curr != NULL && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }
    
    if (curr == NULL) {
        printf("  Result: Key %d not found. Nothing to delete.\n", key);
        return;
    }

    if (prev == NULL) {
        g_hash_table.table[index] = curr->next;
    } else {
        prev->next = curr->next;
    }
    
    free(curr);
    printf("  Result: Successfully deleted key %d.\n", key);
}

static void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static void print_binary_search_step(int arr[], int n, int low, int high, int mid) {
    printf("Index: ");
    for (int i = 0; i < n; i++) {
        printf("%3d ", i);
    }
    printf("\n");

    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%3d ", arr[i]);
    }
    printf("\n");

    printf("       ");
    for (int i = 0; i < n; i++) {
        int is_low = (i == low);
        int is_mid = (i == mid);
        int is_high = (i == high);

        if (is_low && is_mid && is_high) printf("LMH ");
        else if (is_low && is_mid) printf(" LM ");
        else if (is_mid && is_high) printf(" MH ");
        else if (is_low && is_high) printf("L H ");
        else if (is_low)  printf("  L ");
        else if (is_mid)  printf("  M ");
        else if (is_high) printf("  H ");
        else printf("    ");
    }
    printf("\n");
}

static int lomuto_partition(int arr[], int low, int high, int n) {
    int pivot = arr[high];
    int i = (low - 1);

    printf("\n  [Partitioning array from index %d to %d. Pivot is %d (at index %d)]\n", low, high, pivot, high);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    
    int pivot_index = i + 1;
    
    printf("  After partition, pivot %d is in final position %d.\n", pivot, pivot_index);
    printf("  Array state: ");
    print_array(arr, n);
    _press_enter_to_continue();

    return pivot_index;
}

static void quick_sort_recursive(int arr[], int low, int high, int n) {
    if (low < high) {
        int pi = lomuto_partition(arr, low, high, n);
        quick_sort_recursive(arr, low, pi - 1, n);
        quick_sort_recursive(arr, pi + 1, high, n);
    }
}

static void merge(int arr[], int l, int m, int r, int n) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int* L = (int*) malloc(n1 * sizeof(int));
    int* R = (int*) malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("  Memory allocation failed for temp arrays!\n");
        if (L) free(L);
        if (R) free(R);
        return;
    }

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    printf("\n  [Merging]\n");
    printf("  Left sub-array [index %d..%d]: ", l, m);
    print_array(L, n1);
    printf("  Right sub-array [index %d..%d]: ", m + 1, r);
    print_array(R, n2);
    
    i = 0;
    j = 0;
    k = l;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    printf("  Result of merge:\n");
    printf("  Full array state: ");
    print_array(arr, n);
    _press_enter_to_continue();
    
    free(L);
    free(R);
}

static void merge_sort_recursive(int arr[], int l, int r, int n) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_recursive(arr, l, m, n);
        merge_sort_recursive(arr, m + 1, r, n);
        merge(arr, l, m, r, n);
    }
}

static struct BST_Node* heap_build_tree_recursive(int arr[], int i, int n) {
    if (i >= n) {
        return NULL;
    }

    struct BST_Node* root = (struct BST_Node*) malloc(sizeof(struct BST_Node));
    if (root == NULL) return NULL;
    root->data = arr[i];

    root->left = heap_build_tree_recursive(arr, 2 * i + 1, n);
    root->right = heap_build_tree_recursive(arr, 2 * i + 2, n);

    return root;
}

static void heap_print_tree_from_array(int arr[], int n) {
    if (n <= 0) {
        printf("Tree is empty.\n");
        return;
    }
    struct BST_Node* root = heap_build_tree_recursive(arr, 0, n);
    g_tree_print_ascii(root);
    g_tree_free(root);
}

static void heap_swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

static void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        heap_swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void dsa_hash_table() {
    int choice;
    
    hash_init();

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Hash Table (Separate Chaining)          |\n");
        printf("==========================================\n");
        hash_print_table();
        printf("------------------------------------------\n");
        printf(" 1. Insert Key\n");
        printf(" 2. Delete Key\n");
        printf(" 3. Search for Key\n");
        printf(" 4. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                hash_insert();
                _press_enter_to_continue();
                break;
            case 2:
                hash_delete();
                _press_enter_to_continue();
                break;
            case 3:
                hash_search();
                _press_enter_to_continue();
                break;
            case 4:
                hash_free_all();
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 4);
}

void dsa_linear_search() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Linear Search                           |\n");
    printf("==========================================\n");
    
    int n, key, found = 0;
    int* arr = get_array(&n);
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("Enter element to search for: ");
    if(scanf("%d", &key) != 1) { key = -1; }
    clear_input_buffer();

    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            printf("\n--- Result ---\n");
            printf("Element %d found at index %d (position %d).\n", key, i, i + 1);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n--- Result ---\n");
        printf("Element %d not found in the array.\n", key);
    }
    free(arr);
    _press_enter_to_continue();
}

void dsa_binary_search() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Binary Search                           |\n");
    printf("==========================================\n");
    
    printf("\nNOTE: Binary Search requires a SORTED array.\n");
    printf("Please ensure the elements you entered were in ascending order.\n\n");

    int n, key;
    int* arr = get_array(&n);
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }
    
    printf("Enter element to search for: ");
    if(scanf("%d", &key) != 1) { key = -1; }
    clear_input_buffer();

    int low = 0, high = n - 1, mid;
    int pos = -1;
    int step = 0;
    while (low <= high) {
        step++;
        mid = low + (high - low) / 2;
        printf("\n--- Step %d ---\n", step);
        print_binary_search_step(arr, n, low, high, mid);
        printf("Checking middle element: arr[%d] = %d\n", mid, arr[mid]);

        if (arr[mid] == key) {
            pos = mid;
            break;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (pos != -1) {
        printf("\n--- Result ---\n");
        printf("Element %d found at index %d (position %d).\n", key, pos, pos + 1);
    } else {
        printf("\n--- Result ---\n");
        printf("Element %d not found in the array.\n", key);
    }
    
    free(arr);
    _press_enter_to_continue();
}

void dsa_insertion_sort() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Insertion Sort                          |\n");
    printf("==========================================\n");

    int n;
    int* arr = get_array(&n);
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal array: ");
    print_array(arr, n);

    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;

        printf("After pass %d:   ", i);
        print_array(arr, n);
    }

    printf("\n--- Result ---\n");
    printf("Sorted array:   ");
    print_array(arr, n);

    free(arr);
    _press_enter_to_continue();
}

void dsa_quick_sort() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Quick Sort (Lomuto Partition)           |\n");
    printf("==========================================\n");
    printf("Note: We will use the last element of each\n");
    printf("sub-array as the pivot.\n\n");

    int n;
    int* arr = get_array(&n);
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal Array:\n");
    print_array(arr, n);
    _press_enter_to_continue();

    printf("\n--- Starting Quick Sort ---\n");
    quick_sort_recursive(arr, 0, n - 1, n);

    printf("\n--- Final Result ---\n");
    printf("Sorting complete.\n");
    print_array(arr, n);

    free(arr);
    _press_enter_to_continue();
}

void dsa_merge_sort() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Merge Sort (Divide & Conquer)           |\n");
    printf("==========================================\n");
    printf("Note: This will show the two sorted sub-arrays\n");
    printf("right before they are merged.\n\n");

    int n;
    int* arr = get_array(&n);
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal Array:\n");
    print_array(arr, n);
    _press_enter_to_continue();

    printf("\n--- Starting Merge Sort ---\n");
    merge_sort_recursive(arr, 0, n - 1, n);

    printf("\n--- Final Result ---\n");
    printf("Sorting complete.\n");
    print_array(arr, n);

    free(arr);
    _press_enter_to_continue();
}

void dsa_heap_sort() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Heap Sort (Visualized)                  |\n");
    printf("==========================================\n");
    printf("Note: This will show the implicit tree\n");
    printf("structure of the array at each key step.\n\n");

    int n;
    int* arr = get_array(&n);
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal Array:\n");
    print_array(arr, n);
    printf("As a tree:\n");
    heap_print_tree_from_array(arr, n);
    _press_enter_to_continue();

    printf("\n--- Phase 1: Building Max Heap ---\n");
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    printf("Max Heap built. Largest element (%d) is at the root.\n", arr[0]);
    printf("Array state: ");
    print_array(arr, n);
    printf("As a tree:\n");
    heap_print_tree_from_array(arr, n);
    _press_enter_to_continue();

    printf("\n--- Phase 2: Extracting Max Element ---\n");
    for (int i = n - 1; i > 0; i--) {
        printf("  Swapping root (%d) with end of heap (arr[%d]=%d).\n", arr[0], i, arr[i]);
        heap_swap(&arr[0], &arr[i]);

        printf("  Array state (sorted part from index %d):\n", i);
        print_array(arr, n);

        printf("  Calling heapify on root for reduced heap (size %d).\n", i);
        printf("  Tree representation of reduced heap (size %d):\n", i);
        heap_print_tree_from_array(arr, i);

        heapify(arr, i, 0);

        printf("  Heap property restored. New max is %d.\n", arr[0]);
        printf("  Restored heap tree (size %d):\n", i);
        heap_print_tree_from_array(arr, i);
        _press_enter_to_continue();
    }

    printf("\n--- Final Result ---\n");
    printf("Sorting complete.\n");
    print_array(arr, n);

    free(arr);
    _press_enter_to_continue();
}