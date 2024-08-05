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
		newObject->SetOwner(this); //�̰� ��ԵǴ°��� ����ü.. 
		
		for (auto it = m_GameObjects.begin(); it != m_GameObjects.end(); it++)
		{
			if ((*it)->renderOrder > newObject->renderOrder)
			{
				m_GameObjects.insert(it, newObject); 
				return newObject; 
			}			
		}
		
		m_GameObjects.push_back(newObject); //������ ��Ȳ�� ���ؼ��� �ڿ� �ֱ�
	
		return newObject;
	} 
	void InsertGameObject(GameObject* obj);//create�� �ϰ����� �����ؾ��ؼ� �����ڿ� �Ű������� ������������
	//�׷��� �����Ѵ����� �־��ִ� �μ�Ʈ�� �߰���.
	void removeElements(std::list<GameObject*>& origin, const std::list<GameObject*>& remove);
	void DeleteGameObject(GameObject* gameObject);

};

