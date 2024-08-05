#include "pch.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "GameObject.h"
#include "Movement.h"
#include "Transform.h"
#include "AABB.h"
#include "D2DRenderer.h"


BoxCollider::BoxCollider(AABB* aabb, CollisionType type, IColliderNotify* notify, CollisionLayer layer = CollisionLayer::Default)
    : aabb(aabb)
{
    colliderType = ColliderType::Box;
    collisionType = type;
    this->layer = layer;
    this->notify = notify;
}

BoxCollider::~BoxCollider()
{

}

bool BoxCollider::IsCollide(Collider* otherComponent) 
{
    if (otherComponent->GetColliderType() == ColliderType::Box) //상대가 박스일때
    {
        return  aabb->CheckIntersect(*((BoxCollider*)otherComponent)->aabb);
    }
    else if (otherComponent->GetColliderType() == ColliderType::Circle) //상대가 원일때
    {
        return  aabb->CheckIntersect(*((CircleCollider*)otherComponent)->aabb);
    }
}

void BoxCollider::ProcessBlock(Collider* ownedComponent, Collider* otherComponent)
{
    __super::ProcessBlock(ownedComponent, otherComponent);
}

void BoxCollider::Update(float deltaTime)
{
    if (owner->transform)
        aabb->Center = owner->transform->GetWorldLocation(); //이부분은 각 콜라이더로 이전한다
    //받아오는건 월드좌표인데.. 
}

//그리고 겹치는 상태일때도 만들어야함

void BoxCollider::Render(ID2D1RenderTarget* pRenderTarget)
{
#ifdef _DEBUG
    D2DRenderer::GetInstance()->DrawAABB(*aabb);
#endif
}
