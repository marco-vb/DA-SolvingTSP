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
    Edge e = {dest, weight};
    nodes[src].adj.push_back(e);
    Edge rev = {src, weight};
    nodes[dest].adj.push_back(rev);
    dist[src][dest] = dist[dest][src] = weight;
}

double Graph::tsp_exact() {
    auto **memo = new double*[V];
    for (int i = 0; i < V; i++) {
        memo[i] = new double[1 << V];
        for (int j = 0; j < (1 << V); j++) memo[i][j] = -1;
    }

    double ans = tsp_exact(0, 1, memo);

    for (int i = 0; i < V; i++) delete[] memo[i];
    delete[] memo;

    return ans;
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

double Graph::tsp_approx_triangular() {
    return tsp_approx_triangular(0);
}

double Graph::tsp_approx_triangular(int pos) {
    vi path;
    build_mst(pos, path);
    
    double ans = 0;
    for (int i = 0; i < V; i++) ans += dist[path[i]][path[i + 1]];
    ans += dist[path[path.back()]][path[0]];
    
    return ans;
}

void Graph::build_mst(int pos, vi &path) {
    for (auto &node : nodes) {
        node.visited = false;
        node.dist = INF;
        for (auto &edge : node.adj) edge.in_mst = false;
    }

    priority_queue<di, vector<di>, greater<>> pq;
    nodes[pos].dist = 0;    // dist to itself is 0
    pq.push({0, pos});

    while (!pq.empty()) {
        auto top = pq.top(); pq.pop();
        auto node = nodes[top.second];

        if (node.visited) continue;
        node.visited = true;

        for (auto &edge : node.adj) {
            auto dest = nodes[edge.dest];
            if (dest.visited) continue;
            if (edge.weight < dest.dist) {
                dest.dist = edge.weight;
                pq.push({dest.dist, dest.id});
                edge.in_mst = true;
            }
        }
    }

    pre_order(pos, path);
}

void Graph::pre_order(int pos, vi &path) {
    path.push_back(pos);
    for (auto &edge : nodes[pos].adj) {
        if (edge.in_mst) {
            pre_order(edge.dest, path);
        }
    }
}
