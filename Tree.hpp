#pragma once
template<class E>
struct treenode
{
	int tail, head;//两顶点整数标号
	E key;//权值
	treenode() { tail = -1; head = -1; key = E(); }
};
template<class E>
class tree {
protected:
	treenode<E>* edgevalue;
	int maxSize, n;//容量和当前个数
	static const int defaultsize = 1000;
public:
	tree(int sz = defaultsize) :n(0), maxSize(sz) {
		edgevalue = new treenode<E>[sz];
	}
	bool insert(treenode<E>& item) {
		if (n > maxSize - 1)return false;
		edgevalue[n++] = item;
		return true;
	}
	~tree() {
		destroy();
	}
	void destroy() {
		delete[]edgevalue;
		maxSize = n = 0;
	}
	void clear() {
		size = 0;
	}
};