#include <iostream>

#include "Kruskal.hpp"
#include "Prima.hpp"
#include "Dijkstra.hpp"
#include "BellmanFord.hpp"

using namespace std;

int main()
{
    MinHeap<int> heap;
    heap.push(1);
    cout << heap.top() << endl;
    heap.pop();

    ListGraph list;
    list.setVertexCount(4);
    list.addEdge(0, 1, 10);
    list.addEdge(0, 2, 20);
    list.addEdge(1, 2, 50);
    list.addEdge(1, 3, 50);
    list.addEdge(2, 3, 5);

    auto mst = Kruskal::generateMst(list);

    auto mst2 = Prima::generateMst(list);

    auto dijkstra = Dijkstra::getShortestPath(list, 0, 3);

    auto bf = BellmanFord::getShortestPath(list, 0, 3);

    return 0;
}