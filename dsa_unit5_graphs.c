#include "dsa_unit5_graphs.h"
#include "dsa_common.h"

static struct Graph g_graph;
static int g_visited[MAX_GRAPH_VERTICES];

#define BFS_QUEUE_SIZE MAX_GRAPH_VERTICES
static int g_bfs_queue[BFS_QUEUE_SIZE];
static int g_bfs_front = 0;
static int g_bfs_rear = -1;
static int g_bfs_count = 0;

#define DFS_STACK_SIZE MAX_GRAPH_VERTICES
static int g_dfs_vis_stack[DFS_STACK_SIZE];
static int g_dfs_vis_top = -1;
static char g_dfs_traversal_order[MAX_GRAPH_VERTICES * 5 + 10];

static void dfs_vis_stack_init() {
    g_dfs_vis_top = -1;
}

static void dfs_vis_push(int item) {
    if (g_dfs_vis_top < DFS_STACK_SIZE - 1) {
        g_dfs_vis_stack[++g_dfs_vis_top] = item;
    }
}

static void dfs_vis_pop() {
    if (g_dfs_vis_top > -1) {
        g_dfs_vis_top--;
    }
}

static void dfs_vis_print_stack() {
    printf("  DFS Stack: [ ");
    if (g_dfs_vis_top > -1) {
        for (int i = 0; i <= g_dfs_vis_top; i++) {
            printf("%d ", g_dfs_vis_stack[i]);
        }
    }
    printf("] (top is %d)\n", (g_dfs_vis_top > -1 ? g_dfs_vis_stack[g_dfs_vis_top] : -1));
}

static void bfs_queue_init() {
    g_bfs_front = 0;
    g_bfs_rear = -1;
    g_bfs_count = 0;
}

static int bfs_queue_is_empty() {
    return g_bfs_count == 0;
}

static void bfs_enqueue(int item) {
    if (g_bfs_count < BFS_QUEUE_SIZE) {
        g_bfs_rear = (g_bfs_rear + 1) % BFS_QUEUE_SIZE;
        g_bfs_queue[g_bfs_rear] = item;
        g_bfs_count++;
    }
}

static int bfs_dequeue() {
    if (!bfs_queue_is_empty()) {
        int item = g_bfs_queue[g_bfs_front];
        g_bfs_front = (g_bfs_front + 1) % BFS_QUEUE_SIZE;
        g_bfs_count--;
        return item;
    }
    return -1;
}

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

