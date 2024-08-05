#include "pch.h"
#include "Collider.h"
#include "CollisionManager.h"

Collider::Collider()
{
	CollisionManager::GetInstance()->pushCollider(this);
}

Collider::~Collider()
{
	CollisionManager::GetInstance()->EraseCollider(this);
}

void Collider::ClearAndBackupCollideState()
{
    //중복상태에 대한 처리를 다하고 나면.. 바꿔주기...
    collideStatePrev = collideStateCurr; //현재는 이전이 되고 
    collideStateCurr.clear(); //현재는 비워버리기

    //이러면 콜라이더에 중첩에 대한 처리도 모두 끝난거지? 
}

void Collider::ProcessOverlap()
{
    //충돌이 시작 상태
    for (auto* collider : collideStateCurr) {
        if (collideStatePrev.find(collider) == collideStatePrev.end()) {
            notify->OnBeginOverlap(this, collider);
        }
    }

    // 충돌이 끝난 상태
    for (auto* collider : collideStatePrev) {
        if (collideStateCurr.find(collider) == collideStateCurr.end()) {
            notify->OnEndOverlap(this, collider);
        }
    }
    for (auto* collider : collideStateCurr) {
        notify->OnStayOverlap(this, collider);
    }
    ClearAndBackupCollideState();
}

void Collider::ProcessBlock(Collider* ownedComponent, Collider* otherComponent)
{
	notify->OnBlock(ownedComponent, otherComponent);
}
