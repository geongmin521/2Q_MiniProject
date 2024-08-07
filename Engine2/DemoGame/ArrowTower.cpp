#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
#include "../D2DEngine/CircleCollider.h"
#include "../D2DEngine/Circle.h"
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Animation.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/FiniteStateMachine.h"
#include "TowerFsm.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Music.h"
#include "../D2DEngine/World.h" 
#include "EnemyBase.h"
#include "ArrowTower.h"

ArrowTower::ArrowTower()
{
	towerData.name = "ArrowTower";                    //csv에서 읽어와서 다넣어지게끔 
	towerData.attackRange = 300.0f;
	towerData.attackSpeed = 1.0f;
	towerData.HP = 200.0f;

	SetBoundBox(0, 0, towerData.attackRange, towerData.attackRange);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));

	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared"); 
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");                    //적이없어서 일단 attack만 테스트 
	
	renderOrder = 100;
	transform->SetRelativeLocation({200,200});

	//attackRange = new AABB;
	//attackRange->SetExtent(towerData.attackRange, towerData.attackRange);
	////이미지가 정해지면.. 자동으로 회전의 중심좌표를 저장하기.. 
	////BoxCollider* attack;
	//searchBound = CreateComponent<BoxCollider>();
	//searchBound->Init(attackRange, CollisionType::Overlap, this, CollisionLayer::Tower);
	//searchBound->name = "attackbox";
	////GetComponent<>
	//BoxCollider* bound = new BoxCollider(boundBox, CollisionType::Block, this, CollisionLayer::Tower);
	//AddComponent(bound);
	//towerBound = CreateComponent<BoxCollider>();
	////towerBound->Init();
	////towerBound->name = "tower";
	////AddComponent(new BoxCollider(attackRange,CollisionType::Overlap, this, CollisionLayer::Tower));
	////AddComponent(new BoxCollider(boundBox ,CollisionType::Block, this, CollisionLayer::Tower));
	//

}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{

	__super::Update(deltaTime);
	//attackRange->SetCenter(boundBox->Center.x + towerData.attackRange, boundBox->Center.y);
	//Music::soundManager->GetInstance()->PlayMusic();

	//target이 현재 없을때
	//GetComponent<BoxCollider>()->collideStateCurr.begin() it;
	//it = owner name enemy;
	//Getwroldlocation  거리비교
	//	>> 제일작은걸 타겟으로
	//	얘가 죽으면 target null 아니면 타겟;
	if (target == nullptr)
	{
		Find();
	}

}
void ArrowTower::Find()
{
	std::vector<GameObject*> enemys;
	for (auto& col : GetComponent<BoxCollider>()->collideStatePrev)
	{
		if (col->owner->name == "Enemy")
			enemys.push_back(col->owner);
	}
	float min = 1000;
	float curMin;
	float xDistance;
	float yDistance;
	GameObject* curTarget = nullptr;
	if (!enemys.empty())
	{
		for (auto& enemy : enemys)
		{
			std::cout << " 적 있음";
			xDistance = (GetWorldLocation().x - enemy->GetWorldLocation().x);
			//if (xDistance > 0) continue; //일단 타워뒤로가면 공격못하게
			yDistance = std::abs(GetWorldLocation().y - enemy->GetWorldLocation().y);
			curMin = std::min(xDistance, yDistance);

			if (min > curMin)
				min = curMin;

			curTarget = enemy;
		}
	}
	if (curTarget != nullptr)
		target = curTarget;
}

void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);

	//GetComponent<BoxCollider>()->aabb->Center = { 300,300 };
	
}

void ArrowTower::Attack(float deltaTime)
{ 
	
	Arrow* arrow = new Arrow;
	arrow->owner = this->owner;
	Vector2F dir  = Vector2F(target->GetWorldLocation()) - Vector2F(GetWorldLocation());
	dir.Normalize();
	arrow->Init({ dir }, GetWorldLocation());
	owner->m_GameObjects.push_back(arrow);
}

//좀더 확실하고 통제된 환경을 만들어야한다. 

void ArrowTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	std::cout << "test";
}

void ArrowTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	//ownedComponent.get
	//if (otherComponent->getActive())
	//{
	//	if (ownedComponent->name == "attackbox" && otherComponent->owner->name == "Enemy") 
	//	{
	//		objs.push_back(otherComponent->owner); //
	//		std::cout << "적감지";
	//	}
	//}
}


void ArrowTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	std::cout << "적 충돌중";
}

void ArrowTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	/*if (otherComponent->owner->name == "Enemy" && !objs.empty())
		objs.erase(std::remove(objs.begin(),objs.end(),otherComponent->owner));*/
}

void ArrowTower::Hit(GameObject* obj)
{
	EnemyBase* enemy;
	enemy = dynamic_cast<EnemyBase*>(obj);
	towerData.HP -= enemy->enemyData.ATK;
	std::cout << std::endl << towerData.HP << std::endl;
}
