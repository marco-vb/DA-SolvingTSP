/**
 * @file main.cpp
 * @brief This file contains the main entry point for the TSP application.
 */

#include <bits/stdc++.h>
#include "ds/Graph.h"

#define EDGES true
#define NO_EDGES false

void startingScreen();

void menu();

void backtrakingAlgorithm();

void triangularAlgorithm();

void nearestNeighborAlgorithm();

void christofidesAlgorithm();

void clearScreen();

void wait();

void readRNodes(Graph &g, const string &nodes_file) {
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

void readREdges(Graph &g, const string &edges_file) {
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

void ReadREdgesOnly(Graph &g, const string &edges_file, int V) {
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

int main() {

    system("Color 0B");
    startingScreen();
    menu();

    return 0;
}





void startingScreen() {

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

void menu() {

    string option;

    do {
        clearScreen();
        std::cout << "  ===========================================================================  " << std::endl;
        std::cout << R"(//                                                                           \\)"
                  << std::endl;
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
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||    [1] Backtracking Algorithm                                             ||" << std::endl;
        std::cout << "||    [2] Triangular Approximation Heuristic                                 ||" << std::endl;
        std::cout << "||    [3] Nearest Neighbor Algorithm Heuristic                               ||" << std::endl;
        std::cout << "||    [4] Christofides Algorithm Heuristic                                   ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                [0] Exit   ||" << std::endl;
        std::cout << R"(\\                                                                           //)"
                  << std::endl;
        std::cout << "  ===========================================================================  " << std::endl;


        std::cout << "  > ";
        std::getline(std::cin >> std::ws, option);

        if (option == "1") {
            backtrakingAlgorithm();
        } else if (option == "2") {
            triangularAlgorithm();
        } else if (option == "3") {
            nearestNeighborAlgorithm();
        } else if (option == "4") {
            christofidesAlgorithm();
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



// BackTracking Algorithm Menu
void backtrakingAlgorithm() {

    std::string option;

    do {
        clearScreen();
        std::cout << "  ===========================================================================  " << std::endl;
        std::cout << R"(//                                                                           \\)"
                  << std::endl;
        std::cout << "||                       #####    ####    ####   ##  ##                      ||" << std::endl;
        std::cout << "||                       ##  ##  ##  ##  ##  ##  ## ##                       ||" << std::endl;
        std::cout << "||                       #####   ######  ##      ####                        ||" << std::endl;
        std::cout << "||                       ##  ##  ##  ##  ##  ##  ## ##                       ||" << std::endl;
        std::cout << "||                       #####   ##  ##   ####   ##  ##                      ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||        ######  #####    ####    ####   ##  ##  ##  ##  ##   #####         ||" << std::endl;
        std::cout << "||          ##    ##  ##  ##  ##  ##  ##  ## ##   ##  ### ##  ###            ||" << std::endl;
        std::cout << "||          ##    #####   ######  ##      ####    ##  ## ###  ##  ####       ||" << std::endl;
        std::cout << "||          ##    ##  ##  ##  ##  ##  ##  ## ##   ##  ##  ##  ##   ##        ||" << std::endl;
        std::cout << "||          ##    ##  ##  ##  ##   ####   ##  ##  ##  ##  ##   #####         ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                             (Only Toy Graphs)                             ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||    [1] Run Algorithm                                                      ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                [0] Back   ||" << std::endl;
        std::cout << R"(\\                                                                           //)"
                  << std::endl;
        std::cout << "  ===========================================================================  " << std::endl;


        std::cout << "  > ";
        std::getline(std::cin >> std::ws, option);

        if (option == "1") {

            Graph r1, r2, r3;
            clock_t start, end;

            clearScreen();

            cout << "Exact Algorithm:\n";
            ReadREdgesOnly(r1, "../csv/Toy-Graphs/shipping.csv", 14);
            ReadREdgesOnly(r2, "../csv/Toy-Graphs/stadiums.csv", 11);
            ReadREdgesOnly(r3, "../csv/Toy-Graphs/tourism.csv", 5);
            start = clock();
            cout << "Shipping: " << r1.tsp_exact() << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            start = clock();
            cout << "Stadiums: " << r2.tsp_exact() << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            start = clock();
            cout << "Tourism: " << r3.tsp_exact() << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;

            cout << endl;
            cout << "Press Enter to Continue..." << endl;

            wait();

            menu();

        } else if (option == "0") {
            menu();
        } else {
            clearScreen();
            std::cout << "  > Invalid Option!" << std::endl;
            std::cout << "  > Press Enter to Continue..." << std::endl;
            wait();
        }
    } while (option != "1"  && option != "0");
}


// Triangulation Algorithm Menu
void triangularAlgorithm() {

    std::string option;

    do {
        clearScreen();
        std::cout << "  ===========================================================================  " << std::endl;
        std::cout << R"(//                                                                           \\)"
                  << std::endl;
        std::cout << "|| ###### #####   ##   ####   ##  ##   #####   ##  ##  ##      ####   #####  ||" << std::endl;
        std::cout << "||   ##   ##  ##  ##  ##  ##  ### ##  ###      ##  ##  ##     ##  ##  ##  ## ||" << std::endl;
        std::cout << "||   ##   #####   ##  ######  ## ###  ##  #### ##  ##  ##     ######  #####  ||" << std::endl;
        std::cout << "||   ##   ##  ##  ##  ##  ##  ##  ##  ##   ##  ##  ##  ##     ##  ##  ##  ## ||" << std::endl;
        std::cout << "||   ##   ##  ##  ##  ##  ##  ##  ##   #####    ####   ###### ##  ##  ##  ## ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                ####   #####  #####   #####    #####  ##   ##              ||" << std::endl;
        std::cout << "||               ##  ##  ##  ## ##  ##  ##  ##  ##  ##   ## ##               ||" << std::endl;
        std::cout << "||               ######  #####  #####   #####   ##  ##    ###                ||" << std::endl;
        std::cout << "||               ##  ##  ##     ##      ##  ##  ##  ##   ## ##               ||" << std::endl;
        std::cout << "||               ##  ##  ##     ##      ##  ##  #####   ##   ##              ||" << std::endl;
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
        std::cout << "||    [1] Run Algorithm with Real World Graphs                               ||" << std::endl;
        std::cout << "||    [2] Run Algorithm with Extra Graphs                                    ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                [0] Back   ||" << std::endl;
        std::cout << R"(\\                                                                           //)"
                  << std::endl;
        std::cout << "  ===========================================================================  " << std::endl;


        std::cout << "  > ";
        std::getline(std::cin >> std::ws, option);

        if (option == "1") {

            Graph r1, r2, r3;
            clock_t start, end;

            clearScreen();

            cout << "My Algorithms:\n";
            cout << "Triangular Approx:\n";
            readRNodes(r1, "../csv/Real-World-Graphs/graph1/nodes.csv");
            readREdges(r1, "../csv/Real-World-Graphs/graph1/edges.csv");
            readRNodes(r2, "../csv/Real-World-Graphs/graph2/nodes.csv");
            readREdges(r2, "../csv/Real-World-Graphs/graph2/edges.csv");
            readRNodes(r3, "../csv/Real-World-Graphs/graph3/nodes.csv");
            readREdges(r3, "../csv/Real-World-Graphs/graph3/edges.csv");
            start = clock();
            cout << "Real 1:\n" << (int) r1.tsp_triangular(NO_EDGES) / 1000 << " Km" << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            start = clock();
            cout << "Real 2:\n" << (int) r2.tsp_triangular(NO_EDGES) / 1000 << " Km" << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            start = clock();
            cout << "Real 3:\n" << (int) r3.tsp_triangular(NO_EDGES) / 1000 << " Km" << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;

            cout << endl;
            cout << "Press Enter to Continue..." << endl;

            wait();

            menu();

        } else if (option == "2") {

            clock_t start, end;

            clearScreen();

            vi files = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};
            for (int n: files) {
                Graph r, _r;
                string edges_file = "../csv/Extra-Graphs/edges_" + to_string(n) + ".csv";
                ReadREdgesOnly(_r, edges_file, n);
                start = clock();
                cout << "Triangle Approx " << n << ": " << (int) _r.tsp_triangular(EDGES) / 1000 << " Km" << endl;
                end = clock();
                cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            }

            cout << endl;
            cout << "Press Enter to Continue..." << endl;

            wait();

            menu();

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

// Nearest Neighbor Algorithm
void nearestNeighborAlgorithm(){

    std::string option;

    do {
        clearScreen();
        std::cout << "  ===========================================================================  " << std::endl;
        std::cout << R"(//                                                                           \\)"
                  << std::endl;
        std::cout << "||           ##   ##  ######   ####   #####   ######   #####  ######         ||" << std::endl;
        std::cout << "||           ###  ##  ##      ##  ##  ##  ##  ##      ##        ##           ||" << std::endl;
        std::cout << "||           ## # ##  ####    ######  #####   ####     ####     ##           ||" << std::endl;
        std::cout << "||           ##  ###  ##      ##  ##  ##  ##  ##          ##    ##           ||" << std::endl;
        std::cout << "||           ##   ##  ######  ##  ##  ##  ##  ######  #####     ##           ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||       ##   ##  ######  ##   #####    ##  ##  #####    #####  #####        ||" << std::endl;
        std::cout << "||       ###  ##  ##      ##  ###       ##  ##  ##  ##  ##  ##  ##  ##       ||" << std::endl;
        std::cout << "||       ## # ##  ####    ##  ##  ####  ######  #####   ##  ##  #####        ||" << std::endl;
        std::cout << "||       ##  ###  ##      ##  ##   ##   ##  ##  ##  ##  ##  ##  ##  ##       ||" << std::endl;
        std::cout << "||       ##   ##  ######  ##   #####    ##  ##  #####   #####   ##  ##       ||" << std::endl;
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
        std::cout << "||    [1] Run Algorithm with Real World Graphs                               ||" << std::endl;
        std::cout << "||    [2] Run Algorithm with Extra Graphs                                    ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                [0] Back   ||" << std::endl;
        std::cout << R"(\\                                                                           //)"
                  << std::endl;
        std::cout << "  ===========================================================================  " << std::endl;


        std::cout << "  > ";
        std::getline(std::cin >> std::ws, option);

        if (option == "1") {

            Graph r1, r2, r3;
            clock_t start, end;

            clearScreen();

            cout << "My Algorithms:\n";
            cout << "Nearest Neighbor:\n";
            readRNodes(r1, "../csv/Real-World-Graphs/graph1/nodes.csv");
            readREdges(r1, "../csv/Real-World-Graphs/graph1/edges.csv");
            readRNodes(r2, "../csv/Real-World-Graphs/graph2/nodes.csv");
            readREdges(r2, "../csv/Real-World-Graphs/graph2/edges.csv");
            readRNodes(r3, "../csv/Real-World-Graphs/graph3/nodes.csv");
            readREdges(r3, "../csv/Real-World-Graphs/graph3/edges.csv");
            start = clock();
            cout << "Real 1:\n" << (int) r1.tsp_nearest() / 1000 << " Km" << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            start = clock();
            cout << "Real 2:\n" << (int) r2.tsp_nearest() / 1000 << " Km" << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            start = clock();
            cout << "Real 3:\n" << (int) r3.tsp_nearest() / 1000 << " Km" << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;


            cout << endl;
            cout << "Press Enter to Continue..." << endl;

            wait();

            menu();

        } else if (option == "2") {

            clock_t start, end;

            clearScreen();

            vi files = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};
            for (int n: files) {
                Graph r, _r;
                string edges_file = "../csv/Extra-Graphs/edges_" + to_string(n) + ".csv";
                ReadREdgesOnly(_r, edges_file, n);
                start = clock();
                cout << "Nearest Neighbor " << n << ": " << (int) _r.tsp_nearest() / 1000 << " Km" << endl;
                end = clock();
                cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            }

            cout << endl;
            cout << "Press Enter to Continue..." << endl;

            wait();

            menu();

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


// Christofides Algorithm
void christofidesAlgorithm(){

    std::string option;

    do {
        clearScreen();
        std::cout << "  ===========================================================================  " << std::endl;
        std::cout << R"(//                                                                           \\)"
                  << std::endl;
        std::cout << "||  ####  ## ## #####  ##  ##### ######  ##### ##### ## #####  ######  ##### ||" << std::endl;
        std::cout << "|| ##  ## ## ## ##  ## ## ##       ##   ##  ## ##    ## ##  ## ##     ##     ||" << std::endl;
        std::cout << "|| ##     ##### #####  ##  ####    ##   ##  ## ####  ## ##   # ####    ####  ||" << std::endl;
        std::cout << "|| ##  ## ## ## ##  ## ##     ##   ##   ##  ## ##    ## ##  ## ##         ## ||" << std::endl;
        std::cout << "||  ####  ## ## ##  ## ## #####    ##   #####  ##    ## #####  ###### #####  ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                ####   #####  #####   #####    #####  ##   ##              ||" << std::endl;
        std::cout << "||               ##  ##  ##  ## ##  ##  ##  ##  ##  ##   ## ##               ||" << std::endl;
        std::cout << "||               ######  #####  #####   #####   ##  ##    ###                ||" << std::endl;
        std::cout << "||               ##  ##  ##     ##      ##  ##  ##  ##   ## ##               ||" << std::endl;
        std::cout << "||               ##  ##  ##     ##      ##  ##  #####   ##   ##              ||" << std::endl;
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
        std::cout << "||    [1] Run Algorithm with Real World Graphs                               ||" << std::endl;
        std::cout << "||    [2] Run Algorithm with Extra Graphs                                    ||" << std::endl;
        std::cout << "||                                                                           ||" << std::endl;
        std::cout << "||                                                                [0] Back   ||" << std::endl;
        std::cout << R"(\\                                                                           //)"
                  << std::endl;
        std::cout << "  ===========================================================================  " << std::endl;


        std::cout << "  > ";
        std::getline(std::cin >> std::ws, option);

        if (option == "1") {

            Graph r1, r2, r3;
            clock_t start, end;

            clearScreen();

            cout << "My Algorithms:\n";
            cout << "Christofides Approx:\n";
            readRNodes(r1, "../csv/Real-World-Graphs/graph1/nodes.csv");
            readREdges(r1, "../csv/Real-World-Graphs/graph1/edges.csv");
            readRNodes(r2, "../csv/Real-World-Graphs/graph2/nodes.csv");
            readREdges(r2, "../csv/Real-World-Graphs/graph2/edges.csv");
            readRNodes(r3, "../csv/Real-World-Graphs/graph3/nodes.csv");
            readREdges(r3, "../csv/Real-World-Graphs/graph3/edges.csv");
            start = clock();
            cout << "Real 1:\n" << (int) r1.tsp_christofides(NO_EDGES) / 1000 << " Km" << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            start = clock();
            cout << "Real 2:\n" << (int) r2.tsp_christofides(NO_EDGES) / 1000 << " Km" << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            start = clock();
            cout << "Real 3:\n" << (int) r3.tsp_christofides(NO_EDGES) / 1000 << " Km" << endl;
            end = clock();
            cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;

            cout << endl;
            cout << "Press Enter to Continue..." << endl;

            wait();

            menu();

        } else if (option == "2") {

            clock_t start, end;

            clearScreen();

            vi files = {25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900};
            for (int n: files) {
                Graph r, _r;
                string edges_file = "../csv/Extra-Graphs/edges_" + to_string(n) + ".csv";
                ReadREdgesOnly(_r, edges_file, n);
                start = clock();
                cout << "Christofides Approx " << n << ": " << (int) _r.tsp_christofides(EDGES) / 1000 << " Km" << endl;
                end = clock();
                cout << "Time: " << (double) (end - start) / CLOCKS_PER_SEC << endl;
            }

            cout << endl;
            cout << "Press Enter to Continue..." << endl;

            wait();

            menu();

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


void clearScreen() {
    for (int i = 0; i < 50; i++) {
        std::cout << std::endl;
    }
}

void wait() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); std::cin.get();
}
