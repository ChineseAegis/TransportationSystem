/*
 * TrafficAdvisoryCheck.h
 * �Խ�ͨ��ѯ������TrafficAdvisory������������TrafficAdvisoryCheck
 * @author Yan Guo ���� ���� <guoyan49@cug.edu.cn>
 * @date ���� 2024-1-8
 */
#pragma once

#include <iostream>
#include <algorithm>
#include "TrafficAdvisory.h"//��ͨ��ѯ������TrafficAdvisory
using std::cout;
using std::endl;
using std::sort;

//���������TrafficAdvisoryCheck
class TrafficAdvisoryCheck {
	TrafficAdvisory solver;
public:
	TrafficAdvisoryCheck(TrafficAdvisory& s) {
		solver = s;
	};

	//���Դ�㵽�յ�����·�����ܣ������һ�͵ڶ�������Ϊ�գ��������ж��������·�����ܡ�
	// ���������������Ƿ������ϸ��Ϣ��
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
	//			cout << "check��Դ����յ��������" << endl;
	//			exit(-1);
	//		}
	//	}
	//	else {
	//		cout << "check��Դ����յ��������" << endl;
	//		exit(-2);
	//	}
	//	int k;

	//	for (auto s : V) {

	//		//��֤Դ�㵽����������������
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
	//		//��֤·������
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
	//			//���·�����
	//			int Dijkstra_route, Floyd_route;
	//			Dijkstra_route = solver.Dijkstra(s, d);
	//			Floyd_route = solver.Floyd(s, d);
	//			if (Dijkstra_route != Floyd_route)
	//				return false;
	//			if (allroute.size() == 0) {
	//				if (Dijkstra_route != INT_MAX) {
	//					cout << s << " - " << d << "���·������:�����ڣ�����" << endl;
	//					return false;
	//				}
	//			}
	//			else if (Dijkstra_route != allroute[0].dist) {
	//				cout << s << " - " << d << "���·������" << endl;
	//				return false;
	//			}
	//			//�ƹ������·�����
	//			bool found = false;
	//			for (auto p : Vertex) {//p��Ҫ�ƹ��Ķ���
	//				if (p == s || p == d)
	//					continue;
	//				Dijkstra_route = solver.Dijkstra(s, d, p);
	//				Floyd_route = solver.Floyd(s, d, p);
	//				if (Dijkstra_route != Floyd_route)
	//					return false;
	//				if (allroute.size() == 0) {
	//					if (Dijkstra_route != INT_MAX) {
	//						cout << s << " - " << d << "���·������:�����ڣ�����" << endl;
	//						return false;
	//					}
	//				}
	//				else {
	//					int i;
	//					for (i = 0; i < num_allroute; i++) {
	//						auto it = std::find(allroute[i].path.begin(), allroute[i].path.end(), p);
	//						if (it == allroute[i].path.end()) {
	//							if (Dijkstra_route != allroute[i].dist) {
	//								cout << s << " - " << d << "�ƹ�" << p << "�����·������" << endl;
	//								return false;
	//							}
	//							else
	//								found = true;
	//							break;
	//						}
	//					}
	//					if (found == false && Dijkstra_route != INT_MAX) {//(s != d) && i== num_allroute && 
	//						cout << s << " - " << d << "�ƹ�" << p << "�����·������" << endl;
	//						return false;
	//					}
	//				}
	//			}

	//			//����·�����k��·�����
	//			for (k = 1; k <= num_allroute; k++) {
	//				int kth_route = solver.Kth_ShortestPath(s, d, k);
	//				if (num_allroute == 0) {
	//					if (kth_route != INT_MAX)
	//						cout << source << " - " << destination << " �� " << k << "��·������:�����ڣ�����" << endl;
	//					return false;
	//				}
	//				else if (allroute[k - 1].dist != kth_route) {
	//					cout << source << " - " << destination << " �� " << k << "��·������" << endl;
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

	//filename1��·���ļ�,filename2��·�������ļ����ж�filename1�ļ���·���Ƿ���У���������Ƿ��filename2�еľ�����ȡ�
	//�����·�������У����߾��벻ƥ�䣬�򷵻�false�����򷵻�true��
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
					cout << (*lines1)[i][j] << " - " << (*lines1)[i][j + 1] << "�����ڣ�����" << endl;
					return false;
				}
			}
			int  expect = (*lines2)[i][0];
			if (sum != expect) {
				cout << (*lines1)[i][0] << " - " << (*lines1)[i][(*lines1)[i].size() - 1] << "����������" << endl;
				return false;
			}
		}
		return true;
	}
};