#include "pch.h"
#include "CollisionManager.h"
#include "Collider.h"

CollisionManager* CollisionManager::inst = nullptr;

CollisionManager::CollisionManager()
{
	collisonLayer.insert(std::make_pair(CollisionLayer::Tower,CollisionLayer::Enemy));
	collisonLayer.insert(std::make_pair(CollisionLayer::Tower,CollisionLayer::Bullet));
	collisonLayer.insert(std::make_pair(CollisionLayer::Enemy,CollisionLayer::Bullet));
}

CollisionManager::~CollisionManager()
{
}

CollisionManager* CollisionManager::GetInstance()
{
	if (inst == nullptr) {
		inst = new CollisionManager();
	}
	return inst;
}

void CollisionManager::CollisionCheck() //등록된 충돌레이어끼리만 검사하도록 해야하니까 레이어별로 콜라이더를 들고있어야지.. 
{
	for (auto val : collisonLayer)
	{
		for (int source = 0; source < colliders[val.first].size(); source++)  
		{
			for (int target = source; target < colliders[val.second].size(); target++)
			{
				
				if (colliders[val.first][source]->GetCollisionType() == CollisionType::Block &&
					colliders[val.second][target]->GetCollisionType() == CollisionType::Block)
				{
					colliders[val.first][source]->ProcessBlock(colliders[val.first][source],colliders[val.second][target]); //적들 ai에 의해 .. 트리거등들도.. 들어갈수있으니까.. 여기서 너무 높은 알고리즘을 사용하면안되는데.. 
					colliders[val.second][target]->ProcessBlock(colliders[val.second][target],colliders[val.first][source]);//적들의 탐색알고리즘은 그냥 콜라이더일테니까.. 여러개의 콜라이더를 지원할수있어야함. 
				}
				else
				{
					colliders[val.first][source]->InsertCollideState(colliders[val.second][target]); //충돌중인 콜라이더 목록에는
					colliders[val.second][target]->InsertCollideState(colliders[val.first][source]); //오버랩만 들어갈수있다.
				}
			}
		}
	}

	for (auto cols : colliders)
	{
		for (int i = 0; i < cols.second.size(); i++)
		{
			cols.second[i]->ProcessOverlap(); //모든 전처리후 중첩상태에 대한 처리를 돌려주기...
		}
	}
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
