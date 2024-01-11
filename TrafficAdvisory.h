/*
 * TrafficAdvisory.h
 * 定义和实现交通咨询任务类TrafficAdvisory，它有一个GraphAdjacencyList<string,int>类对象。
 * @author Yan Guo 作者 郭艳 <guoyan49@cug.edu.cn>
 * @date 日期 2024-1-5
 */
#pragma once

#include <iostream>
#include <fstream>//ifstream
#include <sstream>//ostringstream
#include <string>
#include <vector>
#include <set>
//#include "GraphAdjacencyList.h"
#include"WUSGraph.hpp"
#include"WUSGraphClient.hpp"
#include "UtilitiesRandom.h"//makeUniqueRandomArray<T>()
#include "UtilitiesString.h"//trim_blank_space()、stringfunction()等
//using namespace std;
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::ifstream;
using std::ostringstream;
using std::cerr;

//操作结果类型1：表示顶点B标签、A顶点到B顶点的最小路径长度
struct Result_Label_PathLength {
	std::string label;  //顶点标签
	int pathLength; //顶点A到标签为label的B顶点的最小路径长度
	bool operator ==(const Result_Label_PathLength& other)const {
		return (label.compare(other.label)==0 && pathLength == other.pathLength);
	}
	bool operator <(const Result_Label_PathLength & other)const {
		return (label.compare(other.label) < 0 || (label.compare(other.label) == 0 && pathLength < other.pathLength));
	}
};

//操作结果类型2：表示路径、路径距离
struct Result_Path_Distance {
	vector<string> path;//顶点标签向量，表示一条路径
	int dist;//path表示的路径的权值（例如距离）之和。
};

class TrafficAdvisoryCheck;

class TrafficAdvisory {
	friend class TrafficAdvisoryCheck; //友元

private:
	WUSGraphClient<string, int> wclient;
	WUSGraph<string, int> g; //在任务类构造一个图对象。

	bool _whetherOutput = false; //是否输出操作结果的详细信息

	//创建一个顶点数是n、边数是e的随机的图。
	void randomGraph(int n, int e) {
		using T = string;
		using E = int;

		//产生随机的字符串数组：图的顶点标签
		T* arr = makeUniqueRandomArray<T>(n, randomString);//创建一个长度为n的值不重复的随机字符串数组

		//矩阵Matrix记录边，以防止生成重复边。
		std::vector<std::vector<E>> Matrix;// 初始化矩阵,
		Matrix.resize(n, std::vector<int>(n, 0));

		for (int i = 0; i < n; ++i)
			g.isVertex(arr[i]);//插入顶点

		// 设置随机种子
		std::srand(std::time(0));

		// 添加随机边
		for (int i = 0; i < e; ++i) {
			int source = std::rand() % n;
			int destination = std::rand() % n;
			E weight = std::rand() % 100; // 随机生成权值，此处范围为0-1010

			// 防止生成自环边和重复边
			while (source == destination || Matrix[source][destination] != 0) {
				source = std::rand() % n;
				destination = std::rand() % n;
			}
			Matrix[source][destination] = 1;
			Matrix[destination][source] = 1;

			// 将边的权值设置为随机整数
			g.addEdge(arr[source], arr[destination], weight);//插入边
			g.addEdge(arr[destination], arr[source], weight);//无向图，插入另一条边
		}

		delete[] arr;
	}
	
