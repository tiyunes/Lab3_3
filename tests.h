#ifndef TESTS_H_INCLUDED
#include <functional>
#include <cmath>
#include <cassert>
#include "graph.hpp"
#include "dir_graph.h"

//boost::unit_test::unit_test_log_t::instance().set_threshold_level( boost::unit_test::log_messages );


bool compKey(TPair<int, int> a, TPair<int, int> b)
{
    if (a.getKey() < b.getKey())
    {
        return 1;
    }
    else return 0;
}

bool compKeyDouble(TPair<double, int> a, TPair<double, int> b)
{
    if (a.getKey() < b.getKey())
    {
        return 1;
    }
    else return 0;
}

function<bool(TPair<int, int>, TPair<int, int>)>cmpKey = compKey;
function<bool(TPair<double, int>, TPair<double, int>)>cmpKeyDouble = compKeyDouble;

void testUndirGraph()
{
    Graph<int> gTest1(3, cmpKey);

    gTest1.addEdge(1, 2, 1);
    gTest1.addEdge(3, 2, 2);
    gTest1.addEdge(1, 3, 3);

    assert( gTest1.isPath(1, 2) == true);
    assert( gTest1.isPath(1, 3) == true);
    assert( gTest1.isPath(2, 3) ==  true);
    assert( gTest1.edgeWeight(1, 2) ==  1);
    assert( gTest1.edgeWeight(2, 3) ==  2);
    assert( gTest1.edgeWeight(1, 3) ==  3);
    assert( gTest1.shortestDist(1, 3) ==  3);
    assert( gTest1.shortestDist(1, 2) ==  1);
    assert( gTest1.shortestDist(2, 3) ==  2);
    assert( gTest1.isEdge(1, 3) ==  true);
    assert( gTest1.isEdge(2, 3) ==  true);
    assert( gTest1.isEdge(1, 2) ==  true);

    Graph<int> gTest2(4, cmpKey);

    gTest2.addEdge(1, 2, 5);
    gTest2.addEdge(1, 3, 9);
    gTest2.addEdge(1, 4, 7);
    gTest2.addEdge(2, 3, 6);
    gTest2.addEdge(2, 4, 8);
    gTest2.addEdge(3, 4, 5);

    assert (gTest2.isPath(1, 2) == true);
    assert (gTest2.isPath(1, 3) == true);
    assert (gTest2.isPath(1, 4) == true);
    assert (gTest2.isPath(2, 3) == true);
    assert (gTest2.isPath(2, 4) == true);
    assert (gTest2.isPath(3, 4) == true);
    assert (gTest2.isEdge(1, 2) == true);
    assert (gTest2.isEdge(1, 3) == true);
    assert (gTest2.isEdge(1, 4) == true);
    assert (gTest2.isEdge(3, 2) == true);
    assert (gTest2.isEdge(3, 4) == true);
    assert (gTest2.isEdge(2, 3) == true);
    assert (gTest2.edgeWeight(1, 2) == 5);
    assert (gTest2.edgeWeight(1, 3) == 9);
    assert (gTest2.edgeWeight(1, 4) == 7);
    assert (gTest2.edgeWeight(2, 3) == 6);
    assert (gTest2.edgeWeight(2, 4) == 8);
    assert (gTest2.edgeWeight(3, 4) == 5);
    assert (gTest2.shortestDist(1, 2) == 5);
    assert (gTest2.shortestDist(1, 3) == 9);
    assert (gTest2.shortestDist(1, 4) == 7);
    assert (gTest2.shortestDist(2, 3) == 6);
    assert (gTest2.shortestDist(4, 2) == 8);
    assert (gTest2.shortestDist(3, 4) == 5);
    assert (gTest2.tsp(1) == 23);

    Graph<int> gTest3(4, cmpKey);

    gTest3.addEdge(1, 2, 10);
    gTest3.addEdge(1, 3, 20);
    gTest3.addEdge(3, 4, 5);

    assert (gTest3.isPath(1, 2) == true);
    assert (gTest3.isPath(1, 3) == true);
    assert (gTest3.isPath(1, 4) == true);
    assert (gTest3.isPath(2, 3) == true);
    assert (gTest3.isPath(2, 4) == true);
    assert (gTest3.isPath(3, 4) == true);
    assert (gTest3.isEdge(1, 2) == true);
    assert (gTest3.isEdge(1, 3) == true);
    assert (gTest3.isEdge(1, 4) == false);
    assert (gTest3.isEdge(3, 2) == false);
    assert (gTest3.isEdge(3, 4) == true);
    assert (gTest3.isEdge(2, 3) == false);
    assert (gTest3.edgeWeight(1, 2) == 10);
    assert (gTest3.edgeWeight(1, 3) == 20);
    assert (gTest3.edgeWeight(3, 4) == 5);
    assert (gTest3.shortestDist(1, 2) == 10);
    assert (gTest3.shortestDist(1, 3) == 20);
    assert (gTest3.shortestDist(1, 4) == 25);
    assert (gTest3.shortestDist(2, 3) == 30);
    assert (gTest3.shortestDist(4, 2) == 35);
    assert (gTest3.shortestDist(3, 4) == 5);

    cout << "Tests for undirected graph are correct" << endl;
}

