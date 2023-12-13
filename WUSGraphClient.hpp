#pragma once
#include"WUSGraph.hpp"
#include"Deque.hpp"
template<typename Object,typename Weight>
class WUSGraphClient {
public:
	WUSGraph<Object,Weight> g;
	int MaxDegree(const WUSGraph& g) {
		int maxdegree;
		int n=g.vertexCount();
		for (int i = 0; i < n; i++) {
			int degree1 = Degree(i), degree2 = Degree(i + 1);
			if (degree1 <degree2 ) {
				maxdegree = degree2;
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
	void BFS(Graph& g, void(*visit), const Object& s) {
		int n = g.vertexCount();
		bool* visited = new bool[n];
		for (int i = 0; i < n; i++)visited[i] = false;
		Object* vertexs = g.getVertices();
		for (int j = 0; j < n; j++) {
			if (s == vertexs[i]) {
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
};