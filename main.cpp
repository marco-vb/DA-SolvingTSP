#include <bits/stdc++.h>
#include "ds/Graph.h"

#define EDGES true
#define NO_EDGES false

bool firstTime, graphToy;
int graphNumber;
void startingScreen();
void menu();
void changeGraph();
void changeGraphNumber();
void backtrakingAlgorithm();
void triangularAlgorithm();
void otherHeuristics();
void clearScreen();
void wait();

void readRNodes(Graph &g, const string &nodes_file)
{
	ifstream nodes(nodes_file);
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
		g.nodes.emplace_back(new Node(id, lat, lon));
	}
}

void readREdges(Graph &g, const string &edges_file)
{
	ifstream edges(edges_file);
	string line;
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
		ss.ignore(numeric_limits<streamsize>::max(), '\n');
		g.nodes[src]->adj.emplace_back(new Edge(dest, weight));
		g.nodes[dest]->adj.emplace_back(new Edge(src, weight));
	}
}

void ReadREdgesOnly(Graph &g, const string &edges_file, int V)
{
	g = Graph(V);
	for (int i = 0; i < V; i++) { g.nodes.emplace_back(new Node(i, 0, 0)); }
	ifstream edges(edges_file);
	string line;

	while (getline(edges, line)) {
		stringstream ss(line);
		int src, dest;
		double weight;
		ss >> src;
		ss.ignore();
		ss >> dest;
		ss.ignore();
		ss >> weight;
		ss.ignore(numeric_limits<streamsize>::max(), '\n');
		g.nodes[src]->adj.emplace_back(new Edge(dest, weight));
		g.nodes[dest]->adj.emplace_back(new Edge(src, weight));
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	Graph r1, r2, r3;
	clock_t start, end;

	cout << "Exact Algorithm:\n";
	ReadREdgesOnly(r1, "../csv/Toy-Graphs/shipping.csv", 14);
	ReadREdgesOnly(r2, "../csv/Toy-Graphs/stadiums.csv", 11);
	ReadREdgesOnly(r3, "../csv/Toy-Graphs/tourism.csv", 5);
	start = clock();
	cout << "Shipping: " << r1.tsp_exact() << endl;
	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	cout << "Stadiums: " << r2.tsp_exact() << endl;
	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	cout << "Tourism: " << r3.tsp_exact() << endl;
	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

	vi files = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};
	for (int n: files) {
		Graph r, _r;
		string edges_file = "../csv/Extra-Graphs/edges_" + to_string(n) + ".csv";
		ReadREdgesOnly(r, edges_file, n);
		ReadREdgesOnly(_r, edges_file, n);
		start = clock();
		cout << "Cristiano Ronaldo " << n << ": " << (int) r.tsp_christofides(EDGES) / 1000 << " Km" << endl;
		end = clock();
		cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
		start = clock();
		cout << "Triangle Chest " << n << ": " << (int) _r.tsp_triangular(EDGES) / 1000 << " Km" << endl;
		end = clock();
		cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
	}

	cout << "My Algorithms:\n";
	cout << "Triangular:\n";
	readRNodes(r1, "../csv/Real-World-Graphs/graph1/nodes.csv");
	readREdges(r1, "../csv/Real-World-Graphs/graph1/edges.csv");
	readRNodes(r2, "../csv/Real-World-Graphs/graph2/nodes.csv");
	readREdges(r2, "../csv/Real-World-Graphs/graph2/edges.csv");
	readRNodes(r3, "../csv/Real-World-Graphs/graph3/nodes.csv");
	readREdges(r3, "../csv/Real-World-Graphs/graph3/edges.csv");
	start = clock();
	cout << "Real 1:\n" << (int) r1.tsp_triangular(NO_EDGES) / 1000 << " Km" << endl;
	cout << "Real 2:\n" << (int) r2.tsp_triangular(NO_EDGES) / 1000 << " Km" << endl;
	cout << "Real 3:\n" << (int) r3.tsp_triangular(NO_EDGES) / 1000 << " Km" << endl;
	end = clock();
	cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;

	cout << "My Heuristics:\n";
	cout << "Christofides:\n";
	readRNodes(r1, "../csv/Real-World-Graphs/graph1/nodes.csv");
	readREdges(r1, "../csv/Real-World-Graphs/graph1/edges.csv");
	readRNodes(r2, "../csv/Real-World-Graphs/graph2/nodes.csv");
	readREdges(r2, "../csv/Real-World-Graphs/graph2/edges.csv");
	readRNodes(r3, "../csv/Real-World-Graphs/graph3/nodes.csv");
	readREdges(r3, "../csv/Real-World-Graphs/graph3/edges.csv");
	start = clock();
	cout << "Real 1:\n" << (int) r1.tsp_christofides(NO_EDGES) / 1000 << " Km" << endl;
	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	cout << "Real 2:\n" << (int) r2.tsp_christofides(NO_EDGES) / 1000 << " Km" << endl;
	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	start = clock();
	cout << "Real 3:\n" << (int) r3.tsp_christofides(NO_EDGES) / 1000 << " Km" << endl;
	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

	cout << "Nearest Neighbor:\n";
	readRNodes(r1, "../csv/Real-World-Graphs/graph1/nodes.csv");
	readRNodes(r2, "../csv/Real-World-Graphs/graph2/nodes.csv");
	readRNodes(r3, "../csv/Real-World-Graphs/graph3/nodes.csv");
	start = clock();
	cout << "Real 1:\n" << (int) r1.tsp_nearest() / 1000 << " Km" << endl;
	cout << "Real 2:\n" << (int) r2.tsp_nearest() / 1000 << " Km" << endl;
	cout << "Real 3:\n" << (int) r3.tsp_nearest() / 1000 << " Km" << endl;
	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

	return 0;
}

