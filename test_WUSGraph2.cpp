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

    // 批量添加顶点
    for (int i = 0; i < 100; ++i) {
        g.addVertex("V" + std::to_string(i));
    }
    REQUIRE(g.vertexCount() == 100);

    // 批量添加边
    for (int i = 0; i < 99; ++i) {
        g.addEdge("V" + std::to_string(i), "V" + std::to_string(i + 1), i + 1);
    }
    REQUIRE(g.edgeCount() == 99);

    // 批量删除顶点
    for (int i = 0; i < 50; ++i) {
        g.removeVertex("V" + std::to_string(i));
    }
    REQUIRE(g.vertexCount() == 50);
    REQUIRE(g.edgeCount() == 49); // 假设边也随之删除
}

TEST_CASE("Special Case Edges", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");
    g.addVertex("B");

    // 添加自环
    g.addEdge("A", "A", 1);
    REQUIRE(g.edgeCount() == 1);

    // 添加重边
    g.addEdge("A", "B", 2);
    
    REQUIRE_THROWS_AS(g.addEdge("A", "B", 3), std::runtime_error);
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

    // 添加重复顶点
    REQUIRE_THROWS_AS(g.addVertex("A"), std::runtime_error);

    // 删除不存在的顶点
    REQUIRE_THROWS_AS(g.removeVertex("Z"), std::runtime_error);

    // 添加边时其中一个顶点不存在
    REQUIRE_THROWS_AS(g.addEdge("A", "Z", 1), std::runtime_error);

    // 删除不存在的边
    REQUIRE_THROWS_AS(g.removeEdge("A", "Z"), std::runtime_error);
}

TEST_CASE("Performance Testing2", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // 添加大量顶点
    for (int i = 0; i < 10000; ++i) {
        g.addVertex("V" + std::to_string(i));
    }

    // 添加大量边
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
    // 不添加 "B" 到 "C" 的边，保留两个分离的连通分量

    REQUIRE(g.isEdge("A", "B") == true);
    REQUIRE(g.isEdge("B", "C") == false);
}
TEST_CASE("getNeighbors Functionality", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // 添加顶点和边
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");
    g.addVertex("D");

    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 2);
    g.addEdge("A", "D", 3);

    // 获取 A 的邻居
    Neighbors<std::string, int> neighbors = g.getNeighbors("A");

    // 检查邻居数量
    REQUIRE(neighbors.size == 3);

    // 创建一个邻居和权重的映射
    std::map<std::string, int> neighborMap;
    for (int i = 0; i < neighbors.size; ++i) {
        neighborMap[neighbors.object[i]] = neighbors.weight[i];
    }

    // 验证邻居和权重
    REQUIRE(neighborMap["B"] == 1);
    REQUIRE(neighborMap["C"] == 2);
    REQUIRE(neighborMap["D"] == 3);

    // 验证不是邻居的顶点
    REQUIRE(neighborMap.find("A") == neighborMap.end());
}

TEST_CASE("getNeighbors With No Neighbors", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    g.addVertex("A");

    // 获取 A 的邻居
    Neighbors<std::string, int> neighbors = g.getNeighbors("A");

    // 检查邻居数量
    REQUIRE(neighbors.size == 0);
}

TEST_CASE("getNeighbors After Removing Edges", "[WUSGraph]") {
    WUSGraph<std::string, int> g;

    // 添加顶点和边
    g.addVertex("A");
    g.addVertex("B");
    g.addVertex("C");

    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 2);

    // 删除一条边
    g.removeEdge("A", "B");

    // 获取 A 的邻居
    Neighbors<std::string, int> neighbors = g.getNeighbors("A");

    // 检查邻居数量
    REQUIRE(neighbors.size == 1);

    // 验证剩余的邻居和权重
    REQUIRE(neighbors.object[0] == "C");
    REQUIRE(neighbors.weight[0] == 2);
}

// 其他可能的测试可以包括特定情况下的邻居检索，如自环、重边等。
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