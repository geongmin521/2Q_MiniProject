#include "pch.h"
#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider()
{
    
}

Collider::~Collider()
{
	CollisionManager::GetInstance()->AddRemove(this);
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
