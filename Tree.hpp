#pragma once
#include"HashMap.hpp"
//#include"Deque.hpp"
#include"ExpandableArrayList.hpp"
template<class Weight>
struct TreeNode {
	int key;           // 节点的值
	int parent;      // 父节点的索引，如果是根节点则为 -1 或自身的索引
    Weight weight;
    TreeNode(int key, int parent,Weight weight) : key(key), parent(parent),weight(weight) {}
    TreeNode() : key(int()), parent(-1),weight(std::numeric_limits<Weight>::max()) {}
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

    bool insert( Object value, Object parent, Weight weight) {
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
        nodes.add(TreeNode<Weight>(num, parenttoint,weight));
        //index.add(n);
        tointMap.Insert(std::make_pair(value, num));
        toObjectMap.Insert(std::make_pair(num, value));
        n++;
        return true;
    }
    bool insert(Object value) {
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
        nodes.add(TreeNode<Weight>(num, -1, std::numeric_limits<Weight>::max()));
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
            std::cout << "  ";  // 缩进表示层级
        }
        Object value = toObjectMap.getValue(nodes[nodeIndex].key);
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
    int findmdistance(Object city) {
        if (!tointMap.containsKey(city))return 0;
        int cityvalue = tointMap.getValue(city);
        int thisvalue = nodes[0];
        int mdis = 0;
        for (int i = 0; node[i]!=city; i++) {
            std::cout << toObjectMap.getValue(nodes[i]) << "->";
            mdis += nodes[i+1].weight;
        }
        std::cout << city << std::endl;
        return mdis;
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
    Object& operator[](int i) {
        if (i < 0 || i >= n) {
            throw std::out_of_range("Index out of range");
        }
        return toObjectMap.getValue( nodes[i]);
    }
};