	/** 
	* 读取整个 CSV 并返回向量。 每个内部列表代表 CSV 的一行，其中每个逗号分隔的值作为一个条目。
	* 假设 CSV 文件除了作为分隔符的逗号之外不包含其他的分隔符。
	* 如果文件名无效，则退出。
	*
	* 逗号分隔值（Comma-Separated Values，CSV，有时也称为字符分隔值，因为分隔字符也可以不是逗号）
	* 文件以纯文本形式存储表格数据（数字和文本）。
	*/
	template<class T>
	vector<vector<T>>*& readCSV(std::string filename, T(*function)(char*)) {
		vector<vector<T>>* records = new vector<vector<T>>();
		typename vector<T>::iterator it2;
		typename vector<vector<T>>::iterator it1;
		ifstream* in = new ifstream(filename);
		if (!in->is_open()) {
			cerr << filename << "文件不能打开！\n";
			exit(EXIT_FAILURE);
		}
		auto ss = ostringstream{};
		char* ptr = NULL, * ptr2 = NULL, * pch, * pch2;

		while (in->peek() != EOF) {
			ss << in->rdbuf();
			string wordbuf = ss.str();
			int wordbuflen = wordbuf.length();
			char* words = new char[wordbuflen + 1];
			if (words == NULL) {
				cerr << filename << "内存不能分配！\n";
				exit(EXIT_FAILURE);
			}
			strcpy_s(words, wordbuflen + 1, wordbuf.c_str());
			pch = strtok_s(words, "\n", &ptr);
			it1 = (*records).begin();

			while (pch != NULL)
			{
				vector<T> l2;
				pch2 = strtok_s(pch, ",", &ptr2);
				while (pch2 != NULL) {
					l2.push_back(function(pch2));
					pch2 = strtok_s(NULL, ",", &ptr2);
				}
				(*records).push_back(l2);
				pch = strtok_s(NULL, "\n", &ptr);
			}
			delete[] words;
		}
		in->close();
		delete in;
		in = NULL;
		return records;
	}

	//从一个文件filename(含顶点标签和顶点间相邻关系)创建图对象g。
	void graphFromFile(string filename) {
		vector<vector<string>>* lines = readCSV<string>(filename, stringfunction);
		vector<vector<string>>::iterator it;

		it = lines->begin();

		for (string name : *it) {
			g.addVertex(name);
		}

		for (it++; it != lines->end(); ++it) {
			vector<string>::iterator it2;
			it2 = (*it).begin();
			string source = *it2;

			++it2;
			string destination = *it2;
			g.addEdge(source, destination, 1);//文件中无权值信息，边权值默认为1
			g.addEdge(destination, source, 1);//无向图，插入另一条边
		}
		lines->clear();
		delete lines;
	}; 

	/* 从名为 filename1、filename2、filename3 文件创建一个 图对象：从文件创建图对象g。
	 * filename1：城市名
	 * filename2：城市间是否相邻
	 * filename3：城市间距离
	*/
	void graphFromFile(string filename1, string filename2, string filename3 ) {
		vector<vector<string>>* lines1 = readCSV<string>(filename1, stringfunction);
		vector<vector<int>>* lines2 = readCSV<int>(filename2, intfunction);
		vector<vector<bool>>* lines3 = readCSV<bool>(filename3, boolfunction);
		vector<vector<string>>::iterator it1;

		it1 = lines1->begin();

		for (string name : *it1) {
			g.addVertex(name);
		}
		
		for (int i=0; i<(*lines3).size(); i++) {
			for (int j = 0; j < (*lines3)[i].size(); j++) {
				if ((*lines3)[i][j] == true) {
					string source = (*lines1)[0][i];
					string destination = (*lines1)[0][j];
					if (i < j) {
						int cost = (*lines2)[j][i];
						g.addEdge(source, destination, cost);
						g.addEdge(destination, source, cost);
					}
				}
				if ((*lines3)[i][j] != (*lines3)[j][i]) {
					cout << "不对称" << (*lines1)[0][i] << "-" << (*lines1)[0][j] << ":" << (*lines3)[i][j] << endl;
					cout << "不对称" << (*lines1)[0][j] << "-" << (*lines1)[0][i] << ":" << (*lines3)[i][j] << endl;
				}
			}
		}
		lines1->clear();
		lines2->clear();
		lines3->clear();
		delete lines1;
		delete lines2;
		delete lines3;
	}; 

public:

	//TrafficAdvisory默认构造函数：顶点数是3、边数是1的随机的TrafficAdvisory
	TrafficAdvisory(bool whetherOutput = false) {
		_whetherOutput = whetherOutput;
		randomGraph(3, 1);
	}

