#include "pch.h"
#include "TowerBase.h"
#include "InputSystem.h"
#include "Transform.h"
#include "Container.h"
#include "EventSystem.h"
#include "Artifact.h"
#include "Factory.h"
#include "Dotween.h" 
#include "Animation.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "TowerFunc.h"
#include "FiniteStateMachine.h"
#include "TowerFsm.h"
#include "HPBar.h"
#include "TowerStar.h"

TowerBase::TowerBase(TowerData data) //�ִ������λ��� �޶����� ������ �����ؾ��ϰ�..  //������Ʈ Ǯ������ init���ϰ� ����ҰŰ�����.. 
{
	this->towerData = data; 
	this->name = "Tower"; //�̸����� �±׷� �����ϱ�
	for (int i = 0; i < data.level; i++)//�����ǥ�� ����ϴµ��̰� �׳� ����ִ¹�������ұ�? 	
		Factory().createObj<TowerStar>().setPosition({ 20.f * i ,0}).setParent(transform);		
	curHP = towerData.HP;
	EventSystem::GetInstance().get()->Ui.insert(this);
	SetBoundBox(0, 0, 150,150);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken")); 
	AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), data.attackRange * 50), CollisionType::Overlap, this, CollisionLayer::Tower));
	renderOrder = 100;

	FiniteStateMachine* fsm = new FiniteStateMachine(); 
	Factory().createObj<HPBar>(curHP, data.HP).setParent(transform);
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");

	TowerType type = (TowerType)(towerData.id / 3);
	if (type == TowerType::Crossbow || type == TowerType::Water) //���� �˰���
	{
		Search = [this]() { TowerFunc::FindTarget(*GetComponent<CircleCollider>(), "Enemy", target); };
		AttackFunc = [this]() { TowerFunc::FireBullet(target[0], this->transform->GetWorldLocation()); };
	}
	if (type == TowerType::Pile)
	{
		Search = [this]() { TowerFunc::FindTargets(*GetComponent<CircleCollider>(), "Enemy", target); };
		AttackFunc = [this]() { TowerFunc::MeleeAttack(target); };
	}
	if (type == TowerType::HolyCross)
	{
		Search = [this]() { TowerFunc::FindTargets(*GetComponent<CircleCollider>(), "Tower", target); };
		AttackFunc = [this]() { TowerFunc::Heal(target); };
	}

	//testEffect = 1; //��Ʈ�� ���� ���� //���� ����ɸŰ������� �ϳ� �������ְ� �����ؼ� �־��ֱ�
	//new DOTween(testEffect, EasingEffect::InOutElastic, StepAnimation::StepOnceForward);
}

//������ƮǮ���� Ÿ���� ���ö�.. init�� ���ľ߰ڴµ�? �ʱ�ȭ ���¿� ���� �˰�����.. 

void TowerBase::Update(float deltaTime) 
{
	__super::Update(deltaTime);
}

void TowerBase::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
}

void TowerBase::Attack(float deltaTime)
{
	AttackFunc();
}

void TowerBase::Hit(float damage)
{
	float plusArmor = Artifact::GetInstance().get()->towerPower.Armor;
	curHP -= damage * plusArmor;
}

void TowerBase::Heal(float heal)
{
	float healHP = curHP;
	healHP += heal;
	if (healHP >= towerData.HP)
		curHP = towerData.HP;
	else
		curHP += heal;
}

void TowerBase::BeginDrag(const MouseState& state)//�� �κ��� �̵������ϰ�.. 
{
	std::cout << "BeginDrag";
	if (container)
		container->Clear();
}

void TowerBase::StayDrag(const MouseState& state)
{
	transform->SetRelativeLocation(state.GetMousePos());
}

void TowerBase::EndDrag(const MouseState& state) //�巡�׾� ����̴ϱ�.. 
{	
	//container
	std::cout << "EndDrag";
}

void TowerBase::OnBlock(Collider* ownedComponent, Collider* otherComponent)
{
}

void TowerBase::OnBeginOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void TowerBase::OnStayOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void TowerBase::OnEndOverlap(Collider* ownedComponent, Collider* otherComponent)
{
}

void TowerBase::OnClick()
{

}
