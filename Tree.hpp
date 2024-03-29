#pragma once
#include"HashMap.hpp"
//#include"Deque.hpp"
#include"ExpandableArrayList.hpp"
template<class Weight>
struct TreeNode {
	int key;           // 节点的值
	int parent;      // 父节点的索引，如果是根节点则为 -1 或自身的索引
    Weight weight;
    Weight distance;
    TreeNode(int key, int parent,Weight weight,Weight Distance=0) : key(key), parent(parent),weight(weight) ,distance(Distance) {}
    TreeNode() : key(int()), parent(-1),weight(std::numeric_limits<Weight>::max()),distance(0) {}
};

template<class Object,class Weight>
class Tree {
protected:
    ExpandableArrayList<TreeNode<Weight>> nodes;
    int n;  // 当前节点个数
    int maxSize;
    //ExpandableArrayList<int> index; // 节点在数组中的索引
    HashMap<Object, int> tointMap;
    HashMap<int, Object> toObjectMap;

public:
    Tree(int Size = 1000) : n(0),maxSize(Size), nodes(Size){
        //for (int i = 0; i < sz; i++)index.add(-1);
    }

    bool insert( Object value, Object parent, Weight weight,Weight distance=0) {
        if (n >= maxSize) return false;
        if (!tointMap.containsKey(parent)) {
            throw std::runtime_error("父结点不存在");
        }
        if (tointMap.containsKey(value)) {
            throw std::runtime_error("结点已存在");
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
        nodes.add(TreeNode<Weight>(num, parenttoint,weight,distance));
        //index.add(n);
        tointMap.Insert(std::make_pair(value, num));
        toObjectMap.Insert(std::make_pair(num, value));
        n++;
        return true;
    }
    bool insert(Object value,Weight distance=0) {
        if (n >= maxSize) return false;
        if (tointMap.containsKey(value)) {
            throw std::runtime_error("结点已存在");
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
        nodes.add(TreeNode<Weight>(num, -1, std::numeric_limits<Weight>::max(), distance));
       // index.add(n);
        tointMap.Insert(std::make_pair(value, num));
        toObjectMap.Insert(std::make_pair(num, value));
        n++;
        return true;
    }
    void printTreeFromRoot(int nodeIndex = 0)  {
        if (nodeIndex < 0 || nodeIndex >= n) {
            return;
        }
        if (nodeIndex != 0)
        {
            Object value = toObjectMap.getValue(nodes[nodeIndex].key);
            std::cout << value <<"("<< nodes[nodeIndex].weight<<")" << std::endl;
        }

        for (int i = 0; i < n; ++i) {
            if (nodes[i].parent == nodeIndex) {
                Object value = toObjectMap.getValue(nodes[i].parent);
                std::cout << value<<"->";
                printTreeFromRoot(i);
            }
        }
    }

    void printWholeTree() {
        printTreeFromRoot();
    }
    Weight findmdistance(Object city) {
        if (!tointMap.containsKey(city))return std::numeric_limits<Weight>::max();
        int cityvalue = tointMap.getValue(city);
        //int thisvalue = nodes[0].key;
        Weight mdis=0; //int i = 0;
      /*  for (i = 0; i < n; i++) {
            if (nodes[i].key == cityvalue)
            {
                break;
            }
        }*/
        int num = tointMap.getValue(city);
        while(nodes[num].parent!=-1) {

            std::cout << toObjectMap.getValue(nodes[num].key) << "<-";
            mdis += nodes[num].weight;
            num = nodes[num].parent;
        }
        std::cout << toObjectMap.getValue(nodes[num].key) << std::endl;
        return mdis;
    }
    Object getparent(Object city) {
        int node = tointMap.getValue(city);
        int parentnode = nodes[node].parent;
        return toObjectMap.getValue(parentnode);
    }
    Weight getweight(Object city) {
        return nodes[tointMap.getValue(city)].weight;
    }
    Weight getdistance(Object city)
    {
        return nodes[tointMap.getValue(city)].distance;
    }
    Weight get_index_distance(int i)
    {
        return nodes[i].distance;
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
    Object operator[](int i) {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range");
        }
        return toObjectMap.getValue( nodes[i].key);
    }
};
