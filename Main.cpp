#include <iostream>

#include "MinHeap.hpp"

#include "UnionFind.hpp"
#include "Kruskal.hpp"


using namespace std;

int main()
{
    MinHeap<int> heap;
    heap.push(1);
    cout << heap.top() << endl;
    heap.pop();

    ListGraph list;
    list.setVertexCount(4);
    list.addEdge(1, 2, 10);
    list.addEdge(1, 3, 20);
    list.addEdge(2, 3, 50);
    list.addEdge(2, 4, 50);
    
    auto mst = Kruskal::generateMst(list);

    return 0;
}