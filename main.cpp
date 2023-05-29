#include <bits/stdc++.h>

#include "ds/Graph.h"

void readToyGraph(Graph &g, const string &filename)
{
	ifstream input(filename);
	int V;
	input >> V;
	input.ignore(numeric_limits<streamsize>::max(), '\n');
	g = Graph(V);
	string line;
	getline(input, line); // skip first line

	while (getline(input, line)) {
		stringstream ss(line);
		int src, dest;
		double weight;
		ss >> src;
		ss.ignore();
		ss >> dest;
		ss.ignore();
		ss >> weight;
		g.addEdge(src, dest, weight);
	}
}

void readRealGraph(Graph& g, const string& nodes_file, const string& edges_file)
{
	ifstream nodes(nodes_file);
	ifstream edges(edges_file);
	int V;
	nodes >> V;
	nodes.ignore(numeric_limits<streamsize>::max(), '\n');
	g = Graph(V);
	string line;
	getline(nodes, line); // skip first line

	while (getline(nodes, line)) {
		stringstream ss(line);
		int id;
		double lat, lon;
		ss >> id;
		ss.ignore();
		ss >> lat;
		ss.ignore();
		ss >> lon;
		g.nodes[id]->lat = lat;
		g.nodes[id]->lon = lon;
	}

	getline(edges, line); // skip first line
	while (getline(edges, line)) {
		stringstream ss(line);
		int src, dest;
		double weight;
		ss >> src;
		ss.ignore();
		ss >> dest;
		ss.ignore();
		ss >> weight;
		g.addEdge(src, dest, weight);
	}
}

int main()
{
	Graph g1, g2, g3;
//	readToyGraph(g1, "../csv/Toy-Graphs/shipping.csv");
//	readToyGraph(g2, "../csv/Toy-Graphs/stadiums.csv");
//	readToyGraph(g3, "../csv/Toy-Graphs/tourism.csv");
//	cout << "Shipping: " << g1.tsp_exact() << endl;
//	cout << "Stadiums: " << g2.tsp_approx_triangular() << endl;
//	cout << "Tourism: " << g3.tsp_approx_triangular() << endl;
	readRealGraph(g1, "../csv/Real-World-Graphs/graph1/nodes.csv", "../csv/Real-World-Graphs/graph1/edges.csv");
	cout << "Real 1:\n" << g1.tsp_approx_triangular() << endl;
	readRealGraph(g1, "../csv/Real-World-Graphs/graph2/nodes.csv", "../csv/Real-World-Graphs/graph2/edges.csv");
	cout << "Real 2:\n" << g1.tsp_approx_triangular() << endl;
	readRealGraph(g1, "../csv/Real-World-Graphs/graph3/nodes.csv", "../csv/Real-World-Graphs/graph3/edges.csv");
	cout << "Real 3:\n" << g1.tsp_approx_triangular() << endl;
	return 0;
}
