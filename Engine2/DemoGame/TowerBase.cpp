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

TowerBase::TowerBase(TowerData data) //최대한위로빼고 달라지는 로직만 적용해야하고.. 
{
	this->towerData = data; 
	this->name = "Tower"; //이름에서 태그로 변경하기
	star = Fac->CreateGameObject<TowerStar>();
	star->Init(this, towerData.level);
	curHP = towerData.HP;
	EventSystem::GetInstance().get()->Ui.insert(this);

	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"Ken")); //애니메이션은데이터의 이름으로 위치찾아서 가져오기
	//이건 어떻게 해야할지 모르겟네.. 박스랑 원충돌부터 인규형이 넘겨준걸 제대로처리할까? //그렇게 하고나면.. 잘될텐데.. 콜라이더 업데이트에서 중심값 업데이트되게 처리하고.
	AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), data.attackRange), CollisionType::Overlap, this, CollisionLayer::Tower));
	renderOrder = 100;

	FiniteStateMachine* fsm = new FiniteStateMachine(); //fsm도 타워도 
	HPbar = Fac->CreateGameObject<HPBar>();
	HPbar->Init(this);
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");

	TowerType type = (TowerType)(towerData.id / 3);
	if (type == TowerType::Crossbow || type == TowerType::Water) //같은 알고리즘
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

	//testEffect = 1; //닷트윈 사용법 예시 //값이 적용될매개변수를 하나 가지고있고 생성해서 넣어주기
	//new DOTween(testEffect, EasingEffect::InOutElastic, StepAnimation::StepOnceForward);
}

//오브젝트풀에서 타워를 빼올때.. init을 거쳐야겠는데? 초기화 상태에 대해 알고있자.. 

void TowerBase::Update(float deltaTime) 
{
	__super::Update(deltaTime);
	if (isMoving)
	{
		transform->SetRelativeLocation(inputSystem->GetMouseState().GetMousePos());
	}
	perHP = (curHP / towerData.HP) * 100; //얘는 굳이 저장해야하나? 
	//적 탐색을 각자에서 찾자.. 
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


void TowerBase::BeginDrag(const MouseState& state)//이 부분은 이동가능하게.. 
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
