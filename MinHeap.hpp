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
            if (child < m && heap[child] > heap[child + 1])//�Һ�������С��һ��
                child++;
            if (temp > heap[child])
            {
                heap[parent] = heap[child];
                parent = child;
                child = parent * 2 + 1;//��������
            }
            else
                break;//�Ѿ���������С������С��
        }
        heap[parent] = temp;
    }
    void SiftUp(int start) {
        V temp = heap[start];
        int parent = (start - 1) / 2;//�ýڵ�ĸ��ڵ�
        int child = start;
        while (child > 0)
        {
            if (temp < heap[parent])
            {
                heap[child] = heap[parent];
                child = parent;
                parent = (child - 1) / 2;//��������
            }
            else
                break;//�ȸ��ڵ���Ѿ�������С��
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
    MinHeap(V arr[], int n) {  //����֪���鹹����С��
        maxSize = (defaultSize<n)?n:defaultSize;
        heap = new V[maxSize];
        for (int i = 0; i < n; i++)
            heap[i] = arr[i];
        currentSize = n;
        int currentPos = (currentSize - 2) / 2;//���һ����Ҷ�ӽڵ�
        while (currentPos >= 0)
        {
            SiftDown(currentPos, currentSize - 1);//����������ɸ������С��
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
    bool RemoveMin(V& v) {//�Ƴ���СԪ��
        if (IsEmpty())
            return false;
        v = heap[0];
        heap[0] = heap[currentSize - 1];//�����һ���ڵ���棬Ȼ����ɸ����
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
