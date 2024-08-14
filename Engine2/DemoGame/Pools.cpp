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
	_Object->SetActive(false);
	_Object->transform->SetRelativeLocation({ 4000, 4000 });
}

//타워는 0이시작
//적은 100이 시작
//총알의 아이디는 500부터 시작? 
//웨이브는 1000이시작 

GameObject* Pools::PopPool(int id)
{
	auto it = PoolList.find(id);

	if (it != PoolList.end()) 
	{
		
		GameObject* popObj = PoolList[id].back();
		PoolList[id].pop_back(); //꺼내줄때도 적이랑 타워같은거는 기본값으로 돌리고 보내줘야할텐데.. 
		popObj->SetActive(true);
		return popObj;
	}
	else 
	{
		//일단 무식하게 분리해볼까? 
		if(id< 100)
			return Factory().createObj<TowerBase>(DataManager::GetInstance().get()->getTowerData(id)).Get<TowerBase>();
		else if(id < 500)
			return Factory().createObj<EnemyBase>(DataManager::GetInstance().get()->getEnemyData(id)).Get<EnemyBase>();
		else if (id <= 512)
			return Factory().createObj<Arrow>(DataManager::GetInstance().get()->getTowerData(id- 500).Type, DataManager::GetInstance().get()->getTowerData(id - 500).ATK, DataManager::GetInstance().get()->getTowerData(id - 500).attackArea).Get<Arrow>();
		else if (id == 513)
			return Factory().createObj<Arrow>("HiddenArrow", DataManager::GetInstance().get()->getTowerData(12).ATK, DataManager::GetInstance().get()->getTowerData(12).attackArea).Get<Arrow>();
		else if (id == 2000)
			return Factory().createObj<Effect>().Get<Effect>();
	}
}


