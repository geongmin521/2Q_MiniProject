#include "pch.h"
#include "World.h"
#include "D2DRenderer.h"
#include "AABB.h"
#include "GameObject.h"
#include "Animation.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "CollisionManager.h"
#include "EventSystem.h"
#include "DOTweenManager.h"


World::World()
{
	m_CullingBoundDefault = new AABB;
	m_CullingBoundDefault->SetExtent(WinSizeX /2, WinSizeY /2);
	m_CullingBoundDefault->SetCenter(0,0);
	SetCullingBound(m_CullingBoundDefault);	

}

World::~World()
{
	for (auto ele : m_GameObjects)
	{
		delete ele;
	}
}

void World::InsertGameObject(GameObject* obj)
{

	obj->SetOwner(this); 

	for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
	{
		if ((*it)->renderOrder > obj->renderOrder)
		{
			m_GameObjects.insert(it, obj); //렌더 순서대로 넣기.. 
			return;
		}
	}

	m_GameObjects.push_back(obj); //나머지 상황에 대해서는 뒤에 넣기
}


void World::Update(float deltaTime)
{
	if (m_Remove.size() != 0)
		Utility::removeElements(m_GameObjects, m_Remove);
	for (auto& obj : m_GameObjects) 
	{
		if (!obj->isActive)
			continue;
		obj->Update(deltaTime);
	}
	EventSystem::GetInstance().get()->Updata(deltaTime);
	CollisionManager::GetInstance()->CollisionCheck();
	DOTweenManager::GetInstance().get()->Update(deltaTime);
}

void World::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto& obj : m_GameObjects) 
	{		
		if (!obj->isActive)
			continue;
		//if (this->m_pCullingBound->CheckIntersect(obj->GetBoundBox())) 
		//{
 			obj->Render(pRenderTarget);
		//}		
	}
}

void World::Clear()
{

	m_GameObjects.clear();
}

void World::MakeObject()
{
}



void World::DeleteGameObject(GameObject* gameObject) //지울 객체를 담아두기
{
	m_Remove.push_back(gameObject);
}

