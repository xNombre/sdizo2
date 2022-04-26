#include <iostream>

#include "Kruskal.hpp"
#include "Prima.hpp"
#include "Dijkstra.hpp"
#include "BellmanFord.hpp"
#include "MatrixGraph.hpp"

using namespace std;

int main()
{
    ListGraph list;
    list.setVertexCount(4);
    list.addEdge(0, 1, 10);
    list.addEdge(0, 2, 20);
    list.addEdge(1, 2, 50);
    list.addEdge(1, 3, 50);
    list.addEdge(2, 3, 5);

    MatrixGraph matrix;
    matrix.addEdge(0, 1, 10);
    matrix.addEdge(0, 2, 20);
    matrix.addEdge(1, 2, 50);
    matrix.addEdge(1, 3, 50);
    matrix.addEdge(2, 3, 5);
    
    //auto mst = Kruskal::generateMst(list);

    //auto mst2 = Prima::generateMst(list);

    auto dijkstra = Dijkstra::getShortestPath(list, 0, 3);
    dijkstra.print();

    auto dijkstra2 = Dijkstra::getShortestPath(matrix, 0, 3);
    dijkstra2.print();
    
    //auto bf = BellmanFord::getShortestPath(list, 0, 3);
    //bf.print();
    

    //matrix.print();

    //mst.print();
    
   // auto kr = Kruskal::generateMst(matrix);
    //kr.print();

   // auto pr1 = Prima::generateMst(list);
   // pr1.print();
    
    //auto pr = Prima::generateMst(matrix);
    //pr.print();
    //list.print();

    return 0;
}