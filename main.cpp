#include <bits/stdc++.h>

#include "ds/Graph.h"

void readGraph(Graph &g, const string &filename) {
    ifstream input(filename);
    int V; input >> V; input.ignore();
    g = Graph(V);
    string line;
    getline(input, line); // skip first line

    while (getline(input, line)) {
        stringstream ss(line);
        int src, dest;
        double weight;
        ss >> src; ss.ignore();
        ss >> dest; ss.ignore();
        ss >> weight;
        g.addEdge(src, dest, weight);
    }
}

int main() {
    Graph g;
    readGraph(g, "../csv/Toy-Graphs/shipping.csv");
    cout << g.tsp_exact() << endl;
    return 0;
}
