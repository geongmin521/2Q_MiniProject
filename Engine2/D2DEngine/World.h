#pragma once
#include "GameObject.h"

class AABB;
class Collider;
class BoxCollider;
class World
{
public:
	World();
	virtual ~World();	
	std::list<GameObject*> m_GameObjects;
	std::list<GameObject*> m_Remove;
	
	AABB* m_pCullingBound = nullptr; 
	AABB* m_CullingBoundDefault;	
public:	
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }
	virtual void MakeObject();
	void InsertGameObject(GameObject* obj);
	void DeleteGameObject(GameObject* gameObject);

	template<typename T>
	T* FindObject(const std::string& GameObjectName);
};

template<typename T>
T* World::FindObject(const std::string& GameObjectName)
{
	if (m_GameObjects.empty()) { return nullptr; }

	for (auto& GameObject : this->m_GameObjects)
	{
		if (GameObject->name.empty()) { continue; }
		if (GameObject->name == GameObjectName)
		{
			T* foundObject = dynamic_cast<T*>(GameObject);
			if (foundObject)
			{
				return foundObject;
			}
		}
	}
	return nullptr;
}
