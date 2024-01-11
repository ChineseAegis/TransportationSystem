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
    WUSGraph<Object, Weight>& g;
    HashMap<int, Object>toObjectMap;
    HashMap<Object, int>tointMap;
public:
    RoutePlanningSystem() : WUSGraphClient<Object, Weight>() {}

    void addCity(Object city) {
        if (!g.isVertex(city))
        {
            g.addVertex(city);
        }
    }

    void removeCity(Object city) {
        if (g.isVertex(city)) {
            g.removeVertex(city);
        }
    }

    void updataCity( Object city,Object newcity) {
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
    void addedge( Object city1, Object city2, Weight weight) {
        if (!g.isEdge(city1, city2))
        {
            g.addEdge(city1, city2, weight);
        }
    }

    void removeedge(Object city1, Object city2) {
        if (g.isEdge(city1, city2)) {
            g.removeEdge(city1, city2);
        }
    }
    void updataefge( Object city1, Object city2, Object newcity1, Object newcity2, Weight weight) {
        if (g.isEdge(city1, city2)) {
            g.removeEdge(city1, city2);
            g.addEdge(newcity1, newcity2, weight);
        }
    }
    
    // 从文件读数据建立城市交通库
    void createFromfile(const string& filepath) {
        this->CreateGraphFromFile(filepath, g);
    }
    //城市数
    void printcitynum() {
        std::cout << g.vertexCount() << std::endl;
    }
    //输出所有城市
    void printcity() {
        Object* vertexs = g.getVertices();
        for (auto u : vertexs) {
            std::cout << u;
        }
        std::cout << std::endl;
    }
    //相邻城市间的道路数（不重复）
    void getRouteCount() {
        std::cout << "相邻城市间的道路数为" << g.edgeCount() / 2 << std::endl;
    }
    //输出所有道路
    void printedge() {
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
    //稀疏程度
   void Sparseness() {
        Object* vertexs = g.getVertices();
        int degreesum, vertexnum = g.vertexCount();
        for (auto u : vertexs) {
            degreesum += g.Degree(u);
        }
        int sparseness = (degreesum / vertexnum)/--vertexnum;
        if (sparseness >= 0 && sparseness <= 1)std::cout<< sparseness<<std::endl;
   }
   void countConnectedhelper(Object city,HashMap<Object,bool>visited) {
       visited.Remove(city); visited.Insert(std::make_pair(city, true);
       for (auto n : g.getNeighbors(city).object) {
           if (!visited.getValue(city)) {
               countConnectedhelper(n, visited, g);
           }
       }
   }
   //连通分量个数
    void countConnected() {
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
        std::cout<<componentCount<<std::endl;
    }
    //每一个连通分量是否有环且输出环路
    void hasCycleInConnectedComponent( int current, int parent, DbLinkedList<int>& visited, DbLinkedList<int>& currentPath, DbLinkedList<int>& hasvisited) {
        visited.Insert(current);
        currentPath.Insert(current);
        hasvisited.Insert(current);
        Object* neighbors = g.getNeighbors(current).object;
        int neighbor_size = g.getNeighbors(current).size;
        for (int i = 0; i < neighbor_size;i++) {
            int toint = tointMap.getValue(neighbors[i]);
            if (visited.Search(toint) == nullptr) {
                // 如果邻居未被访问，递归检查邻居是否形成回路
                hasCycleInConnectedComponent(toint, current, visited, currentPath, hasvisited);
            }
            else if (toint != parent && hasvisited.Search(toint) != nullptr) {
                // 如果邻居已被访问，并且不是当前节点的父节点，说明存在回路
                // 输出回路
                printCycle(currentPath, toint);
            }
        }

        // 当前节点处理完毕后，从路径中移除
        currentPath.Remove(current);
        hasvisited.Remove(current);
    }

    void printCycle(DbLinkedList<int>& cycle, int trg) {
        std::cout << "has cycle:";
        for (int i = cycle.head->rlink; i != cycle.head->llink; ) {
            Object cur = toObjectMap.getValue(i);
            cout << cur << " ";
            i = i->rlink;
        }
        std::cout << std::endl;
    }

    void findAndPrintCycles() {
        DbLinkedList<int> visited;
        DbLinkedList<int> currentPath;
        DbLinkedList<int> curvisited;
        Object* vertexs = g.getVertices();
        int vertex_size = g.vertexCount();
        for (int i = 0; i < vertex_size; i++) { 
            toObjectMap.Insert(std::make_pair(i, vertexs[i])); 
            tointMap.Insert(std::make_pair(vertexs[i], i));
        }
        for (int j = 0; j < vertex_size;j++) {
            if (visited.Search(vertex)==nullptr) {
                // 对于每个未被访问的节点，进行深度优先搜索，并检查是否存在回路
                hasCycleInConnectedComponent( j, -1, visited, currentPath, curvisited);
            }
        }
    }
   bool isCity( Object city) {
       return g.isVertex(city);
   }
   bool isEdge( Object city1, Object city2) {
       return g.isEdge(city1, city2);
   }
   ///输出某城市相邻 的城市数
   void neighbornum(Object city){
       std::cout <<"该城市相邻城市数："<< g.Degree(city) << std::endl;
   }
   //求某条道路的距离值
   void citysdistance(Object city1, Object city2) {
       std::cout << "该道路距离值："<<g.getWeight(city1, city2) << std::endl;
   }
   //输出某城市的所有邻接城市
   void printneighbors(Object city) {
       Object* neighbors = g.getNeighbors(city).object;
       for (auto u : neighbors) {
           std::cout << u << " ";
       }
       std::cout << std::endl;
   }
   //相邻的城市数最多的城市
   void Maxneighborcity() {
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
   //输出从给定顶点出发可以到达的所有顶点
   void getcitys(Object city) {
       this->DFS(g, visit, city);
   }
   //任意两城市最短路径
   void getmsf( Object city1, Object city2) {
       Tree<Object, Weight>msf; int mdis;
       this->Dijkstra(g, city1, msf);
       mdis=msf.findmdistance(city2);
       std::cout << "最短距离为" << mdis << std::endl;
   }
   //任意两城市最长路径
   void getlpt(Object city1, Object city2) {
       Tree<Object, Weight>lpt; int mdis;
       this->LongestPath(g, city1, msf);
       mdis = lpt.findmdistance(city2);
       std::cout << "最长距离为" << mdis << std::endl;
   }
   //从给定城市 s 出发， 以与 s 的距离最小的城市为优先
   void disfirst( Object city) {
       Tree<Object, Weight>msf; 
       this->Dijkstra(g, city1, msf);
       Object* vertexs = g.getVertices();
       int count = g.vertexCount();
       int dis, total;
       for (int i = 1; i < count; i++) {

           dis = g.getWeight(msf[i - 1], msf[i]);
           total += dis;
       }
        msf.printWholeTree();
       std::cout << "总距离：" << total << std::endl;
       delete[]vertexs;
   }
   //给定城市 s 出发，以与所选择的城市集合的距离最小的城市为优先
   void fromSToSet(Object city) {
       Forest<Object, Weight>msf;
       this->Prim(g, msf);
       int count = g.vertexCount();
         int dis, total;
       for (int i = 1; i < count; i++) {
   
           dis = g.getWeight(msf[i - 1], msf[i]);
           total += dis;
       }
       msf.printWholeForest();
       std::cout << "总距离：" << total << std::endl;
   }
   
   //最短的道路为优先
   void edgefirst() {
       Forest<Object, Weight>msf;
       this->Kruskal(g, msf);
       int count = g.vertexCount();
       int dis, total;
       for (int i = 1; i < count; i++) {
           
           dis = g.getWeight(msf[i - 1], msf[i]);
           total += dis;
          
       }
       msf.printWholeForest();
       std::cout << "总距离：" << total << std::endl;
   }
   //用户一键知晓周围所有城市
   void cityfromR( Object city,int R) {
       Tree<Object, Weight>msf;
       this->Dijkstra(g, city1, msf);
       Object* vertexs = g.getVertices();
       int count = g.vertexCount();
       int dis; int total=0;
       for (int i = 1; i < count; i++) {
           dis = msf.findmdistance(city);
           if (dis <= R)std::cout << msf[i] << " ";
           total++;
       }
       std::cout << "R内城市数：" << total << std::endl;
       delete[]vertexs;
   }
   //连接用户感兴趣的一组无重复的城市
   void interestedcity() {
       std::cout << "请输入城市数：" << std::endl;
       int n; std::cin >> n;
       ExpandableArrayList<Object>citys(n);
       int i = 0;
       std::cout << "请输入城市：" << std::endl;
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
       this->Kruskal(G, msf);
       int dis, total;
       for (int i = 1; i < n; i++) {
           
           dis = g.getWeight(msf[i - 1], msf[i]);
           total += dis;
           
       }
       msf.printWholeForest();
       std::cout << "总距离：" << total << std::endl;

   }
   void ManageMenu()
   {
       int tag = 1;
       while (tag)
       {
           system("cls");

           int choose;
           cout << "_____________________________" << endl
               << "1. 添加城市" << endl
               << "2. 更新城市信息" << endl
               << "3. 删除城市" << endl
               << "4. 添加道路" << endl
               << "5. 更新道路信息" << endl
               << "6. 删除道路" << endl
               << "7. 返回菜单" << endl
               << "_____________________________" << endl;
           cout << "您的选择:";
           cin >> choose;
           switch (choose)
           {
           case 1: { 
               Object city;
               std::cout << "请输入城市名" << endl;
               cin >> city;
               addCity(city);
               break; 
           }
           case 2: {
               Object city,newcity;
               std::cout << "请输入旧城市名" << endl;
               cin >> city;
               std::cout << "请输入新城市名" << endl;
               cin >> newcity;
               updataCity(city, newcity);
               break;
           }
           case 3: {
               Object city;
               std::cout << "请输入城市名" << endl;
               cin >> city;
               removeCity( city);
               break;
           }
           case 4: {
               Object city1, city2; Weight weight;
               std::cout << "请输入城市1名" << endl;
               cin >> city1;
               std::cout << "请输入城市2名" << endl;
               cin >> city2;
               std::cout << "请输入道路权值" << endl;
               cin >> weight;
               addedge(city1, city2, weight);
               break;
           }
           case 5: {
               Object city1, city2;
               std::cout << "请输入旧城市1名" << endl;
               cin >> city1;
               std::cout << "请输入旧城市2名" << endl;
               cin >> city2;
               Object newcity1, newcity2; Weight weight;
               std::cout << "请输入新城市1名" << endl;
               cin >> newcity1;
               std::cout << "请输入新城市2名" << endl;
               cin >> newcity2;
               std::cout << "请输入新道路权值" << endl;
               cin >> weight;
               updataefge(city1, city2, newcity1, newcity2, weight);
               break;
           }
           case 6: {
               Object city1, city2; 
               std::cout << "请输入城市1名" << endl;
               cin >> city1;
               std::cout << "请输入城市2名" << endl;
               cin >> city2;
               removeedge(city1, city2);
               break;
           }
           case 7: tag = 0; break;
           default:cout << "Error Input" << endl; break;
           }
           system("pause");
       }
   }

   void MainMenu()
   {
       while (1)
       {
           system("cls");
           
           int choose;
           cout << endl;
           cout << "*******交通路线规划系统*******" << endl;
           cout << "_____________________________" << endl
               << "1. 输出所有城市" << endl
               << "2. 输出城市数" << endl
               << "3. 相邻城市间道路数" << endl
               << "4. 所有道路" << endl
               << "5. 交通图稀疏程度" << endl
               << "6. 城市信息管理" << endl
               << "6. 城市信息管理" << endl
               << "7. 输出某城市所有邻接城市" << endl
               << "8. 输出从给定城市出发可以到达的所有城市" << endl
               << "9. 相邻的城市数最多的城市" << endl
               << "10. 两个城市之间的最短简单路径和最短距离" << endl
               << "11. 与城市s距离优先的路线" << endl
               << "12. 从城市s出发,以与所选择城市集合距离最小的城市为优先的路线" << endl
               << "13. 道路优先的路线" << endl
               << "14. 某城市周围R公里内城市以及数目" << endl
               << "15. 用户感兴趣城市最短路线" << endl
               << "16. 两个城市之间的最长简单路径和最长距离" << endl
               << "17. 交通图连通分量个数" << endl
               << "18. 每一个连通分量是否有环且输出环路" << endl
               << "19. 判断是否有给定城市" << endl
               << "20. 判断是否有给定道路" << endl
               << "21. 输出某城市相邻的城市数" << endl
               << "22. 求某条道路的距离值" << endl
               << "23. 退出" << endl
               << "_____________________________" << endl;
           cout << "您的选择:";
           cin >> choose;
           switch (choose)
           {
           case 1: printcity(); break;
           case 2: printcitynum(); break;
           case 3: getRouteCount(); break;
           case 4: printedge(); break;
           case 5: Sparseness(); break;
           case 6: ManageMenu(); break;
           case 7: {
               Object city;
               std::cout << "请输入指定城市" << std::endl;
               cin >> city;
               printneighbors(city); break;
           }
           case 8: {
               Object city;
               std::cout << "请输入指定城市" << std::endl;
               cin >> city;
               getcitys( city); break;
           }
           case 9:  Maxneighborcity(g); break;
           case 10: {
               Object city1, city2;
               std::cout << "请输入城市1名" << endl;
               cin >> city1;
               std::cout << "请输入城市2名" << endl;
               cin >> city2;
               getmsf( city1, city2); break;
           }
           case 11: {
               Object city;
               std::cout << "请输入指定城市" << std::endl;
               cin >> city;
               disfirst( city); break;
           }
           case 12: {
               Object city;
               std::cout << "请输入指定城市" << std::endl;
               cin >> city;
               fromSToSet( city); break;
           }
           case 13: edgefirst(); break;
           case 14: {
               Object city;
               std::cout << "请输入指定城市" << std::endl;
               cin >> city;
               std::cout << "请输入范围R" << std::endl;
               int R; cin >> R;
               cityfromR( city, R); break;
           }
           case 15: interestedcity(); break;
           case 16: {
               Object city1, city2;
               std::cout << "请输入城市1名" << endl;
               cin >> city1;
               std::cout << "请输入城市2名" << endl;
               cin >> city2;
               getlpt(city1, city2); break;
           }
           case 17:countConnected(); break;
           case 18:findAndPrintCycles(); break;
           case 19: {
               Object city;
               std::cout << "请输入指定城市" << std::endl;
               cin >> city;
               if (!isCity( city)) { std::cout << "该城市不存在" << std::endl; }
               else{ std::cout << "该城市存在" << std::endl; }
               break;
           }
           case 20: {
               Object city1, city2;
               std::cout << "请输入城市1名" << endl;
               cin >> city1;
               std::cout << "请输入城市2名" << endl;
               cin >> city2;
               if (!isEdge( city1,city2)) { std::cout << "该道路不存在" << std::endl; }
               else { std::cout << "该道路存在" << std::endl; }
               break;
           }
           case 21: {
               Object city;
               std::cout << "请输入指定城市" << std::endl;
               cin >> city;
               neighbornum( city);
               break;
           }
           case 22: {
               Object city1, city2;
               std::cout << "请输入城市1名" << endl;
               cin >> city1;
               std::cout << "请输入城市2名" << endl;
               cin >> city2;
               citysdistance( city1, city2);
               break;
           }
           case 23:exit(1); break;
           default:
               cout << "Error Input" << endl;
               break;
           }
           system("pause");
       }

   }
};
