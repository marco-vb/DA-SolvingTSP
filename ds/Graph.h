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
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef vector<vd> vvd;


struct Edge {
    int src, dest;
    double weight;
};

struct Node {
    int id;
    bool visited;
    list<Edge> adj;
};

class Graph {
private:
    vector<Node> nodes;
    int V;
    vvd dist;

public:
    Graph();
    Graph(int V);
    void addEdge(int src, int dest, double weight = 1);
    double tsp_exact();
    double tsp_exact(int src);
    double tsp_approx_triangular();
    double tsp_approx_triangular(int src);

protected:
    double tsp_exact(int pos, ull mask, double **memo);
};


#endif //TSP_GRAPH_H
