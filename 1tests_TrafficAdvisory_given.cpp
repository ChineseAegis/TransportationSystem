/*
 * 1tests_TrafficAdvisory_given.cpp
 * ��ͨ��ѯ������TrafficAdvisory�Ĳ�������
 * ��i����ʮ��������ʵ���������ɳ��򴴽�ͼ�������һ���ļ����봴��ͼ������������ļ����봴��ͼ��
 * @author Josh Hug
 * @authou Yan guo ���� ����<guoyan49@cug.edu.cn>
 * @date ���� 2024-1-5
 */
#include <algorithm>
#include <string>
#include "catch.hpp"
#include "TrafficAdvisory.h" //��ͨ��ѯ������TrafficAdvisory
#include "TrafficAdvisoryCheck.h" //��ͨ��ѯ������TrafficAdvisory�ļ��������TrafficAdvisoryCheck
#include"WUSGraph.hpp"
#include"WUSGraphClient.hpp"
using std::string;
using std::sort;

TEST_CASE("TrafficAdvisory::1 triangle", "[part = 0][weight = 3]") {
    WUSGraph<string, int> g;
    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 1);
    g.addEdge("A", "D", 1);
    g.addEdge("C", "D", 1);
    //TrafficAdvisory solver(g,true);
    WUSGraphClient<string, int> solver;
    //SECTION("numVertices_from") {
    //    vector<Result_Label_PathLength>expect_A = {
    //        { "A",0 },
    //        { "B",1 },
    //        { "C",1 },
    //        { "D",1 }};
    //    std::sort(expect_A.begin(), expect_A.end());
    //    vector<Result_Label_PathLength>actual_A = solver.numVertices_from("A");
    //    std::sort(actual_A.begin(), actual_A.end());
    //    REQUIRE(expect_A == actual_A);
    //}
    SECTION("Dijkstra and Floyd") {
        REQUIRE(solver.Dijkstra(g,"A","B") == 1);
      
        //REQUIRE(1 == solver.Floyd(g,"A", "B"));
    }
    //SECTION("All_nonrepetition_paths") {
    //    REQUIRE(1 == (solver.All_nonrepetition_paths("A", "B")).size());
    //}
    //SECTION("Kth_ShortestPath") {
    //    REQUIRE(1 == solver.Kth_ShortestPath("A", "B", 1));
    //    REQUIRE(INT_MAX == solver.Kth_ShortestPath("A", "B", 2));
    //}
    //TrafficAdvisoryCheck c(solver);
    //REQUIRE(true == c.check_ALL());
    //g.Clear();
}

TEST_CASE("TrafficAdvisory::2 disinsertEdgeed 1", "[part = 0][weight = 6]") {
    WUSGraph<string, int> g;
    g.addEdge("A", "B", 1);
    g.addEdge("C", "D", 1);
    WUSGraphClient<string, int> solver;
    //SECTION("numVertices_from") {
    //    vector<Result_Label_PathLength>expect_A = {
    //        { "A",0 },
    //        { "B",1 },
    //        { "C",INT_MAX },
    //        { "D",INT_MAX } };
    //    std::sort(expect_A.begin(), expect_A.end());
    //    vector<Result_Label_PathLength>actual_A = solver.numVertices_from("A");
    //    std::sort(actual_A.begin(), actual_A.end());
    //    REQUIRE(expect_A == actual_A);
    //}
    SECTION("Dijkstra and Floyd") {
        REQUIRE(1 == solver.Dijkstra(g,"A", "B"));
        //REQUIRE(1 == solver.Floyd("A", "B")); 
        REQUIRE(INT_MAX == solver.Dijkstra(g,"A", "C"));
        //REQUIRE(INT_MAX == solver.Floyd("A", "C"));
        REQUIRE(INT_MAX == solver.Dijkstra(g,"A", "D"));
        //REQUIRE(INT_MAX == solver.Floyd("A", "D"));
    }
    //SECTION("All_nonrepetition_paths") {
    //    REQUIRE(1 == (solver.All_nonrepetition_paths("A", "B")).size());//ֻ��1��
    //    REQUIRE(0 == (solver.All_nonrepetition_paths("A", "C")).size());
    //    REQUIRE(0 == (solver.All_nonrepetition_paths("A", "D")).size());
    //}
    //SECTION("Kth_ShortestPath") {
    //    REQUIRE(1 == solver.Kth_ShortestPath("A", "B", 1));
    //    REQUIRE(INT_MAX == solver.Kth_ShortestPath("A", "B", 2));
    //    REQUIRE(INT_MAX == solver.Kth_ShortestPath("A", "C", 1));
    //    REQUIRE(INT_MAX == solver.Kth_ShortestPath("A", "D", 1));
    //}
    //TrafficAdvisoryCheck c(solver);
    //REQUIRE(true == c.check_ALL());
    //g.Clear();
}
//
//TEST_CASE("TrafficAdvisory::3 disinsertEdgeed 2", "[part = 0][weight = 1]") {
//    GraphAdjacencyList<string, int> g;
//    g.insertEdge("A", "B", 1);
//    g.insertEdge("C", "D", 1);
//    g.insertEdge("E", "D", 1);
//    g.insertEdge("E", "C", 1);
//    TrafficAdvisory solver(g, true);
//    SECTION("All_nonrepetition_paths") {
//        REQUIRE(0 == (solver.All_nonrepetition_paths("A", "D")).size());
//    }
//    TrafficAdvisoryCheck c(solver);
//    REQUIRE(true == c.check_ALL());
//    g.Clear();
//}
//




