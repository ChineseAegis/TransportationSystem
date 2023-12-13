#pragma once
const int defaultSize = 1000;
template<class V>
class MinHeap
{
protected:
    V* heap;
    int maxSize;
    int currentSize;
    void SiftDown(int start, int m) {
        V temp = heap[start];
        int parent = start;
        int child = start * 2 + 1;
        while (child <= m)
        {
            if (child < m && heap[child] > heap[child + 1])//找孩子中最小的一个
                child++;
            if (temp > heap[child])
            {
                heap[parent] = heap[child];
                parent = child;
                child = parent * 2 + 1;//继续向下
            }
            else
                break;//已经比两孩子小，是最小堆
        }
        heap[parent] = temp;
    }
    void SiftUp(int start) {
        V temp = heap[start];
        int parent = (start - 1) / 2;//该节点的父节点
        int child = start;
        while (child > 0)
        {
            if (temp < heap[parent])
            {
                heap[child] = heap[parent];
                child = parent;
                parent = (child - 1) / 2;//继续向上
            }
            else
                break;//比父节点大，已经构建最小堆
        }
        heap[child] = temp;
    }
    void Resize(int newSize) {
        if (newSize <= maxSize) return;

        V* newHeap = new V[newSize];
        for (int i = 0; i < currentSize; i++) {
            newHeap[i] = heap[i];
        }

        delete[] heap;
        heap = newHeap;
        maxSize = newSize;
    }

public:
    MinHeap(int sz = defaultSize) {
        maxSize = sz;
        heap = new V[maxSize];
        currentSize = 0;
    }
    MinHeap(V arr[], int n) {  //从已知数组构建最小堆
        maxSize = (defaultSize<n)?n:defaultSize;
        heap = new V[maxSize];
        for (int i = 0; i < n; i++)
            heap[i] = arr[i];
        currentSize = n;
        int currentPos = (currentSize - 2) / 2;//最后一个非叶子节点
        while (currentPos >= 0)
        {
            SiftDown(currentPos, currentSize - 1);//从下往上下筛构建最小堆
            currentPos--;
        }
    }
    ~MinHeap() { delete[] heap; currentSize = maxSize = 0; }
    bool Insert(const V& v) {
        if (IsFull())
            Resize(2 * maxSize);
        heap[currentSize] = v;
        SiftUp(currentSize);
        currentSize++;
        return true;
    }
    bool RemoveMin(V& v) {//移出最小元素
        if (IsEmpty())
            return false;
        v = heap[0];
        heap[0] = heap[currentSize - 1];//用最后一个节点代替，然后下筛调整
        currentSize--;
        SiftDown(0, currentSize - 1);
        return true;
    }
    bool IsEmpty() { 
        if (currentSize == 0)return true;
        return false;
    }
    bool IsFull() {
        if (currentSize == maxSize) return true;
        return false;
    }
    void MakeEmpty() {
        currentSize = 0;
    }
};
