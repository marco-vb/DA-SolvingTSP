#include "NodeEdge.h"

Node::Node(int id) : id(id), indegree(0)
{}

Edge *Node::addEdge(Node *d, double w)
{
	auto newEdge = new Edge(this, d, w);
	adj.push_back(newEdge);
	d->incoming.push_back(newEdge);
	this->indegree++;
	d->indegree++;
	return newEdge;
}

bool Node::removeEdge(int destID)
{
	bool removedEdge = false;
	auto it = adj.begin();
	while (it != adj.end()) {
		Edge *edge = *it;
		Node *dest = edge->getDest();
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

bool Node::operator<(Node &Node) const
{
	return this->dist < Node.dist;
}

int Node::getId() const
{
	return this->id;
}

std::vector<Edge *> Node::getAdj() const
{
	return this->adj;
}

bool Node::isVisited() const
{
	return this->visited;
}

bool Node::isProcessing() const
{
	return this->processing;
}

unsigned int Node::getIndegree() const
{
	return this->indegree;
}

double Node::getDist() const
{
	return this->dist;
}

Edge *Node::getPath() const
{
	return this->path;
}

std::vector<Edge *> Node::getIncoming() const
{
	return this->incoming;
}

void Node::setId(int id)
{
	this->id = id;
}

void Node::setVisited(bool visited)
{
	this->visited = visited;
}

void Node::setProcesssing(bool proc)
{
	this->processing = proc;
}

void Node::setIndegree(unsigned int in)
{
	this->indegree = in;
}

void Node::setDist(double d)
{
	this->dist = d;
}

void Node::setPath(Edge *p)
{
	this->path = p;
}

Edge::Edge(Node *orig, Node *dest, double w) : orig(orig), dest(dest), weight(w)
{}

Node *Edge::getDest() const
{
	return this->dest;
}

double Edge::getWeight() const
{
	return this->weight;
}

Node *Edge::getOrig() const
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
