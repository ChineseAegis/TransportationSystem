/*
 * 3SpeedTests_TrafficAdvisory_given.cpp
 * 五个参考程序、五个交通咨询任务类TrafficAdvisory函数的执行時間性能测试
 * @author Yan Guo 作者 郭艳 <guoyan49@cug.edu.cn> 
 * @date 日期 2024-1-8
 */
#include <iostream>
#include <string>
#include "catch.hpp"  //测试工具
#include "TrafficAdvisory.h" //交通咨询任务类TrafficAdvisory
#include "UtilitiesSpeedTest.h" //五个参考程序、五个交通咨询任务类TrafficAdvisory函数的执行時間性能测试任务類SpeedTest
using std::cout;
using std::endl;
using std::string;
#include"WUSGraphClient.hpp"


TEST_CASE("TrafficAdvisory::scale varies from 2-8 vertecies and 1-28 edges automatic finding path performed with 50 trial runs", "[part = 0][weight = 12]") {
	cout << "\n\n——TrafficAdvisory的Dijkstra、Floyd、numVertices_from、All_nonrepetition_paths、Kth_ShortestPath和参考程序O_n_add_e、O_n_square、O_elogn、O_n_multiply_e、O_n_cube时间性能能对比———\n";
	SpeedTest<std::string, int, WUSGraphClient<std::string, int>> speedTest;
	WUSGraphClient<std::string, int> w;
	speedTest.run();
	
}
