/*
 * 3SpeedTests_TrafficAdvisory_given.cpp
 * ����ο����������ͨ��ѯ������TrafficAdvisory������ִ�Еr�g���ܲ���
 * @author Yan Guo ���� ���� <guoyan49@cug.edu.cn> 
 * @date ���� 2024-1-8
 */
#include <iostream>
#include <string>
#include "catch.hpp"  //���Թ���
#include "TrafficAdvisory.h" //��ͨ��ѯ������TrafficAdvisory
#include "UtilitiesSpeedTest.h" //����ο����������ͨ��ѯ������TrafficAdvisory������ִ�Еr�g���ܲ��������SpeedTest
using std::cout;
using std::endl;
using std::string;
#include"WUSGraphClient.hpp"


TEST_CASE("TrafficAdvisory::scale varies from 2-8 vertecies and 1-28 edges automatic finding path performed with 50 trial runs", "[part = 0][weight = 12]") {
	cout << "\n\n����TrafficAdvisory��Dijkstra��Floyd��numVertices_from��All_nonrepetition_paths��Kth_ShortestPath�Ͳο�����O_n_add_e��O_n_square��O_elogn��O_n_multiply_e��O_n_cubeʱ�������ܶԱȡ�����\n";
	SpeedTest<std::string, int, WUSGraphClient<std::string, int>> speedTest;
	WUSGraphClient<std::string, int> w;
	speedTest.run();
	
}
