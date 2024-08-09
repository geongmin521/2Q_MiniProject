#include "pch.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "Bitmap.h"
#include "Animation.h"
#include "Transform.h"
#include "D2DRenderer.h"
#include "FiniteStateMachine.h"
#include "InputSystem.h"
#include "Container.h"
#include "TowerFsm.h"
#include "AABB.h"
#include "Music.h"
#include "World.h" 
#include "EnemyBase.h"
#include "Factory.h"
#include "ArrowTower.h"

#include "D2DEffect.h"


ArrowTower::ArrowTower(TowerData data) : TowerBase(data)
{


	towerData.name = "ArrowTower";                    //csv에서 읽어와서 다넣어지게끔 
	towerData.attackRange = 5000.0f;
	towerData.attackSpeed = 0.3f;
	towerData.HP = 20000.0f;
	curHP = towerData.HP;

	SetBoundBox(0, 0, 5000, 5000);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));

	star = Fac->CreateGameObject<TowerStar>();
	towerData.level = 1;
	star->Init(this, towerData.level); //여기서 주인으로 자기를 줘서 자기 트랜스폼 찾게끔

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
	transform->SetRelativeLocation({ 400,300 });

	D2DEffect::GetInstance()->CreateMorphologyEffect(L"as", GetComponent<Animation>()->bitmap, 10);
	//	D2DRenderer::GetInstance()->CreateGaussianBlurEffect(GetComponent<Animation>()->bitmap, 10.f);

}

void ArrowTower::Update(float deltaTime)
{
	__super::Update(deltaTime);

	//target이 현재 없을때
	//GetComponent<BoxCollider>()->collideStateCurr.begin() it;
	//it = owner name enemy;
	//Getwroldlocation  거리비교
	//	>> 제일작은걸 타겟으로
	//	얘가 죽으면 target null 아니면 타겟;
	//transform->AddRelativeRotation(1);
	FindTarget(GetComponent<BoxCollider>());
	
}


void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{

	__super::Render(pRenderTarget);
//	D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffect::GetInstance()->FindEffect(L"as"));
	
}

void ArrowTower::Attack(float deltaTime)
{ 
	if (target != nullptr)
	{
		Arrow* arrow = new Arrow;
		arrow->owner = this->owner;
		arrow->Init(target, GetWorldLocation());
		owner->m_GameObjects.push_back(arrow);    //투사체는 타겟 hit처리를 투사체에서
	}
}

//좀더 확실하고 통제된 환경을 만들어야한다. 

void ArrowTower::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
	
}

void ArrowTower::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	
}


void ArrowTower::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	
}

void ArrowTower::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
	
}

void ArrowTower::BeginDrag(const MouseState& state) //이거는 마우스로 하는거니까 마우스 정보가 계속 들어오면좋을거같은데? 
{
	std::cout << "BeginDrag";
	transform->SetRelativeLocation(state.GetMousePos());
	if (container)
		container->Clear();//담겨있는공간에 비워주기.. 서로 상호참조하고있는게 맞을까? 
}

void ArrowTower::StayDrag(const MouseState& state)
{
	transform->SetRelativeLocation(state.GetMousePos());
}

void ArrowTower::EndDrag(const MouseState& state)
{
	std::cout << "EndDrag";
}

