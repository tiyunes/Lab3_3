#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED
#include <limits.h>
#include <set>
#include "dictionary.h"
#include "sparse_matrix.h"
#include "queue.h"

template<typename T>
class Graph
{
private:
    Sequence<Sequence<TPair<T, int>>*>* adjList;
    set<int> vertices;
    function<bool(TPair<T, int>, TPair<T, int>)> cmp;
public:
    Graph(int number, function<bool(TPair<T, int>, TPair<T, int>)> cmp)
    {
        for (int i = 1; i <= number; i++)
        {
            this->vertices.insert(i);
        }
        this->adjList = new ArraySequence<Sequence<TPair<T, int>>*>(number);
        for (int i = 1; i <= number; i++)
        {
            this->adjList->getP(i) = new ArraySequence<TPair<T, int>>();
        }
        this->cmp = cmp;
    }

    Graph(Sequence<Sequence<TPair<T, int>>*>* adjList1, set<int> &vertices1, function<bool(TPair<T, int>, TPair<T, int>)> cmp)
    {
        this->adjList = new ArraySequence<Sequence<TPair<T, int>>*>(adjList1->getLength());
        this->adjList = adjList1;
        this->vertices = vertices1;
        this->cmp = cmp;
    }

    Graph(set<int> &vertices1, function<bool(TPair<T, int>, TPair<T, int>)> cmp)
    {
        this->adjList = new ArraySequence<Sequence<TPair<T, int>>*>(vertices1.size());
        this->vertices = vertices1;
        this->cmp = cmp;
    }

    int getSize() // number of vertices
    {
        return vertices.size();
    }

    void addEdge(int v1, int v2, T w)
    {
        if (v1 != v2)
        {
            TPair<T, int> p1(w, v2);
            TPair<T, int> p2(w, v1);
            if (vertices.find(v1) != vertices.end())
            {
                this->adjList->get(v1)->append(p1);
            }
            else
            {
                Sequence<TPair<T, int>>* s = new ArraySequence<TPair<T, int>>();
                this->adjList->insertAt(v1, s);
                this->adjList->get(v1)->append(p1);
                this->vertices.insert(v1);
            }

            if (vertices.find(v2) != vertices.end())
            {
                this->adjList->get(v2)->append(p2);
            }
            else
            {
                Sequence<TPair<T, int>>* s = new ArraySequence<TPair<T, int>>();
                this->adjList->insertAt(v2, s);
                this->adjList->get(v2)->append(p2);
                this->vertices.insert(v2);
            }
        }
        else
        {
            throw std::out_of_range("Invalid vertices");
        }
    }

    vector<T>* shortestPath(int v)
    {
        PriorityQueue<T, int>* pq = new PriorityQueue<T, int>(this->cmp);
        vector<T>* dist = new vector<T>(vertices.size() + 1, INT_MAX);
        pq->enqueue(0, v);
        dist->at(v) = 0;
        while (pq->getSize() != 0)
        {
            int u = pq->extractMin().getElement();

            for (int i = 0; i < this->adjList->get(u)->getLength(); i++)
            {
                int z = this->adjList->get(u)->get(i).getElement();
                T w = this->adjList->get(u)->get(i).getKey();

                if (dist->at(z) > (dist->at(u) + w))
                {
                    dist->at(z) = (dist->at(u) + w);
                    pq->enqueue(dist->at(z), z);
                }
            }
        }
        return dist;
    }

    Sequence<Sequence<TPair<T, int>>*>* getAdjList()
    {
        return this->adjList;
    }

    bool isEdge(int v1, int v2)
    {
        for (int i = 0; i < this->adjList->get(v1)->getLength(); i++)
        {
            if (this->adjList->get(v1)->get(i).getElement() == v2)
            {
                return true;
            }
        }
        return false;
    }

    T edgeWeight(int v1, int v2)
    {
        if (isEdge(v1, v2))
        {
            for (int i = 0; i < this->adjList->get(v1)->getLength(); i++)
            {
                if (this->adjList->get(v1)->get(i).getElement() == v2)
                {
                    return this->adjList->get(v1)->get(i).getKey();
                }
            }
        }
        else
        {
            throw std::out_of_range("Invalid vertices");
        }
    }

    bool isPath(int v1, int v2)
    {
        if (v1 == v2)
        {
            return true;
        }
        else
        {
            int V  = this->vertices.size();
            bool *visited = new bool[V];

            for (int i = 0; i < V; i++)
            {
                visited[i] = false;
            }

            Queue<int> q;

            visited[v1] = true;
            q.push(v1);

            while (!q.empty())
            {
                v1 = q.front();
                q.pop();

                for (int i = 0; i < this->adjList->get(v1)->getLength(); i++)
                {
                    if (this->adjList->get(v1)->get(i).getElement() == v2)
                    {
                        return true;
                    }

                    if (!visited[this->adjList->get(v1)->get(i).getElement()])
                    {
                        visited[this->adjList->get(v1)->get(i).getElement()] = true;
                        q.push(this->adjList->get(v1)->get(i).getElement());
                    }
                }
            }

            return false;
        }
    }

    T shortestDist (int v1, int v2)
    {
        if (!isPath(v1, v2))
        {
            throw std::out_of_range("Invalid vertices");
        }
        else
        {
            return this->shortestPath(v1)->at(v2);
        }
    }

    int tsp(int city) // only for complete graph
    {
        int V = this->vertices.size();
        vector<int> vertex;
        for (int i = 1; i <= V; i++)
        {
            if (i != city)
            {
                vertex.push_back(i);
            }
        }

        T m = INT_MAX * 1.0;
        do
        {
            T currPath = 0;
            int k = city;
            for (int i = 0; i < vertex.size(); i++)
            {
                if (isEdge(k, vertex[i]))
                {
                    currPath += edgeWeight(k, vertex[i]);
                    k = vertex[i];
                }

            }

            if (isEdge(k, city))
            {
                currPath += edgeWeight(k, city);
            }

            m = min(m, currPath);
        }
        while (next_permutation(vertex.begin(), vertex.end()));

        return m;
    }

};

#endif // GRAPH_HPP_INCLUDED
