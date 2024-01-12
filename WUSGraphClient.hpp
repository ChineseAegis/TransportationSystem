#pragma once
#include"WUSGraph.hpp"
#include"Deque.hpp"
#include"Neighbors.hpp"
#include"HashMap.hpp"
#include"Forest.hpp"
#include"Tree.hpp"
#include"WQUPCUFSet.hpp"
#include"MinHeap.hpp"
#include<string>
#include<iostream>
#include"MinIndexHeap.hpp"
#include"MinHeap.hpp"
#include"MaxIndexHeap.h"
#include<fstream>
#include <sstream>
#include <vector>

template<typename Object,typename Weight>
class WUSGraphClient {
public:
	
	
	
	WUSGraphClient()
	{

	}
	struct DObject
	{
		Object object;
		Weight distance;
		Object pre_object;
		bool is_pre_object;
		DObject()
		{

		}
		DObject(Object object, Weight distance = std::numeric_limits<Weight>::max()) :object(object), distance(distance),is_pre_object(0) {
		}
		DObject(Object object, Weight distance, Object pre_object) :object(object), distance(distance), pre_object(pre_object) {
			is_pre_object = true;
		}
		bool operator<(const DObject& other)
		{
			return distance < other.distance;
		}
		bool operator<=(const DObject& other)
		{
			return distance <= other.distance;
		}
		bool operator>(const DObject& other)
		{
			return distance > other.distance;
		}
		bool operator>=(const DObject& other)
		{
			return distance >= other.distance;
		}
	};

