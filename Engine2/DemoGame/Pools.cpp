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
		it->second.clear(); // ���� ������ ������Ʈ ó���� �ϴϱ� �ϴ� ���Ҹ� ����ִ°ɷ�
	}
}

void Pools::AddPool(GameObject* _Object) //�̸����� ã����������? �ܿ����� ���ϴµ�?
{

	if (PoolList.find(_Object->id) == PoolList.end()) // ã�����ϸ� 
	{
		std::vector<GameObject*> Pool; 
		Pool.push_back(_Object);       
		PoolList.insert({ _Object->id , Pool });  //���� �ֱ�
	}
	else // �̸��� ������ ������ �ش� ���Ϳ� ������Ʈ�� �ִ´�.
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
	auto it = PoolList.find(id);

	if (it != PoolList.end()) 
	{
		
		GameObject* popObj = PoolList[id].back();
		PoolList[id].pop_back(); //�����ٶ��� ���̶� Ÿ�������Ŵ� �⺻������ ������ ����������ٵ�.. 
		popObj->SetActive(true);
		return popObj;
	}
	else 
	{
		//�ϴ� �����ϰ� �и��غ���? 
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


