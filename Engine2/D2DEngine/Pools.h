#pragma once
#include "SingletonBase.h"
//#include "GameObject.h"



class Pools : public SingletonBase<Pools>
{
//private:
//	std::unordered_map <std::string, std::vector<GameObject*>> PoolList;
//
//public:
//	Pools() {};
//	~Pools();
//
//	template<typename T>
//	void AddPool(T _Object)
//	{
//		bool bIsBase = std::is_base_of<GameObject, T>::value;  //Ȯ�ο�
//		assert(bIsBase == true);
//
//		//_Object // �̸��� Ȯ���ϰ�	
//		if (!PoolList.find(static_cast<GameObject>(_Object).gameObjectName)) // ������Ʈ �̸��� ���� Ű�� ������?
//		{
//			std::vector<GameObject*> Pool; // ������Ʈ�� ���� �� �ִ� Ǯ���� ����� 
//			Pool.push_back(_Object);       // ���Ϳ� ������Ʈ�� �ִ´�
//			PoolList.insert(static_cast<GameObject>(_Object).gameObjectName), Pool); // �ʿ� ������Ʈ�� �̸����� Ű�� �����Ͽ� ���͸� ���� �ִ´�
//		}
//		else // �̸��� ������ ������ �ش� ���Ϳ� ������Ʈ�� �ִ´�.
//		{
//			PoolList.find(static_cast<GameObject>(_Object).gameObjectName).push_back(_Object);
//		}
//	}
//
//	template<typename T>
//	T PopPool(std::string _ObjectName)
//	{
//		auto it = PoolList.find(_ObjectName);
//
//		if (it != PoolList.end())
//		{
//			return PoolList.find(_ObjectName)->second.pop_back();
//		}
//		else // ���� ó��
//		{
//			assert("There is no key for POP in pooling."); 
//		}
//	}
//
};

