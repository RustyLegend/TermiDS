#include "dsa_unit4_searchsort.h"
#include "dsa_common.h"
#define HASH_TABLE_SIZE 10 // For easy visualization

// Node for the linked lists (chains)
struct Hash_Node {
    int key;
    // In a real table, you'd have more data here:
    // char value[100]; 
    struct Hash_Node *next;
}; 

// The Hash Table structure
struct HashTable {
    struct Hash_Node* table[HASH_TABLE_SIZE]; // An array of head pointers
};

// A global static instance for this module
static struct HashTable g_hash_table;

/**
 * @brief (HASH) Initializes all table pointers to NULL.
 */
static void hash_init() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        g_hash_table.table[i] = NULL;
    }
}

/**
 * @brief (HASH) The hash function.
 */
static int hash_function(int key) {
    int index = key % HASH_TABLE_SIZE;
    // Handle negative keys
    return (index < 0) ? index + HASH_TABLE_SIZE : index;
}

/**
 * @brief (HASH) Frees all lists in the hash table.
 */
static void hash_free_all() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        struct Hash_Node* curr = g_hash_table.table[i];
        while (curr != NULL) {
            struct Hash_Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        g_hash_table.table[i] = NULL; // Reset the head pointer
    }
    printf("Hash table memory freed.\n");
}

/**
 * @brief (HASH) [VISUALIZATION] Prints the entire hash table.
 */
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

/**
 * @brief (HASH) Inserts a key into the table.
 */
static void hash_insert() {
    int key;
    printf("Enter key to insert (int): ");
    if(scanf("%d", &key) != 1) { key = 0; }
    clear_input_buffer();
    
    int index = hash_function(key);
    printf("  Hash(%d) = %d. Inserting at Index [%d].\n", key, index, index);

    // Check for duplicates first
    struct Hash_Node* temp = g_hash_table.table[index];
    while (temp != NULL) {
        if (temp->key == key) {
            printf("  Error: Key %d already exists. Duplicates not allowed.\n", key);
            return;
        }
        temp = temp->next;
    }

    // No duplicate, create new node
    struct Hash_Node* newNode = (struct Hash_Node*) malloc(sizeof(struct Hash_Node));
    if (newNode == NULL) {
        printf("  Memory allocation failed!\n");
        return;
    }
    newNode->key = key;

    // Insert at the front of the list at this index
    newNode->next = g_hash_table.table[index];
    g_hash_table.table[index] = newNode;
    
    printf("  Successfully inserted %d.\n", key);
}

/**
 * @brief (HASH) Searches for a key in the table.
 */
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

/**
 * @brief (HASH) Deletes a key from the table.
 */
