#include "pch.h"
#include "TowerBase.h"
#include "D2DRenderer.h"
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

TowerBase::TowerBase(TowerData data) //�ִ������λ��� �޶����� ������ �����ؾ��ϰ�.. 
{
	this->towerData = data; 
	this->name = "Tower"; //�̸����� �±׷� �����ϱ�
	star = Fac->CreateGameObject<TowerStar>();
	star->Init(this, towerData.level);
	curHP = towerData.HP;
	EventSystem::GetInstance().get()->Ui.insert(this);

	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken")); //�ִϸ��̼����������� �̸����� ��ġã�Ƽ� ��������
	//�̰� ��� �ؾ����� �𸣰ٳ�.. �ڽ��� ���浹���� �α����� �Ѱ��ذ� �����ó���ұ�? //�׷��� �ϰ���.. �ߵ��ٵ�.. �ݶ��̴� ������Ʈ���� �߽ɰ� ������Ʈ�ǰ� ó���ϰ�.
	AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), data.attackRange), CollisionType::Overlap, this, CollisionLayer::Tower));
	renderOrder = 100;

	FiniteStateMachine* fsm = new FiniteStateMachine(); //fsm�� Ÿ���� 
	HPbar = Fac->CreateGameObject<HPBar>();
	HPbar->Init(this);
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");

	TowerType type = (TowerType)(towerData.id / 3);
	if (type == TowerType::Crossbow || type == TowerType::Water) //���� �˰���
	{
		Search = [this]() { TowerFunc::FindTarget(*GetComponent<CircleCollider>(), "enemy", target); };
		AttackFunc = [this]() { TowerFunc::FireBullet(target[0]); };
	}
	if (type == TowerType::Pile)
	{
		Search = [this]() { TowerFunc::FindTargets(*GetComponent<CircleCollider>(), "enemy", target); };
		AttackFunc = [this]() { TowerFunc::MeleeAttack(target); };
	}
	if (type == TowerType::HolyCross)
	{
		Search = [this]() { TowerFunc::FindTargets(*GetComponent<CircleCollider>(), "enemy", target); };
		AttackFunc = [this]() { TowerFunc::Heal(target); };
	}

	//testEffect = 1; //��Ʈ�� ���� ���� //���� ����ɸŰ������� �ϳ� �������ְ� �����ؼ� �־��ֱ�
	//new DOTween(testEffect, EasingEffect::InOutElastic, StepAnimation::StepOnceForward);
}

//������ƮǮ���� Ÿ���� ���ö�.. init�� ���ľ߰ڴµ�? �ʱ�ȭ ���¿� ���� �˰�����.. 

void TowerBase::Update(float deltaTime) 
{
	__super::Update(deltaTime);
	if (isMoving)
	{
		transform->SetRelativeLocation(inputSystem->GetMouseState().GetMousePos());
	}
	perHP = (curHP / towerData.HP) * 100; //��� ���� �����ؾ��ϳ�? 
	//�� Ž���� ���ڿ��� ã��.. 
}

void TowerBase::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	int mHp = static_cast<int>(curHP);
	std::wstring hp = std::to_wstring(mHp);
	pRenderTarget->DrawTextW(hp.c_str(), hp.length(), D2DRenderer::GetInstance()->DWriteTextFormat, D2D1::RectF(GetWorldLocation().x - 50, GetWorldLocation().y - 100, GetWorldLocation().x + 50, GetWorldLocation().y),
		D2DRenderer::GetInstance()->Brush);
}

void TowerBase::Attack(float deltaTime)
{
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
	transform->SetRelativeLocation(state.GetMousePos());
	if (container)
		container->Clear();
}

void TowerBase::StayDrag(const MouseState& state)
{
	transform->SetRelativeLocation(state.GetMousePos());
}

void TowerBase::EndDrag(const MouseState& state)
{
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
