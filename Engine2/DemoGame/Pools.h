#pragma once
#include "SingletonBase.h"

class GameObject;
class Pools : public SingletonBase<Pools>
{
private:
	std::unordered_map <int, std::vector<GameObject*>> PoolList; 
public:
	Pools();
	~Pools();
	virtual void reset() override;
	void AddPool(GameObject* _Object);
	GameObject* PopPool(int id);

};



