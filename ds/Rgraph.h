#ifndef TSP_RGRAPH_H
#define TSP_RGRAPH_H

#include <bits/stdc++.h>
#include "Graph.h"

class Rnode
{
public:
	int id, queueIndex = 0;
	double lat, lon, dist;
	bool visited;
	Rnode *root = nullptr;
	set<Rnode*, greater<>> mst_edges;
	bool operator<(Rnode &Node) const;
	/* This is just a trick to get the correct order in the set
	 * This operator will order the set by increasing lat and lon */
	bool operator>(const Rnode &Node) const;
	Rnode(int id, double lat, double lon);
};

class Rgraph
{
public:
	Rgraph();
	explicit Rgraph(int V);
	double tsp_triangular();
	double tsp_christofides();
	void min_weight_matching(vi& matches);
	void overlap(vi& matches);
	void euler_tour(vi& path);
	void build_mst(int pos);
	void pre_order(int pos, vi &path, int &count);
	static double haversine(double lat1, double lon1, double lat2, double lon2);
	double dist(int i, int j);

	int V;
	vector<Rnode> nodes;
};

#endif //TSP_RGRAPH_H