void testDirGraph()
{
    DirGraph<int> gTest1(3, cmpKey);

    gTest1.addEdge(1, 2, 60);
    gTest1.addEdge(1, 3, 7);
    gTest1.addEdge(3, 2, 10);

    assert( gTest1.isPath(1, 2) == true);
    assert( gTest1.isPath(1, 3) == true);
    assert( gTest1.isPath(2, 3) ==  false);
    assert( gTest1.edgeWeight(1, 2) ==  60);
    assert( gTest1.edgeWeight(3, 2) ==  10);
    assert( gTest1.edgeWeight(1, 3) ==  7);
    assert( gTest1.shortestDist(1, 3) ==  7);
    assert( gTest1.shortestDist(1, 2) ==  17);
    assert( gTest1.shortestDist(3, 2) ==  10);
    assert( gTest1.isEdge(1, 3) ==  true);
    assert( gTest1.isEdge(2, 3) ==  false);
    assert( gTest1.isEdge(1, 2) ==  true);

    DirGraph<int> gTest2(4, cmpKey);

    gTest2.addEdge(1, 2, 11);
    gTest2.addEdge(1, 3, 22);
    gTest2.addEdge(4, 2, 33);
    gTest2.addEdge(4, 3, 7);

    assert (gTest2.isPath(1, 2) == true);
    assert (gTest2.isPath(1, 3) == true);
    assert (gTest2.isPath(1, 4) == false);
    assert (gTest2.isPath(2, 3) == false);
    assert (gTest2.isPath(2, 4) == false);
    assert (gTest2.isPath(4, 2) == true);
    assert (gTest2.isPath(3, 4) == false);
    assert (gTest2.isPath(4, 3) == true);
    assert (gTest2.isEdge(1, 2) == true);
    assert (gTest2.isEdge(1, 3) == true);
    assert (gTest2.isEdge(1, 4) == false);
    assert (gTest2.isEdge(3, 2) == false);
    assert (gTest2.isEdge(3, 4) == false);
    assert (gTest2.isEdge(4, 3) == true);
    assert (gTest2.isEdge(2, 3) == false);
    assert (gTest2.edgeWeight(1, 2) == 11);
    assert (gTest2.edgeWeight(1, 3) == 22);
    assert (gTest2.edgeWeight(4, 2) == 33);
    assert (gTest2.edgeWeight(4, 3) == 7);
    assert (gTest2.shortestDist(1, 2) == 11);
    assert (gTest2.shortestDist(1, 3) == 22);
    assert (gTest2.shortestDist(4, 2) == 33);
    assert (gTest2.shortestDist(4, 3) == 7);

    DirGraph<double> gTest3(4, cmpKeyDouble);

    gTest3.addEdge(1, 2, 0.5);
    gTest3.addEdge(2, 3, 1.5);
    gTest3.addEdge(3, 4, 7.4);
    gTest3.addEdge(4, 1, 11.0);
    gTest3.addEdge(4, 2, 3.1);
    gTest3.addEdge(1, 3, 30.0);

    assert (gTest3.isPath(1, 2) == true);
    assert (gTest3.isPath(2, 1) == true);
    assert (gTest3.isPath(1, 3) == true);
    assert (gTest3.isPath(3, 1) == true);
    assert (gTest3.isPath(1, 4) == true);
    assert (gTest3.isPath(2, 3) == true);
    assert (gTest3.isPath(2, 4) == true);
    assert (gTest3.isPath(3, 4) == true);
    assert (gTest3.isEdge(1, 2) == true);
    assert (gTest3.isEdge(1, 2) == true);
    assert (gTest3.isEdge(2, 1) == false);
    assert (gTest3.isEdge(1, 4) == false);
    assert (gTest3.isEdge(4, 1) == true);
    assert (gTest3.isEdge(3, 2) == false);
    assert (gTest3.isEdge(2, 3) == true);
    assert (gTest3.isEdge(3, 4) == true);
    assert (gTest3.edgeWeight(1, 2) == 0.5);
    assert (gTest3.edgeWeight(1, 3) == 30.0);
    assert (gTest3.edgeWeight(3, 4) == 7.4);
    assert (gTest3.shortestDist(1, 2) == 0.5);
    assert (gTest3.shortestDist(1, 3) == 2.0);
    assert (gTest3.shortestDist(1, 4) == 9.4);
    assert (gTest3.shortestDist(2, 3) == 1.5);
    assert (gTest3.shortestDist(4, 2) == 3.1);
    assert (gTest3.shortestDist(3, 4) == 7.4);

    cout << "Tests for directed graph are correct" << endl;
}

#endif // TESTS_H_INCLUDED
