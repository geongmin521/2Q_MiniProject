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
//		bool bIsBase = std::is_base_of<GameObject, T>::value;  //확인용
//		assert(bIsBase == true);
//
//		//_Object // 이름을 확인하고선	
//		if (!PoolList.find(static_cast<GameObject>(_Object).gameObjectName)) // 오브젝트 이름과 같은 키가 없으면?
//		{
//			std::vector<GameObject*> Pool; // 오브젝트를 받을 수 있는 풀링을 만들고선 
//			Pool.push_back(_Object);       // 벡터에 오브젝트를 넣는다
//			PoolList.insert(static_cast<GameObject>(_Object).gameObjectName), Pool); // 맵에 오브젝트의 이름으로 키를 생성하여 백터를 집어 넣는다
//		}
//		else // 이름이 같은게 있으면 해당 벡터에 오브젝트를 넣는다.
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
//		else // 예외 처리
//		{
//			assert("There is no key for POP in pooling."); 
//		}
//	}
//
};

