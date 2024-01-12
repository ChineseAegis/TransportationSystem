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
using namespace std;
template<class Object,class Weight>
class RoutePlanningSystem : public WUSGraphClient<Object, Weight> {
private:
   
    WUSGraph<Object, Weight> g;
    
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
        Neighbors<Object, Weight> nei = g.getNeighbors(city);
        Object*neighbors = nei.object;
        Weight* weight = nei.weight;
        int size = nei.size;
        if (!g.isVertex(city)) {
            return;
        }
        g.removeVertex(city);
        g.addVertex(newcity); int i = 0;

        for (int i = 0; i < size;i++) {
            g.addEdge(newcity, neighbors[i], weight[i]);
        }
    }
    void addedge( Object city1, Object city2, Weight weight) {
        if (!g.isEdge(city1, city2))
        {
            g.addEdge(city1, city2, weight);
        }
        else
        {
            std::cout << "道路已存在" << std::endl;
        }
    }

    void removeedge(Object city1, Object city2) {
        if (g.isEdge(city1, city2)) {
            g.removeEdge(city1, city2);
        }
        else
        {
            std::cout << "道路不存在" << std::endl;
        }
    }
    void updataefge( Object city1, Object city2,Weight weight) {
        if (g.isEdge(city1, city2)) {
            g.removeEdge(city1, city2);
            g.addEdge(city1, city2, weight);
        }
        else
        {
            std::cout << "道路不存在" << std::endl;
        }
    }
    
    // 从文件读数据建立城市交通库
    void createFromfile(const std::string& filepath) {
        this->CreateGraphFromFile2(filepath, g);
    }
    //城市数
    void printcitynum() {
        std::cout << g.vertexCount() << std::endl;
    }
    //输出所有城市
    void printcity() {
        Object* vertexs = g.getVertices();
        int size = g.vertexCount();
        for (int i = 0; i < size;i++) {
            std::cout << vertexs[i]<<" ";
        }
        std::cout << std::endl;
        delete[]vertexs;
    }
    //相邻城市间的道路数（不重复）
    void getRouteCount() {
        std::cout << "相邻城市间的道路数为" << g.edgeCount() << std::endl;
    }
    //输出所有道路
    void printedge() {
        DbLinkedList<Object>* visited = new DbLinkedList< Object>();
        Object* vertexs = g.getVertices();
        int size = g.vertexCount();
        for (int i = 0; i < size; i++) {
            
            Neighbors<Object, Weight>nei = g.getNeighbors(vertexs[i]);
            Object* neighbors = nei.object;
            int neighbors_size = nei.size;
            for (int j = 0; j < neighbors_size; j++) {
                if (visited->Search(neighbors[j]) == nullptr) {
                    std::cout << vertexs[i] << "-> ";
                    std::cout << neighbors[j] << " ";
                    std::cout << std::endl;
                }
            }
            visited->Insert(vertexs[i]);
            

        }
        delete visited;
        delete[] vertexs;
    }
    //稀疏程度
   void Sparseness() {
        Object* vertexs = g.getVertices();
        double vertexnum = g.vertexCount();
        double edgesum = g.edgeCount();
        //for (auto u : vertexs) {
        //    degreesum += g.Degree(u);
        //}
        double sparseness = (2*edgesum / vertexnum)/(vertexnum-1);
        if (sparseness >= 0 && sparseness <= 1)std::cout<< sparseness<<std::endl;
        delete[]vertexs;
   }
   //void countConnectedhelper(Object city, HashMap<Object, bool> &visited) {
   //    //visited.Remove(city);
   //    visited.Insert(std::make_pair(city, true));
   //    Neighbors<Object, Weight>nei = g.getNeighbors(city);
   //    Object* neighbors = nei.object;
   //    int neighbors_size = nei.size;
   //    for (int i = 0; i < neighbors_size;i++) {
   //        if (!visited.getValue(neighbors[i])) {
   //            countConnectedhelper(neighbors[i], visited);
   //        }
   //    }
   //    
   //}
   void countConnectedhelper(Object city, HashMap<Object, bool>& visited) {
       DbLinkedList<Object> stack;
       stack.push_back(city);

       while (!stack.isEmpty()) {
           Object currentCity = stack.top();
           stack.pop_back();

           if (!visited.getValue(currentCity)) {
               visited.Insert(std::make_pair(currentCity, true));

               Neighbors<Object, Weight> nei = g.getNeighbors(currentCity);
               Object* neighbors = nei.object;
               int neighbors_size = nei.size;

               for (int i = 0; i < neighbors_size; i++) {
                   if (!visited.getValue(neighbors[i])) {
                       stack.push_back(neighbors[i]);
                   }
               }
           }
       }
   }


   //连通分量个数
    void countConnected() {
        HashMap<Object, bool> toVisitMap;
        int componentCount = 0;
        Object* vertexs = g.getVertices();
        int n = g.vertexCount();
        for (int i = 0; i < n; i++)toVisitMap.Insert(std::make_pair(vertexs[i], false));

        for (int i = 0; i < n; i++) {
            if (!toVisitMap.getValue(vertexs[i])) {
                countConnectedhelper(vertexs[i], toVisitMap);
                componentCount++;
            }
        }
        std::cout<<componentCount<<std::endl;
        delete[]vertexs;
    }
    //每一个连通分量是否有环且输出环路
    void hasCycleInConnectedComponent(int current, int parent, DbLinkedList<int>& visited, DbLinkedList<int>& currentPath, DbLinkedList<int>& hasvisited) {
        visited.Insert(current);
        currentPath.Insert(current);
        hasvisited.Insert(current);
        Neighbors<Object, Weight>nei = g.getNeighbors(toObjectMap.getValue(current));
        Object* neighbors = nei.object;
        int neighbor_size = nei.size;
        for (int i = 0; i < neighbor_size; i++) {
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
        bool startPrinting = false;//确保两个有公共点的环重复输出
        for (DbListNode<int>* i = cycle.head->rlink; i != cycle.head; i = i->rlink) {
            if (i->data == trg) {//遍历打印路径直到找到环起始点
                startPrinting = true;
            }
            if (startPrinting) {
                Object cur = toObjectMap.getValue(i->data);
                std::cout << cur << " ";
            }
        }
        std::cout << std::endl;

    }

    void findAndPrintCycles() {
        HashMap<int, Object>toObjectMap;
        HashMap<Object, int>tointMap;
        DbLinkedList<int> visited;
        DbLinkedList<int> currentPath;
        DbLinkedList<int> curvisited;
        Object* vertexs = g.getVertices();
        int vertex_size = g.vertexCount();
        for (int i = 0; i < vertex_size; i++) {
            toObjectMap.Insert(std::make_pair(i, vertexs[i]));
            tointMap.Insert(std::make_pair(vertexs[i], i));
        }
        for (int j = 0; j < vertex_size; j++) {
            if (visited.Search(j) == nullptr) {
                // 对于每个未被访问的节点，进行深度优先搜索，并检查是否存在回路
                hasCycleInConnectedComponent(j, -1, visited, currentPath, curvisited);
            }
        }
        delete[]vertexs;
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
       Neighbors<Object, Weight> nei = g.getNeighbors(city);
       Object* neighbors = nei.object;
       int neighbors_size = nei.size;
       for (int i = 0; i < neighbors_size;i++) {
           std::cout << neighbors[i] << " ";
       }
       std::cout << std::endl;
       
   }
   //相邻的城市数最多的城市
   void Maxneighborcity() {
       Object* vertexs = g.getVertices();
       Object goal = vertexs[0];
       int n = g.vertexCount();

       for (int i = 0; i < n-1; i++) {
           if (g.Degree(goal)< g.Degree(vertexs[i + 1])) {
               goal = vertexs[i + 1];
           }
       }
       std::cout << goal << std::endl;
       delete[] vertexs;
   }
   static void visit(Object x) {
       std::cout << x << " ";
   }
   //输出从给定顶点出发可以到达的所有顶点
   void getcitys(Object city) {
       this->DFS(g,&RoutePlanningSystem::visit, city);
   }
   //任意两城市最短路径
   void getmsf( Object city1, Object city2) {
       Tree<Object, Weight>msf; Weight mdis=0;
       this->Dijkstra(g, city1, msf);
       mdis=msf.findmdistance(city2);
       std::cout << "最短距离为" << mdis << std::endl;
   }
   //任意两城市最长路径
   void getlpt(Object city1, Object city2) {
       Tree<Object, Weight>lpt; Weight mdis=0;
       this->LongestPath(g, city1, lpt);
       mdis = lpt.findmdistance(city2);
       std::cout << "最长距离为" << mdis << std::endl;
   }
   //从给定城市 s 出发， 以与 s 的距离最小的城市为优先
   void disfirst( Object city) {
       Tree<Object, Weight>msf; 
       this->Dijkstra(g, city, msf);
       int count = msf.getcount();
       Weight dis=0, total=0;
       for (int i = 0; i < count; i++) {
           if (g.isVertex(msf.getparent(msf[i])))
           {
               dis = g.getWeight(msf[i], msf.getparent(msf[i]));
               total += dis;
           }
       }
        msf.printWholeTree();
       std::cout << "总距离：" << total << std::endl;
   }
   //给定城市 s 出发，以与所选择的城市集合的距离最小的城市为优先
   void fromSToSet(Object city,ExpandableArrayList<Object>& cityArray) {
       HashMap<Object,int> cityMap;
       for (int i = 0; i < cityArray.size(); i++)
       {
           cityMap.Insert(std::make_pair(cityArray[i],i+1));
       }
       Forest<Object, Weight> msf;
       Tree<Object, Weight> tree;

       WUSGraph<Object, Weight> subg;
       this->Dijkstra(g, city, tree);
       Weight minDistance= std::numeric_limits<Weight>::max();
       Object targetCity;
       for (int i = 0; i < tree.getcount(); i++)
       {
           if (cityMap.containsKey(tree[i]))
           {
               if (tree.get_index_distance(i) < minDistance)
               {
                   minDistance = tree.get_index_distance(i);
                   targetCity = tree[i];
               }
           }
       }
       if (cityMap.containsKey(targetCity))
       {
           Weight distance1=tree.findmdistance(targetCity);
           this->CreateSubgraph(g, cityArray, subg);
           this->Prim(subg, msf);
           int count = msf.getCount();
           Weight dis = 0, total = 0;
           for (int i = 0; i < count; i++) {
               if (g.isVertex(msf.getparent(msf[i])))
               {
                   dis = g.getWeight(msf[i], msf.getparent(msf[i]));
                   total += dis;
               }
           }

           msf.printWholeForest();
           std::cout << "总距离：" << total+distance1 << std::endl;
       }
   }
   
   //最短的道路为优先
   void edgefirst() {
       Forest<Object, Weight>msf;
       this->Prim(g, msf);
       int count = msf.getCount();
       Weight  total=0;
       total = msf.findmdistance();
       msf.printWholeForest();
       std::cout << "总距离：" << total << std::endl;
   }
   //用户一键知晓周围所有城市
   void cityfromR( Object city,int R) {
       Tree<Object, Weight>msf;
       this->Dijkstra(g, city, msf);
       //Object* vertexs = g.getVertices();
       int count = msf.getcount();
        int total=0;
       for (int i = 0; i < count; i++) {
           if (msf[i] == city)continue;
           Weight dis = msf.get_index_distance(i);
           if (dis <= R) {
               std::cout<<msf[i]<<" ";
               total++;
           }
           
       }
       std::cout << "R内城市数：" << total << std::endl;
       //delete[]vertexs;
   }
   //连接用户感兴趣的一组无重复的城市
   void interestedcity() {
       std::cout << "请输入城市数：" << std::endl;
       int n; std::cin >> n;
       ExpandableArrayList<Object>citys;
       std::cout << "请输入城市：" << std::endl;
       Object city;
       while (n--) {
           std::cin >> city;
           citys.add(city);
           
       }
       Forest<Object, Weight>msf;
       this->Steiner(g, citys, msf);
       Weight total=0;
       total = msf.findmdistance();
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
               << "1. 所有城市" << endl
               << "2. 所有道路" << endl
               << "3. 添加城市" << endl
               << "4. 更改城市名" << endl
               << "5. 删除城市" << endl
               << "6. 添加道路" << endl
               << "7. 更改道路权值" << endl
               << "8. 删除道路" << endl
               << "9. 返回菜单" << endl
               << "_____________________________" << endl;
           cout << "您的选择:";
           cin >> choose;
           switch (choose)
           {
           case 1: printcity(); break;
           case 2: printedge(); break;
           case 3: { 
               Object city;
               std::cout << "请输入城市名" << endl;
               cin >> city;
               if (g.isVertex(city))
               {
                   std::cout << "城市已存在" << std::endl;
                   break;
               }
               addCity(city);
               break; 
           }
           case 4: {
               Object city,newcity;
               std::cout << "请输入旧城市名" << endl;
               cin >> city;
               while (!g.isVertex(city))
               {
                   std::cout << "城市不存在，请重新输入" << std::endl;
                   cin >> city;
               }
               std::cout << "请输入新城市名" << endl;
               cin >> newcity;
               while (g.isVertex(newcity))
               {
                   std::cout << "城市名已存在，请重新输入" << std::endl;
                   cin >> newcity;
               }
               updataCity(city, newcity);
               break;
           }
           case 5: {
               Object city;
               std::cout << "请输入城市名" << endl;
               cin >> city;
               if (!g.isVertex(city))
               {
                   std::cout << "城市不存在" << std::endl;
               }
               removeCity( city);
               break;
           }
           case 6: {
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
           case 7: {
               Object city1, city2;
               std::cout << "请输入城市1名" << endl;
               cin >> city1;
               std::cout << "请输入城市2名" << endl;
               cin >> city2;
               Weight weight;
               std::cout << "请输入道路新权值" << endl;
               cin >> weight;
               updataefge(city1, city2,weight);
               break;
           }
           case 8: {
               Object city1, city2; 
               std::cout << "请输入城市1名" << endl;
               cin >> city1;
               std::cout << "请输入城市2名" << endl;
               cin >> city2;
               removeedge(city1, city2);
               break;
           }
           case 9: tag = 0; break;
           default:cout << "Error Input" << endl; break;
           }
           system("pause");
       }
   }

   void MainMenu()
   {
       int trg = 1;
       while (trg)
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
               << "23. 加载文件" << endl
               << "24. 退出" << endl
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
           case 9:  Maxneighborcity(); break;
           case 10: {
               Object city1, city2;
               std::cout << "请输入城市1名" << endl;
               cin >> city1;
               std::cout << "请输入城市2名" << endl;
               cin >> city2;
               if (!g.isVertex(city1) || !g.isVertex(city2))
               {
                   std::cout << "城市不存在" << std::endl;
                   break;
               }
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
               ExpandableArrayList<Object> subArray;
               std::cout << "请输入指定城市" << std::endl;
               cin >> city;
               int size=0;
               std::cout << "请输入城市集合的元素数量" << std::endl;
               std::cin >> size;
               while (size > g.vertexCount())
               {
                   std::cout << "请输入城市集合的元素数量" << std::endl;
                   std::cin >> size;
               }
               std::cout << "请输入城市" << std::endl;
               Object obj;
               while (size--)
               {
                   std::cin >> obj;
                   if (g.isVertex(obj))
                   {
                       subArray.add(obj);
                   }
                   else
                   {
                       std::cout << "城市不存在" << std::endl;
                       size++;
                   }
               }
               fromSToSet(city,subArray); break;
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
           case 23: {
               this->createFromfile("usa_small.txt");
               std::cout << "加载成功" << std::endl;
               break;
           }
           case 24:trg = 0; break;
           default:
               cout << "Error Input" << endl;
               break;
           }
           system("pause");
       }

   }
};
