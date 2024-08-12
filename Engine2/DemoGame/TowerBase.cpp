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
#include "GameManager.h"
#include "TowerFsm.h"
#include "HPBar.h"
#include "TowerStar.h"
#include "CommonFunc.h"

TowerBase::TowerBase(TowerData data) //�ִ������λ��� �޶����� ������ �����ؾ��ϰ�..  //������Ʈ Ǯ������ init���ϰ� ����ҰŰ�����.. 
{
	this->towerData = data; 
	name = "Tower"; //�̸����� �±׷� �����ϱ�
	for (int i = 0; i < data.level; i++)//�����ǥ�� ����ϴµ��̰� �׳� ����ִ¹�������ұ�? 	
		Factory().createObj<TowerStar>().setPosition({ 20.f * i ,0}).setParent(transform);		
	curHP = towerData.HP;
	EventSystem::GetInstance().get()->Ui.insert(this);
	SetBoundBox(0, 0, 150,150);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"..\\Data\\CSV\\Ken.csv")); //�ִϸ��̼����������� �̸����� ��ġã�Ƽ� ��������
	//�̰� ��� �ؾ����� �𸣰ٳ�.. �ڽ��� ���浹���� �α����� �Ѱ��ذ� �����ó���ұ�? //�׷��� �ϰ���.. �ߵ��ٵ�.. �ݶ��̴� ������Ʈ���� �߽ɰ� ������Ʈ�ǰ� ó���ϰ�.
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
		Search = [this]() { CommonFunc::FindTarget(*GetComponent<CircleCollider>(), "Enemy", target, towerData.attackRange); };
		AttackFunc = [this]() { TowerFunc::FireBullet(target[0], this->transform->GetWorldLocation()); };
	}
	if (type == TowerType::Pile)
	{
		Search = [this]() { CommonFunc::FindTargets(*GetComponent<CircleCollider>(), "Enemy", target, towerData.attackRange); };
		AttackFunc = [this]() { TowerFunc::MeleeAttack(target); };
	}
	if (type == TowerType::HolyCross)
	{
		Search = [this]() { CommonFunc::FindTargets(*GetComponent<CircleCollider>(), "Tower", target, towerData.attackRange); };
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

void TowerBase::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
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
	if (GameManager::GetInstance().get()->isBattle == true) //�����߿��� �巡�� �Ұ� //�� ���⸸ ���´ٰ� ��ü�� �����°� �ƴ���?
		return;
	if (container)
		container->Clear();
}

void TowerBase::StayDrag(const MouseState& state) 
{
	if (GameManager::GetInstance().get()->isBattle == true) //������ ���ϸ� �̰͵� �ƿ��ȵ����������ڴµ�.. ��.. //�ϴ� ���������� �ʰ� ���;��ϰ�.. 
		// ondrop �̺�Ʈ�� ���ƾ��� .. �װԶ� ��ġ�� �������ִ°Ŷ�.. 
		return;
	transform->SetRelativeLocation(state.GetMousePos());
}

void TowerBase::EndDrag(const MouseState& state) //�巡�׾� ����̴ϱ�.. 
{	
	//container
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
