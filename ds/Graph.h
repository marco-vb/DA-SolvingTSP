//
// Created by marco-vb on 05-05-2023.
//

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
	Node *findNode(const int &id) const;
	void addEdge(int, int, double);
	bool addBidirectionalEdge(const int &sourc, const int &dest, double w);
	int getNumNode() const;
	vector<Node *> getNodeSet() const;
	double tsp_exact();
	double tsp_approx_triangular();

	int V;
	vector<Node *> nodes;
	int findNodeIdx(const int &id) const;
	double tsp_exact(int pos, ull mask, double** memo);
	double tsp_approx_triangular(int pos);
	void build_mst(int pos, vi &path);
	void pre_order(int pos, vi &path);
	vvd dist;
};

#endif //TSP_GRAPH_H
