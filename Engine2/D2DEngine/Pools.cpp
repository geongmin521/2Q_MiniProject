#include "pch.h"
#include "Pools.h"
#include "GameObject.h"

Pools::~Pools()
{
	for (auto it = PoolList.begin(); it != PoolList.end(); ++it)
	{
		it->second.clear(); // 게임 씬에서 오브젝트 처리를 하니깐 일단 원소만 비워넣는걸로
	}
}

void Pools::AddPool(GameObject* _Object) 
{
	if (PoolList.find(_Object->name) == PoolList.end()) // 찾지못하면 
	{
		std::vector<GameObject*> Pool; 
		Pool.push_back(_Object);       
		PoolList.insert({ _Object->name , Pool });  //만들어서 넣기
	}
	else // 이름이 같은게 있으면 해당 벡터에 오브젝트를 넣는다.
	{
		PoolList[_Object->name].push_back(_Object);
	}
}


GameObject* Pools::PopPool(std::string _ObjectName) //오타 못내게 enum으로 만들고싶은데.. 
{
	auto it = PoolList.find(_ObjectName);

	if (it != PoolList.end()) //어떻게 해야하지? 이름으로 찾는게 가독성은 좋을텐데.. 아디랑 이름이랑 편하게 수정할수있는 방법이... 
	{
		GameObject* popObj = PoolList[_ObjectName].back();
		PoolList[_ObjectName].pop_back();
		return popObj;
	}
	else // 예외 처리
	{
		//만들어서 넘겨주기.. 
		assert("There is no key for POP in pooling.");
	}
}