#include "pch.h"
#include "World.h"
#include "D2DRenderer.h"
#include "AABB.h"
#include "GameObject.h"
#include "Animation.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CollisionManager.h"


World::World()
{
	m_CullingBoundDefault = new AABB;
	m_CullingBoundDefault->SetExtent(WinSizeX /2, WinSizeY /2);
	m_CullingBoundDefault->SetCenter(0,0);
	SetCullingBound(m_CullingBoundDefault);	
}

World::~World()
{

}


void World::Update(float deltaTime)
{
	if (m_Remove.size() != 0)
		removeElements(m_GameObjects, m_Remove);
	for (auto& obj : m_GameObjects) 
	{
		if (!obj->isActive)
			continue;
		obj->Update(deltaTime);
	}
	
	CollisionManager::GetInstance()->CollisionCheck();
}

void World::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto& obj : m_GameObjects) 
	{		
		if (!obj->isActive)
			continue;
		if (this->m_pCullingBound->CheckIntersect(obj->GetBoundBox())) 
		{
			obj->Render(pRenderTarget);
		}		
	}
}

void World::Clear()
{
	m_GameObjects.clear();
}

void World::removeElements(std::list<GameObject*>& origin, const std::list<GameObject*>& remove) { //지울객체를 실제로 지우기
	for (auto it = remove.begin(); it != remove.end(); ++it) {
		origin.remove(*it); 
	}
}

void World::DeleteGameObject(GameObject* gameObject) //지울 객체를 담아두기
{
	m_Remove.push_back(gameObject);
}
