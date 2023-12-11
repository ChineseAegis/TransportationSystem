#pragma once
#include <iostream>
#include <stdexcept>

template <typename E>
class ExpandableArrayList {
private:
              // 指向动态分配数组的指针
    int capacity;      // 数组的容量
    int count;         // 数组中元素的实际数量
    E* array;
public:

    //公共接口
    //E& operator[](int i);
    //void resizeList();
    //void Clear();
    

    ExpandableArrayList(int initialCapacity = 10) : capacity(initialCapacity), count(0) {
        array = new E[capacity];
    }
    ExpandableArrayList(int initialCapacity,int initialCount) : capacity(initialCapacity), count(initialCount) {
        array = new E[capacity];
    }
    ~ExpandableArrayList() {
        delete[] array;
    }
    ExpandableArrayList& operator=(const ExpandableArrayList& other)
    {
        if (array != nullptr)
        {
            delete[]array;
            array = nullptr;
        }
        count = other.count;
        capacity = other.capacity;
        array = new E[capacity];
        for (int i = 0; i < count; i++)
        {
            array[i] = other.array[i];
        }
        return *this;
    }
    E& operator[](int i) {
        if (i < 0 || i >= count) {
            throw std::out_of_range("Index out of range");
        }
        return array[i];
    }
    E& operator[](int i) const {
        if (i < 0 || i >= count) {
            throw std::out_of_range("Index out of range");
        }
        return array[i];
    }

    void resizeList() {
        int newCapacity = capacity * 2;
        E* newArray = new E[newCapacity];
        for (int i = 0; i < count; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }
    void resizeList(int newCapacity) {
        E* newArray = new E[newCapacity];
        for (int i = 0; i < count; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }

    void Clear() {
        count = 0;
    }

    void add(const E& element) {
        if (count == capacity) {
            resizeList();
        }
        array[count++] = element;
    }

    int size() const {
        return count;
    }

    int getCapacity() const {
        return capacity;
    }
};