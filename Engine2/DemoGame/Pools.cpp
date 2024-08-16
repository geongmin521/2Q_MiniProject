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
	_Object->transform->SetRelativeLocation({ 4000, 4000 });
}

//Ÿ���� 0�̽���
//���� 100�� ����
//�Ѿ��� ���̵�� 500���� ����? 
//���̺�� 1000�̽��� 

GameObject* Pools::PopPool(int id) 
{
	if (PoolList[id].empty() == false) 
	{
		
		GameObject* popObj = PoolList[id].back();
		PoolList[id].pop_back();
		popObj->SetActive(true);
		return popObj;
	}
	else //���̵� ������ ���� �̽������ϱ�
	{
		if(id< 100)
			return Make(TowerBase)(dataManager->getTowerData(id)).Get<TowerBase>();
		else if(id < 500)
			return Make(EnemyBase)(dataManager->getEnemyData(id)).Get<EnemyBase>();
		else if (id <= 512)
			return Make(Arrow)(dataManager->getTowerData(id- 500).Type, dataManager->getTowerData(id - 500).ATK, dataManager->getTowerData(id - 500).attackArea).Get<Arrow>();
		else if (id == 513)
			return Make(Arrow)("HiddenArrow", dataManager->getTowerData(12).ATK, dataManager->getTowerData(12).attackArea).Get<Arrow>();
		else if (id == 2000)
			return Make(Effect)().Get<Effect>();
	}
}