	int Dijkstra(WUSGraph<Object, Weight>& g, Object& s,Tree<Object,Weight> &tree)
	{
		
		int vertexCount = g.vertexCount();
		Object* obj = g.getVertices();
		MinIndexHeap<DObject> heap(vertexCount);
		HashMap<Object, Weight> Distances;
		HashMap<Object, int> ObjToInt;
		for (int i = 0; i < vertexCount; i++)
		{
			if (obj[i] == s)
			{
				heap.Insert(DObject(obj[i],0));
				Distances.Insert(std::make_pair(obj[i],0));
			}
			else
			{
				heap.Insert(DObject(obj[i]));
				Distances.Insert(std::make_pair(obj[i], std::numeric_limits<Weight>::max()));
			}
			ObjToInt.Insert(std::make_pair(obj[i], i));

		}
		while (vertexCount--)
		{
			DObject cur;
			heap.removeMin(cur);
			Distances.Remove(cur.object);
			Neighbors<Object, Weight> nei = g.getNeighbors(cur.object);
			std::cout << cur.object << " from " << cur.pre_object <<" distance"<<": "<<cur.distance<<std::endl;
			if (!cur.is_pre_object)
			{
				tree.insert(cur.object);
			}
			else
			{
				tree.insert(cur.object, cur.pre_object, g.getWeight(cur.object, cur.pre_object), cur.distance);
			}

			for (int i = 0; i < nei.size; i++)
			{
				if (Distances.containsKey(nei.object[i]))
				{
					Weight pre_weight = Distances.getValue(nei.object[i]);
					Weight self_weight = cur.distance;
					Weight cur_weight = self_weight + nei.weight[i];
					if (cur_weight < pre_weight&&cur_weight >= 0)
					{
						Distances.Remove(nei.object[i]);
						Distances.Insert(std::make_pair(nei.object[i], cur_weight));
						//heap.Insert(DObject(nei.object[i], cur_weight, cur.object));
						heap.Modify(ObjToInt.getValue(nei.object[i]), DObject(nei.object[i], cur_weight, cur.object));
						//std::cout << "顶点：" << nei.object[i] << " 距离：" << cur_weight << std::endl;
					}
				}
			}
		}
		delete[] obj;
		obj = nullptr;
		return 1;
	}
	int Dijkstra(WUSGraph<Object, Weight>& g, Object s,Object s1)
	{

		int vertexCount = g.vertexCount();
		Object* obj = g.getVertices();
		MinIndexHeap<DObject> heap(vertexCount);
		HashMap<Object, Weight> Distances;
		HashMap<Object, int> ObjToInt;
		for (int i = 0; i < vertexCount; i++)
		{
			if (obj[i] == s)
			{
				heap.Insert(DObject(obj[i], 0));
				Distances.Insert(std::make_pair(obj[i], 0));
			}
			else
			{
				heap.Insert(DObject(obj[i]));
				Distances.Insert(std::make_pair(obj[i], std::numeric_limits<Weight>::max()));
			}
			ObjToInt.Insert(std::make_pair(obj[i], i));

		}
		while (vertexCount--)
		{
			DObject cur;
			heap.removeMin(cur);
			Distances.Remove(cur.object);
			Neighbors<Object, Weight> nei = g.getNeighbors(cur.object);
			//std::cout << cur.object << " from " << cur.pre_object << " distance" << ": " << cur.distance << std::endl;
			/*if (!cur.is_pre_object)
			{
				tree.insert(cur.object);
			}
			else
			{
				tree.insert(cur.object, cur.pre_object, g.getWeight(cur.object, cur.pre_object), cur.distance);
			}*/
			if (cur.object == s1)
			{
				delete[] obj;
				obj = nullptr;
				return cur.distance;
			}
			for (int i = 0; i < nei.size; i++)
			{
				if (Distances.containsKey(nei.object[i]))
				{
					Weight pre_weight = Distances.getValue(nei.object[i]);
					Weight self_weight = cur.distance;
					Weight cur_weight = self_weight + nei.weight[i];
					if (cur_weight < pre_weight&&cur_weight>=0)
					{
						Distances.Remove(nei.object[i]);
						Distances.Insert(std::make_pair(nei.object[i], cur_weight));
						//heap.Insert(DObject(nei.object[i], cur_weight, cur.object));
						heap.Modify(ObjToInt.getValue(nei.object[i]), DObject(nei.object[i], cur_weight, cur.object));
						//std::cout << "顶点：" << nei.object[i] << " 距离：" << cur_weight << std::endl;
					}
				}
			}
		}
		delete[] obj;
		obj = nullptr;
		return INT_MAX;
	}
	void Prim(WUSGraph<Object, Weight>& g,Forest<Object,Weight>& f)
	{
		int vertexCount = g.vertexCount();
		Object* obj = g.getVertices();
		MinIndexHeap<DObject> heap(vertexCount);
		HashMap<Object, Weight> Distances;
		HashMap<Object, int> ObjToInt;
		for (int i = 0; i < vertexCount; i++)
		{
			if (i==0)
			{
				heap.Insert(DObject(obj[i], 0));
				Distances.Insert(std::make_pair(obj[i], 0));
			}
			else
			{
				heap.Insert(DObject(obj[i]));
				Distances.Insert(std::make_pair(obj[i], std::numeric_limits<Weight>::max()));
			}
			ObjToInt.Insert(std::make_pair(obj[i], i));

		}
		while (vertexCount--)
		{
			DObject cur;
			heap.removeMin(cur);
			Distances.Remove(cur.object);
			Neighbors<Object, Weight> nei = g.getNeighbors(cur.object);
			std::cout << cur.object << " from " << cur.pre_object << " distance" << ": " << cur.distance << std::endl;
			if (!cur.is_pre_object)
			{
				cur.distance = 0;
				f.insert(cur.object);
			}
			else
			{
				f.insert(cur.object, cur.pre_object, g.getWeight(cur.object, cur.pre_object));
			}
			for (int i = 0; i < nei.size; i++)
			{
				if (Distances.containsKey(nei.object[i]))
				{
					Weight pre_weight = Distances.getValue(nei.object[i]);
					Weight cur_weight = nei.weight[i];
					if (cur_weight < pre_weight)
					{
						Distances.Remove(nei.object[i]);
						Distances.Insert(std::make_pair(nei.object[i], cur_weight));
						//heap.Insert(DObject(nei.object[i], cur_weight, cur.object));
						heap.Modify(ObjToInt.getValue(nei.object[i]), DObject(nei.object[i], cur_weight, cur.object));
						//std::cout << "顶点：" << nei.object[i] << " 距离：" << cur_weight << std::endl;
					}
				}
			}
		}
		delete[] obj;
		obj = nullptr;
	}
	void LongestPath(WUSGraph<Object, Weight>& g, Object& s, Tree<Object,Weight>& lpt) {
		//struct DObject
		//{
		//	Object object;
		//	Weight distance;
		//	Object pre_object;
		//	bool is_pre_object;
		//	DObject()
		//	{

		//	}
		//	DObject(Object object, Weight distance = -1) :object(object), distance(distance), is_pre_object(0) {
		//	}
		//	DObject(Object object, Weight distance, Object pre_object) :object(object), distance(distance), pre_object(pre_object) {
		//		is_pre_object = true;
		//	}
		//	bool operator<(const DObject& other)
		//	{
		//		return distance > other.distance;
		//	}
		//	bool operator<=(const DObject& other)
		//	{
		//		return distance >= other.distance;
		//	}
		//	bool operator>(const DObject& other)
		//	{
		//		return distance < other.distance;
		//	}
		//	bool operator>=(const DObject& other)
		//	{
		//		return distance <= other.distance;
		//	}
		//};


		int vertexCount = g.vertexCount();
		Object* obj = g.getVertices();
		MaxIndexHeap<DObject> heap(vertexCount);
		HashMap<Object, Weight> Distances;
		HashMap<Object, int> ObjToInt;
		for (int i = 0; i < vertexCount; i++)
		{
			if (obj[i] == s)
			{
				heap.Insert(DObject(obj[i], 0));
				Distances.Insert(std::make_pair(obj[i], 0));
			}
			else
			{
				heap.Insert(DObject(obj[i],-1));
				Distances.Insert(std::make_pair(obj[i], -1));
			}
			ObjToInt.Insert(std::make_pair(obj[i], i));

		}
		while (vertexCount--)
		{
			DObject cur;
			heap.removeMin(cur);
			Distances.Remove(cur.object);
			Neighbors<Object, Weight> nei = g.getNeighbors(cur.object);
			std::cout << cur.object << " from " << cur.pre_object << " distance" << ": " << cur.distance << std::endl;
			if (!cur.is_pre_object)
			{
				lpt.insert(cur.object);
			}
			else
			{
				lpt.insert(cur.object, cur.pre_object, g.getWeight(cur.object, cur.pre_object), cur.distance);
			}

			for (int i = 0; i < nei.size; i++)
			{
				if (Distances.containsKey(nei.object[i]))
				{
					Weight pre_weight = Distances.getValue(nei.object[i]);
					Weight self_weight = cur.distance;
					Weight cur_weight = self_weight + nei.weight[i];
					if (cur_weight > pre_weight && cur_weight >= 0)
					{
						Distances.Remove(nei.object[i]);
						Distances.Insert(std::make_pair(nei.object[i], cur_weight));
						//heap.Insert(DObject(nei.object[i], cur_weight, cur.object));
						heap.Modify(ObjToInt.getValue(nei.object[i]), DObject(nei.object[i], cur_weight, cur.object));
						//std::cout << "顶点：" << nei.object[i] << " 距离：" << cur_weight << std::endl;
					}
				}
			}
		}
		delete[] obj;
		obj = nullptr;
	}
	int MaxDegree(const WUSGraph<Object, Weight>& g) {
		Object* vertexs = g.getVertices();
		int maxdegree = Degree(vertexs[0]);
		int n = g.vertexCount();

		for (int i = 0; i < n; i++) {
			if (maxdegree < Degree(vertexs[i + 1])) {
				maxdegree = Degree(vertexs[i + 1]);
			}
		}
		delete[]vertexs;
	}
	void DFS(WUSGraph<Object, Weight>& g, void(*visit)(Object), const Object& s) {
		Object* vertexs = g.getVertices();
		int n = g.vertexCount();
		HashMap<Object, int> tovisitMap;
		for (int i = 0; i < n; i++)tovisitMap.Insert(std::make_pair(vertexs[i], 0));

		DbLinkedList<Object> vertexstack;
		vertexstack.push_back(s);
		tovisitMap.Insert(std::make_pair(s, 1));
		while (!vertexstack.isEmpty()) {
			Object vertex = vertexstack.top();
			
			visit(vertex);
			vertexstack.pop_back();
			Neighbors<Object, Weight> nei = g.getNeighbors(vertex);
			Object* U = nei.object;
			int size = nei.size;
			for (int i=0;i<size;i++)
			{
				if (tovisitMap.getValue(U[i]) == 0) {
					vertexstack.push_back(U[i]);
					tovisitMap.Insert(std::make_pair(U[i], 1));
				}
			}
		}
		delete[]vertexs;
	}
	void BFS(WUSGraph<Object, Weight>& g, void(*visit)(Object), const Object& s) {
		Object* vertexs = g.getVertices();
		int n = g.vertexCount();
		HashMap<Object, int> tovisitMap;
		for (int i = 0; i < n; i++)tovisitMap.Insert(std::make_pair(vertexs[i], 0));

		ADeque<Object> vertexdeque;
		vertexdeque.pushback(s);
		while (!vertexdeque.isEmpty()) {
			Object vertex = vertexdeque.front();
			tovisitMap.Insert(std::make_pair(vertex, 1));
			visit(vertex);
			vertexdeque.pop();
			Object* U = g.getNeighbors(vertex).object;
			int size = g.getNeighbors(vertex).size;
			for (int i = 0; i < size; i++)
			{
				if (tovisitMap.getValue(vertex) == 0) {
					vertexdeque.pushback(U[i]);
				}
			}
		}
		delete[]vertexs;
	}
	void Print(const WUSGraph<Object, Weight>& g) {
		Object* vertexs = g.getVertices();
		int n = g.vertexCount();
		for (int i = 0; i < n; i++) {
			std::cout << vertexs[i] << " ->";
			Neighbors<Object, Weight> neighbors = g.getNeighbors(vertexs[i]);
			int degree = g.Degree(vertexs[i]);
			for (int j = 0; j < degree; j++) {
				std::cout << neighbors->object[j];
			}
			std::cout << std::endl;
		}
		delete[]vertexs;
	}

