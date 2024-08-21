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
#include "GameManager.h"

Pools::Pools()
{
	gameManager->Reset.push_back([this]() { reset(); });
}

Pools::~Pools()
{
	reset();
}

void Pools::reset()
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
	//_Object->transform->SetRelativeLocation({ 4000, 4000 });
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
			return Make(TowerBase)(dataManager->getTowerData(id)).Get<TowerBase>();
		else if(id < 500)
			return Make(EnemyBase)(dataManager->getEnemyData(id)).Get<EnemyBase>();
		else if (id <= 512)
			return Make(Arrow)(dataManager->getTowerData(id - 500).name, dataManager->getTowerData(id - 500).Type, dataManager->getTowerData(id - 500).ATK, dataManager->getTowerData(id - 500).attackArea, DataManager::GetInstance().get()->getTowerData(id - 500).knockBack).Get<Arrow>();
		else if (id == 513)
			return Make(Arrow)("HiddenArrow","HiddenArrow", dataManager->getTowerData(12).ATK, dataManager->getTowerData(12).attackArea, DataManager::GetInstance().get()->getTowerData(512).knockBack).Get<Arrow>();
		if(id == 601)
			return Make(Arrow)(dataManager->getEnemyData(id - 500).name, dataManager->getEnemyData(id - 500).Type, dataManager->getEnemyData(id - 500).ATK, dataManager->getEnemyData(id - 500).ATK, DataManager::GetInstance().get()->getTowerData(0).ATK).Get<Arrow>();
		if (id >2000 || id < 2100) 
			return Make(Effect)(id).Get<Effect>();
	}
}


