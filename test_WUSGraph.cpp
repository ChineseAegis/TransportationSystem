//#include "memory_leak.h"
#include "catch.hpp"
#include"WUSGraph.hpp"
#include"Neighbors.hpp"
#include"WUSGraphClient.hpp"
using TestGraph = WUSGraph<int, int>; 

TEST_CASE("WUSGraph functionality", "[WUSGraph]") {
    TestGraph graph;

    SECTION("Add and check vertex") {
        // Test adding a vertex
        graph.addVertex(1);
        REQUIRE(graph.isVertex(1) == true);

        // Test adding another vertex
        graph.addVertex(2);
        REQUIRE(graph.isVertex(2) == true);
    }

    SECTION("Remove vertex") {
        // Add then remove a vertex
        graph.addVertex(3);
        graph.removeVertex(3);
        REQUIRE(graph.isVertex(3) == false);
    }

    SECTION("Vertex count") {
        // Test the vertex count
        graph.addVertex(4);
        graph.addVertex(5);
        REQUIRE(graph.vertexCount() == 2);
    }
}
TEST_CASE("Vertex Addition and Count", "[WUSGraph]") {
    WUSGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);

    REQUIRE(graph.vertexCount() == 2);
}

TEST_CASE("Edge Addition and Count", "[WUSGraph]") {
    WUSGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 10);

    REQUIRE(graph.edgeCount() == 1);
}

TEST_CASE("Vertex Removal", "[WUSGraph]") {
    WUSGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.removeVertex(1);

    REQUIRE(graph.vertexCount() == 1);
    REQUIRE_FALSE(graph.isVertex(1));
}

TEST_CASE("Edge Removal", "[WUSGraph]") {
    WUSGraph<int, int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addEdge(1, 2, 10);
    graph.removeEdge(1, 2);

    REQUIRE(graph.edgeCount() == 0);
    REQUIRE_FALSE(graph.isEdge(1, 2));
}
TEST_CASE("Add Removal Neighbors", "[WUSGraph]")
{
    WUSGraph<std::string, int> g;
    g.addVertex("����");
    g.addVertex("�麣");
    g.addVertex("����");
    REQUIRE(g.vertexCount() == 3);
    g.addEdge("����", "�麣", 100);
    g.addEdge("����", "����", 90);
    g.addEdge("�麣", "����", 200);
    REQUIRE(g.edgeCount() == 3);
    Neighbors<std::string,int> nei= g.getNeighbors("����");
    REQUIRE(nei.object[0] == "�麣");
    REQUIRE(nei.object[1] == "����");
    REQUIRE(nei.weight[0] == 100);
    REQUIRE(nei.weight[1] == 90);
    g.addVertex("���");
    REQUIRE(g.vertexCount() == 4);
    
    g.addEdge("���", "����", 30);
    g.addEdge("���", "�麣", 250);

    REQUIRE(g.edgeCount() == 5);
    g.removeEdge("����", "����");
    Neighbors<std::string, int> nei2 = g.getNeighbors("����");
    REQUIRE(nei2.size == 1);
    REQUIRE(nei2.object[0] == "�麣");

}
TEST_CASE("Vertex and Edge Addition and Removal", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // ��Ӷ���
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    REQUIRE(g.vertexCount() == 3);

    // ��ӱ�
    g.addEdge("A", "B", 1);
    g.addEdge("B", "C", 2);
    REQUIRE(g.edgeCount() == 2);

    // ɾ������
    g.removeVertex("A");
    REQUIRE(g.vertexCount() == 2);
    REQUIRE(g.edgeCount() == 1); // ��֤��Ҳ��ɾ��

    // ɾ����
    g.removeEdge("B", "C");
    REQUIRE(g.edgeCount() == 0);
}

TEST_CASE("Vertex and Edge Existence", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");
    g.addEdge("A", "B", 1);

    REQUIRE(g.isVertex("A") == true);
    REQUIRE(g.isVertex("C") == false);
    REQUIRE(g.isEdge("A", "B") == true);
    REQUIRE(g.isEdge("B", "A") == true); // ���������ͼ����Ӧ���� true
}

TEST_CASE("Retrieving Vertices and Neighbors", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 2);

    auto vertices = g.getVertices();
    REQUIRE(std::find(vertices, vertices + g.vertexCount(), "A") != vertices + g.vertexCount());
    REQUIRE(std::find(vertices, vertices + g.vertexCount(), "B") != vertices + g.vertexCount());

    auto neighbors = g.getNeighbors("A");
    REQUIRE(neighbors.size == 2);
    bool foundB = (neighbors.object[0] == "B" || neighbors.object[1] == "B");
    bool foundC = (neighbors.object[0] == "C" || neighbors.object[1] == "C");
    REQUIRE(foundB);
    REQUIRE(foundC);
    delete[] vertices;
}


TEST_CASE("Exception Handling", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // ��������ظ��Ķ�����
    g.addVertex("A");
    //REQUIRE_THROWS_AS(g.addVertex("A"), std::runtime_error); // �����ظ���Ӷ�����׳��쳣

    // ����ɾ�������ڵĶ�����
    //REQUIRE_THROWS_AS(g.removeVertex("Z"), std::runtime_error); // ����ɾ�������ڵĶ�����׳��쳣
    //REQUIRE_THROWS_AS(g.removeEdge("A", "Z"), std::runtime_error); // ����ɾ�������ڵı߻��׳��쳣
}

TEST_CASE("Performance Testing", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // ��Ӵ�������ͱ�
    for(int i = 0; i < 1000; ++i) {
        g.addVertex("V" + std::to_string(i));
    }
    for(int i = 0; i < 999; ++i) {
        g.addEdge("V" + std::to_string(i), "V" + std::to_string(i+1), i);
    }

    // ��֤����ͱߵ�����
    REQUIRE(g.vertexCount() == 1000);
    REQUIRE(g.edgeCount() == 999);
}
//TEST_CASE("CreatGraph", "[WUSClient]")
//{
//    WUSGraphClient<std::string, int> c;
//    WUSGraph<std::string, int> g;
//    c.CreateGraphFromFile("usa.txt", g);
//}