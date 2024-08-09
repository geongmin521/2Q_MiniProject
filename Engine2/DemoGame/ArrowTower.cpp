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

// test
#include "D2DFont.h"

ArrowTower::ArrowTower(TowerData data) : TowerBase(data)
{
	towerData.name = "ArrowTower";                    //csv���� �о�ͼ� �ٳ־����Բ� 
	towerData.attackRange = 500.0f;
	towerData.attackSpeed = 0.3f;
	towerData.HP = 20000.0f;
	curHP = towerData.HP;

	SetBoundBox(0, 0, 100, 100);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken"));
	AddComponent(new BoxCollider(boundBox, CollisionType::Overlap, this, CollisionLayer::Tower));

	star = Fac->CreateGameObject<TowerStar>();
	towerData.level = 1;
	star->Init(this, towerData.level); //���⼭ �������� �ڱ⸦ �༭ �ڱ� Ʈ������ ã�Բ�

	FiniteStateMachine* fsm = new FiniteStateMachine();
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");

	renderOrder = 100;
	transform->SetRelativeLocation({ 400,300 });

	//  D2DEffect::GetInstance()->CreateMorphologyEffect(L"as", GetComponent<Animation>()->bitmap, 10);
	//	D2DRenderer::GetInstance()->CreateGaussianBlurEffect(GetComponent<Animation>()->bitmap, 10.f);
	D2DEffect::GetInstance()->Create2DLightEffect(L"as", GetComponent<Animation>()->bitmap);

	AddComponent(new D2DFont(L"�ȳ��ϼ���"));
	GetComponent<D2DFont>()->SetPos(100, 100);
}

void ArrowTower::Update(float deltaTime)
{
	__super::Update(deltaTime);

	//target�� ���� ������
	//GetComponent<BoxCollider>()->collideStateCurr.begin() it;
	//it = owner name enemy;
	//Getwroldlocation  �Ÿ���
	//	>> ���������� Ÿ������
	//	�갡 ������ target null �ƴϸ� Ÿ��;
	//transform->AddRelativeRotation(1);
	FindTarget(GetComponent<BoxCollider>());

}


void ArrowTower::Render(ID2D1HwndRenderTarget* pRenderTarget)
{

	__super::Render(pRenderTarget);
	D2D_MATRIX_3X2_F test = this->transform->worldTransform;
	test.dx += 100;
	test.dy += 100;
	pRenderTarget->SetTransform(test);

}

void ArrowTower::Attack(float deltaTime)
{ 
	if (target != nullptr)
	{
		Arrow* arrow = new Arrow;
		arrow->owner = this->owner;
		arrow->Init(target, GetWorldLocation());
		owner->m_GameObjects.push_back(arrow);    //����ü�� Ÿ�� hitó���� ����ü����
	}
}

//���� Ȯ���ϰ� ������ ȯ���� �������Ѵ�. 

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

void ArrowTower::BeginDrag(const MouseState& state) //�̰Ŵ� ���콺�� �ϴ°Ŵϱ� ���콺 ������ ��� �����������Ű�����? 
{
	std::cout << "BeginDrag";
	transform->SetRelativeLocation(state.GetMousePos());
	if (container)
		container->Clear();//����ִ°����� ����ֱ�.. ���� ��ȣ�����ϰ��ִ°� ������? 

}

void ArrowTower::StayDrag(const MouseState& state)
{
	transform->SetRelativeLocation(state.GetMousePos());
}

void ArrowTower::EndDrag(const MouseState& state)
{
	std::cout << "EndDrag";
}