static void hash_delete() {
    int key;
    printf("Enter key to delete (int): ");
    if(scanf("%d", &key) != 1) { key = 0; }
    clear_input_buffer();

    int index = hash_function(key);
    printf("  Hash(%d) = %d. Searching at Index [%d] for deletion.\n", key, index, index);

    struct Hash_Node* curr = g_hash_table.table[index];
    struct Hash_Node* prev = NULL;

    // Traverse the list to find the key
    while (curr != NULL && curr->key != key) {
        prev = curr;
        curr = curr->next;
    }
    
    // Case 1: Not found
    if (curr == NULL) {
        printf("  Result: Key %d not found. Nothing to delete.\n", key);
        return;
    }

    // Case 2: Found. Now we delete it.
    if (prev == NULL) {
        // It's the head node
        g_hash_table.table[index] = curr->next;
    } else {
        // It's a node in the middle or at the end
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
    // 1. Print Indices
    printf("Index: ");
    for (int i = 0; i < n; i++) {
        printf("%3d ", i); // Print index centered in 3 spaces + 1 space
    }
    printf("\n");

    // 2. Print Array Elements
    printf("Array: ");
    for (int i = 0; i < n; i++) {
        printf("%3d ", arr[i]); // Print element centered in 3 spaces + 1 space
    }
    printf("\n");

    printf("       ");
    for (int i = 0; i < n; i++) {
        int is_low = (i == low);
        int is_mid = (i == mid);
        int is_high = (i == high);

        if (is_low && is_mid && is_high) printf("LMH "); // All overlap
        else if (is_low && is_mid) printf(" LM ");      // L and M overlap
        else if (is_mid && is_high) printf(" MH ");     // M and H overlap
        else if (is_low && is_high) printf("L H ");     // L and H overlap (unlikely in correct binary search)
        else if (is_low)  printf("  L ");             // Just L
        else if (is_mid)  printf("  M ");             // Just M
        else if (is_high) printf("  H ");             // Just H (aligned more to the right)
        else printf("    ");                         // No pointer here
    }
    printf("\n"); // End the pointer line
}

static int lomuto_partition(int arr[], int low, int high, int n) {
    int pivot = arr[high]; // The pivot
    int i = (low - 1); // Index of smaller element

    printf("\n  [Partitioning array from index %d to %d. Pivot is %d (at index %d)]\n", low, high, pivot, high);

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // Increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    // Place the pivot in its final, correct position
    swap(&arr[i + 1], &arr[high]);
    
    int pivot_index = i + 1;
    
    printf("  After partition, pivot %d is in final position %d.\n", pivot, pivot_index);
    printf("  Array state: ");
    print_array(arr, n); // print_array is from dsa_common.c
    _press_enter_to_continue();

    return pivot_index;
}

/**
 * @brief (QUICKSORT) The main recursive function.
 * @param n This is the *total size* of the array, passed for printing only.
 */
static void quick_sort_recursive(int arr[], int low, int high, int n) {
    if (low < high) {
        // pi is partitioning index, arr[pi] is now at right place
        int pi = lomuto_partition(arr, low, high, n);

        // Recursively sort elements before partition
        quick_sort_recursive(arr, low, pi - 1, n);
        
        // Recursively sort elements after partition
        quick_sort_recursive(arr, pi + 1, high, n);
    }
}


static void merge(int arr[], int l, int m, int r, int n) {
    int i, j, k;
    int n1 = m - l + 1; // Size of left temp array
    int n2 = r - m;     // Size of right temp array

    // Create temp arrays
    int* L = (int*) malloc(n1 * sizeof(int));
    int* R = (int*) malloc(n2 * sizeof(int));

    if (L == NULL || R == NULL) {
        printf("  Memory allocation failed for temp arrays!\n");
        if (L) free(L);
        if (R) free(R);
        return;
    }

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // --- Visualization ---
    printf("\n  [Merging]\n");
    printf("  Left sub-array [index %d..%d]: ", l, m);
    print_array(L, n1);
    printf("  Right sub-array [index %d..%d]: ", m + 1, r);
    print_array(R, n2);
    
    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    
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

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // --- Visualization ---
    printf("  Result of merge:\n");
    printf("  Full array state: ");
    print_array(arr, n); // print_array is from dsa_common.c
    _press_enter_to_continue();
    
    // Free the temp arrays
    free(L);
    free(R);
}

/**
 * @brief (MERGESORT) The main recursive function.
 * @param n This is the *total size* of the array, passed for printing only.
 */
static void merge_sort_recursive(int arr[], int l, int r, int n) {
    if (l < r) {
        // Find the middle point
        int m = l + (r - l) / 2; // Same as (l+r)/2, but avoids overflow

        // Sort first and second halves
        merge_sort_recursive(arr, l, m, n);
        merge_sort_recursive(arr, m + 1, r, n);

        // Merge the sorted halves
        merge(arr, l, m, r, n);
    }
}

static struct BST_Node* heap_build_tree_recursive(int arr[], int i, int n) {
    if (i >= n) {
        return NULL; // Out of bounds
    }

    // Create new node for this index
    struct BST_Node* root = (struct BST_Node*) malloc(sizeof(struct BST_Node));
    if (root == NULL) return NULL;
    root->data = arr[i];

    // Recursively build children
    root->left = heap_build_tree_recursive(arr, 2 * i + 1, n);
    root->right = heap_build_tree_recursive(arr, 2 * i + 2, n);

    return root;
}

/**
 * @brief (HEAP) [NEW] Wrapper to build and print the heap tree.
 */
static void heap_print_tree_from_array(int arr[], int n) {
    if (n <= 0) {
        printf("Tree is empty.\n");
        return;
    }
    // Build the temporary tree from the array
    struct BST_Node* root = heap_build_tree_recursive(arr, 0, n);

    // Print it using the global ASCII printer
    g_tree_print_ascii(root);

    // Free the temporary tree
    g_tree_free(root);
}

static void heap_swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

/**
 * @brief (HEAP) The core "heapify" process.
 * This function ensures that the subtree rooted at index 'i'
 * satisfies the max heap property. 'n' is the size of the heap.
 */
static void heapify(int arr[], int n, int i) {
    int largest = i;     // Initialize largest as root
    int left = 2 * i + 1;  // left child
    int right = 2 * i + 2; // right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // If largest is not the root, swap them
    if (largest != i) {
        heap_swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        // (which now contains the value that was at 'i')
        heapify(arr, n, largest);
    }
}

// --- Main Topic Functions (Called by Dispatcher) ---

// (This code goes into dsa_unit4_searchsort.c)
// ... (The other dsa_ functions are here) ...

/**
 * @brief Topic 1: Hash Table Sub-Menu
 * This is the main function called by the dispatcher.
 */
void dsa_hash_table() {
    int choice;
    
    hash_init(); // Initialize the table when the menu is entered

    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Hash Table (Separate Chaining)          |\n");
        printf("==========================================\n");
        hash_print_table(); // Show the table on every loop!
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
                hash_free_all(); // Cleanup before leaving
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 4);
}

