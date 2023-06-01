#include "NodeEdge.h"

TNode::TNode(int id) : id(id), indegree(0)
{}

Edge *TNode::addEdge(TNode *d, double w)
{
	auto newEdge = new Edge(this, d, w);
	adj.push_back(newEdge);
	d->incoming.push_back(newEdge);
	this->indegree++;
	d->indegree++;
	return newEdge;
}

bool TNode::removeEdge(int destID)
{
	bool removedEdge = false;
	auto it = adj.begin();
	while (it != adj.end()) {
		Edge *edge = *it;
		TNode *dest = edge->getDest();
		if (dest->getId() == destID) {
			it = adj.erase(it);
			auto it2 = dest->incoming.begin();
			while (it2 != dest->incoming.end()) {
				if ((*it2)->getOrig()->getId() == id) {
					it2 = dest->incoming.erase(it2);
				} else {
					it2++;
				}
			}
			delete edge;
			removedEdge = true;
		} else {
			it++;
		}
	}
	return removedEdge;
}

bool TNode::operator<(TNode &Node) const
{
	return this->dist < Node.dist;
}

int TNode::getId() const
{
	return this->id;
}

std::vector<Edge *> TNode::getAdj() const
{
	return this->adj;
}

bool TNode::isVisited() const
{
	return this->visited;
}

bool TNode::isProcessing() const
{
	return this->processing;
}

unsigned int TNode::getIndegree() const
{
	return this->indegree;
}

double TNode::getDist() const
{
	return this->dist;
}

Edge *TNode::getPath() const
{
	return this->path;
}

std::vector<Edge *> TNode::getIncoming() const
{
	return this->incoming;
}

void TNode::setId(int id)
{
	this->id = id;
}

void TNode::setVisited(bool visited)
{
	this->visited = visited;
}

void TNode::setProcesssing(bool proc)
{
	this->processing = proc;
}

void TNode::setIndegree(unsigned int in)
{
	this->indegree = in;
}

void TNode::setDist(double d)
{
	this->dist = d;
}

void TNode::setPath(Edge *p)
{
	this->path = p;
}

Edge::Edge(TNode *orig, TNode *dest, double w) : orig(orig), dest(dest), weight(w)
{}

TNode *Edge::getDest() const
{
	return this->dest;
}

double Edge::getWeight() const
{
	return this->weight;
}

TNode *Edge::getOrig() const
{
	return this->orig;
}

Edge *Edge::getReverse() const
{
	return this->reverse;
}

bool Edge::isSelected() const
{
	return this->selected;
}

void Edge::setSelected(bool sel)
{
	this->selected = sel;
}

void Edge::setReverse(Edge *rev)
{
	this->reverse = rev;
}
