#pragma once
#include"DbLinkedList.hpp"
#include"ExpandableArrayList.hpp"
#include <cmath>
template <class K, class E,class V>
class ExpandableLinkedHashTable {
private:

    ExpandableArrayList<DbLinkedList<E>>* _buckets;//桶的数组
    int _bucket_size;//桶数
    int _size;//装载记录的规模大小
    double _max_load_factor;//装载因子的最大值
    int hash(K* key)const {
        if (key == NULL) {
            return 0;
        }
        int id_bucket = key % _bucket_size;

        return id_bucket;
    }

    bool isPrime(int n) {//判断是否是素数
        if (n <= 1) {
            return false;
        }

        int sqrtN = static_cast<int>(sqrt(n));//在0到根号n之间寻找
        for (int i = 2; i <= sqrtN; i++) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }
    int findClosestPrime(int num) {//找离2倍桶数最近的素数
        if (isPrime(num)) {
            return num;  // 如果输入的数本身就是素数，直接返回
        }

        // 向前查找素数
        int smaller = num - 1;
        while (smaller > 1 && !isPrime(smaller)) {
            smaller--;
        }

        // 向后查找素数
        int larger = num + 1;
        while (!isPrime(larger)) {
            larger++;
        }

        // 返回距离较近的素数
        return (num - smaller <= larger - num) ? smaller : larger;
    }
public:
    /** 桶数是16，最大装载因子是0.7。*/
    ExpandableLinkedHashTable() {
        _size = 0;
        _bucket_size = 16;
        _max_load_factor = 0.7;
        _buckets = new ExpandableArrayList<DbLinkedList<E>>[_bucket_size];
    }
    /** 。桶数是initial_bucket_size，最大装载因子是0.7。*/
    ExpandableLinkedHashTable(int initialSize) {

        _size = 0;
        _bucket_size = initialSize;
        _max_load_factor = 0.7;
        _buckets = new ExpandableArrayList<DbLinkedList<E>>[_bucket_size];
    }
    /** 桶数是initial_bucket_size，最大装载因子是maxLoadFactor。*/
    ExpandableLinkedHashTable(int initialSize, double maxLoadFactor) {
 
        _size = 0;
        _bucket_size = initialSize;
        _max_load_factor = maxLoadFactor;
        _buckets = new ExpandableArrayList<DbLinkedList<E>>[_bucket_size];
    }

    DbListNode<E>* findPos(const K& key, int& bucket) const {
        bucket = hash(key);
        DbLinkedList<E>& bucketList = _buckets[bucket];//找到对应链表行
        DbListNode<E> node = bucketList.Search(key);
        if (!node) {
            bucket = -1;
            return 0;
        }
        return node;
    }

    bool Search(const K&) const {
        int bucket;
        return findPos(K, bucket) != nullptr;
    }
    // 用new_bucket_size个桶重建hash表
    void  resizeTable() {
        int new_bucket_size =findClosestPrime( _bucket_size * 2);
        ExpandableArrayList<DbLinkedList<E>>* newBuckets = new ExpandableArrayList<DbLinkedList<E>>[new_bucket_size];

        for (int i = 0; i < _bucket_size; i++) {//遍历每个桶
            DbLinkedList<E>& linkedList = _buckets[i];
            DbListNode<E>* current = linkedList.head->rlink;//每个链表的首结点

            while (current != linkedList.head) {
                int newBucket;
                newBucket = hash(current->data.key);//重新散列
                newBuckets[newBucket].Insert(current->data);
                current = current->rlink;
            }
        }
        delete[] _buckets;
        _buckets = newBuckets;
        _bucket_size = new_bucket_size;
    }
    bool Insert(const E& e) {
        int bucket = hash(E.key);
        DbLinkedList<E>& bucketLink = _buckets[bucket];
        if (findPos(e.key, bucket)) {//先删除再插入
            bucketLink.Remove(E);
        }
        bucketLink.Insert(e);
        _size++;
        double loadFactor = _size / _bucket_size;//判断是否扩容
        if (loadFactor > _max_load_factor) {
            resizeTable();
        }
        return true;
    }
    int Remove(const K&key, E& e) {
        int bucket;
        DbListNode<E>* node = findPos(key, bucket);

        if (node != nullptr) {
            e = node->value;
            DbLinkedList<E>& linkedList = _buckets[bucket];
            linkedList.Remove(key);
            _size--;
            return 1;
        }

        return 0;
    }
    void Clear() {
        for (int i = 0; i < _size; i++) {
            DbLinkedList<E> bucketlink = _buckets[i];
            bucketlink.Clear();
        }
        _size = 0;
    }
    int getCapcity() const {
        return _size;
    }
    int getSize() const {
        return _bucket_size;
    }
    int getBucket(const K& k) const {
        int bucket = hash(k);
        return bucket;
    }
    int getBucketSize(int i)const {
        return _buckets[i].size;
    }
    ~ExpandableLinkedHashTable() {
        Clear();
        if (_buckets != nullptr) {
            delete[]_buckets;
            _buckets = nullptr;
        }
    }
};