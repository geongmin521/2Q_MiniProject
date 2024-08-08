#include "pch.h"
#include "Pools.h"
#include "Factory.h"
#include "GameObject.h" 

Pools::~Pools()
{
	for (auto it = PoolList.begin(); it != PoolList.end(); ++it)
	{
		it->second.clear(); // 게임 씬에서 오브젝트 처리를 하니깐 일단 원소만 비워넣는걸로
	}
}

void Pools::AddPool(GameObject* _Object) //이름으로 찾을일있을까? 외우지도 못하는데?
{
	if (PoolList.find(_Object->id) == PoolList.end()) // 찾지못하면 
	{
		std::vector<GameObject*> Pool; 
		Pool.push_back(_Object);       
		PoolList.insert({ _Object->id , Pool });  //만들어서 넣기
	}
	else // 이름이 같은게 있으면 해당 벡터에 오브젝트를 넣는다.
	{
		PoolList[_Object->id].push_back(_Object);
	}
}

//타워는 0이시작
//적은 100이 시작
//웨이브는 1000이시작 

GameObject* Pools::PopPool(int id)
{
	auto it = PoolList.find(id);

	if (it != PoolList.end()) 
	{
		GameObject* popObj = PoolList[id].back();
		PoolList[id].pop_back();
		return popObj;
	}
	else 
	{
		return Fac->CreateGameObjectFromId(id);
	}
}


