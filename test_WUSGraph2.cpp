#include "catch.hpp"
#include"WUSGraph.hpp"
#include"Neighbors.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include<map>

TEST_CASE("Empty Graph Properties", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    REQUIRE(g.vertexCount() == 0);
    REQUIRE(g.edgeCount() == 0);
}

TEST_CASE("Bulk Vertex and Edge Operations", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // ������Ӷ���
    for (int i = 0; i < 100; ++i) {
        g.addVertex("V" + std::to_string(i));
    }
    REQUIRE(g.vertexCount() == 100);

    // ������ӱ�
    for (int i = 0; i < 99; ++i) {
        g.addEdge("V" + std::to_string(i), "V" + std::to_string(i + 1), i + 1);
    }
    REQUIRE(g.edgeCount() == 99);

    // ����ɾ������
    for (int i = 0; i < 50; ++i) {
        g.removeVertex("V" + std::to_string(i));
    }
    REQUIRE(g.vertexCount() == 50);
    REQUIRE(g.edgeCount() == 49); // �����Ҳ��֮ɾ��
}

TEST_CASE("Special Case Edges", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");

    // ����Ի�
    g.addEdge("A", "A", 1);
    REQUIRE(g.edgeCount() == 1);

    // ����ر�
    g.addEdge("A", "B", 2);
    
    //REQUIRE_THROWS_AS(g.addEdge("A", "B", 3), std::runtime_error);
}

TEST_CASE("Degree Changes on Vertex and Edge Removal", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");

    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 1);

    REQUIRE(g.Degree("A") == 2);

    g.removeVertex("B");
    REQUIRE(g.Degree("A") == 1);

    g.removeEdge("A", "C");
    REQUIRE(g.Degree("A") == 0);
}

TEST_CASE("Exception Handling for Invalid Operations", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");

    // ����ظ�����
    REQUIRE_THROWS_AS(g.addVertex("A"), std::runtime_error);

    // ɾ�������ڵĶ���
    REQUIRE_THROWS_AS(g.removeVertex("Z"), std::runtime_error);

    // ��ӱ�ʱ����һ�����㲻����
    REQUIRE_THROWS_AS(g.addEdge("A", "Z", 1), std::runtime_error);

    // ɾ�������ڵı�
    REQUIRE_THROWS_AS(g.removeEdge("A", "Z"), std::runtime_error);
}

TEST_CASE("Performance Testing2", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // ��Ӵ�������
    for (int i = 0; i < 10000; ++i) {
        g.addVertex("V" + std::to_string(i));
    }

    // ��Ӵ�����
    for (int i = 0; i < 9999; ++i) {
        g.addEdge("V" + std::to_string(i), "V" + std::to_string(i + 1), i);
    }

    REQUIRE(g.vertexCount() == 10000);
    REQUIRE(g.edgeCount() == 9999);
}

TEST_CASE("Edge Weights and Retrieval", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");
    g.addEdge("A", "B", 10);

    REQUIRE(g.getWeight("A", "B") == 10);
    REQUIRE(g.getWeight("B", "A") == 10);
}

TEST_CASE("Graph Connectivity", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");

    g.addEdge("A", "B", 1);
    // ����� "B" �� "C" �ıߣ����������������ͨ����

    REQUIRE(g.isEdge("A", "B") == true);
    REQUIRE(g.isEdge("B", "C") == false);
}
TEST_CASE("getNeighbors Functionality", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // ��Ӷ���ͱ�
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");

    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 2);
    g.addEdge("A", "D", 3);

    // ��ȡ A ���ھ�
    Neighbors<std::string, int> neighbors = g.getNeighbors("A");

    // ����ھ�����
    REQUIRE(neighbors.size == 3);

    // ����һ���ھӺ�Ȩ�ص�ӳ��
    std::map<std::string, int> neighborMap;
    for (int i = 0; i < neighbors.size; ++i) {
        neighborMap[neighbors.object[i]] = neighbors.weight[i];
    }

    // ��֤�ھӺ�Ȩ��
    REQUIRE(neighborMap["B"] == 1);
    REQUIRE(neighborMap["C"] == 2);
    REQUIRE(neighborMap["D"] == 3);

    // ��֤�����ھӵĶ���
    REQUIRE(neighborMap.find("A") == neighborMap.end());
}

TEST_CASE("getNeighbors With No Neighbors", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");

    // ��ȡ A ���ھ�
    Neighbors<std::string, int> neighbors = g.getNeighbors("A");

    // ����ھ�����
    REQUIRE(neighbors.size == 0);
}

