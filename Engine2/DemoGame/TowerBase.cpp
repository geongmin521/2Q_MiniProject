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

TowerBase::TowerBase(TowerData data) //최대한위로빼고 달라지는 로직만 적용해야하고..  //오브젝트 풀에서도 init을하고 줘야할거같은데.. 
{
	this->towerData = data; 
	name = "Tower"; //이름에서 태그로 변경하기
	for (int i = 0; i < data.level; i++)//상대좌표를 줘야하는데이건 그냥 들고있는방식으로할까? 	
		Factory().createObj<TowerStar>().setPosition({ 20.f * i ,0}).setParent(transform);		
	curHP = towerData.HP;
	EventSystem::GetInstance().get()->Ui.insert(this);
	SetBoundBox(0, 0, 150,150);
	AddComponent(new Animation(L"..\\Data\\Image\\ken.png", L"..\\Data\\CSV\\Ken.csv")); //애니메이션은데이터의 이름으로 위치찾아서 가져오기
	//이건 어떻게 해야할지 모르겟네.. 박스랑 원충돌부터 인규형이 넘겨준걸 제대로처리할까? //그렇게 하고나면.. 잘될텐데.. 콜라이더 업데이트에서 중심값 업데이트되게 처리하고.
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
	if (type == TowerType::Crossbow || type == TowerType::Water) //같은 알고리즘
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

	//testEffect = 1; //닷트윈 사용법 예시 //값이 적용될매개변수를 하나 가지고있고 생성해서 넣어주기
	//new DOTween(testEffect, EasingEffect::InOutElastic, StepAnimation::StepOnceForward);
}

//오브젝트풀에서 타워를 빼올때.. init을 거쳐야겠는데? 초기화 상태에 대해 알고있자.. 

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

void TowerBase::BeginDrag(const MouseState& state)//이 부분은 이동가능하게.. 
{
	if (GameManager::GetInstance().get()->isBattle == true) //전투중에는 드래그 불가 //아 여기만 막는다고 전체가 막히는게 아니지?
		return;
	if (container)
		container->Clear();
}

void TowerBase::StayDrag(const MouseState& state) 
{
	if (GameManager::GetInstance().get()->isBattle == true) //시작을 못하면 이것도 아예안들어왔으면좋겠는데.. 흠.. //일단 전투시작이 늦게 들어와야하고.. 
		// ondrop 이벤트도 막아야함 .. 그게또 위치를 변경해주는거라.. 
		return;
	transform->SetRelativeLocation(state.GetMousePos());
}

void TowerBase::EndDrag(const MouseState& state) //드래그앤 드롭이니까.. 
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
