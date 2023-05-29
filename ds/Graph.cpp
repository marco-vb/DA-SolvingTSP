#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include "Graph.h"

Graph::Graph()
{
	this->V = 0;
	this->nodes = vector<Node*>();
}

Graph::Graph(int V)
{
	this->V = V;
	this->dist = vvd(V, vd(V, 0));
	this->nodes = vector<Node*>(V);
	for (int i = 0; i < V; i++) { nodes[i] = new Node(i); }
}

void Graph::addEdge(int src, int dest, double weight)
{
	auto v1 = nodes[src];
	auto v2 = nodes[dest];
	if (!v1 || !v2) throw invalid_argument("Node not found");

	v1->addEdge(v2, weight);
	v2->addEdge(v1, weight);
	dist[src][dest] = dist[dest][src] = weight;
}

double Graph::tsp_exact()
{
	auto** memo = new double* [V];
	for (int i = 0; i < V; i++) {
		memo[i] = new double[1 << V];
		for (int j = 0; j < (1 << V); j++) memo[i][j] = -1;
	}

	double ans = tsp_exact(0, 1, memo);

	for (int i = 0; i < V; i++) delete[] memo[i];
	delete[] memo;

	return ans;
}

double Graph::tsp_exact(int pos, ull mask, double** memo)
{
	if (memo[pos][mask] != -1) return memo[pos][mask];

	double ans = INF, tmp;

	if (mask == (1 << V) - 1) {
		return dist[pos][0] > 0 ? dist[pos][0] : INF;
	}

	for (int i = 0; i < V; i++) {
		if (dist[pos][i] == 0) continue;    // no edge or self
		if (!(mask & (1 << i))) {
			tmp = dist[pos][i] + tsp_exact(i, mask | (1 << i), memo);
			ans = min(ans, tmp);
		}
	}

	return memo[pos][mask] = ans;
}

double Graph::tsp_approx_triangular()
{
	return tsp_approx_triangular(0);
}

double Graph::tsp_approx_triangular(int pos)
{
	vi path;
	build_mst(pos);
	pre_order(pos, path);

	double ans = 0;
	for (int i = 0; i < V - 1; i++) ans += dist[path[i]][path[i + 1]];
	ans += dist[path[path.back()]][path[0]];

	return ans;
}

void Graph::build_mst(int pos)
{
	Heap<Node> q;

	for (auto &v: nodes) {
		v->setDist(INF);
		v->setVisited(false);
		q.insert(v);
	}

	nodes[pos]->setDist(0);
	q.decreaseKey(nodes[pos]);

	while (!q.empty()) {
		auto v = q.extractMin();
		v->setVisited(true);
		for (auto &e: v->getAdj()) {
			auto w = e->getDest();
			if (!w->isVisited() && e->getWeight() < w->getDist()) {
				w->setDist(e->getWeight());
				w->setPath(e);
				q.decreaseKey(w);
			}
		}
	}
}

void Graph::pre_order(int pos, vi &path)
{
	path.push_back(pos);
	auto v = nodes[pos];
	for (auto &edge: v->getAdj()) {
		auto w = edge->getDest();
		if (w->getPath() == edge) {
			pre_order(w->getId(), path);
		}
	}
}

#pragma clang diagnostic pop