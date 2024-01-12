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

    ExpandableArrayList<DbLinkedList<Object>> _buckets;//Ͱ������
    int _bucket_size;//Ͱ��
    int _size;//װ�ؼ�¼�Ĺ�ģ��С
    double _max_load_factor;//װ�����ӵ����ֵ

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


    bool isPrime(int n) {//�ж��Ƿ�������
        if (n <= 1) {
            return false;
        }

        int sqrtN = static_cast<int>(sqrt(n));//��0������n֮��Ѱ��
        for (int i = 2; i <= sqrtN; i++) {
            if (n % i == 0) {
                return false;
            }
        }

        return true;
    }
    int findClosestPrime(int num) {//����2��Ͱ�����������
        if (isPrime(num)) {
            return num;  // �����������������������ֱ�ӷ���
        }

        // ��ǰ��������
        int smaller = num - 1;
        while (smaller > 1 && !isPrime(smaller)) {
            smaller--;
        }

        // ����������
        int larger = num + 1;
        while (!isPrime(larger)) {
            larger++;
        }

        // ���ؾ���Ͻ�������
        return (num - smaller <= larger - num) ? smaller : larger;
    }
public:
    /** Ͱ����16�����װ��������0.7��*/
    ExpandableLinkedHashTable():_bucket_size(16),_buckets(16,16) {
        _size = 0;
        _max_load_factor = 0.7;
    }
    /** ��Ͱ����initial_bucket_size�����װ��������0.7��*/
    ExpandableLinkedHashTable(int initialSize):_bucket_size(initialSize), _buckets(initialSize, initialSize) {

        _size = 0;
        _max_load_factor = 0.7;
    }
    /** Ͱ����initial_bucket_size�����װ��������maxLoadFactor��*/
    ExpandableLinkedHashTable(int initialSize, double maxLoadFactor):_bucket_size(initialSize), _buckets(initialSize, initialSize) {
 
        _size = 0;
        _max_load_factor = maxLoadFactor;
    }

    DbListNode<Object>* findPos(const K& key, int& bucket) const {
        bucket = hash(key);
        DbLinkedList<Object>& bucketList = _buckets[bucket];//�ҵ���Ӧ������
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
    // ��new_bucket_size��Ͱ�ؽ�hash��
    void  resizeTable() {
        int new_bucket_size =findClosestPrime( _bucket_size * 2);
        //ExpandableArrayList<DbLinkedList<E>>* newBuckets = new ExpandableArrayList<DbLinkedList<E>>(new_bucket_size);
        ExpandableArrayList<DbLinkedList<Object>> newBuckets(new_bucket_size, new_bucket_size);
        int old_bucket_size = _bucket_size;
        _bucket_size = new_bucket_size;
        for (int i = 0; i < old_bucket_size; i++) {//����ÿ��Ͱ
            DbLinkedList<Object>& linkedList = _buckets[i];
            DbListNode<Object>* current = linkedList.head->rlink;//ÿ��������׽��

            while (current != linkedList.head) {
                int newBucket;
                newBucket = hash(current->data.first);//����ɢ��
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
       //��ɾ���ٲ���
         Object x;
         Remove(e.first,x);
        
        bucketLink.Insert(e);
        _size++;
        double loadFactor = _size / _bucket_size;//�ж��Ƿ�����
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