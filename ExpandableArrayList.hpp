#pragma once
#include <iostream>
#include <stdexcept>

template <typename Object>
class ExpandableArrayList {
private:
              // 指向动态分配数组的指针
    int capacity;      // 数组的容量
    int count;         // 数组中元素的实际数量
    Object* array;
public:

    //公共接口
    //E& operator[](int i);
    //void resizeList();
    //void Clear();
    

    ExpandableArrayList(int initialCapacity = 10) : capacity(initialCapacity), count(0) {
        array = new Object[capacity];
    }
    ExpandableArrayList(int initialCapacity,int initialCount) : capacity(initialCapacity), count(initialCount) {
        array = new Object[capacity];
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
        array = new Object[capacity];
        for (int i = 0; i < count; i++)
        {
            array[i] = other.array[i];
        }
        return *this;
    }
    ExpandableArrayList& operator=(ExpandableArrayList&& other)
    {
        count = other.count;
        capacity = other.capacity;
        other.capacity = 0;
        other.count = 0;
        if (array != nullptr)
        {
            delete[]array;
            array = nullptr;
        }
        array = other.array;
        other.array = nullptr;
        return *this;
    }
    Object& operator[](int i) {
        if (i < 0 || i >= count) {
            throw std::out_of_range("Index out of range");
        }
        return array[i];
    }
    Object& operator[](int i) const {
        if (i < 0 || i >= count) {
            throw std::out_of_range("Index out of range");
        }
        return array[i];
    }
    void resize(int count) {
        while (count > this->capacity)resizeList();
        this->count = count;
    }
    void resizeList() {
        int newCapacity = capacity * 2;
        Object* newArray = new Object[newCapacity];
        for (int i = 0; i < count; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        capacity = newCapacity;
    }
    void resizeList(int newCapacity) {
        Object* newArray = new Object[newCapacity];
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

    void add(const Object& element) {
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