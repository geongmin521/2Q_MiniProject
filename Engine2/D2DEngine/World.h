#pragma once
#include "GameObject.h"

class AABB;
//class GameObject;
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
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget);
	void Clear();
	void SetCullingBound(AABB* pBound) { m_pCullingBound = pBound; }
	virtual void MakeObject();
	void InsertGameObject(GameObject* obj);
	void removeElements(std::list<GameObject*>& origin, const std::list<GameObject*>& remove);
	void DeleteGameObject(GameObject* gameObject);

};

