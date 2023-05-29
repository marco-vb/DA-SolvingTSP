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

int main()
{
	Graph g1, g2, g3;
	readToyGraph(g1, "../csv/Toy-Graphs/shipping.csv");
	readToyGraph(g2, "../csv/Toy-Graphs/stadiums.csv");
	readToyGraph(g3, "../csv/Toy-Graphs/tourism.csv");
	cout << "Shipping: " << g1.tsp_exact() << endl;
	cout << "Stadiums: " << g2.tsp_exact() << endl;
	cout << "Tourism: " << g3.tsp_exact() << endl;
	return 0;
}