TEST_CASE("getNeighbors After Removing Edges", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // ��Ӷ���ͱ�
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");

    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 2);

    // ɾ��һ����
    g.removeEdge("A", "B");

    // ��ȡ A ���ھ�
    Neighbors<std::string, int> neighbors = g.getNeighbors("A");

    // ����ھ�����
    REQUIRE(neighbors.size == 1);

    // ��֤ʣ����ھӺ�Ȩ��
    REQUIRE(neighbors.object[0] == "C");
    REQUIRE(neighbors.weight[0] == 2);
}

// �������ܵĲ��Կ��԰����ض�����µ��ھӼ��������Ի����رߵȡ�
TEST_CASE("getNeighbors Basic Functionality", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 2);

    Neighbors<std::string, int> neighbors = g.getNeighbors("A");
    REQUIRE(neighbors.size == 2);

    std::map<std::string, int> expected = { {"B", 1}, {"C", 2} };
    for (int i = 0; i < neighbors.size; ++i) {
        REQUIRE(expected[neighbors.object[i]] == neighbors.weight[i]);
    }
}

TEST_CASE("getNeighbors With No Neighbors2", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");

    Neighbors<std::string, int> neighbors = g.getNeighbors("A");
    REQUIRE(neighbors.size == 0);
}

TEST_CASE("getNeighbors After Removing Edges2", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");
    g.addEdge("A", "B", 1);

    g.removeEdge("A", "B");

    Neighbors<std::string, int> neighbors = g.getNeighbors("A");
    REQUIRE(neighbors.size == 0);
}

TEST_CASE("getNeighbors After Removing Vertices2", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");
    g.addEdge("A", "B", 1);

    g.removeVertex("B");
  
    Neighbors<std::string, int> neighbors = g.getNeighbors("A");
    REQUIRE(neighbors.size == 0);
}

//TEST_CASE("getNeighbors With Self-Loops and Multiple Edges", "[WUSGraph]") {
//    WUSGraph<std::string, int> g;
//
//    g.addVertex("A");
//    g.addEdge("A", "A", 1); // Self-loop
//    g.addEdge("A", "A", 2); // Another self-loop
//
//    Neighbors<std::string, int> neighbors = g.getNeighbors("A");
//    REQUIRE(neighbors.size >= 1); // Depending on how self-loops are handled
//}

TEST_CASE("getNeighbors Exception Handling for Nonexistent Vertex", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    REQUIRE_THROWS_AS(g.getNeighbors("A"), std::runtime_error); // Assuming an exception is thrown for nonexistent vertices
}

TEST_CASE("getNeighbors Performance with Large Graph", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    for (int i = 0; i < 1000; ++i) {
        g.addVertex("V" + std::to_string(i));
    }
    for (int i = 0; i < 999; ++i) {
        g.addEdge("V" + std::to_string(i), "V" + std::to_string(i + 1), i);
    }

    Neighbors<std::string, int> neighbors = g.getNeighbors("V500");
    REQUIRE(neighbors.size > 0); // Validate the existence of neighbors
}
TEST_CASE("WUSGraph comprehensive functionality", "[WUSGraph]") {
    WUSGraph<int, int> graph;

    SECTION("Add Edges and Check Vertex Degrees") {
        graph.addVertex(1);
        graph.addVertex(2);
        graph.addVertex(3);
        graph.addEdge(1, 2, 10);
        graph.addEdge(2, 3, 20);

        REQUIRE(graph.Degree(1) == 1);
        REQUIRE(graph.Degree(2) == 2);
        REQUIRE(graph.Degree(3) == 1);
    }

    SECTION("Remove Vertex and Check Neighbors") {
        graph.addVertex(1);
        graph.addVertex(2);
        graph.addVertex(3);
        graph.addEdge(1, 2, 10);
        graph.addEdge(2, 3, 20);
        graph.removeVertex(2);

        REQUIRE(graph.Degree(1) == 0);
        REQUIRE_FALSE(graph.isEdge(1, 2));
        REQUIRE_FALSE(graph.isEdge(2, 3));
    }

    SECTION("Modify Edge Weight and Verify") {
        graph.addVertex(1);
        graph.addVertex(2);
        graph.addEdge(1, 2, 10);
        // Assuming there's a method to modify edge weight
        // graph.modifyEdgeWeight(1, 2, 15);
        // REQUIRE(graph.getWeight(1, 2) == 15);
    }

    SECTION("Verify Graph Integrity After Multiple Operations") {
        graph.addVertex(1);
        graph.addVertex(2);
        graph.addVertex(3);
        graph.addEdge(1, 2, 10);
        graph.addEdge(2, 3, 20);
        graph.removeEdge(1, 2);
        graph.addVertex(4);
        graph.addEdge(3, 4, 30);

        REQUIRE(graph.vertexCount() == 4);
        REQUIRE(graph.edgeCount() == 2);
        REQUIRE(graph.Degree(2) == 1);
        REQUIRE(graph.Degree(4) == 1);
    }

    // ... Additional comprehensive tests as needed
}