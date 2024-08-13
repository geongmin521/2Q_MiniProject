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

Arrow::Arrow(float speed,std::string type,float damage,float attackArea) //�Ѿ˵� �ִϸ��̼� �ִ°ǰ�?�׳� �̹����� �Ǵ°� �ƴѰ�? �ϴ��� �׳� ��Ʈ������ �غ���? 
{
	SetBoundBox(0, 0, attackArea, attackArea);
	//AddComponent(new Bitmap(L"..\\Data\\Image\\" + imagePath));
	//AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Arrow"));
	renderOrder = 100;
	AddComponent(new BezierMovement(transform, speed)); //�߻�Ǵ¼����� ���� ��ġ�� �޾ƿ��°� ����.. 
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
		cirCle->SetCollisionType(CollisionType::Overlap); //���⼭ �ٽ� Ű�°Ը³�? �����ϰ� ����
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
		AttackFunc(); //�Ѿ��� ������Ŀ�꿡�� ���������� ���⼭���־��ҰŰ�����
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