void dsa_linear_search() {
    // This is the implementation from our previous session.
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
        mid = low + (high - low) / 2; // Avoid overflow
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
    int* arr = get_array(&n); // get_array() is the helper in this file
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal array: ");
    print_array(arr, n);

    // --- Insertion Sort Logic ---
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i]; // Pick the element to be inserted
        j = i - 1;

        // Move elements of arr[0..i-1], that are
        // greater than key, to one position ahead
        // of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;

        printf("After pass %d:   ", i);
        print_array(arr, n);
    }
    // --- End of Logic ---

    printf("\n--- Result ---\n");
    printf("Sorted array:   ");
    print_array(arr, n);

    free(arr);
    _press_enter_to_continue();
}

// (This code goes into dsa_unit4_searchsort.c)
// ... (The other dsa_ functions are here) ...

/**
 * @brief Topic 5: Quick Sort
 * This is the main function called by the dispatcher.
 */
void dsa_quick_sort() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Quick Sort (Lomuto Partition)           |\n");
    printf("==========================================\n");
    printf("Note: We will use the last element of each\n");
    printf("sub-array as the pivot.\n\n");

    int n;
    int* arr = get_array(&n); // get_array is from dsa_common.c
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal Array:\n");
    print_array(arr, n);
    _press_enter_to_continue();

    printf("\n--- Starting Quick Sort ---\n");
    // Call the recursive helper, passing 'n' for visualization
    quick_sort_recursive(arr, 0, n - 1, n);

    printf("\n--- Final Result ---\n");
    printf("Sorting complete.\n");
    print_array(arr, n);

    free(arr);
    _press_enter_to_continue();
}

// (This code goes into dsa_unit4_searchsort.c)
// ... (The other dsa_ functions are here) ...

/**
 * @brief Topic 6: Merge Sort
 * This is the main function called by the dispatcher.
 */
void dsa_merge_sort() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Merge Sort (Divide & Conquer)           |\n");
    printf("==========================================\n");
    printf("Note: This will show the two sorted sub-arrays\n");
    printf("right before they are merged.\n\n");

    int n;
    int* arr = get_array(&n); // get_array is from dsa_common.c
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal Array:\n");
    print_array(arr, n);
    _press_enter_to_continue();

    printf("\n--- Starting Merge Sort ---\n");
    // Call the recursive helper, passing 'n' for visualization
    merge_sort_recursive(arr, 0, n - 1, n);

    printf("\n--- Final Result ---\n");
    printf("Sorting complete.\n");
    print_array(arr, n);

    free(arr);
    _press_enter_to_continue();
}

// (This code goes into dsa_unit4_searchsort.c)
// ... (The other dsa_ functions are here) ...

/**
 * @brief Topic 7: Heap Sort
 * This is the main function called by the dispatcher.
 */
/**
 * @brief Topic 7: Heap Sort
 * This is the main function called by the dispatcher.
 */
void dsa_heap_sort() {
    _clear_screen();
    printf("==========================================\n");
    printf("| Heap Sort (Visualized)                  |\n");
    printf("==========================================\n");
    printf("Note: This will show the implicit tree\n");
    printf("structure of the array at each key step.\n\n");

    int n;
    int* arr = get_array(&n); // get_array is from dsa_common.c
    if (arr == NULL) {
        _press_enter_to_continue();
        return;
    }

    printf("\nOriginal Array:\n");
    print_array(arr, n);
    printf("As a tree:\n");
    heap_print_tree_from_array(arr, n);
    _press_enter_to_continue();

    // --- Phase 1: Build Max Heap ---
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

    // --- Phase 2: Extract Elements (Sort-Down) ---
    printf("\n--- Phase 2: Extracting Max Element ---\n");
    for (int i = n - 1; i > 0; i--) {
        // 1. Move current root (max element) to the end
        printf("  Swapping root (%d) with end of heap (arr[%d]=%d).\n", arr[0], i, arr[i]);
        heap_swap(&arr[0], &arr[i]);

        printf("  Array state (sorted part from index %d):\n", i);
        print_array(arr, n);

        // 2. Call max heapify on the *reduced heap* (size 'i')
        printf("  Calling heapify on root for reduced heap (size %d).\n", i);
        printf("  Tree representation of reduced heap (size %d):\n", i);
        heap_print_tree_from_array(arr, i); // Show tree before heapify

        heapify(arr, i, 0);

        printf("  Heap property restored. New max is %d.\n", arr[0]);
        printf("  Restored heap tree (size %d):\n", i);
        heap_print_tree_from_array(arr, i); // Show tree after heapify
        _press_enter_to_continue();
    }

    printf("\n--- Final Result ---\n");
    printf("Sorting complete.\n");
    print_array(arr, n);

    free(arr);
    _press_enter_to_continue();
}