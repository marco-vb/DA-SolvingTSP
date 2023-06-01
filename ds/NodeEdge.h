#ifndef TSP_NODEEDGE_H
#define TSP_NODEEDGE_H

#include <bits/stdc++.h>
#include "Heap.h"

#define INF 1e11

using namespace std;

class Edge;

class TNode
{
public:
	explicit TNode(int id);
	bool operator<(TNode &Node) const;
	int getId() const;
	std::vector<Edge *> getAdj() const;
	bool isVisited() const;
	bool isProcessing() const;
	unsigned int getIndegree() const;
	double getDist() const;
	Edge *getPath() const;
	std::vector<Edge *> getIncoming() const;
	void setId(int info);
	void setVisited(bool visited);
	void setProcesssing(bool proc);
	void setIndegree(unsigned int in);
	void setDist(double d);
	void setPath(Edge *p);
	Edge *addEdge(TNode *dest, double w);
	bool removeEdge(int destID);

	friend class Heap<TNode>;

	int id;
	std::vector<Edge *> adj;
	bool visited = false;
	bool processing = false;
	unsigned int indegree;
	double dist = 0;
	double lat, lon;
	Edge *path = nullptr;
	std::vector<Edge *> incoming;
	int queueIndex = 0;
};

class Edge
{
public:
	Edge(TNode *orig, TNode *dest, double w);
	TNode *getDest() const;
	double getWeight() const;
	bool isSelected() const;
	TNode *getOrig() const;
	Edge *getReverse() const;
	void setSelected(bool selected);
	void setReverse(Edge *rev);

	TNode *dest;
	double weight;
	bool selected = false;
	TNode *orig;
	Edge *reverse = nullptr;
};

#endif //TSP_NODEEDGE_H
