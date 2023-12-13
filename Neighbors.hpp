#pragma once
template<typename Object,typename Weight>
struct Neighbors
{
	Object* object = nullptr;
	Weight* weight = nullptr;
	int size;
	Neighbors(int num)
	{
		object = new Object[num];
		weight = new Weight[num];
		size = num;
	}
	Neighbors(const Neighbors& other)
	{
		size = other.size;
		object = new Object[size];
		weight = new Weight[size];
		for (int i = 0; i < size; i++)
		{
			object[i] = other.object[i];
			weight[i] = other.weight[i];
		}
	}
	Neighbors& operator=(const Neighbors& other)
	{
		if (object != nullptr)
		{
			delete[] object;
			object = nullptr;
		}
		if (weight != nullptr)
		{
			delete[] weight;
			weight = nullptr;
		}
		size = other.size;
		object = new Object[size];
		weight = new Weight[size];
		for (int i = 0; i < size; i++)
		{
			object[i] = other.object[i];
			weight[i] = other.weight[i];
		}
		return *this;
	}
	~Neighbors()
	{
		if (object != nullptr)
		{
			delete[] object;
			object = nullptr;
		}
		if (weight != nullptr)
		{
			delete[] weight;
			weight = nullptr;
		}
	}
};