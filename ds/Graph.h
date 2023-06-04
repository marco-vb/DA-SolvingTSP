#ifndef TSP_GRAPH_H
#define TSP_GRAPH_H

#include <bits/stdc++.h>
#include "Heap.h"

class Edge
{
public:
	Edge(int dest, double w);
	int dest;
	double weight;
};

class Node
{
public:
	int id, queueIndex = 0;
	double lat, lon, dist;
	bool visited;
	Node* root = nullptr;
	vector<Edge*> adj;
	bool operator<(Node &Node) const;
	Node(int id, double lat, double lon);
	// copy constructor
	Node(const Node &Node);
};

class Graph
{
public:
	Graph();
	explicit Graph(int V);
	~Graph();
	double tsp_exact();
	double tsp_exact(int pos, ull mask, vvd &memo, const vvd &dist);
	double tsp_triangular(bool edges = false);
	double tsp_christofides(bool edges = false);
	void min_weight_matching(vi &matches);
	void overlap(vi &matches);
	void euler_tour(vi &path);
	double tsp_nearest();
	void build_mst(int pos);
	void build_mst_no_edges(int pos);
	void pre_order(int pos, vi &path, int &count);
	int nearest_neighbor(int pos);
	static double haversine(double lat1, double lon1, double lat2, double lon2);
	double dist(int i, int j);

	int V;
	vector<Node*> nodes;
	vector<vector<int>> mst_edges;
};

#endif //TSP_GRAPH_H
