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
	towerData.name = "MeleeTower";                    //csv���� �о�ͼ� �ٳ־����Բ� 
	towerData.attackRange = 100.0f;
	towerData.attackSpeed = 1.0f;
	towerData.HP = 20000.0f;
	curHP = towerData.HP;
	SetBoundBox(0, 0, 200, 200); // 
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"MeleeTower")); //�ϴ� �� ���̾��� �������� �ִϸ��̼Ǹ� �ٸ���
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));
	
	
	//star = new Bitmap(L"..\\Data\\Image\\star.png"); //�ٸ���Ʈ�� �߰��ϰԵǸ� �����ҷ��� 
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

	//target�� ���� ������
	//GetComponent<BoxCollider>()->collideStateCurr.begin() it;
	//it = owner name enemy;
	//Getwroldlocation  �Ÿ���
	//	>> ���������� Ÿ������
	//	�갡 ������ target null �ƴϸ� Ÿ��;
	
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
		                          //���� �߰��ʿ�
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
