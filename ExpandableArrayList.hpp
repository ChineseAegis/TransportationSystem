#include <iostream>
#include <stdexcept>

template <typename E>
class ExpandableArrayList {
private:
    E* array;          // ָ��̬���������ָ��
    int capacity;      // ���������
    int count;         // ������Ԫ�ص�ʵ������

public:
    //�����ӿ�
    //E& operator[](int i);
    //void resizeList();
    //void Clear();
    

    ExpandableArrayList(int initialCapacity = 10) : capacity(initialCapacity), count(0) {
        array = new E[capacity];
    }

    ~ExpandableArrayList() {
        delete[] array;
    }

    E& operator[](int i) {
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