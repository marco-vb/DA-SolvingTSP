#ifndef TSP_GRAPH_H
#define TSP_GRAPH_H

#include <bits/stdc++.h>
#include "NodeEdge.h"

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

class Graph
{
public:
	Graph();
	explicit Graph(int V);
	void addEdge(int, int, double);
	double tsp_exact();
	double tsp_approx_triangular();
	double tsp_exact(int pos, ull mask, double **memo);
	double tsp_approx_triangular(int pos);
	void build_mst(int pos);
	void pre_order(int pos, vi &path);

	int V;
	vector<Node *> nodes;
	vvd dist;
};

#endif //TSP_GRAPH_H
