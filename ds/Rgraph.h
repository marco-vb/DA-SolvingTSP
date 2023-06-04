#ifndef TSP_RGRAPH_H
#define TSP_RGRAPH_H

#include <bits/stdc++.h>
#include "Graph.h"

class Redge
{
public:
	Redge(int dest, double w);
	int dest;
	double weight;
};

class Rnode
{
public:
	int id, queueIndex = 0;
	double lat, lon, dist;
	bool visited;
	Rnode* root = nullptr;
	vector<Redge*> adj;
	bool operator<(Rnode &Node) const;
	Rnode(int id, double lat, double lon);
	// copy constructor
	Rnode(const Rnode &Node);
};

class Rgraph
{
public:
	Rgraph();
	explicit Rgraph(int V);
	~Rgraph();
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
	vector<Rnode*> nodes;
	vector<vector<int>> mst_edges;
};

#endif //TSP_RGRAPH_H
