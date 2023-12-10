#pragma once
#include"ExpandableLinkedHashTable.hpp"
#include"DbListNode.hpp"
#include"DbLinkedList.hpp"
#include<set>
#include <utility>
template<typename K,typename V>
class HashMap
{
public:
	int BucketSize;
	int MaxLoadFactor;
	int Default_BucketSize=16;
	int Default_MaxLoadFactor=0.7;
	std::set<K> s;
	struct Element
	{
		K key;
		V value;
	};
	ExpandableLinkedHashTable<K, Element>* table = nullptr;
	HashMap()
	{
		BucketSize = Default_BucketSize;
		MaxLoadFactor = Default_MaxLoadFactor;
		table = new ExpandableLinkedHashTable<K, Element>();
	}
	HashMap(int initialSize)
	{
		BucketSize = initialSize;
		MaxLoadFactor = Default_MaxLoadFactor;
		table = new ExpandableLinkedHashTable<K, Element>(initialSize);
	}
	HashMap(int initialSize, double MaxLoadFactor)
	{
		BucketSize = initialSize;
		this->MaxLoadFactor = MaxLoadFactor;
		table = new ExpandableLinkedHashTable<K, Element>(initialSize,this->MaxLoadFactor);
	}
	~HashMap()
	{
		table->Clear();
		delete table;
		table = nullptr;
	}

	V& getValue(const K& key)
	{
		int bucket;
		V v;
		DbListNode<Element>* node = table->findPos(key, bucket);
		if (bucket != -1)
		{
			while (node != nullptr)
			{
				if (node->data.key == key)
				{
					return node->data.value;
				}
			}
			return v;
		}
		return v;
	}
	std::set<K> keySet()
	{
		
		return s;
	}
	bool containsKey(const K& key)
	{
		return s.find(key)!=s.end();
	}
	void Insert(std::pair<K, V> k_v)
	{
		Element e;
		e.key = k_v.first;
		e.value = k_v.second;
		table->Insert(e);
		s.insert(e.key);
	}
	V& Remove(const K& key)
	{
		Element e;
		if (table->Remove(key, e) != 0)
		{
			s.erase(key);
			return e.value;
		}
		return e.value;
	}
	V& Remove(const K& key, const V& val)
	{
		Element e;
		if (val==getValue(key))
		{
			table->Remove(key, e);
			s.erase(key);
			return e.value;
		}
		return e.value;
	}
	void Clear()
	{
		table->Clear();
		s.clear();
	}
	int getSize()
	{
		return table->getCapcity();
	}
	void resizeTable()
	{
		table->resizeTable();
	}
};