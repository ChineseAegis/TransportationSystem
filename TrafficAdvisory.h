/*
 * TrafficAdvisory.h
 * �����ʵ�ֽ�ͨ��ѯ������TrafficAdvisory������һ��GraphAdjacencyList<string,int>�����
 * @author Yan Guo ���� ���� <guoyan49@cug.edu.cn>
 * @date ���� 2024-1-5
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
#include "UtilitiesString.h"//trim_blank_space()��stringfunction()��
//using namespace std;
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::set;
using std::ifstream;
using std::ostringstream;
using std::cerr;

//�����������1����ʾ����B��ǩ��A���㵽B�������С·������
struct Result_Label_PathLength {
	std::string label;  //�����ǩ
	int pathLength; //����A����ǩΪlabel��B�������С·������
	bool operator ==(const Result_Label_PathLength& other)const {
		return (label.compare(other.label)==0 && pathLength == other.pathLength);
	}
	bool operator <(const Result_Label_PathLength & other)const {
		return (label.compare(other.label) < 0 || (label.compare(other.label) == 0 && pathLength < other.pathLength));
	}
};

//�����������2����ʾ·����·������
struct Result_Path_Distance {
	vector<string> path;//�����ǩ��������ʾһ��·��
	int dist;//path��ʾ��·����Ȩֵ��������룩֮�͡�
};

class TrafficAdvisoryCheck;

class TrafficAdvisory {
	friend class TrafficAdvisoryCheck; //��Ԫ

private:
	WUSGraphClient<string, int> wclient;
	WUSGraph<string, int> g; //�������๹��һ��ͼ����

	bool _whetherOutput = false; //�Ƿ���������������ϸ��Ϣ

	//����һ����������n��������e�������ͼ��
	void randomGraph(int n, int e) {
		using T = string;
		using E = int;

		//����������ַ������飺ͼ�Ķ����ǩ
		T* arr = makeUniqueRandomArray<T>(n, randomString);//����һ������Ϊn��ֵ���ظ�������ַ�������

		//����Matrix��¼�ߣ��Է�ֹ�����ظ��ߡ�
		std::vector<std::vector<E>> Matrix;// ��ʼ������,
		Matrix.resize(n, std::vector<int>(n, 0));

		for (int i = 0; i < n; ++i)
			g.isVertex(arr[i]);//���붥��

		// �����������
		std::srand(std::time(0));

		// ��������
		for (int i = 0; i < e; ++i) {
			int source = std::rand() % n;
			int destination = std::rand() % n;
			E weight = std::rand() % 100; // �������Ȩֵ���˴���ΧΪ0-1010

			// ��ֹ�����Ի��ߺ��ظ���
			while (source == destination || Matrix[source][destination] != 0) {
				source = std::rand() % n;
				destination = std::rand() % n;
			}
			Matrix[source][destination] = 1;
			Matrix[destination][source] = 1;

			// ���ߵ�Ȩֵ����Ϊ�������
			g.addEdge(arr[source], arr[destination], weight);//�����
			g.addEdge(arr[destination], arr[source], weight);//����ͼ��������һ����
		}

		delete[] arr;
	}
	
	/** 
	* ��ȡ���� CSV ������������ ÿ���ڲ��б���� CSV ��һ�У�����ÿ�����ŷָ���ֵ��Ϊһ����Ŀ��
	* ���� CSV �ļ�������Ϊ�ָ����Ķ���֮�ⲻ���������ķָ�����
	* ����ļ�����Ч�����˳���
	*
	* ���ŷָ�ֵ��Comma-Separated Values��CSV����ʱҲ��Ϊ�ַ��ָ�ֵ����Ϊ�ָ��ַ�Ҳ���Բ��Ƕ��ţ�
	* �ļ��Դ��ı���ʽ�洢������ݣ����ֺ��ı�����
	*/
	template<class T>
	vector<vector<T>>*& readCSV(std::string filename, T(*function)(char*)) {
		vector<vector<T>>* records = new vector<vector<T>>();
		typename vector<T>::iterator it2;
		typename vector<vector<T>>::iterator it1;
		ifstream* in = new ifstream(filename);
		if (!in->is_open()) {
			cerr << filename << "�ļ����ܴ򿪣�\n";
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
				cerr << filename << "�ڴ治�ܷ��䣡\n";
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

	//��һ���ļ�filename(�������ǩ�Ͷ�������ڹ�ϵ)����ͼ����g��
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
			g.addEdge(source, destination, 1);//�ļ�����Ȩֵ��Ϣ����ȨֵĬ��Ϊ1
			g.addEdge(destination, source, 1);//����ͼ��������һ����
		}
		lines->clear();
		delete lines;
	}; 

	/* ����Ϊ filename1��filename2��filename3 �ļ�����һ�� ͼ���󣺴��ļ�����ͼ����g��
	 * filename1��������
	 * filename2�����м��Ƿ�����
	 * filename3�����м����
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
					cout << "���Գ�" << (*lines1)[0][i] << "-" << (*lines1)[0][j] << ":" << (*lines3)[i][j] << endl;
					cout << "���Գ�" << (*lines1)[0][j] << "-" << (*lines1)[0][i] << ":" << (*lines3)[i][j] << endl;
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

	//TrafficAdvisoryĬ�Ϲ��캯������������3��������1�������TrafficAdvisory
	TrafficAdvisory(bool whetherOutput = false) {
		_whetherOutput = whetherOutput;
		randomGraph(3, 1);
	}

	//TrafficAdvisory���캯������������n��������e�������TrafficAdvisory
	TrafficAdvisory(int n, int e, bool whetherOutput = false) {
		_whetherOutput = whetherOutput;
		randomGraph(n, e);
	}

	/* Ϊ��Ϊ filename ���ļ�����һ�� TrafficAdvisory���󣺴��ļ�����ͼ����g��
	 * filename�������� + ���м��Ƿ�����
	*/
	TrafficAdvisory(string filename, bool whetherOutput = false) {
		_whetherOutput = whetherOutput;
		graphFromFile(filename);
	}; 

	/* TrafficAdvisory���캯����
	 * Ϊ��Ϊ filename1��filename2��filename3 �ļ�����һ�� TrafficAdvisory���󣺴��ļ�����TrafficAdvisory����
	 * filename1��������
	 * filename2�����м��Ƿ�����
	 * filename3�����м����
	*/
	TrafficAdvisory(string filename1, string filename2, string filename3, bool whetherOutput = false) {
		_whetherOutput = whetherOutput;
		graphFromFile(filename1, filename2, filename3);
	}; 

	/**TrafficAdvisory���캯������ g1���󴴽�һ�� TrafficAdvisory����ͼ����g��g1���*/
	TrafficAdvisory(WUSGraph<string, int>& g1, bool whetherOutput = false) {
		this->g = g1;
		this->_whetherOutput = whetherOutput;
	}; 

	~TrafficAdvisory() {
		//g.Clear();
	};

	//����TrafficAdvisory�Ķ����ǩ����
	//set<string> getLabels() {
	//	return g.getLabels();
	//}

	//TrafficAdvisory�ĸ�ֵ����
	TrafficAdvisory& operator = (const TrafficAdvisory& ta) {
		this->g = ta.g;
		this->_whetherOutput = ta._whetherOutput;
		return *this;
	}

	//����ȫ����������ʡ����е�source�����ٱ��������ظ���ÿ���յ��ǩ��·�����ȣ���������������
	//���У����Դ����յ���ͬһ�����㣬·��������0����������㲻�ܵ��·��������INT_MAX��
	vector<Result_Label_PathLength> numVertices_from(string source) {
		//����Ĵ����滻���������䡣
		return vector<Result_Label_PathLength>();
	}

	//ʹ��Dijkstra���ǩsource��destination�ƹ�passBy��Ĭ��ֵ�ǿմ��������·�������ؾ���ֵ��
	// ������㲻���ڻ��ܵ������INT_MAX��
	int Dijkstra(const string& source, const string& destination, const string& passBy = string()) {
		//����Ĵ����滻���������䡣
		return wclient.Dijkstra(g, source, destination);
		//return 0;
	}

	//ʹ��Floyd���ǩsource��destination�ƹ�passBy��Ĭ��ֵ�ǿմ��������·�������ؾ���ֵ��
	// ������㲻���ڻ��ܵ������INT_MAX��
	int Floyd(const string& source, const string& destination = string(), const string& passBy = string()) {// , const string& method = "Dijkstra") {
		//����Ĵ����滻���������䡣
		return 0;
	}

	// ���ǩsource��destination���в��ظ��Ŀ���·����·�������ж��㲻����maximum_nodes����Ĭ��ֵ��INT_MAX���� 
	// ������Ч��������п��е�·�����������ܳ��Ƚ�������������ļ��������4������Ϊ�գ����������Ļ�������������ָ���ļ�����
	// ���ؿ��еĸ���·�������ǩ����������������Դ����յ���ͬһ�����㣬����0��
	vector<Result_Path_Distance> All_nonrepetition_paths(string source, string destination, int maximum_nodes = INT_MAX, string filename = "") {
		//����Ĵ����滻���������䡣
		return vector<Result_Path_Distance>();
	};

	//ֱ������������м��ǰ�� K �̵�·������������·���ľ��롣
	// ������㲻���ڻ��K�����·�������ڣ�����INT_MAX��
	int  Kth_ShortestPath(string source, string destination, int k) {
		//����Ĵ����滻���������䡣
		return 0;
	}
};
