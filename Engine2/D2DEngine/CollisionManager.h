#pragma once
#include "SingletonBase.h"
class Collider;
enum class CollisionLayer;

#define collisionManager CollisionManager::GetInstance().get()

class CollisionManager :public SingletonBase<CollisionManager>
{
private:	
	static CollisionManager* inst;
	std::vector<Collider*> remove;
	std::map<CollisionLayer, std::vector<Collider*>>  colliders; 
	std::set<std::pair<CollisionLayer, CollisionLayer>> collisonLayer; 
	void EraseCollider(Collider* col);
public:
	CollisionManager();
	~CollisionManager();
	virtual void reset() override;
	void CollisionCheck();
	void AddRemove(Collider* col);
	void pushCollider(Collider* col);
};

