#include "pch.h"
#include "BoxCollider.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "AABB.h"
#include "Music.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "EnemyBase.h"
#include "Movement.h"
#include "TowerBase.h"
#include "ArrowFunc.h"
#include "Pools.h"
#include "BezierMovement.h"
#include "TimeSystem.h"

#include "World.h"
#include "Effect.h"

#include "Arrow.h"

Arrow::Arrow(std::string type,float damage,float attackArea,float knockBack) //총알도 애니메이션 있는건가?그냥 이미지면 되는게 아닌가? 일단은 그냥 비트맵으로 해볼까? 
{
	this->speed = 1.5f;
	this->type = type;
	SetBoundBox(0, 0, attackArea, attackArea);
	renderOrder = 95;
	AddComponent(new Bitmap(L"..\\Data\\Image\\" + Utility::convertFromString(type) + L".png"));
	//발사되는순간에 적의 위치를 받아오는게 맞지.. 
	if (type == "Crossbow")
	{
		AddComponent(new BezierMovement(transform, speed));
		AttackFunc = [this, type, damage, knockBack]() { ArrowFunc::AttackEnemy(this, this->target,type, damage, knockBack); };
		id = 500;
	}
	if (type == "Water")
	{
		AddComponent(new BezierMovement(transform, speed));
		AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), attackArea), CollisionType::Overlap, this, CollisionLayer::Bullet));
		AttackFunc = [this, type, damage, knockBack]() { ArrowFunc::WaterAttack(*GetComponent<CircleCollider>(),type,damage, knockBack); };
		id = 503;
	}
	if (type == "Hidden")
	{
		this->speed = 30.0f;
		AddComponent(new Movement(transform));
		transform->SetRelativeScale({ 0.3f,0.3f });
		AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), attackArea), CollisionType::Overlap, this, CollisionLayer::Bullet));
		AttackFunc = [this,damage]() { ArrowFunc::HiddenAttack(*GetComponent<CircleCollider>(), damage); };
		id = 512;
	}
	if (type == "HiddenArrow")
	{
		transform->SetRelativeScale({ 0.10f,0.10f }); 
		AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), attackArea), CollisionType::Overlap, this, CollisionLayer::Bullet));
		AttackFunc = [this, damage, knockBack]() { ArrowFunc::AttackEnemys(*GetComponent<CircleCollider>(), damage, knockBack); };
		id = 513;
	}
	if (type == "vampire")
	{
		AddComponent(new BezierMovement(transform, speed));
		AttackFunc = [this, type, damage, knockBack]() { ArrowFunc::AttackEnemy(this, this->target, type, damage, knockBack); };
		id = 500000;
	}
}

Arrow::~Arrow()
{
}


void Arrow::Init(MathHelper::Vector2F location, GameObject* target)
{
	if(target !=nullptr)
	this->target = target;
	if(GetComponent<BezierMovement>() != nullptr)
	GetComponent<BezierMovement>()->target = target;

	CircleCollider* cirCle = GetComponent<CircleCollider>();
	if (cirCle)
		cirCle->SetCollisionType(CollisionType::Overlap); //여기서 다시 키는게맞나? 공격하고 끄고
	elapsedTime = 0;
	elapsedTime2 = 0;
	this->transform->SetRelativeLocation(location);
}


void Arrow::Update(float deltaTime)
{
	if (type == "Hidden")
	{
		MathHelper::Vector2F dir = (target->GetWorldLocation() - GetWorldLocation()).Normalize();
		GetComponent<Movement>()->SetVelocity(dir * speed);
	}
	__super::Update(deltaTime);
	/*if (target->GetActive() == false)
	{
		Pools::GetInstance().get()->AddPool(this);
	}*/
	static float abc = 0;
	if (type == "HiddenArrow")
	{
		elapsedTime2 += deltaTime;
		if (elapsedTime2 > attackTime)
		{
			AttackFunc();
			elapsedTime2 = 0;
		}

		elapsedTime += deltaTime;
		if (elapsedTime > duration)
		{
			Pools::GetInstance().get()->AddPool(this);
		}
	}
	if (type != "HiddenArrow" && (target->GetWorldLocation() - GetWorldLocation()).Length() < 5.0f)
	{
		AttackFunc(); //풀에넣는건 각 어택안에서
		
	}
	

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




