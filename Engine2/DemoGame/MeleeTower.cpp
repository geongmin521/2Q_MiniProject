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
#include "MeleeTower.h"

MeleeTower::MeleeTower()
{
	towerData.name = "MeleeTower";                    //csv���� �о�ͼ� �ٳ־����Բ� 
	towerData.attackRange = 200.0f;
	towerData.attackSpeed = 1.0f;
	towerData.HP = 200.0f;

	SetBoundBox(0, 0, towerData.attackRange, 100); // ����Ÿ�� ���̴� �ڱ� ��üũ�⸸ŭ
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"MeleeTower")); //�ϴ� �� ���̾��� �������� �ִϸ��̼Ǹ� �ٸ���
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));

	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");

	renderOrder = 100;
	transform->SetRelativeLocation({ 200,100 });

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
	if (target == nullptr)
	{
		FindTarget(GetComponent<BoxCollider>());
	}

}


void MeleeTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);



}

void MeleeTower::Attack(float deltaTime)
{
	                             //���⼭ �� �ǰ�����?
}

//���� Ȯ���ϰ� ������ ȯ���� �������Ѵ�. 

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

void MeleeTower::Hit(GameObject* obj)
{
	EnemyBase* enemy;
	enemy = dynamic_cast<EnemyBase*>(obj);
	towerData.HP -= enemy->enemyData.ATK;
	std::cout << std::endl << towerData.HP << std::endl;
}
