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
            std::cout << "��·�Ѵ���" << std::endl;
        }
    }

    void removeedge(Object city1, Object city2) {
        if (g.isEdge(city1, city2)) {
            g.removeEdge(city1, city2);
        }
        else
        {
            std::cout << "��·������" << std::endl;
        }
    }
    void updataefge( Object city1, Object city2,Weight weight) {
        if (g.isEdge(city1, city2)) {
            g.removeEdge(city1, city2);
            g.addEdge(city1, city2, weight);
        }
        else
        {
            std::cout << "��·������" << std::endl;
        }
    }
    
    // ���ļ������ݽ������н�ͨ��
    void createFromfile(const std::string& filepath) {
        this->CreateGraphFromFile2(filepath, g);
    }
    //������
    void printcitynum() {
        std::cout << g.vertexCount() << std::endl;
    }
    //������г���
    void printcity() {
        Object* vertexs = g.getVertices();
        int size = g.vertexCount();
        for (int i = 0; i < size;i++) {
            std::cout << vertexs[i]<<" ";
        }
        std::cout << std::endl;
        delete[]vertexs;
    }
    //���ڳ��м�ĵ�·�������ظ���
    void getRouteCount() {
        std::cout << "���ڳ��м�ĵ�·��Ϊ" << g.edgeCount() << std::endl;
    }
    //������е�·
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
    //ϡ��̶�
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


   //��ͨ��������
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
    //ÿһ����ͨ�����Ƿ��л��������·
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
                // ����ھ�δ�����ʣ��ݹ����ھ��Ƿ��γɻ�·
                hasCycleInConnectedComponent(toint, current, visited, currentPath, hasvisited);
            }
            else if (toint != parent && hasvisited.Search(toint) != nullptr) {
                // ����ھ��ѱ����ʣ����Ҳ��ǵ�ǰ�ڵ�ĸ��ڵ㣬˵�����ڻ�·
                // �����·
                printCycle(currentPath, toint);
                
            }
        }

        // ��ǰ�ڵ㴦����Ϻ󣬴�·�����Ƴ�
        currentPath.Remove(current);
        hasvisited.Remove(current);
     
    }

    void printCycle(DbLinkedList<int>& cycle, int trg) {
        std::cout << "has cycle:";
        bool startPrinting = false;//ȷ�������й�����Ļ��ظ����
        for (DbListNode<int>* i = cycle.head->rlink; i != cycle.head; i = i->rlink) {
            if (i->data == trg) {//������ӡ·��ֱ���ҵ�����ʼ��
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
                // ����ÿ��δ�����ʵĽڵ㣬�����������������������Ƿ���ڻ�·
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
   ///���ĳ�������� �ĳ�����
   void neighbornum(Object city){
       std::cout <<"�ó������ڳ�������"<< g.Degree(city) << std::endl;
   }
   //��ĳ����·�ľ���ֵ
   void citysdistance(Object city1, Object city2) {
       std::cout << "�õ�·����ֵ��"<<g.getWeight(city1, city2) << std::endl;
   }
   //���ĳ���е������ڽӳ���
   void printneighbors(Object city) {
       Neighbors<Object, Weight> nei = g.getNeighbors(city);
       Object* neighbors = nei.object;
       int neighbors_size = nei.size;
       for (int i = 0; i < neighbors_size;i++) {
           std::cout << neighbors[i] << " ";
       }
       std::cout << std::endl;
       
   }
   //���ڵĳ��������ĳ���
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
   //����Ӹ�������������Ե�������ж���
   void getcitys(Object city) {
       this->DFS(g,&RoutePlanningSystem::visit, city);
   }
   //�������������·��
   void getmsf( Object city1, Object city2) {
       Tree<Object, Weight>msf; Weight mdis=0;
       this->Dijkstra(g, city1, msf);
       mdis=msf.findmdistance(city2);
       std::cout << "��̾���Ϊ" << mdis << std::endl;
   }
   //�����������·��
   void getlpt(Object city1, Object city2) {
       Tree<Object, Weight>lpt; Weight mdis=0;
       this->LongestPath(g, city1, lpt);
       mdis = lpt.findmdistance(city2);
       std::cout << "�����Ϊ" << mdis << std::endl;
   }
   //�Ӹ������� s ������ ���� s �ľ�����С�ĳ���Ϊ����
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
       std::cout << "�ܾ��룺" << total << std::endl;
   }
   //�������� s ������������ѡ��ĳ��м��ϵľ�����С�ĳ���Ϊ����
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
           std::cout << "�ܾ��룺" << total+distance1 << std::endl;
       }
   }
   
   //��̵ĵ�·Ϊ����
   void edgefirst() {
       Forest<Object, Weight>msf;
       this->Prim(g, msf);
       int count = msf.getCount();
       Weight  total=0;
       total = msf.findmdistance();
       msf.printWholeForest();
       std::cout << "�ܾ��룺" << total << std::endl;
   }
   //�û�һ��֪����Χ���г���
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
       std::cout << "R�ڳ�������" << total << std::endl;
       //delete[]vertexs;
   }
   //�����û�����Ȥ��һ�����ظ��ĳ���
   void interestedcity() {
       std::cout << "�������������" << std::endl;
       int n; std::cin >> n;
       ExpandableArrayList<Object>citys;
       std::cout << "��������У�" << std::endl;
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
       std::cout << "�ܾ��룺" << total << std::endl;
       
   }
   void ManageMenu()
   {
       int tag = 1;
       while (tag)
       {
           system("cls");

           int choose;
           cout << "_____________________________" << endl
               << "1. ���г���" << endl
               << "2. ���е�·" << endl
               << "3. ��ӳ���" << endl
               << "4. ���ĳ�����" << endl
               << "5. ɾ������" << endl
               << "6. ��ӵ�·" << endl
               << "7. ���ĵ�·Ȩֵ" << endl
               << "8. ɾ����·" << endl
               << "9. ���ز˵�" << endl
               << "_____________________________" << endl;
           cout << "����ѡ��:";
           cin >> choose;
           switch (choose)
           {
           case 1: printcity(); break;
           case 2: printedge(); break;
           case 3: { 
               Object city;
               std::cout << "�����������" << endl;
               cin >> city;
               if (g.isVertex(city))
               {
                   std::cout << "�����Ѵ���" << std::endl;
                   break;
               }
               addCity(city);
               break; 
           }
           case 4: {
               Object city,newcity;
               std::cout << "������ɳ�����" << endl;
               cin >> city;
               while (!g.isVertex(city))
               {
                   std::cout << "���в����ڣ�����������" << std::endl;
                   cin >> city;
               }
               std::cout << "�������³�����" << endl;
               cin >> newcity;
               while (g.isVertex(newcity))
               {
                   std::cout << "�������Ѵ��ڣ�����������" << std::endl;
                   cin >> newcity;
               }
               updataCity(city, newcity);
               break;
           }
           case 5: {
               Object city;
               std::cout << "�����������" << endl;
               cin >> city;
               if (!g.isVertex(city))
               {
                   std::cout << "���в�����" << std::endl;
               }
               removeCity( city);
               break;
           }
           case 6: {
               Object city1, city2; Weight weight;
               std::cout << "���������1��" << endl;
               cin >> city1;
               std::cout << "���������2��" << endl;
               cin >> city2;
               std::cout << "�������·Ȩֵ" << endl;
               cin >> weight;
               addedge(city1, city2, weight);
               break;
           }
           case 7: {
               Object city1, city2;
               std::cout << "���������1��" << endl;
               cin >> city1;
               std::cout << "���������2��" << endl;
               cin >> city2;
               Weight weight;
               std::cout << "�������·��Ȩֵ" << endl;
               cin >> weight;
               updataefge(city1, city2,weight);
               break;
           }
           case 8: {
               Object city1, city2; 
               std::cout << "���������1��" << endl;
               cin >> city1;
               std::cout << "���������2��" << endl;
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
           cout << "*******��ͨ·�߹滮ϵͳ*******" << endl;
           cout << "_____________________________" << endl
               << "1. ������г���" << endl
               << "2. ���������" << endl
               << "3. ���ڳ��м��·��" << endl
               << "4. ���е�·" << endl
               << "5. ��ͨͼϡ��̶�" << endl
               << "6. ������Ϣ����" << endl
               << "7. ���ĳ���������ڽӳ���" << endl
               << "8. ����Ӹ������г������Ե�������г���" << endl
               << "9. ���ڵĳ��������ĳ���" << endl
               << "10. ��������֮�����̼�·������̾���" << endl
               << "11. �����s�������ȵ�·��" << endl
               << "12. �ӳ���s����,������ѡ����м��Ͼ�����С�ĳ���Ϊ���ȵ�·��" << endl
               << "13. ��·���ȵ�·��" << endl
               << "14. ĳ������ΧR�����ڳ����Լ���Ŀ" << endl
               << "15. �û�����Ȥ�������·��" << endl
               << "16. ��������֮������·���������" << endl
               << "17. ��ͨͼ��ͨ��������" << endl
               << "18. ÿһ����ͨ�����Ƿ��л��������·" << endl
               << "19. �ж��Ƿ��и�������" << endl
               << "20. �ж��Ƿ��и�����·" << endl
               << "21. ���ĳ�������ڵĳ�����" << endl
               << "22. ��ĳ����·�ľ���ֵ" << endl
               << "23. �����ļ�" << endl
               << "24. �˳�" << endl
               << "_____________________________" << endl;
           cout << "����ѡ��:";
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
               std::cout << "������ָ������" << std::endl;
               cin >> city;
               printneighbors(city); break;
           }
           case 8: {
               Object city;
               std::cout << "������ָ������" << std::endl;
               cin >> city;
               getcitys( city); break;
           }
           case 9:  Maxneighborcity(); break;
           case 10: {
               Object city1, city2;
               std::cout << "���������1��" << endl;
               cin >> city1;
               std::cout << "���������2��" << endl;
               cin >> city2;
               if (!g.isVertex(city1) || !g.isVertex(city2))
               {
                   std::cout << "���в�����" << std::endl;
                   break;
               }
               getmsf( city1, city2); break;
           }
           case 11: {
               Object city;
               std::cout << "������ָ������" << std::endl;
               cin >> city;
               disfirst( city); break;
           }
           case 12: {
               Object city;
               ExpandableArrayList<Object> subArray;
               std::cout << "������ָ������" << std::endl;
               cin >> city;
               int size=0;
               std::cout << "��������м��ϵ�Ԫ������" << std::endl;
               std::cin >> size;
               while (size > g.vertexCount())
               {
                   std::cout << "��������м��ϵ�Ԫ������" << std::endl;
                   std::cin >> size;
               }
               std::cout << "���������" << std::endl;
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
                       std::cout << "���в�����" << std::endl;
                       size++;
                   }
               }
               fromSToSet(city,subArray); break;
           }
           case 13: edgefirst(); break;
           case 14: {
               Object city;
               std::cout << "������ָ������" << std::endl;
               cin >> city;
               std::cout << "�����뷶ΧR" << std::endl;
               int R; cin >> R;
               cityfromR( city, R); break;
           }
           case 15: interestedcity(); break;
           case 16: {
               Object city1, city2;
               std::cout << "���������1��" << endl;
               cin >> city1;
               std::cout << "���������2��" << endl;
               cin >> city2;
               getlpt(city1, city2); break;
           }
           case 17:countConnected(); break;
           case 18:findAndPrintCycles(); break;
           case 19: {
               Object city;
               std::cout << "������ָ������" << std::endl;
               cin >> city;
               if (!isCity( city)) { std::cout << "�ó��в�����" << std::endl; }
               else{ std::cout << "�ó��д���" << std::endl; }
               break;
           }
           case 20: {
               Object city1, city2;
               std::cout << "���������1��" << endl;
               cin >> city1;
               std::cout << "���������2��" << endl;
               cin >> city2;
               if (!isEdge( city1,city2)) { std::cout << "�õ�·������" << std::endl; }
               else { std::cout << "�õ�·����" << std::endl; }
               break;
           }
           case 21: {
               Object city;
               std::cout << "������ָ������" << std::endl;
               cin >> city;
               neighbornum( city);
               break;
           }
           case 22: {
               Object city1, city2;
               std::cout << "���������1��" << endl;
               cin >> city1;
               std::cout << "���������2��" << endl;
               cin >> city2;
               citysdistance( city1, city2);
               break;
           }
           case 23: {
               this->createFromfile("usa_small.txt");
               std::cout << "���سɹ�" << std::endl;
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