static void bfs_run_traversal() {
    int start_vertex;
    char traversal_order[MAX_GRAPH_VERTICES * 5 + 10]; 

    printf("Enter start vertex for BFS (0 to %d): ", g_graph.V - 1);
    if(scanf("%d", &start_vertex) != 1 || start_vertex < 0 || start_vertex >= g_graph.V) {
        printf("Invalid start vertex.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    for (int i = 0; i < g_graph.V; i++) {
        g_visited[i] = 0;
    }
    bfs_queue_init();

    printf("\n--- BFS Traversal Steps ---\n");
    strcpy(traversal_order, "Start"); 

    sprintf(traversal_order + strlen(traversal_order), " -> %d", start_vertex); 
    
    printf("Visited: %d\n", start_vertex);
    g_visited[start_vertex] = 1;
    bfs_enqueue(start_vertex);
    printf("Initial Queue: "); bfs_print_queue();

    while (!bfs_queue_is_empty()) {
        int u = bfs_dequeue();
        printf("\nDequeued: %d. Exploring neighbors...\n", u);

        for (int v = 0; v < g_graph.V; v++) {
            if (g_graph.adjMatrix[u][v] == 1 && g_visited[v] == 0) {
                sprintf(traversal_order + strlen(traversal_order), " -> %d", v); 
                
                printf("  Visited: %d\n", v);
                g_visited[v] = 1;
                bfs_enqueue(v);
                bfs_print_queue();
            }
        }
    }
    printf("\n--- Traversal Complete ---\n");

    printf("\n--- Traversal for this component finished ---\n");

    printf("\nFinal Traversal Order:\n%s\n", traversal_order); 
}

static int g_dist[MAX_GRAPH_VERTICES];
static int g_sptSet[MAX_GRAPH_VERTICES];
static int g_parent[MAX_GRAPH_VERTICES];

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

static void dijkstra_print_path(int j) {
    if (g_parent[j] == -1) {
        printf("%d", j);
        return;
    }
    dijkstra_print_path(g_parent[j]);
    printf(" -> %d", j);
}

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

static void dijkstra_run() {
    int src;
    printf("Enter source vertex for Dijkstra (0 to %d): ", g_graph.V - 1);
    if(scanf("%d", &src) != 1 || src < 0 || src >= g_graph.V) {
        printf("Invalid source vertex.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    for (int i = 0; i < g_graph.V; i++) {
        g_dist[i] = INT_MAX;
        g_sptSet[i] = 0;
        g_parent[i] = -1;
    }
    g_dist[src] = 0;

    printf("\n--- Running Dijkstra from Source %d ---\n", src);
    printf("Initial state:\n");
    dijkstra_print_state(-1);
    _press_enter_to_continue();

    for (int count = 0; count < g_graph.V - 1; count++) {
        int u = dijkstra_min_distance_vertex();

        if (u == -1) {
             printf("Error: Could not find minimum distance vertex. Graph might be disconnected.\n");
             break;
        }

        g_sptSet[u] = 1;
        printf("\n--- Iteration %d: Processing Vertex %d ---\n", count + 1, u);

        for (int v = 0; v < g_graph.V; v++) {
            if (!g_sptSet[v] && g_graph.adjMatrix[u][v] > 0 &&
                g_dist[u] != INT_MAX &&
                g_dist[u] + g_graph.adjMatrix[u][v] < g_dist[v])
            {
                printf("  Updating dist[%d]: %d -> %d (via %d)\n", v, (g_dist[v] == INT_MAX ? -1 : g_dist[v]), g_dist[u] + g_graph.adjMatrix[u][v], u);
                g_parent[v] = u;
                g_dist[v] = g_dist[u] + g_graph.adjMatrix[u][v];
            }
        }
        dijkstra_print_state(u);
        _press_enter_to_continue();
    }

    dijkstra_print_solution(src);
}

static void graph_init(int is_weighted) {
    int v_num = 0;
    while (v_num <= 0 || v_num > MAX_GRAPH_VERTICES) {
        printf("Enter number of vertices (1 to %d): ", MAX_GRAPH_VERTICES);
        if(scanf("%d", &v_num) != 1) { v_num = 0; }
        clear_input_buffer();
    }
    g_graph.V = v_num;
    g_graph.is_weighted = is_weighted;
    for (int i = 0; i < g_graph.V; i++) {
        for (int j = 0; j < g_graph.V; j++) {
            g_graph.adjMatrix[i][j] = 0;
        }
    }
    if (is_weighted) {
        printf("Created a new WEIGHTED graph with %d vertices (0 to %d).\n", g_graph.V, g_graph.V - 1);
    } else {
        printf("Created a new UNWEIGHTED graph with %d vertices (0 to %d).\n", g_graph.V, g_graph.V - 1);
    }
}

static void graph_confirm_or_create(int needs_weighted) {
    if (g_graph.V > 0 && g_graph.V <= MAX_GRAPH_VERTICES) {
        _clear_screen();
        printf("==========================================\n");
        printf("| Existing Graph Found                    |\n");
        printf("==========================================\n");
        printf("A graph with %d vertices already exists.\n", g_graph.V);

        if (g_graph.is_weighted && !needs_weighted) {
            printf("\nWARNING: This existing graph is WEIGHTED.\n");
            printf("You are entering an UNWEIGHTED module (DFS/BFS).\n");
            printf("This may fail if edges are not 1.\n");
        } else if (!g_graph.is_weighted && needs_weighted) {
            printf("\nWARNING: This existing graph is UNWEIGHTED.\n");
            printf("You are entering a WEIGHTED module (Dijkstra).\n");
            printf("Weights will be treated as 1.\n");
        }

        printf("------------------------------------------\n");
        printf(" 1. Use existing graph\n");
        printf(" 2. Create a new graph (discards old one)\n");
        printf("------------------------------------------\n");
        printf("Enter your choice: ");

        int choice;
        if (scanf("%d", &choice) != 1) { choice = -1; }
        clear_input_buffer();

        if (choice == 2) {
            printf("Creating a new graph...\n");
            graph_init(needs_weighted);
        } else {
            printf("Using existing graph.\n");
            if (g_graph.is_weighted != needs_weighted) {
                 printf("Warning: Mismatched graph type. Results may be incorrect.\n");
                 g_graph.is_weighted = needs_weighted;
            }
        }

    } else {
        printf("No valid graph found. Creating a new one...\n");
        graph_init(needs_weighted);
    }
    _press_enter_to_continue();
}

static void graph_add_edge_weighted() {
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

    g_graph.adjMatrix[src][dest] = weight;
    g_graph.adjMatrix[dest][src] = weight;
    printf("Added undirected edge between %d and %d with weight %d.\n", src, dest, weight);
}

static void graph_add_edge_unweighted() {
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

    printf("Enter weight for edge %d <-> %d (must be 1 for unweighted): ", src, dest);
    if(scanf("%d", &weight) != 1) {
        printf("Invalid input.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    if (weight != 1) {
        printf("\nError: Weight must be 1 for unweighted graphs (DFS/BFS).\n");
        printf("Edge not added. Please use a weight of 1.\n");
        return;
    }

    if (src == dest) {
        printf("Self-loops are not allowed.\n");
        return;
    }

    g_graph.adjMatrix[src][dest] = 1;
    g_graph.adjMatrix[dest][src] = 1;
    printf("Added unweighted edge between %d and %d.\n", src, dest);
}

static void graph_print_matrix() {
    printf("--- Adjacency Matrix (Weights, 0=No Edge) ---\n");
    printf("   ");
    for (int i = 0; i < g_graph.V; i++) {
        printf("%3d", i);
    }
    printf("\n  +--");
    for (int i = 0; i < g_graph.V; i++) {
        printf("---");
    }
    printf("\n");

    for (int i = 0; i < g_graph.V; i++) {
        printf("%2d|", i);
        for (int j = 0; j < g_graph.V; j++) {
            printf("%3d", g_graph.adjMatrix[i][j]);
        }
        printf("\n");
    }
    printf("--------------------------------------------\n");
}

static void dfs_recursive(int v) {

    dfs_vis_push(v);
    printf("\nEntering DFS(%d):\n", v);
    dfs_vis_print_stack();

    g_visited[v] = 1;
    sprintf(g_dfs_traversal_order + strlen(g_dfs_traversal_order), " -> %d", v);
    printf(" (Visited)\nExploring neighbors...\n");

    for (int i = 0; i < g_graph.V; i++) {
        if (g_graph.adjMatrix[v][i] == 1 && g_visited[i] == 0) {
            printf("  DFS(%d): Found unvisited neighbor %d. Calling DFS(%d).\n", v, i, i);
            dfs_recursive(i);
            printf("\nReturning to DFS(%d) from DFS(%d):\n", v, i);
            dfs_vis_print_stack();
        } else if (g_graph.adjMatrix[v][i] == 1 && g_visited[i] != 0) {
             printf("  DFS(%d): Neighbor %d already visited. Skipping.\n", v, i);
        }
    }

    printf("\nExiting DFS(%d): All neighbors explored. Backtracking...\n", v);
    dfs_vis_pop();
    dfs_vis_print_stack();
}

static void dfs_run_traversal() {
    int start_vertex;

    printf("Enter start vertex for DFS (0 to %d): ", g_graph.V - 1);
    if(scanf("%d", &start_vertex) != 1 || start_vertex < 0 || start_vertex >= g_graph.V) {
        printf("Invalid start vertex.\n"); clear_input_buffer(); return;
    }
    clear_input_buffer();

    for (int i = 0; i < g_graph.V; i++) {
        g_visited[i] = 0;
    }
    dfs_vis_stack_init();
    strcpy(g_dfs_traversal_order, "Start");

    printf("\n--- DFS Call Stack Visualization ---\n");
    printf("(Traversal Order will be printed at the end)\n");

    dfs_recursive(start_vertex);

    printf("\n\n--- Traversal from start node Complete ---\n");

    printf("\nFinal Traversal Order:\n%s\n", g_dfs_traversal_order);
}

void dsa_dfs() {
    int choice;
    
    graph_confirm_or_create(0);

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
                graph_add_edge_unweighted();
                _press_enter_to_continue();
                break;
            case 2:
                dfs_run_traversal();
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

void dsa_bfs() {
    int choice;
    
    graph_confirm_or_create(0);

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
                graph_add_edge_unweighted();
                _press_enter_to_continue();
                break;
            case 2:
                bfs_run_traversal();
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

void dsa_dijkstra() {
    int choice;

    graph_confirm_or_create(1);

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
                graph_add_edge_weighted();
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