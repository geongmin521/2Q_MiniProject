#include "pch.h"
#include "BoxCollider.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "FiniteStateMachine.h"
#include "TowerFsm.h"
#include "AABB.h"
#include "Music.h"
#include "World.h" 
#include "EnemyBase.h"
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
	
	
	//star = new Bitmap(L"..\\Data\\Image\\star.png"); //다른비트맵 추가하게되면 구별할려고 
	//AddComponent(star);
	//star->
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

	//target이 현재 없을때
	//GetComponent<BoxCollider>()->collideStateCurr.begin() it;
	//it = owner name enemy;
	//Getwroldlocation  거리비교
	//	>> 제일작은걸 타겟으로
	//	얘가 죽으면 target null 아니면 타겟;
	
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
