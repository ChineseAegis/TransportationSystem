#pragma once
#include "WUSGraph.hpp"
#include "WUSGraphClient.hpp"
#include"DbLinkedList.hpp"
#include"HashMap.hpp"
#include"Neighbors.hpp"
#include"Tree.hpp"
#include <string>
#include<iostream>
template<class Object,class Weight>
class RoutePlanningSystem : public WUSGraphClient<Object, Weight> {
private:
    HashMap<Object, bool> toVisitMap;
public:
    RoutePlanningSystem() {
        // 任务 3.1 初始化城市路线规划系统
    }

    void addCity(WUSGraph<Object, Weight>& g,Object city) {
        if (!g.isVertex(city))
        {
            g.addVertex(city);
        }
    }

    void removeCity(WUSGraph<Object, Weight>& g,Object city) {
        if (g.isVertex(city)) {
            g.removeVertex(city);
        }
    }

    void updataCity(WUSGraph<Object, Weight>& g, Object city,Object newcity) {
        Neighbors<Object, Weight>neighbors = g.getNeighbors(city).object;
        int* weight = g.getNeighbors(city).weight;
        if (g.isVertex(city)) {
            g.removeVertex(city);
        }
        g.addVertex(newcity); int i = 0;
        for (auto u : neighbors) {
            g.addEdge(newcity, u, weight[i]);
        }
    }
    void addedge(WUSGraph<Object, Weight>& g, Object city1, Object city2, Weight weight) {
        if (!g.isEdge(city1, city2))
        {
            g.addEdge(city1, city2, weight);
        }
    }

    void removeedge(WUSGraph<Object, Weight>& g, Object city1, Object city2) {
        if (g.isEdge(city1, city2)) {
            g.removeEdge(city1, city2);
        }
    }
    void updataefge(WUSGraph<Object, Weight>& g, Object city1, Object city2, Object newcity1, Object newcity2, Weight weight) {
        if (g.isEdge(city1, city2)) {
            g.removeEdge(city1, city2);
            g.addEdge(newcity1, newcity2, weight);
        }
    }
    void createGraphFromFile(std::string filepath) {
        // 任务 3.3 从文件读数据建立城市交通库
    }
    void printcitynum(WUSGraph<Object, Weight>& g) {
        std::cout << g.vertexCount() << std::endl;
    }
    void printcity(WUSGraph<Object, Weight>& g) {
        Object* vertexs = g.getVertices();
        for (auto u : vertexs) {
            std::cout << u;
        }
        std::cout << std::endl;
    }
    void printedge(WUSGraph<Object, Weight>& g) {
        DbLinkedList<Object>* visited;
        Object* vertexs = g.getVertices();
        for (auto u : vertexs) {
            std::cout << u << "-> ";
            Object* neighbors = g.getNeighbors(u);
            for (auto n : neighbors) {
                if (visited->Search(n) = nullptr) {
                    std::cout << n<<" ";
                    visited->Insert(n);
                }
            }
            std::cout << std::endl;
        }
    }
   int Sparseness(WUSGraph<Object, Weight>& g) {
        Object* vertexs = g.getVertices();
        int degreesum, vertexnum = g.vertexCount();
        for (auto u : vertexs) {
            degreesum += g.Degree(u);
        }
        int sparseness = (degreesum / vertexnum)--vertexnum;
        if (sparseness >= 0 && sparseness <= 1)return sparseness;
   }
   void countConnectedhelper(Object city,HashMap<Object,bool>visited, WUSGraph<Object, Weight>& g) {
       visited.Remove(city); visited.Insert(std::make_pair(city, true);
       for (auto n : g.getNeighbors(city).object) {
           if (!visited.getValue(city)) {
               countConnectedhelper(n, visited, g);
           }
       }
   }
    int countConnected(WUSGraph<Object, Weight>& g) {
        int componentCount = 0;
        Object* vertices = g.getVertices();
        int n = g.vertexCount();
        for (int i = 0; i < n; i++)toVisitMap.Insert(std::make_pair(vertexs[i], false));

        for (int i = 0; i < n; i++) {
            if (!toVisitMap[vertices[i]]) {
                countConnectedhelper(vertices[i], toVisitMap,g);
                componentCount++;
            }
        }
        return componentCount;
    }
   bool isCity(WUSGraph<Object, Weight>& g, Object city) {
       return g.isVertex(city);
   }
   bool isEdge(WUSGraph<Object, Weight>& g, Object city1, Object city2) {
       return g.isEdge(city1, city2);
   }
   void neighbornum(WUSGraph<Object, Weight>& g,Object city){
       std::cout << g.Degree(city) << std::endl;
   }
   void citysdistance(WUSGraph<Object, Weight>& g, Object city1, Object city2) {
       std::cout << g.getWeight(city1, city2) << std::endl;
   }
   void printneighbors(WUSGraph<Object, Weight>& g, Object city) {
       Object* neighbors = g.getNeighbors(city).object;
       for (auto u : neighbors) {
           std::cout << u << " ";
       }
       std::cout << std::endl;
   }
   void Maxneighborcity(WUSGraph<Object, Weight>& g) {
       Object* vertexs = g.getVertices();
       Object goal = vertexs[0];
       int n = g.vertexCount();

       for (int i = 0; i < n; i++) {
           if (g.Degree[vertexs[i]]< g.Degree(vertexs[i + 1])) {
               goal = vertexs[i + 1];
           }
       }
       std::cout << goal << std::endl;
   }
   void* visit(Object x) {
       std::cout << x << " ";
   }
   void getcitys(WUSGraph<Object, Weight>& g,Object city) {
       DFS(g, visit, city);
   }
   int getmsf(WUSGraph<Object, Weight>& g, Object city1, Object city2) {
       Tree<Object, Weight>msf; int mdis;
       Dijkstra(g, city1, msf);
       mdis=msf.findmdistance(city2);
       return mdis;
   }
   int getlpt(WUSGraph<Object, Weight>& g, Object city1, Object city2) {
       Tree<Object, Weight>lpt; int mdis;
       LongestPath(g, city1, msf);
       mdis = lpt.findmdistance(city2);
       return mdis;
   }
};
