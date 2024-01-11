/*
 * 1tests_TrafficAdvisory_given.cpp
 * 交通咨询任务类TrafficAdvisory的测试用例
 * 给i出来十三个测试实例：三个由程序创建图，五个从一个文件输入创建图，五个从三个文件输入创建图。
 * @author Josh Hug
 * @authou Yan guo 作者 郭艳<guoyan49@cug.edu.cn>
 * @date 日期 2024-1-5
 */
#include <algorithm>
#include <string>
#include "catch.hpp"
#include "TrafficAdvisory.h" //交通咨询任务类TrafficAdvisory
#include "TrafficAdvisoryCheck.h" //交通咨询任务类TrafficAdvisory的检查任务类TrafficAdvisoryCheck
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
    //    REQUIRE(1 == (solver.All_nonrepetition_paths("A", "B")).size());//只有1条
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
    TrafficAdvisory solver(".\\input\\party5.txt", true); //调用时必须显式地传递一个额外的参数，这样就能匹配到有文件名的构造函数，否则匹配到其他构造函数。
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
//{"北京",3},
//{"上海",3},
//{"天津",3},
//{"重庆",1},
//{"哈尔滨",3},
//{"长春",3},
//{"沈阳",3},
//{"呼和浩特",2},
//{"石家庄",2},
//{"太原",2},
//{"济南",2},
//{"郑州",1},
//{"西安",1},
//{"兰州",2},
//{"银川",2},
//{"西宁",3},
//{"乌鲁木齐",3},
//{"合肥",1},
//{"南京",2},
//{"杭州",2},
//{"长沙",1},
//{"南昌",1},
//{"武汉",0},
//{"成都",2},
//{"贵阳",2},
//{"福州",2},
//{"台北",3},
//{"广州",2},
//{"海口",3},
//{"南宁",2},
//{"昆明",3},
//{"拉萨",3},
//{"香港",3},
//{"澳门",3} };
//   vector<Result_Label_PathLength>  actual_Wuhan = solver.numVertices_from("武汉");
//   std::sort(expect_Wuhan.begin(), expect_Wuhan.end());
//   std::sort(actual_Wuhan.begin(), actual_Wuhan.end());
//    REQUIRE(expect_Wuhan == actual_Wuhan);
//}
//
//TEST_CASE("TrafficAdvisory::11 All_nonrepetition_paths 2", "[part = 0][weight = 2]") {
//    TrafficAdvisory solver(".\\input\\3.csv", ".\\input\\2.csv", ".\\input\\1.csv", true);
//    REQUIRE(1963 == (solver.All_nonrepetition_paths("北京", "武汉", 10, ".\\output\\北京-武汉10.txt")).size());
//    REQUIRE(1963 == (solver.All_nonrepetition_paths("武汉", "北京", 10, ".\\output\\武汉-北京10.txt")).size());
//    //solver.TrafficAdvisoryCheck(".\\TrafficAdvisoryCheck\\cq-cs.csv", ".\\TrafficAdvisoryCheck\\juli.csv");
//
//   REQUIRE(2681 == (solver.All_nonrepetition_paths("重庆", "长沙", 10, ".\\output\\重庆-长沙10.txt")).size());//806
//   REQUIRE(2681 == (solver.All_nonrepetition_paths("长沙", "重庆", 10, ".\\output\\长沙-重庆10.txt")).size());//806
//}





