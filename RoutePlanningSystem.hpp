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
    
    // ���ļ������ݽ������н�ͨ��
    void createFromfile(const string& filepath) {
        this->CreateGraphFromFile(filepath, g);
    }
    //������
    void printcitynum() {
        std::cout << g.vertexCount() << std::endl;
    }
    //������г���
    void printcity() {
        Object* vertexs = g.getVertices();
        for (auto u : vertexs) {
            std::cout << u;
        }
        std::cout << std::endl;
    }
    //���ڳ��м�ĵ�·�������ظ���
    void getRouteCount() {
        std::cout << "���ڳ��м�ĵ�·��Ϊ" << g.edgeCount() / 2 << std::endl;
    }
    //������е�·
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
    //ϡ��̶�
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
   //��ͨ��������
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
    //ÿһ����ͨ�����Ƿ��л��������·
    void hasCycleInConnectedComponent( int current, int parent, DbLinkedList<int>& visited, DbLinkedList<int>& currentPath, DbLinkedList<int>& hasvisited) {
        visited.Insert(current);
        currentPath.Insert(current);
        hasvisited.Insert(current);
        Object* neighbors = g.getNeighbors(current).object;
        int neighbor_size = g.getNeighbors(current).size;
        for (int i = 0; i < neighbor_size;i++) {
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
                // ����ÿ��δ�����ʵĽڵ㣬�����������������������Ƿ���ڻ�·
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
       Object* neighbors = g.getNeighbors(city).object;
       for (auto u : neighbors) {
           std::cout << u << " ";
       }
       std::cout << std::endl;
   }
   //���ڵĳ��������ĳ���
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
   //����Ӹ�������������Ե�������ж���
   void getcitys(Object city) {
       this->DFS(g, visit, city);
   }
   //�������������·��
   void getmsf( Object city1, Object city2) {
       Tree<Object, Weight>msf; int mdis;
       this->Dijkstra(g, city1, msf);
       mdis=msf.findmdistance(city2);
       std::cout << "��̾���Ϊ" << mdis << std::endl;
   }
   //�����������·��
   void getlpt(Object city1, Object city2) {
       Tree<Object, Weight>lpt; int mdis;
       this->LongestPath(g, city1, msf);
       mdis = lpt.findmdistance(city2);
       std::cout << "�����Ϊ" << mdis << std::endl;
   }
   //�Ӹ������� s ������ ���� s �ľ�����С�ĳ���Ϊ����
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
       std::cout << "�ܾ��룺" << total << std::endl;
       delete[]vertexs;
   }
   //�������� s ������������ѡ��ĳ��м��ϵľ�����С�ĳ���Ϊ����
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
       std::cout << "�ܾ��룺" << total << std::endl;
   }
   
   //��̵ĵ�·Ϊ����
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
       std::cout << "�ܾ��룺" << total << std::endl;
   }
   //�û�һ��֪����Χ���г���
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
       std::cout << "R�ڳ�������" << total << std::endl;
       delete[]vertexs;
   }
   //�����û�����Ȥ��һ�����ظ��ĳ���
   void interestedcity() {
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
       this->Kruskal(G, msf);
       int dis, total;
       for (int i = 1; i < n; i++) {
           
           dis = g.getWeight(msf[i - 1], msf[i]);
           total += dis;
           
       }
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
               << "1. ��ӳ���" << endl
               << "2. ���³�����Ϣ" << endl
               << "3. ɾ������" << endl
               << "4. ��ӵ�·" << endl
               << "5. ���µ�·��Ϣ" << endl
               << "6. ɾ����·" << endl
               << "7. ���ز˵�" << endl
               << "_____________________________" << endl;
           cout << "����ѡ��:";
           cin >> choose;
           switch (choose)
           {
           case 1: { 
               Object city;
               std::cout << "�����������" << endl;
               cin >> city;
               addCity(city);
               break; 
           }
           case 2: {
               Object city,newcity;
               std::cout << "������ɳ�����" << endl;
               cin >> city;
               std::cout << "�������³�����" << endl;
               cin >> newcity;
               updataCity(city, newcity);
               break;
           }
           case 3: {
               Object city;
               std::cout << "�����������" << endl;
               cin >> city;
               removeCity( city);
               break;
           }
           case 4: {
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
           case 5: {
               Object city1, city2;
               std::cout << "������ɳ���1��" << endl;
               cin >> city1;
               std::cout << "������ɳ���2��" << endl;
               cin >> city2;
               Object newcity1, newcity2; Weight weight;
               std::cout << "�������³���1��" << endl;
               cin >> newcity1;
               std::cout << "�������³���2��" << endl;
               cin >> newcity2;
               std::cout << "�������µ�·Ȩֵ" << endl;
               cin >> weight;
               updataefge(city1, city2, newcity1, newcity2, weight);
               break;
           }
           case 6: {
               Object city1, city2; 
               std::cout << "���������1��" << endl;
               cin >> city1;
               std::cout << "���������2��" << endl;
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
           cout << "*******��ͨ·�߹滮ϵͳ*******" << endl;
           cout << "_____________________________" << endl
               << "1. ������г���" << endl
               << "2. ���������" << endl
               << "3. ���ڳ��м��·��" << endl
               << "4. ���е�·" << endl
               << "5. ��ͨͼϡ��̶�" << endl
               << "6. ������Ϣ����" << endl
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
               << "23. �˳�" << endl
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
           case 9:  Maxneighborcity(g); break;
           case 10: {
               Object city1, city2;
               std::cout << "���������1��" << endl;
               cin >> city1;
               std::cout << "���������2��" << endl;
               cin >> city2;
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
               std::cout << "������ָ������" << std::endl;
               cin >> city;
               fromSToSet( city); break;
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
           case 23:exit(1); break;
           default:
               cout << "Error Input" << endl;
               break;
           }
           system("pause");
       }

   }
};
