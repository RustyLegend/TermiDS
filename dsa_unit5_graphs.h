#ifndef DSA_UNIT5_GRAPHS_H
#define DSA_UNIT5_GRAPHS_H
#define MAX_GRAPH_VERTICES 10
#include <limits.h>

void dsa_dfs();

void dsa_bfs();

void dsa_dijkstra();

struct Graph {
    int V;
    int adjMatrix[MAX_GRAPH_VERTICES][MAX_GRAPH_VERTICES];
    int is_weighted;
};


#endif