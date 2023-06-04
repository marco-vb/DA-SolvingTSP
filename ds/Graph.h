/**
 * @file Graph.h
 * @brief This file contains the declaration of the Graph class and related classes.
 */

#ifndef TSP_GRAPH_H
#define TSP_GRAPH_H

#include <bits/stdc++.h>
#include "Heap.h"

/**
 * @class Edge
 * @brief Represents an edge in the graph.
 */
class Edge
{
public:
    /**
     * @brief Constructs an Edge object.
     * @param dest The destination node of the edge.
     * @param w The weight of the edge.
     */
    Edge(int dest, double w);

    int dest;           ///< The destination node of the edge.
    double weight;      ///< The weight of the edge.
};

/**
 * @class Node
 * @brief Represents a node in the graph.
 */
class Node
{
public:
    /**
     * @brief Constructs a Node object.
     * @param id The ID of the node.
     * @param lat The latitude of the node.
     * @param lon The longitude of the node.
     */
    Node(int id, double lat, double lon);

    /**
     * @brief Copy constructor for Node.
     * @param node The Node object to be copied.
     */
    Node(const Node& node);

    int id;                 ///< The ID of the node.
    int queueIndex;         ///< The index of the node in the priority queue.
    double lat;             ///< The latitude of the node.
    double lon;             ///< The longitude of the node.
    double dist;            ///< The distance of the node.
    bool visited;           ///< Flag indicating if the node has been visited.
    Node* root;             ///< Pointer to the root node.
    std::vector<Edge*> adj; ///< List of adjacent edges.

    /**
     * @brief Overloaded less than operator for comparing nodes.
     * @param node The Node object to be compared.
     * @return True if the current node is less than the given node, False otherwise.
     */
    bool operator<(Node& node) const;
};

/**
 * @class Graph
 * @brief Represents a graph.
 */
class Graph
{
public:
    /**
     * @brief Default constructor for Graph.
     */
    Graph();

    /**
     * @brief Constructs a Graph object with the specified number of nodes.
     * @param V The number of nodes in the graph.
     */
    explicit Graph(int V);

    /**
     * @brief Destructor for Graph.
     */
    ~Graph();

    /**
     * @brief Solves the Traveling Salesman Problem using the exact algorithm.
     * @return The minimum cost of the TSP tour.
     */
    double tsp_exact();

    /**
     * @brief Helper function for the tsp_exact algorithm.
     * @param pos The current position in the TSP tour.
     * @param mask The bitmask representing visited nodes.
     * @param memo The memoization table for dynamic programming.
     * @param dist The distance matrix.
     * @return The minimum cost of the TSP tour from the current position with the given bitmask.
     */
    double tsp_exact(int pos, ull mask, vvd& memo, const vvd& dist);

    /**
     * @brief Solves the Traveling Salesman Problem using the triangular approximation heuristic.
     * @param edges Flag indicating whether to include edge information in the output.
     * @return The approximate minimum cost of the TSP tour.
     */
    double tsp_triangular(bool edges = false);

    /**
     * @brief Solves the Traveling Salesman Problem using the Christofides algorithm.
     * @param edges Flag indicating whether to include edge information in the output.
     * @return The approximate minimum cost of the TSP tour.
     */
    double tsp_christofides(bool edges = false);

    /**
     * @brief Finds the minimum weight perfect matching of the graph.
     * @param matches The vector to store the matching edges.
     */
    void min_weight_matching(vi& matches);

    /**
     * @brief Overlaps the matching edges to form an Euler tour.
     * @param matches The vector containing the matching edges.
     */
    void overlap(vi& matches);

    /**
     * @brief Constructs the Euler tour from the overlapping edges.
     * @param path The vector to store the Euler tour path.
     */
    void euler_tour(vi& path);

    /**
     * @brief Solves the Traveling Salesman Problem using the nearest neighbor heuristic.
     * @return The approximate minimum cost of the TSP tour.
     */
    double tsp_nearest();

    /**
     * @brief Builds the minimum spanning tree (MST) starting from the given position.
     * @param pos The starting position.
     */
    void build_mst(int pos);

    /**
     * @brief Builds the MST without considering the edges.
     * @param pos The starting position.
     */
    void build_mst_no_edges(int pos);

    /**
     * @brief Performs a pre-order traversal of the MST starting from the given position.
     * @param pos The starting position.
     * @param path The vector to store the pre-order traversal path.
     * @param count The current count of nodes visited.
     */
    void pre_order(int pos, vi& path, int& count);

    /**
     * @brief Finds the nearest neighbor of the given position.
     * @param pos The position for which to find the nearest neighbor.
     * @return The index of the nearest neighbor.
     */
    int nearest_neighbor(int pos);

    /**
     * @brief Calculates the Haversine distance between two points specified by their latitude and longitude.
     * @param lat1 The latitude of the first point.
     * @param lon1 The longitude of the first point.
     * @param lat2 The latitude of the second point.
     * @param lon2 The longitude of the second point.
     * @return The Haversine distance between the two points.
     */
    static double haversine(double lat1, double lon1, double lat2, double lon2);

    /**
     * @brief Calculates the distance between two nodes.
     * @param i The index of the first node.
     * @param j The index of the second node.
     * @return The distance between the two nodes.
     */
    double dist(int i, int j);

    int V;                          ///< The number of nodes in the graph.
    std::vector<Node*> nodes;       ///< List of nodes in the graph.
    std::vector<std::vector<int>> mst_edges; ///< List of edges in the minimum spanning tree.
};

#endif // TSP_GRAPH_H
