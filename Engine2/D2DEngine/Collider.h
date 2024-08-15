#pragma once
#include "IColliderNotify.h"
#include "Component.h"
enum class CollisionType //�浹 Ÿ��
{
	NoCollision,
	Block,
	Overlap
};

enum class ColliderType //�浹ü�� Ÿ��
{
	Box,
	Circle
};

enum class CollisionLayer //�浹 ���̾�
{
	Tower, 
	Enemy,
	Bullet,
	Default
};

/*
	�߻� Ŭ����
*/
class AABB;
class Collider : public Component
{
public:
	Collider(CollisionType type, IColliderNotify* notify, CollisionLayer layer);
	virtual ~Collider();

protected:
	CollisionType collisionType;	// �ø��� Ÿ�� (���ø���,��, ������)
	ColliderType colliderType;		// �ݶ��̴� ���
	D2D1_COLOR_F color;				// �׸���� ����
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

