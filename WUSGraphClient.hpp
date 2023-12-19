#pragma once
#include"WUSGraph.hpp"
#include"Deque.hpp"
#include"Neighbors.hpp"
#include<iostream>
template<typename Object,typename Weight>
class WUSGraphClient {
public:
	
	//WUSGraph<Object,Weight> G;
	int MaxDegree(const WUSGraph& g) {
		int maxdegree= Degree(vertexs[i]);
		int n=g.vertexCount();
		Object* vertexs = g.getVertices();
		for (int i = 0; i < n; i++) {
			if ( maxdegree < Degree(vertexs[i+1])) {
				maxdegree = Degree(vertexs[i + 1]);
			}
		}
	}
	void DFS(WUSGraph& g, void(*visit), const Object&s) {
		int i, loc, n = g.vertexCount();
		bool* visited = new bool[n];
		for (int i = 0; i < n; i++)visited[i] = false;
		Object* vertexs = g.getVertices();
		for (int j = 0; j < n; j++) {
			if (s == vertexs[i]) {
				loc = j;
				break;
			}
		}
		for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n) {
			if (!visited[i]) {
				DFS(g, i, visited,*visit);
			}
		}
		delete[]visited;
	}
	void DFS(WUSGraph& g, int v, bool visited[], void(*visit)) {
		*visit(v);
		visited[v] = true;
		Object* U = g.getNeighbors(v).object[];
		for (int w : U) {
			if (!visited[w]) {
				DFS(g, w, visited, *visit);
			}
		}
	}
	void BFS(WUSGraph& g, void(*visit), const Object& s) {
		int n = g.vertexCount();
		bool* visited = new bool[n];
		for (int i = 0; i < n; i++)visited[i] = false;
		Object* vertexs = g.getVertices();
		for (int j = 0; j < n; j++) {
			if (s == vertexs[j]) {
				loc = j;
				break;
			}
		}
		if (loc < 0)return;
		ADeque<int>Q;
		for (i = loc; i <= (i + n - 1) % n; i = (i + 1) % n) {
			if (!visited[i]) {
				visited[i] = true;
				Q.pushback(i);
				while (!Q.isEmpty()) {
					loc = Q.front();
					Q.pop();
					*visit(loc);
					Object* U = g.getNeighbors(loc).object[];
					for (int w : U) {
						if (!visited[w]) {
							visited[w] = true;
							Q.pushback(w);
						}
					}
				}
			}
		}
		delete[]visited;
	}
	void Print(const WUSGraph& g) {
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
};