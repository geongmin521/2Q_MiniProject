#include "pch.h"
#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider(CollisionType type, IColliderNotify* notify, CollisionLayer layer) : collisionType(type), notify(notify), layer(layer)
{
    collisionManager->pushCollider(this);
}

Collider::~Collider()
{
    collisionManager->AddRemove(this);
}

void Collider::ClearAndBackupCollideState()
{
    collideStatePrev = collideStateCurr; 
    collideStateCurr.clear();
}

void Collider::ProcessOverlap()
{
    //�浹�� ���� ����
    for (auto& collider : collideStateCurr) {
        if (collideStatePrev.find(collider) == collideStatePrev.end()) {
            if (notify)
            notify->OnBeginOverlap(this, collider);
        }
    }

    // �浹�� ���� ����
    for (auto& collider : collideStatePrev) {
        if (collideStateCurr.find(collider) == collideStateCurr.end()) {
            notify->OnEndOverlap(this, collider);
        }
    }
    // �浹���� �ֵ�
    for (auto& collider : collideStateCurr) {
        if(onStay)
            notify->OnStayOverlap(this, collider);
    }

    ClearAndBackupCollideState();
}

void Collider::ProcessBlock(Collider* ownedComponent, Collider* otherComponent)
{
	notify->OnBlock(ownedComponent, otherComponent);
}

void Collider::Enable()
{
    collisionManager->pushCollider(this);
}

void Collider::Disable()
{
    collisionManager->AddRemove(this);
}
