#include "pch.h"
#include "Pools.h"
#include "GameObject.h"

Pools::~Pools()
{
	for (auto it = PoolList.begin(); it != PoolList.end(); ++it)
	{
		it->second.clear(); // ���� ������ ������Ʈ ó���� �ϴϱ� �ϴ� ���Ҹ� ����ִ°ɷ�
	}
}

void Pools::AddPool(GameObject* _Object) 
{
	if (PoolList.find(_Object->name) == PoolList.end()) // ã�����ϸ� 
	{
		std::vector<GameObject*> Pool; 
		Pool.push_back(_Object);       
		PoolList.insert({ _Object->name , Pool });  //���� �ֱ�
	}
	else // �̸��� ������ ������ �ش� ���Ϳ� ������Ʈ�� �ִ´�.
	{
		PoolList[_Object->name].push_back(_Object);
	}
}


GameObject* Pools::PopPool(std::string _ObjectName) //��Ÿ ������ enum���� ����������.. 
{
	auto it = PoolList.find(_ObjectName);

	if (it != PoolList.end()) //��� �ؾ�����? �̸����� ã�°� �������� �����ٵ�.. �Ƶ�� �̸��̶� ���ϰ� �����Ҽ��ִ� �����... 
	{
		GameObject* popObj = PoolList[_ObjectName].back();
		PoolList[_ObjectName].pop_back();
		return popObj;
	}
	else // ���� ó��
	{
		//���� �Ѱ��ֱ�.. 
		assert("There is no key for POP in pooling.");
	}
}