/*
 * TrafficAdvisoryCheck.h
 * 对交通咨询任务类TrafficAdvisory做检查的任务类TrafficAdvisoryCheck
 * @author Yan Guo 作者 郭艳 <guoyan49@cug.edu.cn>
 * @date 日期 2024-1-8
 */
#pragma once

#include <iostream>
#include <algorithm>
#include "TrafficAdvisory.h"//交通咨询任务类TrafficAdvisory
using std::cout;
using std::endl;
using std::sort;

//检查任务类TrafficAdvisoryCheck
class TrafficAdvisoryCheck {
	TrafficAdvisory solver;
public:
	TrafficAdvisoryCheck(TrafficAdvisory& s) {
		solver = s;
	};

	//检查源点到终点的五个路径功能，如果第一和第二个参数为空，则检查所有顶点间的五个路径功能。
	// 第三个参数控制是否输出详细信息。
	//bool check_ALL(string source = "", string destination = "", bool whetherOutput = false) {
	//	set<string> Vertex = solver.g.getLabels();
	//	int length = Vertex.size();
	//	set<string> V;
	//	if (source == "" && destination == "")
	//		V = Vertex;
	//	else if (source != "" && destination != "") {
	//		if (solver.g.isVertex(source) && solver.g.isVertex(destination)) {
	//			V.insert(source);
	//			V.insert(destination);
	//		}
	//		else {
	//			cout << "check的源点和终点输入错误" << endl;
	//			exit(-1);
	//		}
	//	}
	//	else {
	//		cout << "check的源点和终点输入错误" << endl;
	//		exit(-2);
	//	}
	//	int k;

	//	for (auto s : V) {

	//		//验证源点到其它各顶点边数检查
	//		vector<Result_Label_PathLength> expect_numVertices;
	//		for (auto d : V) {
	//			Result_Label_PathLength temp;
	//			temp.label = d;
	//			temp.pathLength = solver.Dijkstra(s, d);
	//			expect_numVertices.push_back(temp);

	//		}
	//		vector<Result_Label_PathLength> actual_numVertices = solver.numVertices_from(s);
	//		std::sort(expect_numVertices.begin(), expect_numVertices.end());
	//		std::sort(actual_numVertices.begin(), actual_numVertices.end());
	//		if (actual_numVertices != expect_numVertices)
	//			return false;
	//		//验证路径操作
	//		for (auto d : V) {
	//			vector<Result_Path_Distance> allroute;
	//			if (whetherOutput)
	//			{
	//				allroute = solver.All_nonrepetition_paths(s, d, length, ".\\output\\" + s + " - " + d + std::to_string(length) + ".txt");
	//			}
	//			else
	//			{
	//				allroute = solver.All_nonrepetition_paths(s, d, length);
	//			}
	//			int num_allroute = allroute.size();
	//			//最短路径检查
	//			int Dijkstra_route, Floyd_route;
	//			Dijkstra_route = solver.Dijkstra(s, d);
	//			Floyd_route = solver.Floyd(s, d);
	//			if (Dijkstra_route != Floyd_route)
	//				return false;
	//			if (allroute.size() == 0) {
	//				if (Dijkstra_route != INT_MAX) {
	//					cout << s << " - " << d << "最短路径出错:不存在？存在" << endl;
	//					return false;
	//				}
	//			}
	//			else if (Dijkstra_route != allroute[0].dist) {
	//				cout << s << " - " << d << "最短路径出错" << endl;
	//				return false;
	//			}
	//			//绕过的最短路径检查
	//			bool found = false;
	//			for (auto p : Vertex) {//p：要绕过的顶点
	//				if (p == s || p == d)
	//					continue;
	//				Dijkstra_route = solver.Dijkstra(s, d, p);
	//				Floyd_route = solver.Floyd(s, d, p);
	//				if (Dijkstra_route != Floyd_route)
	//					return false;
	//				if (allroute.size() == 0) {
	//					if (Dijkstra_route != INT_MAX) {
	//						cout << s << " - " << d << "最短路径出错:不存在？存在" << endl;
	//						return false;
	//					}
	//				}
	//				else {
	//					int i;
	//					for (i = 0; i < num_allroute; i++) {
	//						auto it = std::find(allroute[i].path.begin(), allroute[i].path.end(), p);
	//						if (it == allroute[i].path.end()) {
	//							if (Dijkstra_route != allroute[i].dist) {
	//								cout << s << " - " << d << "绕过" << p << "的最短路径出错" << endl;
	//								return false;
	//							}
	//							else
	//								found = true;
	//							break;
	//						}
	//					}
	//					if (found == false && Dijkstra_route != INT_MAX) {//(s != d) && i== num_allroute && 
	//						cout << s << " - " << d << "绕过" << p << "的最短路径出错" << endl;
	//						return false;
	//					}
	//				}
	//			}

	//			//所有路径与第k条路径检查
	//			for (k = 1; k <= num_allroute; k++) {
	//				int kth_route = solver.Kth_ShortestPath(s, d, k);
	//				if (num_allroute == 0) {
	//					if (kth_route != INT_MAX)
	//						cout << source << " - " << destination << " 第 " << k << "短路径出错:不存在？存在" << endl;
	//					return false;
	//				}
	//				else if (allroute[k - 1].dist != kth_route) {
	//					cout << source << " - " << destination << " 第 " << k << "短路径出错" << endl;
	//					return false;
	//				}
	//				if (kth_route == INT_MAX)
	//					break;
	//			}
	//			if (solver.Kth_ShortestPath(s, d, num_allroute + 1) != INT_MAX)
	//				return false;
	//		}
	//	}
	//	return true;
	//}

	//filename1是路径文件,filename2是路径距离文件。判断filename1文件的路径是否可行，如果可行是否和filename2中的距离相等。
	//如果有路径不可行，或者距离不匹配，则返回false。否则返回true。
	bool check_Files(string filename1, string filesname2)
	{
		vector<vector<string>>* lines1 = solver.readCSV<string>(filename1, stringfunction);
		vector<vector<int>>* lines2 = solver.readCSV<int>(filesname2, intfunction);
		for (int i = 0; i < (*lines1).size(); i++) {
			int sum = 0;
			for (int j = 0; j < (*lines1)[i].size() - 1; j++) {
				if (solver.g.getWeight((*lines1)[i][j], (*lines1)[i][j + 1]) != INT_MAX)
					sum += solver.g.getWeight((*lines1)[i][j], (*lines1)[i][j + 1]);
				else {
					cout << (*lines1)[i][j] << " - " << (*lines1)[i][j + 1] << "不相邻，出错！" << endl;
					return false;
				}
			}
			int  expect = (*lines2)[i][0];
			if (sum != expect) {
				cout << (*lines1)[i][0] << " - " << (*lines1)[i][(*lines1)[i].size() - 1] << "距离计算错误" << endl;
				return false;
			}
		}
		return true;
	}
};