TEST_CASE("TrafficAdvisory::4 Dijkstra and Floyd three parameters", "[part = 0][weight = 1]") {
    WUSGraph<string, int> g;
    g.addEdge("A", "B", 1);
    g.addEdge("A", "C", 3);
    g.addEdge("B", "C", 1);
    WUSGraphClient<string, int> solver;
    //REQUIRE(3 == solver.Dijkstra("A", "C", "B"));
    //REQUIRE(3 == solver.Floyd("A", "C", "B"));
    //g.Clear();
}



//
//TEST_CASE("TrafficAdvisory::5 input 1", "[part = 0][weight = 5]") {
//    TrafficAdvisory solver(".\\input\\party1.txt", true);
//    SECTION("All_nonrepetition_paths") {
//        REQUIRE(2 == (solver.All_nonrepetition_paths("Michelle", "Brian")).size());
//    }
//    TrafficAdvisoryCheck c(solver);
//    REQUIRE(true == c.check_ALL());
//}
//
//TEST_CASE("TrafficAdvisory::6 input 2", "[part = 0][weight = 1]") {
//    TrafficAdvisory solver(".\\input\\party2.txt", true);
//    SECTION("All_nonrepetition_paths") {
//        REQUIRE(1 == (solver.All_nonrepetition_paths("Louis Tomlinson", "Niall Horan")).size());
//    }
//    TrafficAdvisoryCheck c(solver);
//    REQUIRE(true == c.check_ALL());
//}
//
TEST_CASE("TrafficAdvisory::7 input 2::full connected", "[part = 0][weight = 4]") {
    TrafficAdvisory solver(".\\input\\party5.txt", true); //����ʱ������ʽ�ش���һ������Ĳ�������������ƥ�䵽���ļ����Ĺ��캯��������ƥ�䵽�������캯����
    //SECTION("All_nonrepetition_paths") {
    //    REQUIRE(5 == (solver.All_nonrepetition_paths("Michelle", "Brian")).size());
    //}
    SECTION("Dijkstra and Floyd") {
        REQUIRE(1 == solver.Dijkstra("Michelle", "Brian"));
       // REQUIRE(1 == solver.Floyd("Michelle", "Brian"));
    }
    //SECTION("Kth_ShortestPath") {
    //    REQUIRE(1 == solver.Kth_ShortestPath("Michelle", "Brian", 1));
    //    REQUIRE(2 == solver.Kth_ShortestPath("Michelle", "Brian", 2));
    //    REQUIRE(2 == solver.Kth_ShortestPath("Michelle", "Brian", 3));
    //    REQUIRE(3 == solver.Kth_ShortestPath("Michelle", "Brian", 4));
    //    REQUIRE(3 == solver.Kth_ShortestPath("Michelle", "Brian", 5));
    //    REQUIRE(INT_MAX == solver.Kth_ShortestPath("Michelle", "Brian", 6));
    //}
    //TrafficAdvisoryCheck c(solver);
    //REQUIRE(true == c.check_ALL());
}
//
//TEST_CASE("TrafficAdvisory::8 input 3", "[part = 0][weight = 1]") {
//    TrafficAdvisory solver(".\\input\\party3.txt", true);
//    SECTION("All_nonrepetition_paths") {
//        REQUIRE(5 == (solver.All_nonrepetition_paths("Eggplant", "Fig")).size());
//    }
//    TrafficAdvisoryCheck c(solver);
//    REQUIRE(true == c.check_ALL());
//}
//
//TEST_CASE("TrafficAdvisory::9 input 4", "[part = 0][weight = 1]") {
//    TrafficAdvisory solver(".\\input\\party4.txt", true);
//    SECTION("All_nonrepetition_paths") {
//        REQUIRE(0 == (solver.All_nonrepetition_paths("Louis Tomlinson", "Fig")).size());
//    }
//    TrafficAdvisoryCheck c(solver);
//    REQUIRE(true == c.check_ALL());
//}
//
//TEST_CASE("TrafficAdvisory::10 numVertices_from", "[part = 0][weight = 1]") {
//    TrafficAdvisory solver(".\\input\\3.csv", ".\\input\\2.csv", ".\\input\\1.csv", true);
//    vector<Result_Label_PathLength> expect_Wuhan = {
//{"����",3},
//{"�Ϻ�",3},
//{"���",3},
//{"����",1},
//{"������",3},
//{"����",3},
//{"����",3},
//{"���ͺ���",2},
//{"ʯ��ׯ",2},
//{"̫ԭ",2},
//{"����",2},
//{"֣��",1},
//{"����",1},
//{"����",2},
//{"����",2},
//{"����",3},
//{"��³ľ��",3},
//{"�Ϸ�",1},
//{"�Ͼ�",2},
//{"����",2},
//{"��ɳ",1},
//{"�ϲ�",1},
//{"�人",0},
//{"�ɶ�",2},
//{"����",2},
//{"����",2},
//{"̨��",3},
//{"����",2},
//{"����",3},
//{"����",2},
//{"����",3},
//{"����",3},
//{"���",3},
//{"����",3} };
//   vector<Result_Label_PathLength>  actual_Wuhan = solver.numVertices_from("�人");
//   std::sort(expect_Wuhan.begin(), expect_Wuhan.end());
//   std::sort(actual_Wuhan.begin(), actual_Wuhan.end());
//    REQUIRE(expect_Wuhan == actual_Wuhan);
//}
//
//TEST_CASE("TrafficAdvisory::11 All_nonrepetition_paths 2", "[part = 0][weight = 2]") {
//    TrafficAdvisory solver(".\\input\\3.csv", ".\\input\\2.csv", ".\\input\\1.csv", true);
//    REQUIRE(1963 == (solver.All_nonrepetition_paths("����", "�人", 10, ".\\output\\����-�人10.txt")).size());
//    REQUIRE(1963 == (solver.All_nonrepetition_paths("�人", "����", 10, ".\\output\\�人-����10.txt")).size());
//    //solver.TrafficAdvisoryCheck(".\\TrafficAdvisoryCheck\\cq-cs.csv", ".\\TrafficAdvisoryCheck\\juli.csv");
//
//   REQUIRE(2681 == (solver.All_nonrepetition_paths("����", "��ɳ", 10, ".\\output\\����-��ɳ10.txt")).size());//806
//   REQUIRE(2681 == (solver.All_nonrepetition_paths("��ɳ", "����", 10, ".\\output\\��ɳ-����10.txt")).size());//806
//}





