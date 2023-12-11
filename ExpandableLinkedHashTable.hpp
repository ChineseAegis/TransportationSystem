#pragma once
#include"DbLinkedList.hpp"
#include"ExpandableArrayList.hpp"
#include <cmath>
#include <functional> 
template <class K, class E>
class ExpandableLinkedHashTable {
private:

    ExpandableArrayList<DbLinkedList<E>> _buckets;//Ͱ������
    int _bucket_size;//Ͱ��
    int _size;//װ�ؼ�¼�Ĺ�ģ��С
    double _max_load_factor;//װ�����ӵ����ֵ
    int hash(K key)const {
        
        std::hash<K> hash_function; // ����һ����ϣ��������
        int hash_value = hash_function(key); // ���ɹ�ϣֵ
        int id_bucket = hash_value % _bucket_size; // ����Ͱ������
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
            return num;  // ������������������������ֱ�ӷ���
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
    ExpandableLinkedHashTable():_bucket_size(16),_buckets(16) {
        _size = 0;
        _max_load_factor = 0.7;
    }
    /** ��Ͱ����initial_bucket_size�����װ��������0.7��*/
    ExpandableLinkedHashTable(int initialSize):_bucket_size(initialSize), _buckets(initialSize) {

        _size = 0;
        _max_load_factor = 0.7;
    }
    /** Ͱ����initial_bucket_size�����װ��������maxLoadFactor��*/
    ExpandableLinkedHashTable(int initialSize, double maxLoadFactor):_bucket_size(initialSize), _buckets(initialSize) {
 
        _size = 0;
        _max_load_factor = maxLoadFactor;
    }

    DbListNode<E>* findPos(const K& key, int& bucket) const {
        bucket = hash(key);
        DbLinkedList<E>& bucketList = _buckets[bucket];//�ҵ���Ӧ������
        for (DbListNode<E> *i = bucketList.head->rlink; i !=bucketList.head; )
        {
            if (key == i->data.key) {
                return i;
            }
            i = i->rlink;
        }
        
         bucket = -1;
         return 0;
        
    }

    bool Search(const K&) const {
        int bucket;
        return findPos(K, bucket) != nullptr;
    }
    // ��new_bucket_size��Ͱ�ؽ�hash��
    void  resizeTable() {
        int new_bucket_size =findClosestPrime( _bucket_size * 2);
        //ExpandableArrayList<DbLinkedList<E>>* newBuckets = new ExpandableArrayList<DbLinkedList<E>>(new_bucket_size);
        ExpandableArrayList<DbLinkedList<E>> newBuckets(new_bucket_size);
        
        for (int i = 0; i < _bucket_size; i++) {//����ÿ��Ͱ
            DbLinkedList<E>& linkedList = _buckets[i];
            DbListNode<E>* current = linkedList.head->rlink;//ÿ���������׽��

            while (current != linkedList.head) {
                int newBucket;
                newBucket = hash(current->data.key);//����ɢ��
                newBuckets[newBucket].Insert(current->data);
                current = current->rlink;
            }
        }
        _buckets = newBuckets;
        //delete[] _buckets;
        //_buckets = newBuckets;
        _bucket_size = new_bucket_size;
    }
    bool Insert(const E& e) {
        int bucket = hash(e.key);
        DbLinkedList<E>& bucketLink = _buckets[bucket];
        if (findPos(e.key, bucket)) {//��ɾ���ٲ���
            bucketLink.Remove(e);
        }
        bucketLink.Insert(e);
        _size++;
        double loadFactor = _size / _bucket_size;//�ж��Ƿ�����
        if (loadFactor > _max_load_factor) {
            resizeTable();
        }
        return true;
    }
    int Remove(const K&key, E& e) {
        int bucket;
        DbListNode<E>* node = findPos(key, bucket);

        if (node != nullptr) {
            e = node->data;
            DbLinkedList<E>& linkedList = _buckets[bucket];
            for (DbListNode<E>* i = linkedList.head->rlink; i != linkedList.head; )
            {
                if (key == i->data.key) {
                    i->llink->rlink = i->rlink;
                    i->rlink->llink = i->llink;
                    delete i;
                    linkedList.size--;
                }
                i = i->rlink;
            }
            _size--;
            return 1;
        }

        return 0;
    }
    void Clear() {
        for (int i = 0; i < _size; i++) {
            DbLinkedList<E> &bucketlink = _buckets[i];
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