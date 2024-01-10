#include "catch.hpp"
#include"WUSGraphClient.hpp"
#include"WUSGraph.hpp"
TEST_CASE("Dijkstra", "[Dijkstra]")
{
	WUSGraph<int, int> graph;
	WUSGraphClient<int, int> c;
	graph.addVertex(1);
	graph.addVertex(2);
	graph.addVertex(3);
	graph.addVertex(4);
	graph.addVertex(5);
	graph.addEdge(1, 2, 10);
	graph.addEdge(2, 3, 20);
	graph.addEdge(1, 3, 20);
	graph.addEdge(2, 4, 5);
	graph.addEdge(3, 5, 10);
	graph.addEdge(4, 5, 5);
	graph.addEdge(2, 5, 5);
	//REQUIRE(graph.vertexCount() == 3);
	int i = 1;
	//c.Dijkstra(graph,i);
	//c.Prim(graph);
}
TEST_CASE("Dijkstra and Prim - Complex Graph", "[Graph Algorithms]") {
    WUSGraph<int, int> graph;
    WUSGraphClient<int, int> c;

    // 添加顶点
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addVertex(6);
    graph.addVertex(7);
    graph.addVertex(8);
    graph.addVertex(9);

    // 添加边
    graph.addEdge(1, 2, 4);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 2);
    graph.addEdge(2, 4, 5);
    graph.addEdge(3, 4, 8);
    graph.addEdge(3, 5, 10);
    graph.addEdge(4, 5, 2);
    graph.addEdge(5, 6, 1);
    graph.addEdge(6, 7, 7);
    graph.addEdge(7, 8, 6);
    graph.addEdge(8, 9, 12);
    graph.addEdge(7, 9, 5);
    graph.addEdge(5, 9, 8);

    // 运行算法
    int start_vertex = 1;
    //c.Dijkstra(graph, start_vertex);
    c.Prim(graph);

    // 可以添加一些 REQUIRE 语句来验证算法的正确性
}
