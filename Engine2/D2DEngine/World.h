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
	template<typename T>
	T* CreateGameObject()
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		newObject->SetOwner(this); //이건 어떻게되는거지 도대체.. 
		
		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
		{
			if ((*it)->renderOrder > newObject->renderOrder)
			{
				m_GameObjects.insert(it, newObject); 
				return newObject; 
			}			
		}
		
		m_GameObjects.push_back(newObject); //나머지 상황에 대해서는 뒤에 넣기
	
		return newObject;
	} 
	void InsertGameObject(GameObject* obj);//create는 일관성을 유지해야해서 생성자에 매개변수를 넣을수없었음
	//그래서 생성한다음에 넣어주는 인서트를 추가함.
	void removeElements(std::list<GameObject*>& origin, const std::list<GameObject*>& remove);
	void DeleteGameObject(GameObject* gameObject);

};

