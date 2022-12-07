#include "AdjacencyList.h"
#include <queue>
#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;
void AdjacencyList::retrieveNodes()
{
    // open Nodes.csv
    ifstream nodesFile("csvs/Nodes.csv");
    // read Nodes.csv with delimeter ;
    string line;
    while (getline(nodesFile, line))
    {
        // Split line into tokens
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ';'))
        {
            tokens.push_back(token);
        }
        // Create Node from tokens
        try
        {
            nodes.push_back(new Node(tokens[2], stoi(tokens[0]), stoi(tokens[12]), stoi(tokens[13])));
        }
        catch (exception e)
        {
            cout << "Failed to push node " << tokens[2] << " trying again..." << endl;
            try
            {
                nodes.push_back(new Node(tokens[2], stoi(tokens[0]), 1000, 1000));
            }
            catch (exception e)
            {
                cout << "Failed to push node " << tokens[2] << " skipping" << endl;
            }
        }
    }
    cout << "Retrieved " << nodes.size() << " nodes" << endl;
}
void AdjacencyList::retrieveEdges()
{
    string line;

    // Open Edges.csv
    ifstream edgesFile("csvs/Edges.csv");
    // Read Edges.csv with delimeter ;

    while (getline(edgesFile, line))
    {
        // Split line into tokens
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, ';'))
        {
            tokens.push_back(token);
        }
        try
        {
            Edge *e = new Edge(nodes[stoi(tokens[0])], nodes[stoi(tokens[1])]);
            edges.push_back(e);
        }
        catch (const std::exception &e)
        {
            cout << "Failed to push edge, skipping" << endl;
        }
    }
    cout << "Retrieved " << edges.size() << " edges" << endl;
}

void AdjacencyList::addEdge(Edge *e)
{
    int birthYearFrom = e->to->birthYear;
    int birthYearTo = e->from->birthYear;
    int weight = abs(birthYearTo - birthYearFrom);
    adjList[e->from].push_back(make_pair(weight, e->to));
    adjList[e->to].push_back(make_pair(weight, e->from));
}
map<Node *, vector<pair<int, Node *>>> AdjacencyList::getAdjList()
{
    return adjList;
}
void AdjacencyList::createGraph()
{
    for (Edge *e : edges)
    {
        addEdge(e);
    }
}
vector<Node *> AdjacencyList::getNodes()
{
    return nodes;
}
void AdjacencyList::djikstra(string startName, string endName, bool byBirthYear)
{

    // find start and end nodes in nodes vector
    Node *start = nullptr;
    Node *end = nullptr;
    for (Node *n : nodes)
    {
        if (n->name == startName)
        {
            start = n;
        }
        if (n->name == endName)
        {
            end = n;
        }
    }
    if (start == nullptr || end == nullptr)
    {
        cout << "Invalid nodes inputted" << endl;
        return;
    }
    // initializes all distances to INT_MAX
    vector<int> dist(nodes.size(), INT_MAX);
    priority_queue<pair<int, Node *>, vector<pair<int, Node *>>, greater<pair<int, Node *>>> pq;

    pq.push(make_pair(0, start));
    dist[start->id] = 0;
    while (!pq.empty())
    {
        Node *u = pq.top().second;
        pq.pop();
        int weight;
        for (auto v : adjList[u])
        {
            // change weight based on if we are using birth year or not
            if (byBirthYear)
            {
                weight = v.first;
            }
            else
            {
                weight = 1;
            }

            // if there is shorter path to v through u.
            if (dist[v.second->id] > dist[u->id] + weight)
            {
                // for debugging purposes (distance should never be negative)
                if (v.second->id < 0)
                {
                    cout << "v.second->id < 0" << endl;
                }
                dist[v.second->id] = dist[u->id] + weight;
                pq.push(make_pair(dist[v.second->id], v.second));
            }
        }
    }
    string append;
    // if the distance is still INT_MAX, then there is no path
    if (dist[end->id] == INT_MAX)
    {
        cout << "No connection exists between " << start->name << " and " << end->name << endl;
    }
    else
    {
        // change output based on if we are using birth year or not
        if (byBirthYear)
        {
            append = " years and they lived " + to_string(abs(start->birthYear - end->birthYear)) + " years apart!";
            cout << "Shortest distance between " << start->name << " and " << end->name << " is " << dist[end->id] << append << endl;
        }
        else
        {
            // get all nodes in shortest path
            vector<Node *> shortestPath;
            Node *current = end;
            while (current != start)
            {
                shortestPath.push_back(current);
                for (auto v : adjList[current])
                {
                    if (dist[v.second->id] == dist[current->id] - 1)
                    {
                        current = v.second;
                        break;
                    }
                }
            }
            shortestPath.push_back(start);
            // reverse vector
            reverse(shortestPath.begin(), shortestPath.end());
            string append = " and the shortest path is:\n";
            for (Node *n : shortestPath)
            {
                append += n->name + " -> ";
            }
            append = append.substr(0, append.size() - 4);
            cout << "Shortest distance between " << start->name << " and " << end->name << " is " << dist[end->id] << append << endl;
        }
    }
}
