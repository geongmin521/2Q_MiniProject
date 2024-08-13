#include "pch.h"
#include "BoxCollider.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "AABB.h"
#include "Music.h"
#include "Utility.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "EnemyBase.h"
#include "TowerBase.h"
#include "ArrowFunc.h"
#include "Pools.h"
#include "../D2DEngine/BezierMovement.h"

#include "World.h"
#include "Effect.h"

#include "Arrow.h"

Arrow::Arrow(float speed,std::string type,float damage,float attackArea) //총알도 애니메이션 있는건가?그냥 이미지면 되는게 아닌가? 일단은 그냥 비트맵으로 해볼까? 
{
	SetBoundBox(0, 0, attackArea, attackArea);
	//AddComponent(new Bitmap(L"..\\Data\\Image\\" + imagePath));
	//AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Arrow"));
	renderOrder = 100;
	AddComponent(new BezierMovement(transform, speed)); //발사되는순간에 적의 위치를 받아오는게 맞지.. 
	if (type == "Crossbow")
	{
		AddComponent(new Bitmap(L"..\\Data\\Image\\Crossbow.png" ));
		AttackFunc = [this, type, damage]() { ArrowFunc::AttackEnemy(this->target,type, damage); };
		id = 500;

	}
	if (type == "Water")
	{	
		AddComponent(new Bitmap(L"..\\Data\\Image\\Water.png"));
		AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), attackArea), CollisionType::Overlap, this, CollisionLayer::Bullet));
		AttackFunc = [this, type, damage]() { ArrowFunc::AttackEnemys(*GetComponent<CircleCollider>(),type,damage); };
		id = 501;
	}
	if (type == "Hidden")
	{

	}
	if (type == "Vampire")
	{
		AddComponent(new Bitmap(L"..\\Data\\Image\\vampire.png"));
		id = 500000;
	}
}

Arrow::~Arrow()
{
}


void Arrow::Init(GameObject* target, MathHelper::Vector2F location)
{
	this->target = target;
	this->transform->SetRelativeLocation(location);
	GetComponent<BezierMovement>()->target = target;
	
	CircleCollider* cirCle = GetComponent<CircleCollider>();
	if (cirCle)
		cirCle->SetCollisionType(CollisionType::Overlap); //여기서 다시 키는게맞나? 공격하고 끄고
}

void Arrow::Update(float deltaTime)
{
	preDir = curDir;
	__super::Update(deltaTime);
	curDir = transform->GetRelativeLocation();
	if(target->GetActive() == false)
	{
		Pools::GetInstance().get()->AddPool(this);
	}
	if ((target->GetWorldLocation() - GetWorldLocation()).Length() < 5.0f) 
	{
		AttackFunc(); //총알을 벨지에커브에서 없애지말고 여기서없애야할거같은대
		Pools::GetInstance().get()->AddPool(this);
	}
	
	float moveX = curDir.x - preDir.x;
    float moveY = curDir.y - preDir.y;
	float moveR = atan2(moveX, moveY) * (180.0f / PI);
	//transform->SetRelativeRotation(moveR);

}

void Arrow::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}



void Arrow::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void Arrow::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void Arrow::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void Arrow::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}




