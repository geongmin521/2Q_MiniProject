#include "pch.h"
#include "Pools.h"
#include "Factory.h"
#include "GameObject.h" 
#include "EnemyBase.h"
#include "Arrow.h"
#include "TowerBase.h"
#include "Transform.h"
#include "Effect.h"
#include "DataManager.h"

Pools::~Pools()
{
	for (auto it = PoolList.begin(); it != PoolList.end(); ++it)
	{
		it->second.clear(); 
	}
}

void Pools::AddPool(GameObject* _Object)
{

	if (PoolList.find(_Object->id) == PoolList.end()) 
	{
		std::vector<GameObject*> Pool; 
		Pool.push_back(_Object);       
		PoolList.insert({ _Object->id , Pool });  
	}
	else 
	{
		PoolList[_Object->id].push_back(_Object);
	}
	_Object->SetActive(false);
	_Object->transform->SetRelativeLocation({ 4000, 4000 });
}

//타워는 0이시작
//적은 100이 시작
//총알의 아이디는 500부터 시작? 
//웨이브는 1000이시작 

GameObject* Pools::PopPool(int id)
{
	if (PoolList[id].empty() == false) 
	{
		GameObject* popObj = PoolList[id].back();
		PoolList[id].pop_back();
		popObj->SetActive(true);
		return popObj;
	}
	else //아이디 관리에 대한 이슈정리하기
	{
		if(id< 100)
			return Factory().createObj<TowerBase>(DataManager::GetInstance().get()->getTowerData(id)).Get<TowerBase>();
		else if(id < 500)
			return Factory().createObj<EnemyBase>(DataManager::GetInstance().get()->getEnemyData(id)).Get<EnemyBase>();
		else if (id < 550)
			return Factory().createObj<Arrow>(0.3f, DataManager::GetInstance().get()->getTowerData(id- 500).Type, DataManager::GetInstance().get()->getTowerData(id - 500).ATK, DataManager::GetInstance().get()->getTowerData(id - 500).attackArea).Get<Arrow>();
		else if (id == 2000)
			return Factory().createObj<Effect>().Get<Effect>();
	}
}


