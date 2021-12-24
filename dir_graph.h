#ifndef DIR_GRAPH_H_INCLUDED
#define DIR_GRAPH_H_INCLUDED
#include <iostream>
#include "sequence.H"
#include "stack.h"
#include "queue.h"

using namespace std;

template<typename T>
class DirGraph
{
private:
    Sequence<Sequence<TPair<T, int>>*>* adjList;
    set<int> vertices;
    function<bool(TPair<T, int>, TPair<T, int>)> cmp;

public:
    DirGraph(int number, function<bool(TPair<T, int>, TPair<T, int>)> cmp)
    {
        this->adjList = new ArraySequence<Sequence<TPair<T, int>>*>(number);
        this->cmp = cmp;
        for (int i = 1; i <= number; i++)
        {
            this->vertices.insert(i);
        }
        for (int i = 1; i <= number; i++)
        {
            this->adjList->getP(i) = new ArraySequence<TPair<T, int>>();
        }
    }

    DirGraph(Sequence<Sequence<TPair<T, int>>*>* adjList1, function<bool(TPair<T, int>, TPair<T, int>)> cmp)
    {
        this->adjList = new ArraySequence<Sequence<TPair<T, int>>*>(adjList1->getLength());
        this->adjList = adjList1;
        this->cmp = cmp;
    }

    DirGraph(Sequence<Sequence<TPair<T, int>>*>* adjList1, const set<int>& vertices, function<bool(TPair<T, int>, TPair<T, int>)> cmp)
    {
        this->adjList = new ArraySequence<Sequence<TPair<T, int>>*>(vertices.size());
        this->adjList = adjList1;
        this->vertices = vertices;
        this->cmp = cmp;
    }


    DirGraph(const set<int>& vertices, function<bool(TPair<T, int>, TPair<T, int>)> cmp)
    {
        this->adjList = new ArraySequence<Sequence<TPair<T, int>>*>(vertices.size());
        for(int i = 1; i <= vertices.size(); i++)
        {
            this->adjList->set(i, new ArraySequence<TPair<T, int>>(0));
        }
        this->vertices = vertices;
        this->cmp = cmp;
    }

    int getSize()
    {
        return this->adjList->getLength();
    }

    void addEdge(int v1, int v2, T w)
    {
        if (v1 != v2)
        {
            TPair<T, int> p1(w, v2);
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

            if (vertices.find(v2) == vertices.end())
            {
                Sequence<TPair<T, int>>* s = new ArraySequence<TPair<T, int>>();
                this->adjList->insertAt(v2, s);
            }
            this->vertices.insert(v2);
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

    void topologicalSort()
    {
        int V = this->vertices.size();
        bool *flag = new bool[V + 1];
        Stack<int>* ans = new Stack<int>();
        for (int i = 1; i <= V; i++)
        {
            flag[i] = false;
        }

        for (int i = 1; i <= V; i++)
        {
            if (flag[i] == false)
            {
                topologicalSortH(i, flag, ans);
            }
        }

        while(ans->empty() == false)
        {
            cout << ans->top() << " ";
            ans->pop();
        }
    }

    void topologicalSortH(int v, bool flag[], Stack<int>* ans)
    {
        int V = this->vertices.size();
        flag[v] = true;
        for (int i = 0; i < this->adjList->get(v)->getLength(); i++)
        {
            if (!flag[this->adjList->get(v)->get(i).getElement()])
            {
                topologicalSortH(this->adjList->get(v)->get(i).getElement(), flag, ans);
            }
        }
        ans->push(v);
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

};


#endif // DIR_GRAPH_H_INCLUDED
