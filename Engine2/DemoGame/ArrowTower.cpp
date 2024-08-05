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
#include "ArrowTower.h"

ArrowTower::ArrowTower()
{
	SetBoundBox(0, 0, 102, 82);
	AddComponent(new Animation(L"..\\Data\\Image\\run.png", L"Run"));

	
	//�̹����� ��������.. �ڵ����� ȸ���� �߽���ǥ�� �����ϱ�.. 
	AddComponent(new BoxCollider(boundBox ,CollisionType::NoCollision, this, CollisionLayer::Tower));
	//AddComponent(new BoxCollider( , CollisionType::Overlap, this, CollisionLayer::Tower));
	//�ڽ��� ������ �پ��� ���� ��ġ�� ȸ���ϴµ� �ֱ׷���>? 
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);

	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");

	fsm->SetNextState("Attack");                    //���̾�� �ϴ� attack�� �׽�Ʈ 
	towerData.name = "ArrowTower";                    //csv���� �о�ͼ� �ٳ־����Բ� 
	towerData.attackRange = 500.0f;
	renderOrder = 100;
	transform->relativeLocation = { 200,200 };
}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{
	
	__super::Update(deltaTime);
	//Music::soundManager->GetInstance()->PlayMusic();
	//�׽�Ʈ������ ȸ���ɾ���� �߾��� �������� ȸ���ϵ��ϸ����
	//transform->AddRelativeRotation(1);

}

void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	//GetComponent<BoxCollider>()->aabb->Center = { 300,300 };
	//D2DRenderer::GetInstance()->DrawAABB(*GetComponent<BoxCollider>()->aabb); //��ġ�� �̻��ѵ�? �� �߱׸��µ�.. ���� ��������ϴϱ� �����ϼ��ִ°� �� �˻��غ���
}

void ArrowTower::Attack(float deltaTime)
{ 
	attacktime -= deltaTime;
	if (attacktime <= 0)
	{
		arrows.push_back(owner->CreateGameObject<Arrow>());
		arrows.back()->transform->relativeLocation = { GetWorldLocation().x + 100.f, GetWorldLocation().y -20.f };
	
		attacktime = 3.0f;
	}
}

void ArrowTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	
}

void ArrowTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	if (target == nullptr)
	{
		
		
	}
}

void ArrowTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}
