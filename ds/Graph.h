//
// Created by marco-vb on 05-05-2023.
//

#ifndef TSP_GRAPH_H
#define TSP_GRAPH_H

#include <bits/stdc++.h>

#define INF 1e11

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> ii;
typedef pair<double, int> di;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;


struct Edge {
    int dest;
    double weight;
    bool in_mst = false;
};

struct Node {
    int id;
    bool visited;
    list<Edge> adj;
    double dist = INF;
};

class Graph {
private:
    vector<Node> nodes;
    int V;
    vvd dist;

public:
    Graph();
    explicit Graph(int V);
    void addEdge(int src, int dest, double weight = 1);
    double tsp_exact();
    double tsp_approx_triangular();

protected:
    double tsp_exact(int pos, ull mask, double **memo);
    double tsp_approx_triangular(int pos);
    void build_mst(int pos, vi& path);
    void pre_order(int pos, vi& path);
};


#endif //TSP_GRAPH_H
