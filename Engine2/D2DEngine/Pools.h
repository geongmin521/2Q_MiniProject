#pragma once
#include "SingletonBase.h"

class GameObject;
class Pools : public SingletonBase<Pools>
{
private:
	std::unordered_map <std::string, std::vector<GameObject*>> PoolList;
public:
	Pools() {};
	~Pools();
	void AddPool(GameObject* _Object);
	GameObject* PopPool(std::string _ObjectName);
};



