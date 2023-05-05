//
// Created by marco-vb on 05-05-2023.
//

#include "Graph.h"

Graph::Graph() {
    this->V = 0;
}

Graph::Graph(int V) {
    this->V = V;
    this->nodes = vector<Node>(V);
    for (int i = 0; i < V; i++) {
        nodes[i].id = i;
        nodes[i].visited = false;
    }
    this->dist = vvd(V, vd(V, 0));
}

void Graph::addEdge(int src, int dest, double weight) {
    Edge e = {src, dest, weight};
    nodes[src].adj.push_back(e);
    nodes[dest].adj.push_back(e);
    dist[src][dest] = dist[dest][src] = weight;
}

double Graph::tsp_exact() {
    auto **memo = new double*[V];
    for (int i = 0; i < V; i++) {
        memo[i] = new double[1 << V];
        for (int j = 0; j < (1 << V); j++) {
            memo[i][j] = -1;
        }
    }
    return tsp_exact(0, 1, memo);
}

double Graph::tsp_exact(int pos, ull mask, double **memo) {
    if (memo[pos][mask] != -1) return memo[pos][mask];

    double ans = INF, tmp;

    if (mask == (1 << V) - 1) return dist[pos][0];

    for (int i = 0; i < V; i++) {
        if (dist[pos][i] == 0) continue;    // no edge or self
        if (!(mask & (1 << i))) {
            tmp = dist[pos][i] + tsp_exact(i, mask | (1 << i), memo);
            ans = min(ans, tmp);
        }
    }

    return memo[pos][mask] = ans;
}
