#pragma once
#include "IColliderNotify.h"
#include "Component.h"
enum class CollisionType //충돌 타입
{
	NoCollision,
	Block,
	Overlap
};

enum class ColliderType //충돌체의 타입
{
	Box,
	Circle
};

enum class CollisionLayer //충돌 레이어
{
	Tower, 
	Enemy,
	Bullet,
	Default
};

/*
	추상 클래스
*/
class AABB;
class Collider : public Component
{
public:
	Collider(CollisionType type, IColliderNotify* notify, CollisionLayer layer);
	virtual ~Collider();

protected:
	CollisionType collisionType;	// 컬리전 타입 (노컬리전,블럭, 오버랩)
	ColliderType colliderType;		// 콜라이더 모양
	D2D1_COLOR_F color;				// 그리기용 색상
	IColliderNotify* notify;
	CollisionLayer layer;
	bool isBlock[2] = { false,false }; //x,y
	bool onStay = false; 
public:
	std::set<Collider*> collideStateCurr; 
	std::set<Collider*> collideStatePrev;
	std::string name;
	CollisionType GetCollisionType() { return collisionType; }
	ColliderType GetColliderType() { return colliderType; }
	CollisionLayer GetCollisionLayer() { return layer; }
	void SetCollisionType(CollisionType Type) { collisionType = Type; }
	void SetCollisionLayer(CollisionLayer layer) { this->layer = layer; }
	void SetNotify(IColliderNotify* notify) { this->notify = notify; }
	void SetOnStay(bool onStay) { this->onStay = onStay; }
	bool GetOnStay() { return onStay; }
	D2D1_COLOR_F GetColor() const { return color; }
	void SetColor(D2D1_COLOR_F val) { color = val; }

	bool IsEmptyCollideStateCurr() { return collideStateCurr.empty(); } 
	void InsertCollideState(Collider* pColliderComponent) { collideStateCurr.insert(pColliderComponent); }

	void ClearAndBackupCollideState();	
	void ProcessOverlap();				
	virtual	void ProcessBlock(Collider* ownedComponent, Collider* otherComponent); 
	virtual bool IsCollide(Collider* ownedComponent) = 0;

	virtual void Enable() override;
	virtual void Disable() override;
};

