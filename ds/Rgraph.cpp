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

Rgraph::Rgraph() : V(0)
{}

Rgraph::Rgraph(int V) : V(V)
{
	nodes.reserve(V);
	mst_edges.resize(V);
}

double Rgraph::tsp_triangular()
{
	vi path(V);
	build_mst(0);

	for (auto node: nodes) { node->visited = false; }
	int count = 0;
	pre_order(0, path, count);
	while (count < V) {
		auto next = nearest_neighbor(path[count - 1]);
		path[count++] = next;
	}

	double ans = 0;
	for (int i = 0; i < V - 1; i++) ans += dist(path[i], path[i + 1]);
	ans += dist(path[path.back()], path[0]);

	return ans;
}

void Rgraph::build_mst(int pos)
{
	Heap<Rnode> q;

	for (auto v: nodes) {
		v->dist = INF;
		v->visited = false;
		q.insert(v);
	}

	nodes[pos]->dist = 0;
	q.decreaseKey(nodes[pos]);

	while (!q.empty()) {
		auto v = q.extractMin();
		v->visited = true;

		if (v->root) {
			mst_edges[v->root->id].push_back(v->id);
			mst_edges[v->id].push_back(v->root->id);
		}

		for (auto &edge: v->adj) {
			auto node = nodes[edge->dest];
			if (node->visited) { continue; }
			double d = edge->weight;
			if (d < node->dist) {
				node->dist = d;
				node->root = v;
				q.decreaseKey(node);
			}
		}
	}
}

void Rgraph::pre_order(int pos, vi &path, int &count)
{
	nodes[pos]->visited = true;
	path[count++] = pos;

	sort(mst_edges[pos].begin(), mst_edges[pos].end(), [&](int i, int j)
	{
		if (nodes[i]->lat == nodes[j]->lat) { return nodes[i]->lon < nodes[j]->lon; }
		return nodes[i]->lat < nodes[j]->lat;
	});

	for (auto &e: mst_edges[pos]) {
		auto w = nodes[e];
		if (!w->visited) { pre_order(w->id, path, count); }
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
//	static int count = 1;
	for (auto &edge: nodes[i]->adj) {
		if (edge->dest == j) { return edge->weight; }
	}
//	cout << "Using haversine distance for " << count++ << "th time" << endl;
	return haversine(nodes[i]->lat, nodes[i]->lon, nodes[j]->lat, nodes[j]->lon);
}

double Rgraph::tsp_christofides()
{
	vi degree(V, 0), matching(V, -1), path;
	build_mst(0);

	for (Rnode*&v: nodes) {
		degree[v->id] = (int) mst_edges[v->id].size();
		if (degree[v->id] % 2) { v->visited = false; }
		else { v->visited = true; }
	}

	min_weight_matching(matching); // find min weight matching
	overlap(matching);    // add edges from matching to MST
	euler_tour(path); // find euler tour

	vi visited(V, 0);
	visited[path[0]] = 1;
	double ans = 0;

	int i = 0, n = (int) path.size();
	for (; i < n - 1; i++) {
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
		if (node->visited || matches[node->id] != -1) continue;
		int nearest = nearest_neighbor(node->id);
		matches[node->id] = nearest;
		matches[nearest] = node->id;
		node->visited = true;
		nodes[nearest]->visited = true;
	}
}

void Rgraph::overlap(vi &matches)
{
	for (int i = 0; i < V; i++) {
		if (matches[i] == -1) continue;
		mst_edges[i].push_back(matches[i]);
	}
}

void Rgraph::euler_tour(vi &path)
{
	std::stack<int> stack;
	stack.push(0);

	while (!stack.empty()) {
		int u = stack.top();

		if (mst_edges[u].empty()) {
			stack.pop();
			path.push_back(u);
		} else {
			Rnode* v = nodes[*mst_edges[u].begin()];
			mst_edges[u].erase(mst_edges[u].begin());
			mst_edges[v->id].erase(std::find(mst_edges[v->id].begin(), mst_edges[v->id].end(), u));
			stack.push(v->id);
		}
	}

	// Reverse the tour to get the correct order
	std::reverse(path.begin(), path.end());
}

double Rgraph::tsp_nearest()
{
	for (int i = 0; i < V; i++) { nodes[i]->visited = false; }

	vi path(V);
	path[0] = 0;
	nodes[0]->visited = true;

	for (int i = 1; i < V; i++) {
		int min_pos = nearest_neighbor(path[i - 1]);
		path[i] = min_pos;
		nodes[min_pos]->visited = true;
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
		if (pos == i || nodes[i]->visited) continue;
		double d = dist(pos, i);
		if (d < min_dist) {
			min_dist = d;
			min_pos = i;
		}
	}
	return min_pos;
}

Redge::Redge(int dest, double w) :
		dest(dest), weight(w)
{
}
