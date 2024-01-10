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
#include"MinIndexHeap.hpp"
#include"MinHeap.hpp"

template<typename Object,typename Weight>
class WUSGraphClient {
public:
	HashMap<std::string, int> tovisitMap;
	HashMap<std::string, int>toVertexMap;
	//WUSGraph<Object,Weight> G;
	//int MaxDegree(const WUSGraph<Object,Weight>& g) {
	//	int maxdegree= Degree(vertexs[i]);
	//	int n=g.vertexCount();
	//	Object* vertexs = g.getVertices();
	//	for (int i = 0; i < n; i++) {
	//		if ( maxdegree < Degree(vertexs[i+1])) {
	//			maxdegree = Degree(vertexs[i + 1]);
	//		}
	//	}
	//}
	//void DFS(WUSGraph<Object,Weight>& g, void(*visit), const Object&s) {
	//	int i, loc, n = g.vertexCount();
	//	bool* visited = new bool[n];
	//	for (int i = 0; i < n; i++)visited[i] = false;
	//	Object* vertexs = g.getVertices();
	//	for (int j = 0; j < n; j++) {
	//		if (s == vertexs[i]) {
	//			loc = j;
	//			break;
	//		}
	//	}
	//	for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n) {
	//		if (!visited[i]) {
	//			DFS(g, i, visited,*visit);
	//		}
	//	}
	//	delete[]visited;
	//}
	//void DFS(WUSGraph<Object, Weight>& g, int v, bool visited[], void(*visit)) {
	//	*visit(v);
	//	visited[v] = true;
	//	Object* U = g.getNeighbors(v).object[];
	//	for (int w : U) {
	//		if (!visited[w]) {
	//			DFS(g, w, visited, *visit);
	//		}
	//	}
	//}
	//void BFS(WUSGraph<Object, Weight>& g, void(*visit), const Object& s) {
	//	int n = g.vertexCount();
	//	bool* visited = new bool[n];
	//	for (int i = 0; i < n; i++)visited[i] = false;
	//	Object* vertexs = g.getVertices();
	//	for (int j = 0; j < n; j++) {
	//		if (s == vertexs[j]) {
	//			loc = j;
	//			break;
	//		}
	//	}
	//	if (loc < 0)return;
	//	ADeque<int>Q;
	//	for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n) {
	//		if (!visited[i]) {
	//			visited[i] = true;
	//			Q.pushback(i);
	//			while (!Q.isEmpty()) {
	//				loc = Q.front();
	//				Q.pop();
	//				*visit(loc);
	//				Object* U = g.getNeighbors(loc).object[];
	//				for (int w : U) {
	//					if (!visited[w]) {
	//						visited[w] = true;
	//						Q.pushback(w);
	//					}
	//				}
	//			}
	//		}
	//	}
	//	delete[]visited;
	//}
	void Print(const WUSGraph<Object, Weight>& g) {
		Object* vertexs = g.getVertices();
		int n = g.vertexCount();
		for (int i = 0; i < n; i++) {
			std::cout << vertexs[i] << " ->";
			Neighbors<Object, Weight>* neighbors = g.getNeighbors(vertexs[i]);
			int degree = g.Degree(vertexs[i]);
			for (int j = 0; j < degree; j++) {
				std::cout << neighbors->object[j];
			}
			std::cout << std::endl;
		}

	}
	struct DObject
	{
		Object object;
		Weight distance;
		Object pre_object;
		DObject()
		{

		}
		DObject(Object object, Weight distance = std::numeric_limits<Weight>::max()) :object(object), distance(distance) {
		}
		DObject(Object object, Weight distance, Object pre_object) :object(object), distance(distance), pre_object(pre_object) {
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

	void Dijkstra(WUSGraph<Object, Weight>& g, Object& s)
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
			for (int i = 0; i < nei.size; i++)
			{
				if (Distances.containsKey(nei.object[i]))
				{
					Weight pre_weight = Distances.getValue(nei.object[i]);
					Weight self_weight = cur.distance;
					Weight cur_weight = self_weight + nei.weight[i];
					if (cur_weight < pre_weight)
					{
						Distances.Remove(nei.object[i]);
						Distances.Insert(std::make_pair(nei.object[i], cur_weight));
						//heap.Insert(DObject(nei.object[i], cur_weight, cur.object));
						heap.Modify(ObjToInt.getValue(nei.object[i]), DObject(nei.object[i], cur_weight, cur.object));
						std::cout << "顶点：" << nei.object[i] << " 距离：" << cur_weight << std::endl;
					}
				}
			}
		}
		delete obj;
		obj = nullptr;
	}
	void Prim(WUSGraph<Object, Weight>& g)
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
		delete obj;
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
	}
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
	void Kruskal(WUSGraph<Object, Weight>& g, Forest<Object, Weight>& msf) {
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

