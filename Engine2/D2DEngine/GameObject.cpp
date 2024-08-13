#include "pch.h"
#include "GameObject.h"
#include "AABB.h"
#include "D2DRenderer.h"
#include "CollisionManager.h"
#include "CircleCollider.h"
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
	if (transform)
		boundBox->Center = transform->GetWorldLocation(); //이부분은 각 콜라이더로 이전한다 //카메라로 컬링을 할일이 있을까? 우리게임에서? 
}


void GameObject::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	if (!isActive)
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
	isActive = active;
	for (auto var : transform->childScene)
	{
		var->owner->SetActive(active); //계층적으로 할수있도록 설정.. 
	}
	//CircleCollider* col = GetComponent<CircleCollider>(); //적들이랑 타워모두 서클콜라이더만 사용한다는 전제하에?
	Collider* col = GetComponent<Collider>(); //적들이랑 타워모두 서클콜라이더만 사용한다는 전제하에?
	if (col == nullptr)
		return;
	if (active == false)
	{
		CollisionManager::GetInstance()->AddRemove(col);
	}
	else
	{
		CollisionManager::GetInstance()->pushCollider(col);
	}
}

MathHelper::Vector2F GameObject::GetWorldLocation()
{ 
	MathHelper::Vector2F temp{ 0,0 };
	if (transform)
		temp = transform->GetWorldLocation();

	return temp;
}
