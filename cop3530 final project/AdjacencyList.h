#include <string>
#include <map>
#include <vector>
#include <utility>
#pragma once
struct Node
{
    std::string name;
    int id, birthYear, deathYear;
    Node() : name(""), id(0), birthYear(0), deathYear(0){};
    Node(std::string name, int id, int birthYear, int deathYear) : name(name), id(id), birthYear(birthYear), deathYear(deathYear) {}
    ~Node() {}
    bool operator<(const Node *&rhs) const
    {
        return id < rhs->id;
    }
};

struct Edge
{
    Node *from, *to;
    Edge();
    Edge(Node *from, Node *to) : from(from), to(to) {}
    ~Edge() {}
};

class AdjacencyList
{
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
    std::map<Node *, std::vector<std::pair<int, Node *>>> adjList;

public:
    // destructor
    ~AdjacencyList() {}
    std::map<Node *, std::vector<std::pair<int, Node *>>> getAdjList();
    void retrieveNodes();
    void retrieveEdges();
    std::vector<Node *> getNodes();
    void createGraph();
    void addEdge(Edge *e);
    void createGraph(std::vector<Edge *> edges);
    void djikstra(std::string start, std::string end, bool byBirthYear);
};