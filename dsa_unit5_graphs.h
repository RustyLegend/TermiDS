#ifndef DSA_UNIT5_GRAPHS_H
#define DSA_UNIT5_GRAPHS_H
#define MAX_GRAPH_VERTICES 10
#include <limits.h>
// --- Function Prototypes for Unit 5 ---

// Topic: Depth First Search (DFS)
void dsa_dfs();

// Topic: Breadth First Search (BFS)
void dsa_bfs();

// Topic: Dijkstra's Shortest Path
void dsa_dijkstra();

struct Graph {
    int V; // Number of vertices
    int adjMatrix[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES];
};

#endif // DSA_UNIT5_GRAPHS_H