	void Kruskal(WUSGraph<Object, Weight>& g, Forest<Object, Weight>& msf) {
		int n = g.vertexCount();
		if (n <= 0) return;
		Object* vertices = g.getVertices();
		HashMap<Object, int>toVertexMap;
		for (int i = 0; i < n; i++) {
			toVertexMap.Insert(std::make_pair(vertices[i], i));
		}

		WQUPCUFSet uf(n);

		// 初始化最小堆，存储所有边
		int m = g.edgeCount();
		MinHeap<ForestNode<Weight>> H(m);

		for (int i = 0; i < n; i++) {
			Neighbors<Object, Weight> neighbors = g.getNeighbors(vertices[i]);
			for (int j = 0; j < neighbors.size; j++) {
				Object u = vertices[i];
				Object v = neighbors.object[j];
				Weight w = neighbors.weight[j];
				if (toVertexMap.getValue(u) < toVertexMap.getValue(v)) {//只处理父节点在前的边
					if (!uf.isConnected(toVertexMap.getValue(u), toVertexMap.getValue(v))) {
						ForestNode<Weight> edgeNode(toVertexMap.getValue(v), toVertexMap.getValue(u), w);
						H.Insert(edgeNode);
					}
				}
			}
		}

		// 构建最小生成森林
		int count = 0;
		while (count < n - 1 && !H.IsEmpty()) {
			ForestNode<Weight> edgeNode;
			H.RemoveMin(edgeNode);
			int u = uf.find(edgeNode.key);
			int v = uf.find(edgeNode.parent);
			if (u != v) {
				uf.Union(u, v);
				msf.insert(vertices[edgeNode.key], vertices[edgeNode.parent], edgeNode.weight);
				//std::cout << vertices[edgeNode.parent] << vertices[edgeNode.key] << edgeNode.weight << std::endl;
				count++;
			}
		}
		
		delete[] vertices;
	}
	bool Eula(WUSGraph<Object, Weight>& g) {
		Object* vertexs = g.addVertex();
		int size = g.vertexCount();
		for (int i = 0; i < size;i++) {
			if (g.Degree(vertexs[i]) % 2 != 0)return false;
		}
		return true;
		delete[]vertexs;
	}
	void CreateGraphFromFile(std::string filepath, WUSGraph<Object, Weight>& g,int Num1=3,int Num2=2)
	{
		int vertexNum = 0;
		int edgeNum = 0;
		std::ifstream file(filepath, std::ios::binary);
		if (!file) {
			std::cerr << "无法打开文件" << std::endl;

		}

		const size_t blockSize = 1024;
		char buffer[blockSize];
		std::string lastPartialWord;
		std::vector<std::string> words;
		while (file.read(buffer, sizeof(buffer)) || file.gcount()) {
			//std::cout << lastPartialWord << std::endl;
			std::stringstream stream(std::string(lastPartialWord) + std::string(buffer, file.gcount()));
			std::string word;
			std::string line;
			while (std::getline(stream, line, '\n'))
			{
				if (stream.tellg() < 0 && !file.eof())
				{
					lastPartialWord = line;
					break;
				}
				std::stringstream lineStream(line);
				while (lineStream >> word) {
					words.push_back(word);
				}
			}
			// 保存最后一个可能不完整的单词，用于与下一个块拼接
			//stream.clear();
			//stream.seekg(0, std::ios::end); // 移动到流的末尾
			//size_t endPos = stream.tellg(); // 获取当前位置（末尾）
			//lastPartialWord = std::string(buffer + endPos, file.gcount() - endPos);
		}

		file.close();
		int beginNum = 2;
		int num1=Num1;
		int num2=Num2;
		vertexNum = std::stoi(words[0]);
		edgeNum = std::stoi(words[1]);
		//std::cout << vertexNum << " " << edgeNum << std::endl;
		HashMap<std::string, std::pair<int, int>> h;
		for (int i = 0; i < vertexNum; i++)
		{
			std::string vertexName = words[i * num1 + beginNum];
			//std::cout << vertexName << " " << words[i * 3 + beginNum + 1]<< " "<<words[i * 3 + beginNum + 2]<< std::endl;
			g.addVertex(vertexName);
			int x = std::stoi(words[i * num1 + beginNum + 1]);
			int y = std::stoi(words[i * num1 + beginNum + 2]);
			h.Insert(std::make_pair(vertexName, std::make_pair(x, y)));
		}
		for (int i = 0; i < edgeNum; i++)
		{
			std::string v1 = words[i * num2 + vertexNum * num1 + beginNum];
			std::string v2 = words[i * num2 + vertexNum * num1 + beginNum + 1];
			//std::cout << words[i * 2 + vertexNum * 3 + beginNum] << " " << words[i * 2 + vertexNum * 3 + beginNum + 1] << std::endl;
			std::pair<int, int> p1 = h.getValue(v1);
			std::pair<int, int> p2 = h.getValue(v2);
			int distance = std::sqrt(std::abs(p1.first - p2.first) * std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second) * std::abs(p1.second - p2.second));
			g.addEdge(v1, v2, distance);
		}
		std::cout << g.vertexCount() << " " << g.edgeCount() << std::endl;
		//// 输出读取的单词
		//for (const auto& w : words) {
		//	std::cout << w << std::endl;
		//}


	}
	void CreateGraphFromFile2(std::string filepath, WUSGraph<Object, Weight>& g, int Num1 = 1, int Num2 = 3)
	{
		int vertexNum = 0;
		int edgeNum = 0;
		std::ifstream file(filepath, std::ios::binary);
		if (!file) {
			std::cerr << "无法打开文件" << std::endl;

		}

		const size_t blockSize = 1024;
		char buffer[blockSize];
		std::string lastPartialWord;
		std::vector<std::string> words;
		while (file.read(buffer, sizeof(buffer)) || file.gcount()) {
			//std::cout << lastPartialWord << std::endl;
			std::stringstream stream(std::string(lastPartialWord) + std::string(buffer, file.gcount()));
			std::string word;
			std::string line;
			while (std::getline(stream, line, '\n'))
			{
				if (stream.tellg() < 0 && !file.eof())
				{
					lastPartialWord = line;
					break;
				}
				std::stringstream lineStream(line);
				while (lineStream >> word) {
					words.push_back(word);
				}
			}
			// 保存最后一个可能不完整的单词，用于与下一个块拼接
			//stream.clear();
			//stream.seekg(0, std::ios::end); // 移动到流的末尾
			//size_t endPos = stream.tellg(); // 获取当前位置（末尾）
			//lastPartialWord = std::string(buffer + endPos, file.gcount() - endPos);
		}

		file.close();
		int beginNum = 2;
		int num1 = Num1;
		int num2 = Num2;
		vertexNum = std::stoi(words[0]);
		edgeNum = std::stoi(words[1]);
		//std::cout << vertexNum << " " << edgeNum << std::endl;
		HashMap<std::string, std::pair<int, int>> h;
		for (int i = 0; i < vertexNum; i++)
		{
			std::string vertexName = words[i * num1 + beginNum];
			//std::cout << vertexName << " " << words[i * 3 + beginNum + 1]<< " "<<words[i * 3 + beginNum + 2]<< std::endl;
			g.addVertex(vertexName);
		}
		for (int i = 0; i < edgeNum; i++)
		{
			std::string v1 = words[i * num2 + vertexNum * num1 + beginNum];
			std::string v2 = words[i * num2 + vertexNum * num1 + beginNum + 1];
			//std::cout << words[i * 2 + vertexNum * 3 + beginNum] << " " << words[i * 2 + vertexNum * 3 + beginNum + 1] << std::endl;
			int distance = std::stoi(words[i * num2 + vertexNum * num1 + beginNum + 2]);
			g.addEdge(v1, v2, distance);
		}
		std::cout << g.vertexCount() << " " << g.edgeCount() << std::endl;
		//// 输出读取的单词
		//for (const auto& w : words) {
		//	std::cout << w << std::endl;
		//}


	}
};

