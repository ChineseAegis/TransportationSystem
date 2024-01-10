#pragma once
#pragma once
#include "HashMap.hpp"
#include "ExpandableArrayList.hpp"
#include <stdexcept>
#include <iostream>
template<class Weight>
struct ForestNode {
    int key;           // 节点的值
    int parent;      // 父节点的索引，如果是根节点则为 -1 或自身的索引
    Weight Weight;//与父结点的权重
    ForestNode(int key, int parent, int weight) : key(key), parent(parent), Weight(weight) {}
    //ForestNode() : key(int()), parent(-1), Weight(0) {}
    bool operator<(const ForestNode& y) {
        return this->Weight < y.Weight;
    }
    bool operator>(const ForestNode& y) {
        return this->Weight > y.Weight;
    }
};
template<class Object,class Weight>
class Forest {
protected:
    ExpandableArrayList<ForestNode<Weight>> nodes;
    int n;  // 当前节点个数
    int maxSize;
    HashMap<Object, int> tointMap;
    HashMap<int, Object> toObjectMap;

public:
    Forest(int Size = 1000) : n(0), maxSize(Size), nodes(Size) {}

    bool insertEdge(Object value, Object parent, Weight weight ) {
        if (n >= maxSize) return false;
        if (!tointMap.containsKey(parent)) {
            throw std::runtime_error("父结点不存在");
        }
        if (tointMap.containsKey(value)) {
            throw std::runtime_error("结点已存在");
        }
        int parenttoint = tointMap.getValue(parent);
        int num = n;
        nodes.add(ForestNode(num, parenttoint, weight));
        tointMap.Insert(std::make_pair(value, num));
        toObjectMap.Insert(std::make_pair(num, value));
        n++;
        return true;
    }
    void printTreeFromRoot(int nodeIndex = 0, int level = 0) {
        if (nodeIndex < 0 || nodeIndex >= n) {
            return;
        }
        for (int i = 0; i < level; ++i) {
            std::cout << "  ";
        }
        E value = toObjectMap.getValue(nodes[nodeIndex].key);
        std::cout << value << std::endl;
        for (int i = 0; i < n; ++i) {
            if (nodes[i].parent == nodeIndex) {
                printTreeFromRoot(i, level + 1);
            }
        }
    }

    void printWholeForest() {
        for (int i = 0; i < n; ++i) {
            if (nodes[i].parent == -1) {  // 打印每棵树的根节点
                printTreeFromRoot(i);
            }
        }
    }

    ~Forest() {
        destroy();
    }

    void destroy() {
        nodes.Clear();
        maxSize = n = 0;
    }

    void clear() {
        n = 0;
    }

};