//system("Color 0B");
/*
	firstTime = true;

	startingScreen();
	changeGraph();
	*/


void startingScreen()
{

	clearScreen();
	std::cout << "  ===========================================================================  " << std::endl;
	std::cout << R"(//                                                                           \\)" << std::endl;
	std::cout << "||    ##        ##  ######  ##      #####    #####  ####     ####  ######    ||" << std::endl;
	std::cout << "||    ##   ##   ##  ##      ##     ##   ##  ##  ##  ## ##   ## ##  ##        ||" << std::endl;
	std::cout << "||    ##   ##   ##  ####    ##     ##       ##  ##  ##  ## ##  ##  ####      ||" << std::endl;
	std::cout << "||     ## #### ##   ##      ##     ##   ##  ##  ##  ##   ###   ##  ##        ||" << std::endl;
	std::cout << "||      ###  ###    ######  #####   #####   #####   ##         ##  ######    ||" << std::endl;
	std::cout << "||                                                                           ||" << std::endl;
	std::cout << "||                                       .                                   ||" << std::endl;
	std::cout << "||              . .                     -:-             .  .  .              ||" << std::endl;
	std::cout << R"(||            .'.:,'.        .  .  .     ' .           . \ | / .             ||)" << std::endl;
	std::cout << R"(||            .'.;.`.       ._. ! ._.       \          .__\:/__.             ||)" << std::endl;
	std::cout << R"(||             `,:.'         ._\!/_.                      .';`.      . ' .   ||)" << std::endl;
	std::cout << "||             ,'             . ! .        ,.,      ..======..       .:.     ||" << std::endl;
	std::cout << "||            ,                 .         ._!_.     ||::: : | .        ',    ||" << std::endl;
	std::cout << "||     .====.,                  .           ;  .~.===: : : :|   ..===.       ||" << std::endl;
	std::cout << R"(||     |.::'||      .=====.,    ..=======.~,   |"|: :|::::::|   ||:::|=====| ||)" << std::endl;
	std::cout << R"(||  ___| :::|!__.,  |:::::|!_,   |: :: ::|"|l_l|"|:: |:;;:::|___!| ::|: : :| ||)" << std::endl;
	std::cout << R"(|| |: :|::: |:: |!__|; :: |: |===::: :: :|"||_||"| : |: :: :|: : |:: |:::::| ||)" << std::endl;
	std::cout << R"(|| |:::| _::|: :|:::|:===:|::|:::|:===F=:|"!/|\!"|::R|:====:|::_:|: :|:7__:| ||)" << std::endl;
	std::cout << R"(|| !_[]![_]_!_[]![]_!_[__]![]![_]![_][I_]!//_:_\\![]I![_][_]!_[_]![]_!_[__]! ||)" << std::endl;
	std::cout << R"(|| -----------------------------------"---''''```---"----------------------- ||)" << std::endl;
	std::cout << "|| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |= _ _:_ _ =| _ _ _ _ _ _ _ _ _ _ _ _ ||" << std::endl;
	std::cout << R"(||    D - M - P         \ō͡≡o˞̶        |=    :    =|                G05_6    ||)" << std::endl;
	std::cout << "|| ____________________________________L___________J________________________ ||" << std::endl;
	std::cout << "|| ------------------------------------------------------------------------- ||" << std::endl;
	std::cout << "||                                                                           ||" << std::endl;
	std::cout << "||                      --- Press Enter to Continue ---                      ||" << std::endl;
	std::cout << R"(\\                                                                           //)" << std::endl;
	std::cout << "  ===========================================================================  " << std::endl;
	wait();
}

void changeGraph()
{

	string option;

	if (firstTime) {
		do {
			clearScreen();
			std::cout << "  ===========================================================================  " << std::endl;
			std::cout << R"(//                                                                           \\)" << std::endl;
			std::cout << "||             #####  #####   ######   #####   ##  ######  ##  ##            ||" << std::endl;
			std::cout << "||            ##      ##  ##  ##      ##   ##  ##  ##      ##  ##            ||" << std::endl;
			std::cout << "||             ####   #####   ####    ##       ##  ####     ####             ||" << std::endl;
			std::cout << "||                ##  ##      ##      ##   ##  ##  ##        ##              ||" << std::endl;
			std::cout << "||            #####   ##      ######   #####   ##  ##        ##              ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||   ######  ##  ##  ######        #####    #####    ####   #####   ##  ##   ||" << std::endl;
			std::cout << "||     ##    ##  ##  ##           ###       ##  ##  ##  ##  ##  ##  ##  ##   ||" << std::endl;
			std::cout << "||     ##    ######  ####         ##  ####  #####   ######  #####   ######   ||" << std::endl;
			std::cout << "||     ##    ##  ##  ##           ##   ##   ##  ##  ##  ##  ##      ##  ##   ||" << std::endl;
			std::cout << "||     ##    ##  ##  ######        #####    ##  ##  ##  ##  ##      ##  ##   ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||    [1] Toy Graphs                                                         ||" << std::endl;
			std::cout << "||    [2] Real Life Graphs                                                   ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << R"(\\                                                                           //)" << std::endl;
			std::cout << "  ===========================================================================  " << std::endl;
			wait();

			std::cout << "  > ";
			std::getline(std::cin >> std::ws, option);

			if (option == "1") {
				graphToy = true;
				changeGraphNumber();
			} else if (option == "2") {
				graphToy = false;
				changeGraphNumber();
			} else {
				clearScreen();
				std::cout << "  > Invalid Option!" << std::endl;
				std::cout << "  > Press Enter to Continue..." << std::endl;
				wait();
			}
		} while (option != "1" && option != "2");
	} else {
		do {
			clearScreen();
			std::cout << "  ===========================================================================  " << std::endl;
			std::cout << R"(//                                                                           \\)"
			          << std::endl;
			std::cout << "||             #####  #####   ######   #####   ##  ######  ##  ##            ||" << std::endl;
			std::cout << "||            ##      ##  ##  ##      ##   ##  ##  ##      ##  ##            ||" << std::endl;
			std::cout << "||             ####   #####   ####    ##       ##  ####     ####             ||" << std::endl;
			std::cout << "||                ##  ##      ##      ##   ##  ##  ##        ##              ||" << std::endl;
			std::cout << "||            #####   ##      ######   #####   ##  ##        ##              ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||   ######  ##  ##  ######        #####    #####    ####   #####   ##  ##   ||" << std::endl;
			std::cout << "||     ##    ##  ##  ##           ###       ##  ##  ##  ##  ##  ##  ##  ##   ||" << std::endl;
			std::cout << "||     ##    ######  ####         ##  ####  #####   ######  #####   ######   ||" << std::endl;
			std::cout << "||     ##    ##  ##  ##           ##   ##   ##  ##  ##  ##  ##      ##  ##   ||" << std::endl;
			std::cout << "||     ##    ##  ##  ######        #####    ##  ##  ##  ##  ##      ##  ##   ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||    [1] Toy Graphs                                                         ||" << std::endl;
			std::cout << "||    [2] Real Life Graphs                                                   ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                                                                [0] Back   ||" << std::endl;
			std::cout << R"(\\                                                                           //)"
			          << std::endl;
			std::cout << "  ===========================================================================  " << std::endl;
			wait();

			std::cout << "  > ";
			std::getline(std::cin >> std::ws, option);

			if (option == "1") {
				graphToy = true;
				changeGraphNumber();
			} else if (option == "2") {
				graphToy = false;
				changeGraphNumber();
			} else if (option == "0") {
				menu();
			} else {
				clearScreen();
				std::cout << "  > Invalid Option!" << std::endl;
				std::cout << "  > Press Enter to Continue..." << std::endl;
				wait();
			}
		} while (option != "1" && option != "2" && option != "0");
	}
}

void menu()
{

	string option;

	do {
		clearScreen();
		std::cout << "  ===========================================================================  " << std::endl;
		std::cout << R"(//                                                                           \\)" << std::endl;
		std::cout << "||                           ######   #####  #####                           ||" << std::endl;
		std::cout << "||                             ##    ##      ##  ##                          ||" << std::endl;
		std::cout << "||                  #####      ##     ####   #####     #####                 ||" << std::endl;
		std::cout << "||                             ##        ##  ##                              ||" << std::endl;
		std::cout << "||                             ##    #####   ##                              ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||    #####   #####    #####  #####   ##      ######  ####   ####   #####    ||" << std::endl;
		std::cout << "||    ##  ##  ##  ##  ##  ##  ##  ##  ##      ##      ## ## ## ##  ##        ||" << std::endl;
		std::cout << "||    #####   #####   ##  ##  #####   ##      ####    ##  ###  ##   ####     ||" << std::endl;
		std::cout << "||    ##      ##  ##  ##  ##  ##  ##  ##      ##      ##       ##      ##    ||" << std::endl;
		std::cout << "||    ##      ##  ##  #####   #####   ######  ######  ##       ##  #####     ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		if (graphToy) {
			std::cout << "||                            --- Toy Graph ---                              ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                            --- Graph nº " << graphNumber << " ---                             ||"
			          << std::endl;
		} else {
			std::cout << "||                         --- Real Life Graph ---                           ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||                            --- Graph nº " << graphNumber << " ---                             ||"
			          << std::endl;
		}
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||    [1] Backtracking Algorithm                                             ||" << std::endl;
		std::cout << "||    [2] Triangular Approximation Heuristic                                 ||" << std::endl;
		std::cout << "||    [3] Other Heuristic                                                    ||" << std::endl;
		std::cout << "||    [4] Change Graph                                                       ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                [0] Exit   ||" << std::endl;
		std::cout << R"(\\                                                                           //)" << std::endl;
		std::cout << "  ===========================================================================  " << std::endl;
		wait();

		std::cout << "  > ";
		std::getline(std::cin >> std::ws, option);

		if (option == "1") {
			//backtrakingAlgorithm();
		} else if (option == "2") {
			//triangularAlgorithm();
		} else if (option == "3") {
			//otherHeuristics();
		} else if (option == "4") {
			changeGraph();
		} else if (option == "0") {
			break;
		} else {
			clearScreen();
			std::cout << "  > Invalid Option!" << std::endl;
			std::cout << "  > Press Enter to Continue..." << std::endl;
			wait();
		}
	} while (option != "1" && option != "2" && option != "3" && option != "4" && option != "0");

}

void changeGraphNumber()
{
	string option;
	do {
		clearScreen();
		std::cout << "  ===========================================================================  " << std::endl;
		std::cout << R"(//                                                                           \\)"
		          << std::endl;

		if (graphToy) {
			std::cout << "||                           ######   #####  ##  ##                          ||" << std::endl;
			std::cout << "||                             ##    ##  ##  ##  ##                          ||" << std::endl;
			std::cout << "||                             ##    ##  ##   ####                           ||" << std::endl;
			std::cout << "||                             ##    ##  ##    ##                            ||" << std::endl;
			std::cout << "||                             ##    #####     ##                            ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||               #####    #####    ####   #####   ##  ##   #####             ||" << std::endl;
			std::cout << "||              ###       ##  ##  ##  ##  ##  ##  ##  ##  ##                 ||" << std::endl;
			std::cout << "||              ##  ####  #####   ######  #####   ######   ####              ||" << std::endl;
			std::cout << "||              ##   ##   ##  ##  ##  ##  ##      ##  ##      ##             ||" << std::endl;
			std::cout << "||               #####    ##  ##  ##  ##  ##      ##  ##  #####              ||" << std::endl;
		} else {
			std::cout << "||      #####   ######   ####   ##           ##      ##  ######  ######      ||" << std::endl;
			std::cout << "||      ##  ##  ##      ##  ##  ##           ##      ##  ##      ##          ||" << std::endl;
			std::cout << "||      #####   ####    ######  ##           ##      ##  ####    ####        ||" << std::endl;
			std::cout << "||      ##  ##  ##      ##  ##  ##           ##      ##  ##      ##          ||" << std::endl;
			std::cout << "||      ##  ##  ######  ##  ##  ######       ######  ##  ##      ######      ||" << std::endl;
			std::cout << "||                                                                           ||" << std::endl;
			std::cout << "||               #####    #####    ####   #####   ##  ##   #####             ||" << std::endl;
			std::cout << "||              ###       ##  ##  ##  ##  ##  ##  ##  ##  ##                 ||" << std::endl;
			std::cout << "||              ##  ####  #####   ######  #####   ######   ####              ||" << std::endl;
			std::cout << "||              ##   ##   ##  ##  ##  ##  ##      ##  ##      ##             ||" << std::endl;
			std::cout << "||               #####    ##  ##  ##  ##  ##      ##  ##  #####              ||" << std::endl;
		}

		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||    [1] Graph - 1                                                          ||" << std::endl;
		std::cout << "||    [2] Graph - 2                                                          ||" << std::endl;
		std::cout << "||    [3] Graph - 3                                                          ||" << std::endl;
		std::cout << "||                                                                           ||" << std::endl;
		std::cout << "||                                                                [0] Back   ||" << std::endl;
		std::cout << R"(\\                                                                           //)"
		          << std::endl;
		std::cout << "  ===========================================================================  " << std::endl;
		wait();

		std::cout << "  > ";
		std::getline(std::cin >> std::ws, option);

		if (option == "1") {
			graphNumber = 1;
			firstTime = false;
			menu();
		} else if (option == "2") {
			graphNumber = 2;
			firstTime = false;
			menu();
		} else if (option == "3") {
			graphNumber = 3;
			firstTime = false;
			menu();
		} else if (option == "0") {
			changeGraph();
		} else {
			clearScreen();
			std::cout << "  > Invalid Option!" << std::endl;
			std::cout << "  > Press Enter to Continue..." << std::endl;
			wait();
		}
	} while (option != "1" && option != "2" && option != "3" && option != "0");
}

void clearScreen()
{
	for (int i = 0; i < 50; i++) {
		std::cout << std::endl;
	}
}

void wait()
{
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();
}
