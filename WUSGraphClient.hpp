#pragma once
#include"WUSGraph.hpp"
#include"Deque.hpp"
#include"Neighbors.hpp"
#include"HashMap.hpp"
#include"Forest.hpp"
#include"WQUPCUFSet.hpp"
#include"MinHeap.hpp"
#include<string>
#include<iostream>
#include<stack>
template<typename Object,typename Weight>
class WUSGraphClient {
public:
	HashMap<std::string, int> tovisitMap;
	HashMap<std::string, int>toVertexMap;
	//WUSGraph<Object,Weight> G;
	int MaxDegree(const WUSGraph<Object, Weight>& g) {
		Object* vertexs = g.getVertices();
		int maxdegree= Degree(vertexs[0]);
		int n=g.vertexCount();
	
		for (int i = 0; i < n; i++) {
			if ( maxdegree < Degree(vertexs[i+1])) {
				maxdegree = Degree(vertexs[i + 1]);
			}
		}
	}
	void DFS(WUSGraph<Object, Weight>& g, void(*visit), const Object& s) {
		Object* vertexs = g.getVertices();
		int n = g.vertexCount();
		for (int i = 0; i < n; i++)tovisitMap.Insert(std::make_pair(vertexs[i], 0));
		
		std::stack<Object> vertexstack;
		vertexstack.push(s);
		while (!vertexstack.empty()) {
			Object vertex = vertexstack.top();
			tovisitMap.Insert(std::make_pair(vertex, 1));
			visit(vertex);
			vertexstack.pop();
			Object* U = g.getNeighbors(vertex).object;
			for (Object v : U)
			{
				if (tovisitMap.getValue(vertex) == 0) {
					vertexstack.push(v);
				}
			}
		}
	}
	//void DFS(WUSGraph& g, void(*visit), const Object&s) {
	//	int i, loc, n = g.vertexCount();
	//	Object* vertexs = g.getVertices();
	//	//bool* visited = new bool[n];
	//	for (int i = 0; i < n; i++)tovisitMap.Insert(std::make_pair(vertexs[i], 0));
	//	
	//	for (int j = 0; j < n; j++) {
	//		if (s == vertexs[i]) {
	//			loc = j;
	//			break;
	//		}
	//	}
	//	for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n) {
	//		if (tovisitMap.getValue(vertexs[i])==0) {
	//			DFS(g, vertexs[i], *visit);
	//		}
	//	}
	//	
	//}
	//void DFS(WUSGraph& g, Object v, void(*visit)) {
	//	*visit(v);
	//	tovisitMap.Insert(std::make_pair(v, 1));
	//	Object* U = g.getNeighbors(v).object[];
	//	for (Object w : U) {
	//		if (tovisitMap.getValue(w)==0) {
	//			DFS(g, w, *visit);
	//		}
	//	}
	//}
	//void BFS(WUSGraph& g, void(*visit), const Object& s) {
	//	int n = g.vertexCount();
	//	Object* vertexs = g.getVertices();
	//	//bool* visited = new bool[n];
	//	for (int i = 0; i < n; i++)tovisitMap.Insert(std::make_pair(vertexs[i], 0));
	//	//for (int i = 0; i < n; i++)visited[i] = false;
	//	
	//	for (int j = 0; j < n; j++) {
	//		if (s == vertexs[j]) {
	//			loc = j;
	//			break;
	//		}
	//	}
	//	if (loc < 0)return;
	//	ADeque<Object>Q;
	//	for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n) {
	//		if (tovisitMap.getValue(vertexs[i]==0) ){
	//			tovisitMap.Insert(std::make_pair(vertexs[i], 1));
	//			Q.pushback(to);
	//			while (!Q.isEmpty()) {
	//				loc = Q.front();
	//				Q.pop();
	//				*visit(loc);
	//				Object* U = g.getNeighbors(loc).object[];
	//				for (Object w : U) {
	//					if (tovisitMap.getValue(w)==0) {
	//						tovisitMap.Insert(std::make_pair(w, 1));
	//						Q.pushback(w);
	//					}
	//				}
	//			}
	//		}
	//	}
	//	delete[]visited;
	//}
	void BFS(WUSGraph<Object, Weight>& g, void(*visit), const Object& s) {
		Object* vertexs = g.getVertices();
		int n = g.vertexCount();
		for (int i = 0; i < n; i++)tovisitMap.Insert(std::make_pair(vertexs[i], 0));

		ADeque<Object> vertexdeque;
		vertexdeque.pushback(s);
		while (!vertexdeque.isEmpty()) {
			Object vertex = vertexdeque.front();
			tovisitMap.Insert(std::make_pair(vertex, 1));
			vertexdeque.pop();
			Object* U = g.getNeighbors(vertex).object;
			for (Object v : U)
			{
				if (tovisitMap.getValue(vertex) == 0) {
					vertexdeque.pushback(v);
				}
			}
		}
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

	}
	void Kruskal( WUSGraph<Object, Weight>& g, Forest<Object, Weight>& msf) {
		int n = g.vertexCount();
		if (n <= 0) return;
		Object* vertices = g.getVertices();
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
				//msf.insert(vertices[edgeNode.key], vertices[edgeNode.parent], edgeNode.weight);
				std::cout << vertices[edgeNode.parent] << vertices[edgeNode.key] << edgeNode.weight << std::endl;
				count++;
			}
		}

		delete[] vertices;
	}

};
