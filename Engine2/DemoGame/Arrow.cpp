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

#include "Artifact.h"
#include "DataManager.h"
#include "GameManager.h"

Arrow::Arrow(std::string name,std::string type,float damage,float attackArea,float knockBack) //총알도 애니메이션 있는건가?그냥 이미지면 되는게 아닌가? 일단은 그냥 비트맵으로 해볼까? 
{
	this->speed = 1.0f;
	this->type = type;
	SetBoundBox(0, 0, attackArea, attackArea);
	renderOrder = 101;
	if(type != "HiddenArrow")
	AddComponent(new Bitmap(L"..\\Data\\Image\\Tower\\" + Utility::convertFromString(name) + L"Arrow.png"));

	if (artifact->isOwned(static_cast<int>(ArtifactId::Laurel)))
	{
		ArtifactData data = dataManager->getArtifactData(static_cast<int>(ArtifactId::Laurel));
		knockBack += data.power;
	}
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
		AttackFunc = [this, type, damage, knockBack]() { ArrowFunc::WaterAttack(this,*GetComponent<CircleCollider>(),type,damage, knockBack); };
		id = 503;
	}
	if (type == "Hidden")
	{   
		this->speed = 160.0f;
		AddComponent(new Movement(transform));
		transform->SetRelativeScale({ 0.5f,0.5f });
		AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), attackArea), CollisionType::Overlap, this, CollisionLayer::Bullet));
		AttackFunc = [this,damage]() { ArrowFunc::HiddenAttack(*GetComponent<CircleCollider>(), damage); };
		id = 512;
	}
	if (type == "HiddenArrow")
	{
		AddComponent(new Animation((L"..\\Data\\Image\\Tower\\" + Utility::convertFromString(name) + L"Arrow.png"), L"..\\Data\\CSV\\TowerAni\\HiddenArrow.csv"));
		transform->SetRelativeScale({ 1.7f,1.7f });
		GetComponent<Animation>()->SetAnimation(0, false, false);
		AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), attackArea), CollisionType::Overlap, this, CollisionLayer::Bullet));
		AttackFunc = [this, damage, knockBack]() { ArrowFunc::AttackEnemys(*GetComponent<CircleCollider>(), damage, knockBack); };
		id = 513;
	}
	if (type == "Normal")
	{
		AddComponent(new BezierMovement(transform, speed));
		transform->SetRelativeScale({ 0.3f,0.3f });

		float WaveLevel = dataManager->getWaveData(gameManager->WaveLevel).levelPower;
		AttackFunc = [this, type, damage, knockBack, WaveLevel]() { ArrowFunc::AttackTower(this, this->target, type, damage, knockBack); };
		id = 601;
	}
}

Arrow::~Arrow()
{
}


void Arrow::Init(MathHelper::Vector2F location, GameObject* target,float level)
{
	this->level = level;
	if(target !=nullptr)
	this->target = target;
	if (GetComponent<BezierMovement>() != nullptr)
	{
		GetComponent<BezierMovement>()->target = target;
		GetComponent<BezierMovement>()->Init();
	}
	
	CircleCollider* cirCle = GetComponent<CircleCollider>();
	if (cirCle)
		cirCle->SetCollisionType(CollisionType::Overlap); //여기서 다시 키는게맞나? 공격하고 끄고
	elapsedTime = 0;
	elapsedTime2 = 0;
	this->transform->SetRelativeLocation(location);

	if(GetComponent<Animation>() != nullptr)
	GetComponent<Animation>()->SetAnimation(0, false, false);
	Attackstart = false;
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
	if (type == "HiddenArrow")
	{
		if (GetComponent<Animation>()->IsEnd())
		{
			Attackstart = true;
		}
		if (Attackstart == true)
		{
			GetComponent<Animation>()->SetAnimation(1, false, true);
			Attackstart = false;
			
		}
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

	if (type != "HiddenArrow" && (target->GetWorldLocation() - GetWorldLocation()).Length() <= 15.0f)
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




