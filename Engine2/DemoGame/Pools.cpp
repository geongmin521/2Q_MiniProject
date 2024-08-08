#include "pch.h"
#include "Pools.h"
#include "Factory.h"
#include "GameObject.h" 

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
}

//Ÿ���� 0�̽���
//���� 100�� ����
//���̺�� 1000�̽��� 

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


