#pragma once
#include"HashMap.hpp"
#include"Deque.hpp"
struct TreeNode {
	int key;           // �ڵ��ֵ
	int parent;      // ���ڵ������������Ǹ��ڵ���Ϊ -1 �����������
	TreeNode() : key(int()), parent(-1) {}
};

template<class E>
class Tree {
protected:
    TreeNode* nodes;
    int maxSize, n;  // �����͵�ǰ�ڵ����
    static const int defaultSize = 1000;
    HashMap<E,int > tointMap;
    ADeque<int> intQueue;
public:
    Tree(int sz = defaultSize) : n(0), maxSize(sz) {
        nodes = new TreeNode[sz];
    }

    bool insert( E value, E parent) {
        if (n >= maxSize) return false;
        if (!tointMap.containsKey(parent)) {
            throw std::runtime_error("����㲻����");
        }
        if (tointMap.containsKey(value)) {
            throw std::runtime_error("����Ѵ���");
        }
        int parenttoint = tointMap.getValue(parent);
        int num;
        if (intQueue.isEmpty())
        {
            num = n + 1;
        }
        else
        {
            num = intQueue.front();
            intQueue.pop();
        }
        nodes[n].key = num;
        nodes[n].parent = parenttoint;
        n++;
        return true;
    }

    ~Tree() {
        destroy();
    }

    void destroy() {
        delete[] nodes;
        maxSize = n = 0;
    }

    void clear() {
        n = 0;
    }
};
