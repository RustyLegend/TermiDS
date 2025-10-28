#include "dsa_unit5_graphs.h"
#include "dsa_common.h"

// A global static instance for this module
static struct Graph g_graph;
static int g_visited[MAX_GRAPH_VERTICES];

// (This code goes into dsa_unit5_graphs.c)
// ... (The DFS static helpers like dfs_recursive are here) ...

// ====================================================================
// --- 2. Static Helpers for Breadth First Search (BFS) ---
// ====================================================================

// Simple queue for BFS
#define BFS_QUEUE_SIZE MAX_GRAPH_VERTICES
static int g_bfs_queue[BFS_QUEUE_SIZE];
static int g_bfs_front = 0;
static int g_bfs_rear = -1;
static int g_bfs_count = 0;

// (This code goes into dsa_unit5_graphs.c)
// ... (The BFS static helpers like bfs_enqueue are here) ...

// ====================================================================
// --- 2a. Static Helpers for DFS Stack Visualization ---
// ====================================================================

// Simple stack for DFS visualization
#define DFS_STACK_SIZE MAX_GRAPH_VERTICES
static int g_dfs_vis_stack[DFS_STACK_SIZE];
static int g_dfs_vis_top = -1;
static char g_dfs_traversal_order[MAX_GRAPH_VERTICES * 5 + 10];

/**
 * @brief (DFS VIZ STACK) Initializes the visualization stack.
 */
static void dfs_vis_stack_init() {
    g_dfs_vis_top = -1;
}

/**
 * @brief (DFS VIZ STACK) Pushes an item onto the visualization stack.
 */
static void dfs_vis_push(int item) {
    if (g_dfs_vis_top < DFS_STACK_SIZE - 1) {
        g_dfs_vis_stack[++g_dfs_vis_top] = item;
    }
}

/**
 * @brief (DFS VIZ STACK) Pops an item from the visualization stack.
 */
static void dfs_vis_pop() {
    if (g_dfs_vis_top > -1) {
        g_dfs_vis_top--;
    }
}

/**
 * @brief (DFS VIZ STACK) Prints the current state of the visualization stack.
 */
static void dfs_vis_print_stack() {
    printf("  DFS Stack: [ ");
    if (g_dfs_vis_top > -1) {
        for (int i = 0; i <= g_dfs_vis_top; i++) {
            printf("%d ", g_dfs_vis_stack[i]);
        }
    }
    printf("] (top is %d)\n", (g_dfs_vis_top > -1 ? g_dfs_vis_stack[g_dfs_vis_top] : -1));
}

/**
 * @brief (BFS QUEUE) Initializes the queue.
 */
static void bfs_queue_init() {
    g_bfs_front = 0;
    g_bfs_rear = -1;
    g_bfs_count = 0;
}

/**
 * @brief (BFS QUEUE) Checks if the queue is empty.
 */
static int bfs_queue_is_empty() {
    return g_bfs_count == 0;
}

/**
 * @brief (BFS QUEUE) Adds an item to the rear of the queue.
 */
static void bfs_enqueue(int item) {
    if (g_bfs_count < BFS_QUEUE_SIZE) {
        g_bfs_rear = (g_bfs_rear + 1) % BFS_QUEUE_SIZE;
        g_bfs_queue[g_bfs_rear] = item;
        g_bfs_count++;
    }
}

/**
 * @brief (BFS QUEUE) Removes an item from the front of the queue.
 */
static int bfs_dequeue() {
    if (!bfs_queue_is_empty()) {
        int item = g_bfs_queue[g_bfs_front];
        g_bfs_front = (g_bfs_front + 1) % BFS_QUEUE_SIZE;
        g_bfs_count--;
        return item;
    }
    return -1; // Indicate error/empty
}

/**
 * @brief (BFS QUEUE) Helper to print the queue state.
 */
