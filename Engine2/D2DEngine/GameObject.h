#pragma once
class Component;
class World;
class Transform;
class AABB;

class GameObject
{
private:
	bool isActive;
	virtual void Enable() {}
	virtual void Disable() {}
public:
	GameObject();
	virtual ~GameObject();	
	int id = 9999;
	int renderOrder;
	AABB* boundBox;
	World* owner = nullptr;
	Transform* transform = nullptr;
	std::string name;
	std::vector<Component*> ownedComponents;	
	std::string gameObjectName;
	
public:
	virtual void Update(float deltaTime);
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha =1);
	const AABB& GetBoundBox() const { return *boundBox; }
	void SetBoundBox(int x, int y, int weight, int height);
	void SetBoundBox(int x, int y, MathHelper::Vector2F bound);
	void AddComponent(Component* pComponent);
	void SetOwner(World* pOwner) { owner = pOwner; } 
	void SetActive(bool active);
	bool GetActive() { return isActive; }
	MathHelper::Vector2F GetWorldLocation();

	template<typename T>
	T* GetComponent()
	{
		for (int i = 0; i < ownedComponents.size(); i++)
		{
			if (T* component = dynamic_cast<T*>(ownedComponents[i]))
			{
				return component; 
			}
		}
		return nullptr; 
	}

	template<typename T>
	T* CreateComponent()
	{
		bool bIsBase = std::is_base_of<Component, T>::value;
		T* pComponent = new T();
		AddComponent(pComponent);
		return pComponent;
	}
};