TEST_CASE("TrafficAdvisory::12 Dijkstra and Floyd 2", "[part = 0][weight = 12]") {
    TrafficAdvisory solver(".\\input\\3.csv", ".\\input\\2.csv", ".\\input\\1.csv", true);
    REQUIRE(1105 == solver.Dijkstra("����", "�人"));
    //REQUIRE(1105 == solver.Floyd("�人", "����"));
    REQUIRE(1347 == solver.Dijkstra("����", "�Ϻ�"));//1710
   // REQUIRE(1347 == solver.Floyd("�Ϻ�", "����"));//1710
    REQUIRE(956 == solver.Dijkstra("����", "����"));// 1482
    //REQUIRE(956 == solver.Floyd("����", "����"));//1482
    REQUIRE(904 == solver.Dijkstra("�Ϻ�", "��ɳ"));
    //REQUIRE(904 == solver.Floyd("��ɳ", "�Ϻ�"));
    REQUIRE(904 == solver.Dijkstra("�Ϻ�", "��ɳ"));//1078
    //REQUIRE(904 == solver.Floyd("��ɳ", "�Ϻ�"));//1078
    //REQUIRE(1025 == solver.Dijkstra("�Ϻ�", "��ɳ", "�ϲ�"));
   // REQUIRE(1025 == solver.Floyd("��ɳ", "�Ϻ�", "�ϲ�"));
    REQUIRE(670 == solver.Dijkstra("��ɳ", "���"));//694
    //REQUIRE(670 == solver.Floyd("���", "��ɳ"));//694
    REQUIRE(1199 == solver.Dijkstra("�ϲ�", "�ɶ�"));//��������ܺã�Դ���뵽���յ�λ�÷Ŵ�
    //REQUIRE(1199 == solver.Floyd("�ɶ�", "�ϲ�"));
    REQUIRE(971 == solver.Dijkstra("�人", "����"));
    //REQUIRE(971 == solver.Floyd("����", "�人"));
    REQUIRE(1028 == solver.Dijkstra("�人", "�ɶ�"));
    //REQUIRE(1028 == solver.Floyd("�ɶ�", "�人"));
    //REQUIRE(2121 == solver.Dijkstra("���", "����", "�人"));
    //REQUIRE(2121 == solver.Floyd("����", "���", "�人"));
    //REQUIRE(1388 == solver.Dijkstra("�人", "����", "֣��"));//2087
    //REQUIRE(1388 == solver.Floyd("����", "�人", "֣��"));
    //REQUIRE(INT_MAX == solver.Dijkstra("�人", "����", "ʯ��ׯ"));
    //REQUIRE(INT_MAX == solver.Floyd("����", "�人", "ʯ��ׯ"));

    //REQUIRE(1258 == solver.Dijkstra("�人", "�ɶ�", "����"));
    //REQUIRE(1258 == solver.Floyd("�ɶ�", "�人", "����"));

    //solver.All_nonrepetition_paths("����", "����", 10, ".\\output\\����-����10.txt");
    //REQUIRE(2124 == solver.Dijkstra("����", "����", "�人"));//**
    //REQUIRE(2124 == solver.Floyd("����", "����", "�人")); //**

    //REQUIRE(2201 == solver.Dijkstra("����", "����", "�人"));
    //REQUIRE(2201 == solver.Floyd("����", "����", "�人"));
}







