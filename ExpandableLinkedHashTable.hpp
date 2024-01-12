#pragma once
#include"DbLinkedList.hpp"
#include"ExpandableArrayList.hpp"
#include <cmath>
#include <functional> 


//struct PairHash {
//    size_t operator()(const std::pair<T1, T2>& p) const {
//        std::hash<T1> hash1;
//        std::hash<T2> hash2;
//        return hash1(p.first) ^ (hash2(p.second) << 1);  // Combine the hash values
//    }
//};
namespace std {
    template <class T1, class T2>
    struct hash<std::pair<T1, T2>> {
        size_t operator()(const std::pair<T1, T2>& p) const {
            std::hash<T1> hash1;
            std::hash<T2> hash2;
            return hash1(p.first) ^ (hash2(p.second) << 1);  // Combine the hash values
        }
    };
}




template <class K, class Object>
class ExpandableLinkedHashTable {
private:

    ExpandableArrayList<DbLinkedList<Object>> _buckets;//桶的数组
    int _bucket_size;//桶数
    int _size;//装载记录的规模大小
    double _max_load_factor;//装载因子的最大值

    //template <class T1, class T2>
    //int hash(const std::pair<K, K>& key) const {
    //    OrderedPairHash<K, K> h;
    //    size_t hashCode = h(key);
    //    int id_bucket = (0x7fffffff & hashCode) % _bucket_size;
    //    return id_bucket;
    //}
    int hash(const K& key)const {
        
        std::hash<K> h;
        size_t hashCode = h(key);
        int id_bucket = (0x7fffffff & hashCode) % _bucket_size;
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
    ExpandableLinkedHashTable():_bucket_size(16),_buckets(16,16) {
        _size = 0;
        _max_load_factor = 0.7;
    }
    /** 。桶数是initial_bucket_size，最大装载因子是0.7。*/
    ExpandableLinkedHashTable(int initialSize):_bucket_size(initialSize), _buckets(initialSize, initialSize) {

        _size = 0;
        _max_load_factor = 0.7;
    }
    /** 桶数是initial_bucket_size，最大装载因子是maxLoadFactor。*/
    ExpandableLinkedHashTable(int initialSize, double maxLoadFactor):_bucket_size(initialSize), _buckets(initialSize, initialSize) {
 
        _size = 0;
        _max_load_factor = maxLoadFactor;
    }

    DbListNode<Object>* findPos(const K& key, int& bucket) const {
        bucket = hash(key);
        DbLinkedList<Object>& bucketList = _buckets[bucket];//找到对应链表行
        for (DbListNode<Object> *i = bucketList.head->rlink; i !=bucketList.head; )
        {
            if (key == i->data.first) {
                return i;
            }
            i = i->rlink;
        }
        
         bucket = -1;
         return nullptr;
        
    }

    DbListNode<Object>* get_front()
    {
        for(int i=0;i< _bucket_size;i++)
        {
        DbLinkedList<Object>& bucketList = _buckets[i];
        DbListNode<Object>* n = bucketList.head->rlink;
        if(n!=bucketList.head)
        {
             return n;
        }
        }
        return nullptr;
    }

    bool Search(const K&key) const {
        int bucket;
        return findPos(key, bucket) != nullptr;
    }
    // 用new_bucket_size个桶重建hash表
    void  resizeTable() {
        int new_bucket_size =findClosestPrime( _bucket_size * 2);
        //ExpandableArrayList<DbLinkedList<E>>* newBuckets = new ExpandableArrayList<DbLinkedList<E>>(new_bucket_size);
        ExpandableArrayList<DbLinkedList<Object>> newBuckets(new_bucket_size, new_bucket_size);
        int old_bucket_size = _bucket_size;
        _bucket_size = new_bucket_size;
        for (int i = 0; i < old_bucket_size; i++) {//遍历每个桶
            DbLinkedList<Object>& linkedList = _buckets[i];
            DbListNode<Object>* current = linkedList.head->rlink;//每个链表的首结点

            while (current != linkedList.head) {
                int newBucket;
                newBucket = hash(current->data.first);//重新散列
                newBuckets[newBucket].Insert(current->data);
                current = current->rlink;
            }
        }
        _buckets = std::move(newBuckets);
        //delete[] _buckets;
        //_buckets = newBuckets;
        
    }
    bool Insert(const Object& e) {
        int bucket = hash(e.first);
        DbLinkedList<Object>& bucketLink = _buckets[bucket];
       //先删除再插入
         Object x;
         Remove(e.first,x);
        
        bucketLink.Insert(e);
        _size++;
        double loadFactor = _size / _bucket_size;//判断是否扩容
        if (loadFactor >= _max_load_factor) {
            resizeTable();
        }
        return true;
    }
    int Remove(const K&key, Object& e) {
        int bucket;
        DbListNode<Object>* node = findPos(key, bucket);

        if (node != nullptr) {
            e = node->data;
            DbLinkedList<Object>& linkedList = _buckets[bucket];
            //for (DbListNode<E>* i = linkedList.head->rlink; i != linkedList.head; )
            //{

                    node->llink->rlink = node->rlink;
                    node->rlink->llink = node->llink;
                    delete node;
                    linkedList.size--;
 
            //    }
            //    i = i->rlink;
            //}
            _size--;
            return 1;
        }

        return 0;
    }
    void Clear() {
        for (int i = 0; i < _bucket_size; i++) {
            DbLinkedList<Object> &bucketlink = _buckets[i];
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
        //if (_buckets != nullptr) {
        //    delete[]_buckets;
        //    _buckets = nullptr;
        //}
    }
};