TEST_CASE("TrafficAdvisory::12 Dijkstra and Floyd 2", "[part = 0][weight = 12]") {
    TrafficAdvisory solver(".\\input\\3.csv", ".\\input\\2.csv", ".\\input\\1.csv", true);
    REQUIRE(1105 == solver.Dijkstra("北京", "武汉"));
    //REQUIRE(1105 == solver.Floyd("武汉", "北京"));
    REQUIRE(1347 == solver.Dijkstra("北京", "上海"));//1710
   // REQUIRE(1347 == solver.Floyd("上海", "北京"));//1710
    REQUIRE(956 == solver.Dijkstra("北京", "西安"));// 1482
    //REQUIRE(956 == solver.Floyd("西安", "北京"));//1482
    REQUIRE(904 == solver.Dijkstra("上海", "长沙"));
    //REQUIRE(904 == solver.Floyd("长沙", "上海"));
    REQUIRE(904 == solver.Dijkstra("上海", "长沙"));//1078
    //REQUIRE(904 == solver.Floyd("长沙", "上海"));//1078
    //REQUIRE(1025 == solver.Dijkstra("上海", "长沙", "南昌"));
   // REQUIRE(1025 == solver.Floyd("长沙", "上海", "南昌"));
    REQUIRE(670 == solver.Dijkstra("长沙", "香港"));//694
    //REQUIRE(670 == solver.Floyd("香港", "长沙"));//694
    REQUIRE(1199 == solver.Dijkstra("南昌", "成都"));//这个案例很好，源代码到达终点位置放错！
    //REQUIRE(1199 == solver.Floyd("成都", "南昌"));
    REQUIRE(971 == solver.Dijkstra("武汉", "澳门"));
    //REQUIRE(971 == solver.Floyd("澳门", "武汉"));
    REQUIRE(1028 == solver.Dijkstra("武汉", "成都"));
    //REQUIRE(1028 == solver.Floyd("成都", "武汉"));
    //REQUIRE(2121 == solver.Dijkstra("天津", "广州", "武汉"));
    //REQUIRE(2121 == solver.Floyd("广州", "天津", "武汉"));
    //REQUIRE(1388 == solver.Dijkstra("武汉", "北京", "郑州"));//2087
    //REQUIRE(1388 == solver.Floyd("北京", "武汉", "郑州"));
    //REQUIRE(INT_MAX == solver.Dijkstra("武汉", "北京", "石家庄"));
    //REQUIRE(INT_MAX == solver.Floyd("北京", "武汉", "石家庄"));

    //REQUIRE(1258 == solver.Dijkstra("武汉", "成都", "重庆"));
    //REQUIRE(1258 == solver.Floyd("成都", "武汉", "重庆"));

    //solver.All_nonrepetition_paths("北京", "广州", 10, ".\\output\\北京-广州10.txt");
    //REQUIRE(2124 == solver.Dijkstra("北京", "广州", "武汉"));//**
    //REQUIRE(2124 == solver.Floyd("广州", "北京", "武汉")); //**

    //REQUIRE(2201 == solver.Dijkstra("昆明", "北京", "武汉"));
    //REQUIRE(2201 == solver.Floyd("北京", "昆明", "武汉"));
}







//TEST_CASE("TrafficAdvisory::13 Kth_ShortestPath", "[part = 0][weight = 6]") {
//    TrafficAdvisory solver(".\\input\\3.csv", ".\\input\\2.csv", ".\\input\\1.csv", true);
//    REQUIRE(1105 == solver.Kth_ShortestPath("武汉", "北京", 1));
//    REQUIRE(1105 == solver.Kth_ShortestPath("北京", "武汉", 1));
//    REQUIRE(1263 == solver.Kth_ShortestPath("武汉", "北京", 3));
//    REQUIRE(1263 == solver.Kth_ShortestPath("北京", "武汉", 3));
//    REQUIRE(1517 == solver.Kth_ShortestPath("武汉", "北京", 10));
//    REQUIRE(1517 == solver.Kth_ShortestPath("北京", "武汉", 10));
//    REQUIRE(2102 == solver.Kth_ShortestPath("武汉", "北京", 50));
//    REQUIRE(2102 == solver.Kth_ShortestPath("北京", "武汉", 50));
//    REQUIRE(3399 == solver.Kth_ShortestPath("武汉", "北京", 700));
//    REQUIRE(3399 == solver.Kth_ShortestPath("北京", "武汉", 700));
//    /*    TrafficAdvisoryCheck c(solver);
//    REQUIRE(true == c.check_ALL("北京", "武汉",true));
//    */
//    REQUIRE(3250 == solver.Kth_ShortestPath("哈尔滨", "长沙", 67));//3265
//    REQUIRE(3250 == solver.Kth_ShortestPath("长沙", "哈尔滨", 67));//3265
//    REQUIRE(1028 == solver.Kth_ShortestPath("成都", "武汉", 1));
//    REQUIRE(1028 == solver.Kth_ShortestPath("武汉", "成都", 1));
//    REQUIRE(1712 == solver.Kth_ShortestPath("成都", "武汉", 10));
//    REQUIRE(1712 == solver.Kth_ShortestPath("武汉", "成都", 10));
//}
