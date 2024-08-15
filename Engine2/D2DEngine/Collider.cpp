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
    //충돌이 시작 상태
    for (auto& collider : collideStateCurr) {
        if (collideStatePrev.find(collider) == collideStatePrev.end()) {
            if (notify)
            notify->OnBeginOverlap(this, collider);
        }
    }

    // 충돌이 끝난 상태
    for (auto& collider : collideStatePrev) {
        if (collideStateCurr.find(collider) == collideStateCurr.end()) {
            notify->OnEndOverlap(this, collider);
        }
    }
    // 충돌중인 애들
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
