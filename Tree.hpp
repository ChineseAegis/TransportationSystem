#pragma once
#include"HashMap.hpp"
//#include"Deque.hpp"
#include"ExpandableArrayList.hpp"
struct TreeNode {
	int key;           // �ڵ��ֵ
	int parent;      // ���ڵ������������Ǹ��ڵ���Ϊ -1 �����������
    TreeNode(int key, int parent) : key(key), parent(parent) {}
	TreeNode() : key(int()), parent(-1) {}
};

template<class E>
class Tree {
protected:
    ExpandableArrayList<TreeNode> nodes;
    int n;  // ��ǰ�ڵ����
    int maxSize;
    //ExpandableArrayList<int> index; // �ڵ��������е�����
    HashMap<E, int> tointMap;
    HashMap<int, E> toObjectMap;

public:
    Tree(int Size = 1000) : n(0),maxSize(Size), nodes(Size){
        //for (int i = 0; i < sz; i++)index.add(-1);
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
        //int parentindex = index[parenttoint];
        int num;
        /*if (intQueue.isEmpty())
        {*/
            num = n;
       // }
       /* else
        {
            num = intQueue.front();
            intQueue.pop();
        }*/
        nodes.add(TreeNode(num, parenttoint));
        //index.add(n);
        tointMap.Insert(std::make_pair(value, num));
        toObjectMap.Insert(std::make_pair(num, value));
        n++;
        return true;
    }
    bool insert(E value) {
        if (n >= maxSize) return false;
        if (tointMap.containsKey(value)) {
            throw std::runtime_error("����Ѵ���");
        }
        int num;
       /* if (intQueue.isEmpty())
        {*/
            num = n;
        /*}
        else
        {
            num = intQueue.front();
            intQueue.pop();
        }*/
        nodes.add(TreeNode(num, -1));
       // index.add(n);
        tointMap.Insert(std::make_pair(value, num));
        toObjectMap.Insert(std::make_pair(num, value));
        n++;
        return true;
    }
    void printTreeFromRoot(int nodeIndex = 0, int level = 0)  {
        if (nodeIndex < 0 || nodeIndex >= n) {
            return;
        }

        for (int i = 0; i < level; ++i) {
            std::cout << "  ";  // ������ʾ�㼶
        }
        E value = toObjectMap.getValue(nodes[nodeIndex].key);
        std::cout << value << std::endl;

        for (int i = 0; i < n; ++i) {
            if (nodes[i].parent == nodeIndex) {
                printTreeFromRoot(i, level + 1);
            }
        }
    }

    void printWholeTree() {
        printTreeFromRoot();
    }

    int getcount() {
        return n;
    }
    ~Tree() {
        destroy();
    }

    void destroy() {
        nodes.Clear();
       //index.add();
        maxSize = n = 0;
    }

    void clear() {
        n = 0;
    }
};
