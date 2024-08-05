#pragma once
#include "IColliderNotify.h"

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

enum class CollisionLayer //레이어로 구분해서 필요한 애들만 충돌검사를 하도록 만들기
{
	Tower, 
	Enemy,
	Bullet,
	Default //디폴트는 누구랑도 충돌안함? 아니면 모두랑 충돌해야하나? 
};

/*
	추상 클래스
*/
class AABB;
class Collider
{
public:
	Collider(); //추상클래스라도 생성자는 호출될때니까 여기서 월드한테 등록할수있게하면될듯?
	virtual ~Collider();

protected:
	CollisionType collisionType;		// 컬리전 타입 (노컬리전,블럭, 오버랩)
	ColliderType colliderType;		// 콜라이더 모양
	D2D1_COLOR_F color;				// 그리기용 색상
	IColliderNotify* notify;
	CollisionLayer layer;
	bool isBlock[2] = { false,false }; //0 x축 1 y축;
	std::set<Collider*> collideStateCurr;    // 현재 충돌 상태
	std::set<Collider*> collideStatePrev;	 // 이전 충돌 상태
public:

	CollisionType GetCollisionType() { return collisionType; }
	ColliderType GetColliderType() { return colliderType; }
	CollisionLayer GetCollisionLayer() { return layer; }
	void SetCollisionType(CollisionType Type) { collisionType = Type; }

	D2D1_COLOR_F GetColor() const { return color; }
	void SetColor(D2D1_COLOR_F val) { color = val; }

	bool IsEmptyCollideStateCurr() { return collideStateCurr.empty(); } //현재 충돌한 콜라이더가있는지 
	void InsertCollideState(Collider* pColliderComponent) { collideStateCurr.insert(pColliderComponent); }//set이라 겹치는건 없을거고.. 
	//충돌줄 콜라이더 목록에까지는 넣어줌.. 

	void ClearAndBackupCollideState();	//현재와 이전을 비교해서 각 콜라이더한테 맞는신호를 보내줘야함. 
	void ProcessOverlap();				//겹치는중에 notify한테 알려줘야하고..  얘네는 왜 virtual이 아니지?
	virtual	void ProcessBlock(Collider* ownedComponent, Collider* otherComponent); 
	virtual bool IsCollide(Collider* ownedComponent) = 0;
};

