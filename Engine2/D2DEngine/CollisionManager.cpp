#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"

CollisionManager::CollisionManager()
{
	collisonLayer.insert(std::make_pair(CollisionLayer::Tower,CollisionLayer::Enemy));
	collisonLayer.insert(std::make_pair(CollisionLayer::Tower, CollisionLayer::Tower));
	collisonLayer.insert(std::make_pair(CollisionLayer::Tower,CollisionLayer::Bullet));
	collisonLayer.insert(std::make_pair(CollisionLayer::Enemy,CollisionLayer::Bullet));
}

CollisionManager::~CollisionManager()
{
	std::cout << "¼Ò¸ê";
}

void CollisionManager::CollisionCheck() 
{
	for (auto val : remove) 
		EraseCollider(val);
	remove.clear();
	for (auto val : collisonLayer)
	{
		for (int source = 0; source < colliders[val.first].size(); source++)  
		{
			for (int target = 0; target < colliders[val.second].size(); target++)
			{
				if (!colliders[val.first][source]->IsCollide(colliders[val.second][target]))
					continue;
				if (colliders[val.first][source]->owner == (colliders[val.second][target])->owner)
					continue;
				
				if(colliders[val.first][source]->GetCollisionType() == CollisionType::NoCollision ||
				   colliders[val.second][target]->GetCollisionType() == CollisionType::NoCollision)
					continue;

				if (colliders[val.first][source]->GetCollisionType() == CollisionType::Block &&
					colliders[val.second][target]->GetCollisionType() == CollisionType::Block)
				{
					colliders[val.first][source]->ProcessBlock(colliders[val.first][source],colliders[val.second][target]);  
					colliders[val.second][target]->ProcessBlock(colliders[val.second][target],colliders[val.first][source]);
				}
				else
				{
					colliders[val.first][source]->InsertCollideState(colliders[val.second][target]); 
					colliders[val.second][target]->InsertCollideState(colliders[val.first][source]); 
				}
			}
		}
	}

	for (auto cols : colliders)
	{
		for (int i = 0; i < cols.second.size(); i++)
		{
			cols.second[i]->ProcessOverlap(); 
		}
	}
}

void CollisionManager::AddRemove(Collider* col)
{
	remove.push_back(col);
}

void CollisionManager::EraseCollider(Collider* remove)
{
	CollisionLayer layer = remove->GetCollisionLayer();
	colliders[layer].erase(std::remove_if(colliders[layer].begin(), colliders[layer].end(),
		[remove](auto x) -> bool { return x == remove; }), colliders[layer].end());
}

void CollisionManager::pushCollider(Collider* col)
{
	colliders[col->GetCollisionLayer()].push_back(col); 
}
