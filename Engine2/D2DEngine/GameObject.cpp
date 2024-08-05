#include "pch.h"
#include "GameObject.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "Transform.h"

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
		if(pComponent->getActive())
			pComponent->Update(deltaTime);
	}
	//if (transform)
	//	boundBox->Center = transform->GetWorldLocation(); //이부분은 각 콜라이더로 이전한다 //카메라로 컬링을 할일이 있을까? 우리게임에서? 
}


void GameObject::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (!isActive)
		return;
	for (auto& pComponent : ownedComponents) 
	{	
		pComponent->Render(pRenderTarget);
	}
}


void GameObject::SetBoundBox(int x, int y,int weight, int height)
{  
	if (boundBox == nullptr)
		boundBox = new AABB();
	boundBox->SetExtent(weight / 2, height / 2);
	boundBox->SetCenter(x,y);
}

void GameObject::AddComponent(Component* pComponent)
{
	pComponent->SetOwner(this);
	ownedComponents.push_back(pComponent);
}

D2D1_VECTOR_2F GameObject::GetWorldLocation()
{ 
	D2D1_VECTOR_2F temp{ 0,0 };
	if (transform)
		temp = transform->GetWorldLocation();

	return temp;
}