//TEST_CASE("TrafficAdvisory::13 Kth_ShortestPath", "[part = 0][weight = 6]") {
//    TrafficAdvisory solver(".\\input\\3.csv", ".\\input\\2.csv", ".\\input\\1.csv", true);
//    REQUIRE(1105 == solver.Kth_ShortestPath("�人", "����", 1));
//    REQUIRE(1105 == solver.Kth_ShortestPath("����", "�人", 1));
//    REQUIRE(1263 == solver.Kth_ShortestPath("�人", "����", 3));
//    REQUIRE(1263 == solver.Kth_ShortestPath("����", "�人", 3));
//    REQUIRE(1517 == solver.Kth_ShortestPath("�人", "����", 10));
//    REQUIRE(1517 == solver.Kth_ShortestPath("����", "�人", 10));
//    REQUIRE(2102 == solver.Kth_ShortestPath("�人", "����", 50));
//    REQUIRE(2102 == solver.Kth_ShortestPath("����", "�人", 50));
//    REQUIRE(3399 == solver.Kth_ShortestPath("�人", "����", 700));
//    REQUIRE(3399 == solver.Kth_ShortestPath("����", "�人", 700));
//    /*    TrafficAdvisoryCheck c(solver);
//    REQUIRE(true == c.check_ALL("����", "�人",true));
//    */
//    REQUIRE(3250 == solver.Kth_ShortestPath("������", "��ɳ", 67));//3265
//    REQUIRE(3250 == solver.Kth_ShortestPath("��ɳ", "������", 67));//3265
//    REQUIRE(1028 == solver.Kth_ShortestPath("�ɶ�", "�人", 1));
//    REQUIRE(1028 == solver.Kth_ShortestPath("�人", "�ɶ�", 1));
//    REQUIRE(1712 == solver.Kth_ShortestPath("�ɶ�", "�人", 10));
//    REQUIRE(1712 == solver.Kth_ShortestPath("�人", "�ɶ�", 10));
//}
