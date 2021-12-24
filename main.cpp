#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <stdlib.h>
#include "sequence.h"
#include "priority_queue.h"
#include "graph.hpp"
#include "dir_graph.h"
#include "tests.h"
//#include <boost/graph/adjacency_list.hpp>
//#include <boost/graph/graphviz.hpp>

//bool compKey(TPair<int, int> a, TPair<int, int> b)
//{
//    if (a.getKey() < b.getKey())
//    {
//        return 1;
//    }
//    else return 0;
//}

bool compElement(TPair<int, int> a, TPair<int, int> b)
{
    if (a.getElement() < b.getElement())
    {
        return 1;
    }
    else return 0;
}

bool comp4(TPair<int, TPair<int, int>> a, TPair<int, TPair<int, int>> b)
{
    if (a.getKey() < b.getKey())
    {
        return 1;
    }
    else return 0;
}

//function<bool(TPair<int, int>, TPair<int, int>)>cmpKey = compKey;
function<bool(TPair<int, int>, TPair<int, int>)>cmpElement = compElement;
function<bool(TPair<int, TPair<int, int>>, TPair<int, TPair<int, int>>)> compMatrix = comp4;

using namespace std;

int main()
{
    testUndirGraph();
    testDirGraph();

    int var = 0;
    while (var != 3)
    {
        cout << endl;
        cout << "Choose the option: " << endl;
        cout << "1. Create undirected graph " << endl << "2. Create directed graph" << endl << "3. Exit" << endl;
        cin >> var;
        switch(var)
        {
        case 1:
            {
                int num_vertices = 0;
                cout << "Enter the number of vertices: " << endl;
                cin >> num_vertices;
                set<int> vert;

                FILE *grviz = fopen("grviz.dot", "wt");
                fprintf(grviz, "graph G {\n");

                for (int i = 1; i <= num_vertices; i++)
                {
                    vert.insert(i);
                    fprintf(grviz, "%d [shape=\"circle\" label=\"%d\"];\n", i, i);
                }

                Graph<int> g(vert.size(), cmpKey);

                int flag = 0;

                while (flag != 2)
                {
                    cout << endl;
                    cout << "Choose the option: " << endl;
                    cout << "1. Add the edge " << endl << "2. Finish creating a graph" << endl;
                    cout << endl;
                    cin >> flag;
                    switch(flag)
                    {
                    case 1:
                        {
                            cout << endl;
                            cout << "Enter the start vertex, end vertex and edge weight" << endl;
                            int v1, v2, weight;
                            cin >> v1 >> v2 >> weight;
                            g.addEdge(v1, v2, weight);
                            fprintf(grviz, "%d--%d [label=\" %d \"];\n", v1, v2, weight);
                            break;
                        }
                    case 2:
                        {
                            break;
                        }
                    }

                }
                cout << endl;
                fprintf(grviz, "}");
                fclose(grviz);
                system("cd C:/Users/yunes/Documents/C++/Lab3_3");
                system("dot grviz.dot -Tpng -o grviz.png");
                system("grviz.png");
                cout << endl;

                int c = 0;
                while (c != 4)
                {
                    cout << "Choose the option: " << endl;
                    cout << "1. The shortest paths from vertex" << endl << "2. Travelling salesman problem (for complete graph)" << endl
                    << "3. Length of the shortest path between two vertices" << endl << "4. Exit" << endl;
                    cin >> c;
                    switch(c)
                    {
                    case 1:
                        {
                            vector<int>* v;
                            cout << "Enter the starting vertex" << endl;
                            int v3;
                            cin >> v3;
                            v = g.shortestPath(v3);
                            cout << endl;
                            std::set<int>::iterator it = vert.begin();
                            for (int i = 1; i <= v->size(); i++)
                            {
                                if (g.isPath(v3, i))
                                {
                                    cout << "Length from " << v3 << " to " << i << " = " << v->at(i) << endl;
                                    //it++;
                                }

                            }
                            cout << endl;
                            break;
                        }
                    case 2:
                        {
                            cout << "Weight a path for TSP = " << g.tsp(1) << endl;
                            break;
                        }
                    case 3:
                        {
                            cout << "Enter two vertices" << endl;
                            int v4, v5;
                            cin >> v4 >> v5;
                            cout << "The length of shortest path between " << v4 << " and " << v5 << " = "
                             << g.shortestDist(v4, v5) << endl;
                             break;
                        }
                    case 4:
                        {
                            break;
                        }

                    }
                }
                break;
        }
        case 2:
            {
                int num_vertices = 0;
                cout << "Enter the number of vertices: " << endl;
                cin >> num_vertices;
                set<int> vert;

                FILE *grviz = fopen("grviz.dot", "wt");
                fprintf(grviz, "digraph G {\n");

                for (int i = 1; i <= num_vertices; i++)
                {
                    vert.insert(i);
                    fprintf(grviz, "%d [shape=\"circle\" label=\"%d\"];\n", i, i);
                }

                DirGraph<int> g(vert.size(), cmpKey);

                int flag = 0;

                while (flag != 2)
                {
                    cout << endl;
                    cout << "Choose the option: " << endl;
                    cout << "1. Add the edge " << endl << "2. Finish creating a graph" << endl;
                    cout << endl;
                    cin >> flag;
                    switch(flag)
                    {
                    case 1:
                        {
                            cout << endl;
                            cout << "Enter the start vertex, end vertex and edge weight" << endl;
                            int v1, v2, weight;
                            cin >> v1 >> v2 >> weight;
                            g.addEdge(v1, v2, weight);
                            fprintf(grviz, "%d->%d [label=\" %d \"];\n", v1, v2, weight);
                            break;
                        }
                    case 2:
                        {
                            break;
                        }
                    }
                }
                cout << endl;
                fprintf(grviz, "}");
                fclose(grviz);
                system("cd C:/Users/yunes/Documents/C++/Lab3_3");
                system("dot grviz.dot -Tpng -o grviz.png");
                system("grviz.png");
                cout << endl;
                int c = 0;
                while (c != 4)
                {
                    cout << endl;
                    cout << "Choose the option: " << endl;
                    cout << "1. The shortest paths from vertex" << endl << "2. Topological sort" << endl
                    << "3. Length of the shortest path between two vertices" << endl << "4. Exit" << endl;
                    cin >> c;
                    switch(c)
                    {
                    case 1:
                        {
                            vector<int>* v;
                            cout << "Enter the starting vertex" << endl;
                            int v3;
                            cin >> v3;
                            v = g.shortestPath(v3);
                            cout << endl;
                            std::set<int>::iterator it = vert.begin();
                            for (int i = 1; i <= vert.size(); i++)
                            {
                                if (g.isPath(v3, *it))
                                {
                                    cout << "Length from " << v3 << " to " << *it << " = " << v->at(i) << endl;
                                }
                                else
                                {
                                    cout << "There is not path between " << v3 << " and " << *it << endl;
                                }
                                it++;
                            }
                            cout << endl;
                            break;

                        }
                    case 2:
                        {
                            cout << "Topological sort: " << endl;
                            g.topologicalSort();
                            cout << endl;
                            break;
                        }
                    case 3:
                        {
                            cout << "Enter two vertices" << endl;
                            int v4, v5;
                            cin >> v4 >> v5;
                            if (g.isPath(v4, v5))
                            {
                                cout << "The length of shortest path between " << v4 << " and " << v5 << " = "
                                << g.shortestDist(v4, v5) << endl;
                            }
                            else
                            {
                                cout << "There is not path between " << v4 << " and " << v5 << endl;
                            }
                            cout << endl;
                            break;
                        }
                    case 4:
                        {
                            break;
                        }

                    }
                }
                break;

            }
            case 3:
            {
                break;
            }
        }
    }

    return 0;
}
