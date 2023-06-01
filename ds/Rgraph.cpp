#include "Rgraph.h"

Rnode::Rnode(int id, double lat, double lon) :
		id(id), lat(lat), lon(lon), dist(0), visited(false)
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
		if (v->root) { v->root->mst_edges.insert(v); }

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
		pre_order(w->id, path, count);
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

double Rgraph::tsp_christofides()
{
	int odd = 0;
	vi degree(V, 0);
	build_mst(0);

	for (Rnode &v: nodes) {
		for (Rnode* w: v.mst_edges) { w->mst_edges.insert(&v); }  // make MST undirected
	}

	for (int i = 0; i < V; i++) {
		degree[i] = (int) nodes[i].mst_edges.size();
		if (degree[i] % 2) { odd++; }
	}

	Rgraph g(odd);

	for (int i = 0; i < V; i++) {
		if (degree[i] % 2) { g.nodes.emplace_back(i, nodes[i].lat, nodes[i].lon); }
	}

	vi matching(V, -1);
	g.min_weight_matching(matching);
	overlap(matching);    // add edges from matching to MST
	vi path;
	euler_tour(path); // find euler tour

	vi visited(V, 0);
	visited[path[0]] = 1;
	double ans = 0;

	for (int i = 0; i < (int) path.size() - 1; i++) {
		if (!visited[path[i + 1]]) {
			ans += dist(path[i], path[i + 1]);
			visited[path[i + 1]] = 1;
		}
	}

	ans += dist(path.back(), path[0]);
	return ans;
}

void Rgraph::min_weight_matching(vi &matches)
{
	for (auto &node: nodes) {
		vd distances(V, INF);
		vi parents(V, -1);
		vi in_queue(V, 0);

		queue<int> q;
		q.push(node.id);
		distances[node.id] = 0;
		in_queue[node.id] = 1;

		while (!q.empty()) {
			int u = q.front();
			q.pop();
			in_queue[u] = 0;

			for (auto &w: nodes) {
				if (u == w.id) continue;
				int v = w.id;
				double d = dist(u, v);

				if (d < distances[v]) {
					distances[v] = d;
					parents[v] = u;
					if (!in_queue[v]) {
						q.push(v);
						in_queue[v] = 1;
					}
				}
			}
		}

		int v = node.id;
		while (parents[v] != -1) {
			int next = parents[v];
			matches[next] = v;
			matches[v] = next;
			v = matches[next];
		}
	}
}

void Rgraph::overlap(vi &matches)
{
	for (int i = 0; i < V; i++) {
		if (matches[i] == -1) continue;
		nodes[i].mst_edges.insert(&nodes[matches[i]]);
	}
}

void Rgraph::euler_tour(vi &path)
{
	vi visited(V, 0);
	stack<int> s;
	s.push(0);

	while (!s.empty()) {
		int u = s.top();
		s.pop();

		if (visited[u]) continue;
		visited[u] = 1;
		path.push_back(u);

		for (Rnode* w: nodes[u].mst_edges) {
			s.push(w->id);
		}
	}
}
