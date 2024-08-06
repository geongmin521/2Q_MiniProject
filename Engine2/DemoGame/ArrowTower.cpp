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

	towerData.name = "ArrowTower";                    //csv���� �о�ͼ� �ٳ־����Բ� 
	towerData.attackRange = 300.0f;
	towerData.attackSpeed = 5.0f;
	AABB* attackRange = new AABB;
	attackRange->SetExtent(towerData.attackRange, towerData.attackRange);
	//�̹����� ��������.. �ڵ����� ȸ���� �߽���ǥ�� �����ϱ�.. 
	AddComponent(new BoxCollider(boundBox ,CollisionType::Block, this, CollisionLayer::Tower));
	AddComponent(new BoxCollider(attackRange, CollisionType::Overlap, this, CollisionLayer::Tower));
	//�ڽ��� ������ �پ��� ���� ��ġ�� ȸ���ϴµ� �ֱ׷���>? 
	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");

	fsm->SetNextState("Idle");                    //���̾�� �ϴ� attack�� �׽�Ʈ 
	
	renderOrder = 100;
	transform->SetRelativeLocation({200,200});
	
}

ArrowTower::~ArrowTower()
{
}

void ArrowTower::Update(float deltaTime)
{
	
	__super::Update(deltaTime);
	if (target == nullptr && !objs.empty())
	{

		ExploreTarget(*this, objs);

	}
	//Music::soundManager->GetInstance()->PlayMusic();

}

void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	//GetComponent<BoxCollider>()->aabb->Center = { 300,300 };

}

void ArrowTower::Attack(float deltaTime)
{ 
	/*attacktime -= deltaTime;
	if (attacktime <= 0)
	{
		arrows.push_back(owner->CreateGameObject<Arrow>());
		arrows.back()->transform->relativeLocation = { GetWorldLocation().x + 100.f, GetWorldLocation().y -20.f };
	
		attacktime = 3.0f;
	}*/
	arrows.push_back(owner->CreateGameObject<Arrow>());
	arrows.back()->transform->SetRelativeLocation ({ GetWorldLocation().x + 100.f, GetWorldLocation().y - 20.f });
}


void ArrowTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	if(otherComponent->owner->name == "enemy")
	objs.push_back(otherComponent->owner);
}

void ArrowTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void ArrowTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	if (otherComponent->owner->name == "enemy")
	objs.erase(std::remove(objs.begin(),objs.end(),otherComponent->owner));
}
