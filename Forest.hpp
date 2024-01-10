#pragma once
#include "HashMap.hpp"
#include "ExpandableArrayList.hpp"
#include <stdexcept>
#include <iostream>
template<class Weight>
struct ForestNode {
    int key;           // �ڵ��ֵ
    int parent;      // ���ڵ������������Ǹ��ڵ���Ϊ -1 �����������
    Weight weight;//�븸����Ȩ��
    ForestNode(int key, int parent,int weight) : key(key), parent(parent),weight(weight) {}
    ForestNode() : key(int()), parent(-1) ,weight(std::numeric_limits<Weight>::max()) {}
    bool operator<( const ForestNode& y) {
        return this->weight < y.weight;
    }
    bool operator>( const ForestNode& y) {
        return this->weight > y.weight;
    }
};
template<class Object,class Weight>
class Forest {
protected:
    ExpandableArrayList<ForestNode<Weight>> nodes;
    int n;  // ��ǰ�ڵ����
    int maxSize;
    HashMap<Object, int> tointMap;
    HashMap<int, Object> toObjectMap;

public:
    Forest(int Size = 1000) : n(0), maxSize(Size), nodes(Size) {}

    bool insert(Object value, Object parent, Weight weight) {
        if (n >= maxSize) return false;
     /*   if (!tointMap.containsKey(parent)) {
            throw std::runtime_error("����㲻����");
        }*/
        /*if (tointMap.containsKey(value)) {
            throw std::runtime_error("����Ѵ���");
        }*/
        int parenttoint=0; int n0; int num=0 ;
        if (tointMap.containsKey(parent)) {
            parenttoint = tointMap.getValue(parent);
            num = n; n++;
        }
        else if(!tointMap.containsKey(parent)&& !tointMap.containsKey(value)) {
            parenttoint = n;
            num = n + 1; n += 2;
        }
        
        nodes.add(ForestNode<Weight>(num, parenttoint,weight));
        tointMap.Insert(std::make_pair(value, num));
        tointMap.Insert(std::make_pair(parent, parenttoint));
        toObjectMap.Insert(std::make_pair(num, value));
        toObjectMap.Insert(std::make_pair(parenttoint, parent));
        //n++;
        return true;
    }

    bool insert(Object value) {
        if (n >= maxSize) return false;
        if (tointMap.containsKey(value)) {
            throw std::runtime_error("����Ѵ���");
        }
        int num = n;
        nodes.add(ForestNode<Weight>(num, -1, std::numeric_limits<Weight>::max())); // -1 ��ʾ����һ������
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
        Object value = toObjectMap.getValue(nodes[nodeIndex].key);
        if (nodes[nodeIndex].parent >= 0) {
            Object parentValue = toObjectMap.getValue(nodes[nodeIndex].parent);
            Weight weight = nodes[nodeIndex].weight;
            std::cout << value << " (Parent: " << parentValue << ", Weight: " << weight << ")" << std::endl;
        }
        else {
            std::cout << value << " (Root)" << std::endl;
        }

        for (int i = 0; i < n; ++i) {
            if (nodes[i].parent == nodeIndex) {
                printTreeFromRoot(i, level + 1);
            }
        }
    }

    void printWholeForest() {
        for (int i = 0; i < n; ++i) {
            if (nodes[i].parent == -1) {  // ��ӡÿ�����ĸ��ڵ�
                printTreeFromRoot(i);
            }
        }
    }

    int getCount() {
        return n;
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
    Object& operator[](int i) {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range");
        }
        return toObjectMap.getValue(nodes[i]);
    }
};
