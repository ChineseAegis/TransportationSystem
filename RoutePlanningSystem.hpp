#pragma once
#include "WUSGraph.hpp"
#include "WUSGraphClient.hpp"
#include"DbLinkedList.hpp"
#include"HashMap.hpp"
#include"Neighbors.hpp"
#include"Tree.hpp"
#include"Forest.hpp"
#include"ExpandableArrayList.hpp"
#include <string>
#include<iostream>
template<class Object,class Weight>
class RoutePlanningSystem : public WUSGraphClient<Object, Weight> {
private:
    HashMap<Object, bool> toVisitMap;
public:
    RoutePlanningSystem() {
        // ���� 3.1 ��ʼ������·�߹滮ϵͳ
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
        // ���� 3.3 ���ļ������ݽ������н�ͨ��
    }
    //������
    void printcitynum(WUSGraph<Object, Weight>& g) {
        std::cout << g.vertexCount() << std::endl;
    }
    //������г���
    void printcity(WUSGraph<Object, Weight>& g) {
        Object* vertexs = g.getVertices();
        for (auto u : vertexs) {
            std::cout << u;
        }
        std::cout << std::endl;
    }
    //������е�·
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
    //ϡ��̶�
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
   //��ͨ��������
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
   ///���ĳ�������� �ĳ�����
   void neighbornum(WUSGraph<Object, Weight>& g,Object city){
       std::cout << g.Degree(city) << std::endl;
   }
   //��ĳ����·�ľ���ֵ
   void citysdistance(WUSGraph<Object, Weight>& g, Object city1, Object city2) {
       std::cout << g.getWeight(city1, city2) << std::endl;
   }
   //���ĳ���е������ڽӳ���
   void printneighbors(WUSGraph<Object, Weight>& g, Object city) {
       Object* neighbors = g.getNeighbors(city).object;
       for (auto u : neighbors) {
           std::cout << u << " ";
       }
       std::cout << std::endl;
   }
   //���ڵĳ��������ĳ���
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
   //����Ӹ�������������Ե�������ж���
   void getcitys(WUSGraph<Object, Weight>& g,Object city) {
       DFS(g, visit, city);
   }
   //�������������·��
   int getmsf(WUSGraph<Object, Weight>& g, Object city1, Object city2) {
       Tree<Object, Weight>msf; int mdis;
       Dijkstra(g, city1, msf);
       mdis=msf.findmdistance(city2);
       return mdis;
   }
   //�����������·��
   int getlpt(WUSGraph<Object, Weight>& g, Object city1, Object city2) {
       Tree<Object, Weight>lpt; int mdis;
       LongestPath(g, city1, msf);
       mdis = lpt.findmdistance(city2);
       return mdis;
   }
   //�Ӹ������� s ������ ���� s �ľ�����С�ĳ���Ϊ����
   void disfirst(WUSGraph<Object, Weight>& g, Object city) {
       Tree<Object, Weight>msf; 
       Dijkstra(g, city1, msf);
       Object* vertexs = g.getVertices();
       int count = g.vertexCount();
       std::cout << city << "->";
       int dis; int total;
       for (int i = 1; i < count; i++) {
           std::cout << msf[i];
           dis = msf.findmdistance(msf[i]);
           total += dis;
           std::cout << "(" << dis << ")->";
       }
       std::cout << "�ܾ��룺" << total << std::endl;
   }
   //��̵ĵ�·Ϊ����
   void edgefirst(WUSGraph<Object, Weight>& g) {
       Forest<Object, Weight>msf;
       Kruskal(g, msf);
       int count = g.vertexCount();
       std::cout << msf[0]; int dis, total;
       for (int i = 1; i < count; i++) {
           std::cout << msf[i];
           dis = g.getWeight(msf[i - 1], msf[i]);
           total += dis;
           std::cout<< "(" << dis << ")->";
       }
       std::cout << "�ܾ��룺" << total << std::endl;
   }
   //�û�һ��֪����Χ���г���
   void cityfromR(WUSGraph<Object, Weight>& g, Object city,int R) {
       Tree<Object, Weight>msf;
       Dijkstra(g, city1, msf);
       Object* vertexs = g.getVertices();
       int count = g.vertexCount();
       int dis; int total=0;
       for (int i = 1; i < count; i++) {
           dis = msf.findmdistance(city);
           if (dis <= R)std::cout << msf[i] << " ";
           total++;
       }
       std::cout << "R�ڳ�������" << total << std::endl;
   }
   //�����û�����Ȥ��һ�����ظ��ĳ���
   void intestcity(WUSGraph<Object, Weight>& g) {
       std::cout << "�������������" << std::endl;
       int n; std::cin >> n;
       ExpandableArrayList<Object>citys(n);
       int i = 0;
       std::cout << "��������У�" << std::endl;
       WUSGraph<Object, Weight>G;
       while (n--) {
           std::cin >> citys[i];
           G.addVertex(citys[i]);
           i++;
       }
       for (i = 0; i < n; i++) {
           Neighbors<Object, Weight>neighbors = g.getNeighbors(citys[i]).object;
           
           for (int j = i+1; j < n; j++) {
               for (auto u : neighbors) {
                   if (citys[j] == u) {
                       G.addEdge(citys[i], citys[j], g.getWeight(citys[i], citys[j]));
                   }
               }
           }
       }
       Forest<Object, Weight>msf;
       Kruskal(G, msf);
       std::cout << msf[0]; int dis, total;
       for (int i = 1; i < n; i++) {
           std::cout << msf[i];
           dis = g.getWeight(msf[i - 1], msf[i]);
           total += dis;
           std::cout << "(" << dis << ")->";
       }
       std::cout << "�ܾ��룺" << total << std::endl;

   }
};
