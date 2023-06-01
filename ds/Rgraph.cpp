#include "Rgraph.h"

Rnode::Rnode(int id, double lat, double lon) :
		id(id), lat(lat), lon(lon), dist(0), visited(false)
{}

Rnode::Rnode(const Rnode &Node) :
		id(Node.id), lat(Node.lat), lon(Node.lon), dist(Node.dist), visited(Node.visited)
{}

bool Rnode::operator<(Rnode &Node) const
{
	return this->dist < Node.dist;
}

bool Rnode::operator>(const Rnode &Node) const
{
	if (this->lat == Node.lat) { return this->lon < Node.lon; }
	return this->lat < Node.lat;
}

Rgraph::Rgraph() : V(0)
{}

Rgraph::Rgraph(int V) : V(V)
{
	nodes.reserve(V);
}

double Rgraph::tsp_triangular()
{
	vi path(V);
	build_mst(0);

	int count = 0;
	pre_order(0, path, count);

	double ans = 0;
	for (int i = 0; i < V - 1; i++) ans += dist(path[i], path[i + 1]);
	ans += dist(path[path.back()], path[0]);

	return ans;
}

void Rgraph::build_mst(int pos)
{
	Heap<Rnode> q;

	for (auto &v: nodes) {
		v.dist = INF;
		v.visited = false;
		q.insert(&v);
	}

	nodes[pos].dist = 0;
	nodes[pos].root = nullptr;
	q.decreaseKey(&nodes[pos]);

	while (!q.empty()) {
		auto v = q.extractMin();
		v->visited = true;
		if (v->root) { v->root->mst_edges.insert(*v); }

		for (auto &node: nodes) {
			if (v->id == node.id || node.visited) continue;
			double d = dist(v->id, node.id);
			if (d < node.dist) {
				node.dist = d;
				node.root = v;
				q.decreaseKey(&node);
			}
		}
	}
}

void Rgraph::pre_order(int pos, vi &path, int &count)
{
	path[count++] = pos;
	auto neighbours = nodes[pos].mst_edges;
	for (auto &w: neighbours) {
		pre_order(w.id, path, count);
	}
}

double Rgraph::haversine(double lat1, double lon1, double lat2, double lon2)
{
	double dLat = (lat2 - lat1) * M_PI / 180.0;
	double dLon = (lon2 - lon1) * M_PI / 180.0;

	lat1 = lat1 * M_PI / 180.0;
	lat2 = lat2 * M_PI / 180.0;

	double a = pow(sin(dLat / 2), 2) +
	           pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
	double rad = 6371000;
	double c = 2 * asin(sqrt(a));
	return rad * c;
}

double Rgraph::dist(int i, int j)
{
	return haversine(nodes[i].lat, nodes[i].lon, nodes[j].lat, nodes[j].lon);
}

double Rgraph::tsp_nearest()
{
	for (int i = 0; i < V; i++) { nodes[i].visited = false; }

	vi path(V);
	path[0] = 0;
	nodes[0].visited = true;

	for (int i = 1; i < V; i++) {
		int min_pos = nearest_neighbor(path[i - 1]);
		path[i] = min_pos;
		nodes[min_pos].visited = true;
	}

	double ans = 0;
	for (int i = 0; i < V - 1; i++) ans += dist(path[i], path[i + 1]);
	ans += dist(path[path.back()], path[0]);

	return ans;
}

int Rgraph::nearest_neighbor(int pos)
{
	double min_dist = INF;
	int min_pos = -1;
	for (int i = 0; i < V; i++) {
		if (pos == i || nodes[i].visited) continue;
		double d = dist(pos, i);
		if (d < min_dist) {
			min_dist = d;
			min_pos = i;
		}
	}
	return min_pos;
}