static void bfs_print_queue() {
    printf("  Queue: [ ");
    if (!bfs_queue_is_empty()) {
        int i = g_bfs_front;
        int j;
        for (j = 0; j < g_bfs_count; j++) {
            printf("%d ", g_bfs_queue[i]);
            i = (i + 1) % BFS_QUEUE_SIZE;
        }
    }
    printf("] (front)\n");
}

// (This code goes into dsa_unit5_graphs.c)

/**
 * @brief (BFS) The main BFS traversal function (CORRECTED).
 */
// (This code goes into dsa_unit5_graphs.c)
static void bfs_run_traversal() {
    int start_vertex;
    // <<< NEW: Buffer to store the final traversal order >>>
    char traversal_order[MAX_GRAPH_VERTICES * 5 + 10]; // Rough estimate for size
    
    printf("Enter start vertex for BFS (0 to %d): ", g_graph.V - 1);
    if(scanf("%d", &start_vertex) != 1 || start_vertex < 0 || start_vertex >= g_graph.V) {
        printf("Invalid start vertex.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    // 1. Reset visited array and initialize queue
    for (int i = 0; i < g_graph.V; i++) {
        g_visited[i] = 0; 
    }
    bfs_queue_init();

    printf("\n--- BFS Traversal Steps ---\n");
    // <<< NEW: Initialize the traversal order string >>>
    strcpy(traversal_order, "Start"); 

    // --- Start BFS from the initial vertex ---
    // <<< NEW: Append start node to the string >>>
    sprintf(traversal_order + strlen(traversal_order), " -> %d", start_vertex); 
    
    printf("Visited: %d\n", start_vertex); // Print visit step
    g_visited[start_vertex] = 1;
    bfs_enqueue(start_vertex);
    printf("Initial Queue: "); bfs_print_queue();


    // --- Main BFS Loop ---
    while (!bfs_queue_is_empty()) {
        int u = bfs_dequeue();
        printf("\nDequeued: %d. Exploring neighbors...\n", u);

        for (int v = 0; v < g_graph.V; v++) {
            if (g_graph.adjMatrix[u][v] != 0 && g_visited[v] == 0) { // Check weight > 0
                // <<< NEW: Append visited node to the string >>>
                sprintf(traversal_order + strlen(traversal_order), " -> %d", v); 
                
                printf("  Visited: %d\n", v); // Print visit step
                g_visited[v] = 1;
                bfs_enqueue(v);
                bfs_print_queue();
            }
        }
    }
    printf("\n--- Main Traversal Complete ---\n");


    // --- Check for disconnected components ---
    for (int i = 0; i < g_graph.V; i++) {
        if (g_visited[i] == 0) {
            printf("\nNote: Vertex %d was unreached. Starting BFS from %d...\n", i, i);
            // <<< NEW: Append disconnected node >>>
            sprintf(traversal_order + strlen(traversal_order), " -> %d", i); 
            
            printf("Visited: %d\n", i); // Print visit step
            g_visited[i] = 1;
            bfs_enqueue(i);
            bfs_print_queue();

            // Run BFS for the disconnected component
            while (!bfs_queue_is_empty()) {
                int u = bfs_dequeue();
                 printf("\nDequeued: %d. Exploring neighbors...\n", u);

                for (int v = 0; v < g_graph.V; v++) {
                     if (g_graph.adjMatrix[u][v] != 0 && g_visited[v] == 0) { // Check weight > 0
                         // <<< NEW: Append visited node >>>
                         sprintf(traversal_order + strlen(traversal_order), " -> %d", v); 

                         printf("  Visited: %d\n", v); // Print visit step
                         g_visited[v] = 1;
                         bfs_enqueue(v);
                         bfs_print_queue();
                     }
                 }
            }
             printf("\n--- Disconnected Component Traversal Complete ---\n");
        }
    }
    printf("\n--- All Components Traversed ---\n");

    // <<< NEW: Print the final accumulated traversal order >>>
    printf("\nFinal Traversal Order:\n%s\n", traversal_order); 
}

static int g_dist[MAX_GRAPH_VERTICES];   // Stores shortest distance from source
static int g_sptSet[MAX_GRAPH_VERTICES]; // 1 if vertex is included in shortest path tree
static int g_parent[MAX_GRAPH_VERTICES]; // Stores the path

/**
 * @brief (DIJKSTRA) Finds the vertex with the minimum distance value,
 * from the set of vertices not yet included in the shortest path tree.
 */
static int dijkstra_min_distance_vertex() {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < g_graph.V; v++) {
        if (g_sptSet[v] == 0 && g_dist[v] <= min) {
            min = g_dist[v];
            min_index = v;
        }
    }
    return min_index;
}

/**
 * @brief (DIJKSTRA) [VISUALIZATION] Prints the current state of dist and parent arrays.
 */
static void dijkstra_print_state(int finalized_vertex) {
    printf("  Finalized: %d. Current state:\n", finalized_vertex);
    printf("  Vertex | Dist | Parent\n");
    printf("  -------|------|-------\n");
    for (int i = 0; i < g_graph.V; i++) {
        printf("  %5d | ", i);
        if (g_dist[i] == INT_MAX) printf(" INF |");
        else printf("%4d |", g_dist[i]);
        if (g_parent[i] == -1) printf("  N/A\n");
        else printf("  %3d\n", g_parent[i]);
    }
}

/**
 * @brief (DIJKSTRA) Prints the final shortest path from source to j.
 */
static void dijkstra_print_path(int j) {
    if (g_parent[j] == -1) { // Base case: source node
        printf("%d", j);
        return;
    }
    dijkstra_print_path(g_parent[j]);
    printf(" -> %d", j);
}

/**
 * @brief (DIJKSTRA) Prints the final computed shortest distances and paths.
 */
static void dijkstra_print_solution(int src) {
    printf("\n--- Final Shortest Paths from Source %d ---\n", src);
    printf("Vertex | Distance | Path\n");
    printf("-------|----------|-----------------\n");
    for (int i = 0; i < g_graph.V; i++) {
        printf("%5d | ", i);
        if (g_dist[i] == INT_MAX) {
            printf("  INF    | Not Reachable\n");
        } else {
            printf("%8d | ", g_dist[i]);
            dijkstra_print_path(i);
            printf("\n");
        }
    }
}

/**
 * @brief (DIJKSTRA) The main algorithm implementation.
 */
static void dijkstra_run() {
    int src;
    printf("Enter source vertex for Dijkstra (0 to %d): ", g_graph.V - 1);
    if(scanf("%d", &src) != 1 || src < 0 || src >= g_graph.V) {
        printf("Invalid source vertex.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    // 1. Initialize dist[], sptSet[], and parent[]
    for (int i = 0; i < g_graph.V; i++) {
        g_dist[i] = INT_MAX;
        g_sptSet[i] = 0; // Not included in shortest path tree yet
        g_parent[i] = -1; // No parent yet
    }
    g_dist[src] = 0; // Distance from source to itself is 0

    printf("\n--- Running Dijkstra from Source %d ---\n", src);
    printf("Initial state:\n");
    dijkstra_print_state(-1); // -1 indicates initial state
    _press_enter_to_continue();


    // 2. Find shortest path for all vertices
    for (int count = 0; count < g_graph.V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices
        // not yet processed. u is always equal to src in the first iteration.
        int u = dijkstra_min_distance_vertex();

        if (u == -1) {
             printf("Error: Could not find minimum distance vertex. Graph might be disconnected.\n");
             break; // Should not happen if graph is connected and weights > 0
        }

        // Mark the picked vertex as processed
        g_sptSet[u] = 1;
        printf("\n--- Iteration %d: Processing Vertex %d ---\n", count + 1, u);

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < g_graph.V; v++) {
            // Update dist[v] only if:
            // 1. v is not in sptSet
            // 2. There is an edge from u to v (weight > 0)
            // 3. Total weight of path from src to v through u is smaller than current value of dist[v]
            if (!g_sptSet[v] && g_graph.adjMatrix[u][v] > 0 &&
                g_dist[u] != INT_MAX && // Check if u is reachable
                g_dist[u] + g_graph.adjMatrix[u][v] < g_dist[v])
            {
                printf("  Updating dist[%d]: %d -> %d (via %d)\n", v, (g_dist[v] == INT_MAX ? -1 : g_dist[v]), g_dist[u] + g_graph.adjMatrix[u][v], u);
                g_parent[v] = u; // Update parent
                g_dist[v] = g_dist[u] + g_graph.adjMatrix[u][v]; // Update distance
            }
        }
        dijkstra_print_state(u);
        _press_enter_to_continue();
    }

    // 3. Print the final solution
    dijkstra_print_solution(src);
}

/**
 * @brief (GRAPH) Initializes the graph for weighted edges.
 * Asks user for V and sets all matrix entries to 0 (no edge).
 */
static void graph_init() {
    int v_num = 0;
    while (v_num <= 0 || v_num > MAX_GRAPH_VERTICES) {
        printf("Enter number of vertices (1 to %d): ", MAX_GRAPH_VERTICES);
        if(scanf("%d", &v_num) != 1) { v_num = 0; }
        clear_input_buffer();
    }
    g_graph.V = v_num;

    // Initialize adjacency matrix to all 0s (no edges)
    for (int i = 0; i < g_graph.V; i++) {
        for (int j = 0; j < g_graph.V; j++) {
            g_graph.adjMatrix[i][j] = 0; // 0 now means no direct edge
        }
    }
    printf("Created a weighted graph with %d vertices (0 to %d).\n", g_graph.V, g_graph.V - 1);
}

/**
 * @brief (GRAPH) Adds a weighted, undirected edge between two vertices.
 */
static void graph_add_edge() {
    int src, dest, weight;
    printf("Enter source vertex (0 to %d): ", g_graph.V - 1);
    if(scanf("%d", &src) != 1 || src < 0 || src >= g_graph.V) {
        printf("Invalid source.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    printf("Enter destination vertex (0 to %d): ", g_graph.V - 1);
    if(scanf("%d", &dest) != 1 || dest < 0 || dest >= g_graph.V) {
        printf("Invalid destination.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    printf("Enter weight for edge %d <-> %d (must be > 0): ", src, dest);
    if(scanf("%d", &weight) != 1 || weight <= 0) {
        printf("Invalid weight. Must be positive.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();


    if (src == dest) {
        printf("Self-loops are not allowed.\n");
        return;
    }

    // Add weighted undirected edge
    g_graph.adjMatrix[src][dest] = weight;
    g_graph.adjMatrix[dest][src] = weight;
    printf("Added undirected edge between %d and %d with weight %d.\n", src, dest, weight);
}

/**
 * @brief (GRAPH) [VISUALIZATION] Prints the weighted adjacency matrix.
 */
static void graph_print_matrix() {
    printf("--- Adjacency Matrix (Weights, 0=No Edge) ---\n");
    printf("   "); // Adjust spacing
    for (int i = 0; i < g_graph.V; i++) {
        printf("%3d", i); // Allocate 3 spaces per column header
    }
    printf("\n  +--");
    for (int i = 0; i < g_graph.V; i++) {
        printf("---");
    }
    printf("\n");

    for (int i = 0; i < g_graph.V; i++) {
        printf("%2d|", i); // Adjust spacing
        for (int j = 0; j < g_graph.V; j++) {
            printf("%3d", g_graph.adjMatrix[i][j]); // Allocate 3 spaces per cell
        }
        printf("\n");
    }
    printf("--------------------------------------------\n"); // Adjust line length
}


// (This code goes into dsa_unit5_graphs.c)

/**
 * @brief (DFS) The core recursive function with explicit stack visualization.
 * @param v The current vertex being visited.
 */
static void dfs_recursive(int v) { // Removed depth parameter

    // --- Visualization: Entering the function (Push) ---
    dfs_vis_push(v);
    printf("\nEntering DFS(%d):\n", v);
    dfs_vis_print_stack();

    // 1. Mark current node as visited
    g_visited[v] = 1;
    sprintf(g_dfs_traversal_order + strlen(g_dfs_traversal_order), " -> %d", v);
    printf(" (Visited)\nExploring neighbors...\n");


    // 2. Recurse for all adjacent, unvisited vertices
    for (int i = 0; i < g_graph.V; i++) {
        // If vertex 'i' is adjacent to 'v' AND 'i' has not been visited
        if (g_graph.adjMatrix[v][i] != 0 && g_visited[i] == 0) {
            printf("  DFS(%d): Found unvisited neighbor %d. Calling DFS(%d).\n", v, i, i);
            dfs_recursive(i); // <<< RECURSIVE CALL
            // --- Visualization: Returning from recursive call ---
            printf("\nReturning to DFS(%d) from DFS(%d):\n", v, i);
            dfs_vis_print_stack(); // Show stack after child returns
        } else if (g_graph.adjMatrix[v][i] != 0 && g_visited[i] != 0) {
             printf("  DFS(%d): Neighbor %d already visited. Skipping.\n", v, i);
        }
    }

    // --- Visualization: Exiting the function (Pop) ---
    printf("\nExiting DFS(%d): All neighbors explored. Backtracking...\n", v);
    dfs_vis_pop();
    dfs_vis_print_stack();
}
// (This code goes into dsa_unit5_graphs.c)

/**
 * @brief (DFS) Wrapper to start the traversal with stack visualization.
 */
// (This code goes into dsa_unit5_graphs.c)

/**
 * @brief (DFS) Wrapper to start the traversal with stack visualization.
 */
static void dfs_run_traversal() {
    int start_vertex;

    printf("Enter start vertex for DFS (0 to %d): ", g_graph.V - 1);
    if(scanf("%d", &start_vertex) != 1 || start_vertex < 0 || start_vertex >= g_graph.V) {
        printf("Invalid start vertex.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    // 1. Reset visited array and VISUALIZATION stack
    for (int i = 0; i < g_graph.V; i++) {
        g_visited[i] = 0;
    }
    dfs_vis_stack_init(); // <<< Initialize the viz stack
    strcpy(g_dfs_traversal_order, "Start");

    printf("\n--- DFS Call Stack Visualization ---\n");
    printf("(Traversal Order will be printed in the end)\n");
    dfs_recursive(start_vertex);

    // --- Traversal Complete ---
    printf("\n\n--- Main Traversal from start node Complete ---\n");
    // (Actual traversal order string construction would ideally happen here)
    // Example (requires modifying dfs_recursive to populate a string):
    // printf("Final Traversal Order: %s\n", traversal_order_string);


    // 3. Check for disconnected components
    printf("\n--- Checking for Disconnected Components ---\n");
    int found_disconnected = 0;
    for (int i = 0; i < g_graph.V; i++) {
        if (g_visited[i] == 0) {
            found_disconnected = 1;
            printf("\nNote: Vertex %d was unreached.\n", i);
            printf("Starting DFS from %d...\n", i);
            dfs_vis_stack_init(); // Re-init stack for this component
            dfs_recursive(i);
            printf("\n--- Disconnected Component Traversal Complete ---\n");
        }
    }
    if (!found_disconnected) {
        printf("No disconnected components found.\n");
    }
    printf("\n--- All Components Traversed ---\n");

    printf("\nFinal Traversal Order:\n%s\n", g_dfs_traversal_order);
}
// --- Main Topic Function (Called by Dispatcher) ---

/**
 * @brief Topic 1: Depth First Search (DFS)
 * This is the main function called by the dispatcher.
 */
void dsa_dfs() {
    int choice;
    
    // 1. Initialize the graph first
    _clear_screen();
    printf("==========================================\n");
    printf("| Depth First Search (DFS) Setup          |\n");
    printf("==========================================\n");
    graph_init();
    _press_enter_to_continue();


    // 2. Main menu
    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Depth First Search (DFS) Menu           |\n");
        printf("==========================================\n");
        graph_print_matrix();
        printf("------------------------------------------\n");
        printf(" 1. Add Undirected Edge\n");
        printf(" 2. Run DFS Traversal\n");
        printf(" 3. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                graph_add_edge();
                _press_enter_to_continue();
                break;
            case 2:
                dfs_run_traversal();
                _press_enter_to_continue();
                break;
            case 3:
                // No need to free, graph is static.
                // In a dynamic version, we'd free the matrix here.
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 3);
}

// (This code goes into dsa_unit5_graphs.c)
// ... (The DFS function and helpers are here) ...

/**
 * @brief Topic 2: Breadth First Search (BFS)
 * This is the main function called by the dispatcher.
 */
void dsa_bfs() {
    int choice;
    
    // 1. Initialize the graph first
    _clear_screen();
    printf("==========================================\n");
    printf("| Breadth First Search (BFS) Setup        |\n");
    printf("==========================================\n");
    // Reuse the same init as DFS
    // IMPORTANT: If you just ran DFS, the graph is already set up.
    // We might want a way to reset it, but for now we'll reuse.
    if (g_graph.V <= 0 || g_graph.V > MAX_GRAPH_VERTICES) {
        printf("Graph not initialized or invalid. Initializing...\n");
         graph_init(); // Initialize if not already done
         _press_enter_to_continue();
    } else {
        printf("Using the graph previously defined (Vertices: %d).\n", g_graph.V);
        printf("You can add more edges if needed.\n");
        _press_enter_to_continue();
    }

    // 2. Main menu
    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Breadth First Search (BFS) Menu         |\n");
        printf("==========================================\n");
        graph_print_matrix();
        printf("------------------------------------------\n");
        printf(" 1. Add Undirected Edge\n");
        printf(" 2. Run BFS Traversal (Visualized)\n");
        printf(" 3. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                graph_add_edge();
                _press_enter_to_continue();
                break;
            case 2:
                bfs_run_traversal();
                _press_enter_to_continue();
                break;
            case 3:
                // No need to free, graph is static.
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 3);
}

// (This code goes into dsa_unit5_graphs.c)
// ... (The BFS function and helpers are here) ...

/**
 * @brief Topic 3: Dijkstra's Shortest Path
 * This is the main function called by the dispatcher.
 */
void dsa_dijkstra() {
    int choice;

    // 1. Initialize/Confirm Graph Setup
    _clear_screen();
    printf("==========================================\n");
    printf("| Dijkstra's Algorithm Setup              |\n");
    printf("==========================================\n");
    if (g_graph.V <= 0 || g_graph.V > MAX_GRAPH_VERTICES) {
        printf("Graph not initialized or invalid. Initializing...\n");
         graph_init(); // Requires weights now
         _press_enter_to_continue();
    } else {
        printf("Using the weighted graph previously defined (Vertices: %d).\n", g_graph.V);
        printf("Ensure edges have weights > 0.\n");
        _press_enter_to_continue();
    }

    // 2. Main menu
    do {
        _clear_screen();
        printf("==========================================\n");
        printf("| Dijkstra's Algorithm Menu               |\n");
        printf("==========================================\n");
        graph_print_matrix();
        printf("------------------------------------------\n");
        printf(" 1. Add/Update Weighted Edge (>0)\n");
        printf(" 2. Run Dijkstra's Algorithm (Visualized)\n");
        printf(" 3. Back to Topics Menu\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        switch (choice) {
            case 1:
                graph_add_edge(); // Now adds weighted edges
                _press_enter_to_continue();
                break;
            case 2:
                dijkstra_run();
                _press_enter_to_continue();
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Please try again.\n");
                _press_enter_to_continue();
        }
    } while (choice != 3);
}