	//TrafficAdvisory构造函数：顶点数是n、边数是e的随机的TrafficAdvisory
	TrafficAdvisory(int n, int e, bool whetherOutput = false) {
		_whetherOutput = whetherOutput;
		randomGraph(n, e);
	}

	/* 为名为 filename 的文件创建一个 TrafficAdvisory对象：从文件创建图对象g。
	 * filename：城市名 + 城市间是否相邻
	*/
	TrafficAdvisory(string filename, bool whetherOutput = false) {
		_whetherOutput = whetherOutput;
		graphFromFile(filename);
	}; 

	/* TrafficAdvisory构造函数：
	 * 为名为 filename1、filename2、filename3 文件创建一个 TrafficAdvisory对象：从文件创建TrafficAdvisory对象。
	 * filename1：城市名
	 * filename2：城市间是否相邻
	 * filename3：城市间距离
	*/
	TrafficAdvisory(string filename1, string filename2, string filename3, bool whetherOutput = false) {
		_whetherOutput = whetherOutput;
		graphFromFile(filename1, filename2, filename3);
	}; 

	/**TrafficAdvisory构造函数：从 g1对象创建一个 TrafficAdvisory对象：图对象g被g1替代*/
	TrafficAdvisory(WUSGraph<string, int>& g1, bool whetherOutput = false) {
		this->g = g1;
		this->_whetherOutput = whetherOutput;
	}; 

	~TrafficAdvisory() {
		//g.Clear();
	};

	//返回TrafficAdvisory的顶点标签集合
	//set<string> getLabels() {
	//	return g.getLabels();
	//}

	//TrafficAdvisory的赋值操作
	TrafficAdvisory& operator = (const TrafficAdvisory& ta) {
		this->g = ta.g;
		this->_whetherOutput = ta._whetherOutput;
		return *this;
	}

	//返回全国其它各个省会城市到source的最少边数，返回复合每个终点标签与路径长度（边数）的向量。
	//其中，如果源点和终点是同一个顶点，路径长度是0。如果两顶点不能到达，路径长度是INT_MAX。
	vector<Result_Label_PathLength> numVertices_from(string source) {
		//将你的代码替换掉下面的语句。
		return vector<Result_Label_PathLength>();
	}

	//使用Dijkstra求标签source到destination绕过passBy（默认值是空串）的最短路径，返回距离值。
	// 如果顶点不存在或不能到达，返回INT_MAX。
	int Dijkstra(const string& source, const string& destination, const string& passBy = string()) {
		//将你的代码替换掉下面的语句。
		return wclient.Dijkstra(g, source, destination);
		//return 0;
	}

	//使用Floyd求标签source到destination绕过passBy（默认值是空串）的最短路径，返回距离值。
	// 如果顶点不存在或不能到达，返回INT_MAX。
	int Floyd(const string& source, const string& destination = string(), const string& passBy = string()) {// , const string& method = "Dijkstra") {
		//将你的代码替换掉下面的语句。
		return 0;
	}

	// 求标签source到destination所有不重复的可行路径，路径上所有顶点不超过maximum_nodes个（默认值是INT_MAX）， 
	// 利用有效排序对所有可行的路径方案依据总长度进行排序输出到文件（如果第4个参数为空，则输出到屏幕，否则输出到其指定文件），
	// 返回可行的复合路径顶点标签序列与距离的向量（源点和终点是同一个顶点，返回0）
	vector<Result_Path_Distance> All_nonrepetition_paths(string source, string destination, int maximum_nodes = INT_MAX, string filename = "") {
		//将你的代码替换掉下面的语句。
		return vector<Result_Path_Distance>();
	};

	//直接求解两个城市间的前第 K 短的路径，返回这条路径的距离。
	// 如果顶点不存在或第K条最短路径不存在，返回INT_MAX。
	int  Kth_ShortestPath(string source, string destination, int k) {
		//将你的代码替换掉下面的语句。
		return 0;
	}
};
