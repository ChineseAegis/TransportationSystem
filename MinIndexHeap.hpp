#pragma once
const int defaultSize = 1000;
template<class E>
class MinIndexHeap {
private:
    E* data;        // 存放数据的数组
    int* indexes;   // 堆位置处的元素在数组中的实际位置
    int* reverse;   // 数组中元素在堆或者indexes中的位置
    int capacity;   // 堆的容量
    int size;       // 堆的当前大小

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
    void shiftUp(int k) {
        while (k > 0 && data[indexes[(k - 1) / 2]] > data[indexes[k]]) {
            std::swap(indexes[(k - 1) / 2], indexes[k]);
            reverse[indexes[(k - 1) / 2]] = (k - 1) / 2;
            reverse[indexes[k]] = k;
            k = (k - 1) / 2;
        }
    }

    void shiftDown(int k) {
        while (2 * k + 1 < size) {
            int j = 2 * k + 1; // 左子节点
            if (j + 1 < size && data[indexes[j + 1]] < data[indexes[j]]) {
                j++; // 有右子节点且右子节点更小
            }
            if (data[indexes[k]] <= data[indexes[j]]) break;
            std::swap(indexes[k], indexes[j]);
            reverse[indexes[k]] = k;
            reverse[indexes[j]] = j;
            k = j;
        }
    }
    void resize(int newCapacity) {
        E* newData = new E[newCapacity];
        int* newIndexes = new int[newCapacity];
        int* newReverse = new int[newCapacity];

        for (int i = 0; i <size; i++) {
            newData[i] = data[i];
            newIndexes[i] = indexes[i];
            newReverse[i] = reverse[i];
        }

        delete[] data;
        delete[] indexes;
        delete[] reverse;

        data = newData;
        indexes = newIndexes;
        reverse = newReverse;
        capacity = newCapacity;
    }
public:
    MinIndexHeap(E arr[], int n) : capacity(n), size(n) {
        data = new E[n];
        indexes = new int[n];
        reverse = new int[n];

        for (int i = 0; i < n; i++) {
            data[i] = arr[i];
            indexes[i] = i;
            reverse[i] = i;
        }

        // 从最后一个非叶子节点开始向下进行堆化
        for (int i = (size - 2) / 2; i >= 0; i--) {
            shiftDown(i);
        }
    }
    MinIndexHeap(int capacity= defaultSize) : capacity(capacity), size(0) {
        data = new E[capacity ];
        indexes = new int[capacity ];
        reverse = new int[capacity ];

        for (int i = 0; i < capacity; i++) {
            reverse[i] = -1;
        }
    }

    bool Insert(const E& x) {
        if (size >= capacity) resize(2 * capacity);

        data[size++] = x;
        indexes[size-1] = size-1;
        reverse[size-1] = size-1;
        shiftUp(size-1);
        return true;
    }

    bool removeMin(E& x) {
        if (size == 0) return false;

        x = data[indexes[0]];
        std::swap(indexes[0], indexes[size-1]);
        reverse[indexes[0]] = 0;
        reverse[indexes[size-1]] = -1;
        size--;
        shiftDown(0);
        return true;
    }

    bool Modify(int i, const E& x) {
        if (i < 0 || i >= size) return false;

        data[i] = x;
        int j = reverse[i];
        shiftUp(j);
        shiftDown(j);
        return true;
    }

    ~MinIndexHeap() {
        delete[] data;
        delete[] indexes;
        delete[] reverse;
    }
};