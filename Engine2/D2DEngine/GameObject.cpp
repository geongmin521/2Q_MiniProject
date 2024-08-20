#include "pch.h"
#include "GameObject.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "CollisionManager.h"
#include "Transform.h"
#include "Collider.h"

GameObject::GameObject()
{
	transform = new Transform(); //모든 게임오브젝트는 트랜스폼을 들고있다.
	AddComponent(transform);
	boundBox = new AABB();
	isActive = true;
}

GameObject::~GameObject() 
{
	for (auto& pComponent : ownedComponents)
	{
		delete pComponent;
	}
	ownedComponents.clear();
}

void GameObject::Update(float deltaTime) 
{
	if (!isActive)
		return;
	for (auto& pComponent : ownedComponents)
	{
		if(pComponent->GetActive())
			pComponent->Update(deltaTime);
	}
	if (transform)
		boundBox->Center = transform->GetWorldLocation();
}


void GameObject::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	if (!isActive) //오브젝트만 껴져도 컴포넌트를 안돌긴하는데 흠.. 
		return;
	for (auto& pComponent : ownedComponents) 
	{	
		pComponent->Render(pRenderTarget, Alpha);
	}
}


void GameObject::SetBoundBox(int x, int y,int weight, int height)
{  
	if (boundBox == nullptr)
		boundBox = new AABB();
	boundBox->SetExtent(weight / 2, height / 2);
	boundBox->SetCenter(x,y);
}

void GameObject::SetBoundBox(int x, int y, MathHelper::Vector2F bound)
{
	if (boundBox == nullptr)
		boundBox = new AABB();
	boundBox->SetExtent(bound.x / 2, bound.y / 2);
	boundBox->SetCenter(x, y);
}


void GameObject::AddComponent(Component* pComponent)
{
	pComponent->SetOwner(this);
	ownedComponents.push_back(pComponent);
}

void GameObject::SetActive(bool active)
{
	if (isActive == active)
		return;
	isActive = active;
	if (active)
		Enable();
	else
		Disable();
	for (auto var : transform->childScene) 
		var->owner->SetActive(active); 	
	for (auto var : ownedComponents) 
		var->SetActive(active); 
}

MathHelper::Vector2F GameObject::GetWorldLocation()
{ 
	MathHelper::Vector2F temp{ 0,0 };
	if (transform)
		temp = transform->GetWorldLocation();

	return temp;
}
