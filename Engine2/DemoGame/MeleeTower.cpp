#include "../D2DEngine/pch.h"
#include "../D2DEngine/BoxCollider.h"
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
#include "Factory.h"
#include "MeleeTower.h"

MeleeTower::MeleeTower(TowerData data) : TowerBase(data)
{
	towerData.name = "MeleeTower";                    //csv에서 읽어와서 다넣어지게끔 
	towerData.attackRange = 100.0f;
	towerData.attackSpeed = 1.0f;
	towerData.HP = 20000.0f;
	curHP = towerData.HP;
	SetBoundBox(0, 0, 200, 200); // 
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"MeleeTower")); //일단 켄 같이쓰고 근접공격 애니메이션만 다르게
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));
	
	star = Fac->CreateGameObject<TowerStar>();
	towerData.level = 2;
	star->Init(this,towerData.level); 

	HPbar = Fac->CreateGameObject<HPBar>();
	HPbar->Init(this); //여기서 주인으로 자기를 줘서 자기 트랜스폼 찾게끔
	
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");

	renderOrder = 100;
	transform->SetRelativeLocation({ 500,100 });

}

MeleeTower::~MeleeTower()
{
	
}

void MeleeTower::Update(float deltaTime)
{

	__super::Update(deltaTime);

	
	FindTarget(GetComponent<BoxCollider>(),true);
	

}


void MeleeTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);



}

void MeleeTower::Attack(float deltaTime)
{
	std::vector<EnemyBase*> enemys;
	for (auto& enemy : targets)
	{
		enemys.push_back(dynamic_cast<EnemyBase*>(enemy));
	}
	
	for (auto& enemy : enemys)
	{
		                          //계산기 추가필요
		enemy->Hit(50);
		//std::cout << enemy->curHP << std::endl;
	}
}


void MeleeTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	
}

void MeleeTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}


void MeleeTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}

void MeleeTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{

}
