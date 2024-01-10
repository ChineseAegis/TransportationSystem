#pragma once

class WQUPCUFSet {
private:
	int* parent;
	int size;
public:
	WQUPCUFSet(int sz = 1000) {
		size = sz;
		parent = new int[size];
		for (int i = 0; i < size; i++) {
			parent[i] = -1;
		}
	}
	~WQUPCUFSet() {
		delete[] parent;
	}
	int find(int i) {
		int j = i;
		while (parent[j] >= 0)j = parent[j];//找到根节点
		while (i != j) {//将寻找j路上看到的节点都指向根节点
			int temp = parent[i];
			parent[i] = j;//指向根节点
			i = temp;//继续将下一个节点指向根节点
		}
		return j;
	}
	bool isConnected(int p, int q) {
		if (parent != nullptr && size > 0 && p < size && q < size) {
			return find(p) == find(q);
		}
	}
	void  Union(int root1, int root2) {
		int r1, r2, temp;
		r1 = find(root1); r2 = find(root2);
		if (r1 != r2) {
			temp = parent[r1] + parent[r2];
			if (parent[r2] < parent[r1]) {
				parent[r1] = r2;
				parent[r2] = temp;
			}
			else {
				parent[r2] = r1;
				parent[r1] = temp;
			}
		}
	}
};