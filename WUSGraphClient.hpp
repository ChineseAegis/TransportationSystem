#pragma once
#include"WUSGraph.hpp"
#include"Deque.hpp"
#include"Neighbors.hpp"
#include<iostream>
#include"MinIndexHeap.hpp"
#include"MinHeap.hpp"
template<typename Object,typename Weight>
class WUSGraphClient {
public:
	
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
						std::cout << "¶¥µã£º" << nei.object[i] << " ¾àÀë£º" << cur_weight << std::endl;
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
						//std::cout << "¶¥µã£º" << nei.object[i] << " ¾àÀë£º" << cur_weight << std::endl;
					}
				}
			}
		}
		delete obj;
		obj = nullptr;
	}
};