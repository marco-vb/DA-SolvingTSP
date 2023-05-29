#ifndef TSP_NODEEDGE_H
#define TSP_NODEEDGE_H

#include <bits/stdc++.h>
#include "Heap.h"

#define INF 1e11

using namespace std;

class Edge;

class Node
{
public:
	explicit Node(int id);
	bool operator<(Node &Node) const;
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
	Edge *addEdge(Node *dest, double w);
	bool removeEdge(int destID);

	friend class Heap<Node>;

	int id;
	std::vector<Edge *> adj;
	bool visited = false;
	bool processing = false;
	unsigned int indegree;
	double dist = 0;
	Edge *path = nullptr;
	std::vector<Edge *> incoming;
	int queueIndex = 0;
};

class Edge
{
public:
	Edge(Node *orig, Node *dest, double w);
	Node *getDest() const;
	double getWeight() const;
	bool isSelected() const;
	Node *getOrig() const;
	Edge *getReverse() const;
	void setSelected(bool selected);
	void setReverse(Edge *rev);

	Node *dest;
	double weight;
	bool selected = false;
	Node *orig;
	Edge *reverse = nullptr;
};

#endif //TSP_NODEEDGE_H
