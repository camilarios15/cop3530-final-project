#include "AdjacencyList.h"
#include "AdjacencyList.cpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <climits>
#include <time.h>
using namespace std;

int main()
{
    AdjacencyList graph;
    graph.retrieveNodes();
    graph.retrieveEdges();
    graph.createGraph();
    cout << "---------------------------------" << endl;
    cout << "Welcome!" << endl;
    // gets the user input and determines what to do with it
    while (true)
    {
        cout << "Would you like to randomly pick two people or enter two people?" << endl;
        cout << "1. Randomly pick two people" << endl;
        cout << "2. Enter two people" << endl;
        string choice;
        string name1, name2;
        getline(cin, choice);
        bool valid = false;
        // makes it so the random names are different every time
        srand(time(NULL));
        while (!valid)
        {
            valid = true;
            if (choice == "1")
            {
                // randomly select 2 unique nodes from the graph
                int random1 = rand() % graph.getNodes().size();
                int random2 = rand() % graph.getNodes().size();
                while (random1 == random2)
                {
                    random2 = rand() % graph.getNodes().size();
                }
                // selects 2 random names
                name1 = graph.getNodes()[random1]->name;
                name2 = graph.getNodes()[random2]->name;
                cout << "Selected " << name1 << " and " << name2 << "!" << endl;
            }
            else if (choice == "2")
            {
                bool found1 = false;
                bool found2 = false;
                while (!(found1 && found2))
                {
                    cout << "Start Person: ";
                    getline(cin, name1);

                    cout << "End Person: ";
                    getline(cin, name2);
                    // make sure both names are in the graph

                    for (int i = 0; i < graph.getNodes().size(); i++)
                    {
                        if (graph.getNodes()[i]->name == name1)
                        {
                            found1 = true;
                        }
                        if (graph.getNodes()[i]->name == name2)
                        {
                            found2 = true;
                        }
                    }
                    // ensures that both names are in the graph
                    if (!(found1 && found2))
                    {
                        cout << "One or both of the names you entered are not in the data. Please try again." << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid input. Please try again." << endl;
                valid = false;
            }
        }
        cout << endl;
        // decides how to compute shortest path between 2 nodes
        cout << "Choose an option" << endl;
        cout << "1. Find shortest path of people between two people" << endl;
        cout << "2. Find shortest path in years between two people" << endl;

        string option;
        getline(cin, option);
        cout << endl;

        switch (stoi(option))
        {
        case 1:
            // shortest path where all weights are 1
            graph.djikstra(name1, name2, false);
            break;
        case 2:
            // shortest path where weights are difference in birth years
            graph.djikstra(name1, name2, true);
            break;
        default:
            cout << "Invalid option" << endl;
            return 0;
        }
        cout << endl;
        cout << "Would you like to try again? (y/n)" << endl;
        string again;
        getline(cin, again);
        if (again == "y")
        {
            cout << endl;
            continue;
        }
        else
        {
            break;
        }
    }
}
