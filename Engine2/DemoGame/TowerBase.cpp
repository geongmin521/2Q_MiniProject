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
#include "Pools.h"
#include "World.h"

TowerBase::TowerBase(TowerData data) //�ִ������λ��� �޶����� ������ �����ؾ��ϰ�..  //������Ʈ Ǯ������ init���ϰ� ����ҰŰ�����.. 
{
	renderOrder = 100;
	this->towerData = data; 
	name = "Tower"; //�̸����� �±׷� �����ϱ�
	for (int i = 0; i < data.level; i++)//�����ǥ�� ����ϴµ��̰� �׳� ����ִ¹�������ұ�? 	
		Factory().createObj<TowerStar>().setPosition({ 20.f * i ,0}).setParent(transform);
	id = towerData.id;
	curHP = towerData.HP;
	if(towerData.name == "HiddenTower")
	AddComponent(new Animation(L"..\\Data\\Image\\" + Utility::convertFromString(towerData.name) + L".png", L"..\\Data\\CSV\\Animation\\" + Utility::convertFromString(towerData.name) + L".csv"));
	else
	AddComponent(new Animation(L"..\\Data\\Image\\" + Utility::convertFromString(towerData.name) + L".png", L"..\\Data\\CSV\\Animation\\TowerBase.csv"));
	EventSystem::GetInstance().get()->Ui.insert(this);
	SetBoundBox(0, 0, 150,150);
	//�̰� ��� �ؾ����� �𸣰ٳ�.. �ڽ��� ���浹���� �α����� �Ѱ��ذ� �����ó���ұ�? //�׷��� �ϰ���.. �ߵ��ٵ�.. �ݶ��̴� ������Ʈ���� �߽ɰ� ������Ʈ�ǰ� ó���ϰ�.
	AddComponent(new CircleCollider(boundBox, new Circle(transform->GetWorldLocation(), data.attackRange * 50), CollisionType::Overlap, this, CollisionLayer::Tower));

	TowerType type = (TowerType)(towerData.id / 3);
	if (type == TowerType::Crossbow || type == TowerType::Water) //���� �˰��� 
	{
		
		Search = [this]() { CommonFunc::FindTarget(*GetComponent<CircleCollider>(), "Enemy", target, towerData.attackRange); };
		AttackFunc = [this]() { TowerFunc::FireBullet(target[0], this->transform->GetWorldLocation(), towerData.id); };
	}
	if (type == TowerType::Pile)
	{
		
		Search = [this]() { CommonFunc::FindTargets(*GetComponent<CircleCollider>(), "Enemy", target, towerData.attackRange); };
		AttackFunc = [this]() { TowerFunc::MeleeAttack(this,target); };
	}
	if (type == TowerType::HolyCross)
	{
		Search = [this]() { CommonFunc::FindTargets(*GetComponent<CircleCollider>(), "Tower", target, towerData.attackRange); };
		AttackFunc = [this]() { TowerFunc::Heal(target); };
	}
	if (type == TowerType::Hidden)
	{
		
		Search = [this]() { CommonFunc::FindTarget(*GetComponent<CircleCollider>(), "Enemy", target, towerData.attackRange); };
		AttackFunc = [this]() { TowerFunc::FireBullet(target[0], this->transform->GetWorldLocation(), towerData.id); };
	}


	FiniteStateMachine* fsm = new FiniteStateMachine();
	Factory().createObj<HPBar>(curHP, data.HP).setParent(transform);
	AddComponent(fsm);
	fsm->CreateState<TowerIdle>("Idle");
	fsm->CreateState<TowerAttack>("Attack");
	fsm->CreateState<TowerShared>("Shared");
	fsm->CreateState<TowerDeath>("Death");
	fsm->SetNextState("Idle");
	//testEffect = 1; //��Ʈ�� ���� ���� //���� ����ɸŰ������� �ϳ� �������ְ� �����ؼ� �־��ֱ�
	//new DOTween(testEffect, EasingEffect::InBounce, StepAnimation::StepOnceForward);
}

//������ƮǮ���� Ÿ���� ���ö�.. init�� ���ľ߰ڴµ�? �ʱ�ȭ ���¿� ���� �˰�����.. 



void TowerBase::Init(MathHelper::Vector2F pos)
{
	curHP = towerData.HP;  //setactive�� Ǯ���� ���� ���� //������ �ش簴üinit ������ ���θ���
	transform->SetRelativeLocation(pos); 
	GetComponent<FiniteStateMachine>()->SetNextState("Idle");
}

void TowerBase::Update(float deltaTime)
{
	__super::Update(deltaTime);
	//transform->SetRelativeScale({ testEffect, testEffect });
}

void TowerBase::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}

void TowerBase::Attack(float deltaTime)
{
	AttackFunc();
}

void TowerBase::Hit(float damage, float knockback)
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
		//ondrop �̺�Ʈ�� ���ƾ��� .. �װԶ� ��ġ�� �������ִ°Ŷ�.. 
		return;
	transform->SetRelativeLocation(state.GetMousePos());
}

void TowerBase::EndDrag(const MouseState& state) //�巡�׾� ����̴ϱ�.. 
{	
	//container
}

void TowerBase::FailDrop()
{
	if (container != nullptr) //�̰� �ΰ˻��ϴ°� �̳� �������� define���� �����?
		transform->SetRelativeLocation(container->GetWorldLocation());

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

void TowerBase::OnDoubleClick()
{
	GameObject* newTower =nullptr;
	std::vector<TowerBase*> towers;
	int merageCount = 2; //��ĥ���ʿ��� �ڽ����� ���� �⹰��
	int minDis = INT_MAX;
	float distance = 0;
	for (auto& tower : owner->m_GameObjects)
	{
		TowerBase* sameTower = dynamic_cast<TowerBase*>(tower);
		if(sameTower != nullptr && tower->GetActive() == true && sameTower != this && sameTower->towerData.id == this->towerData.id)
		{
			if (towers.size() == merageCount)
			{
				std::vector<TowerBase*>::iterator farTower; //�EŸ�� ��ġ ��ƵѰ�
				for (auto nearTower = towers.begin(); nearTower != towers.end(); ++nearTower)
				{
					distance = ((*nearTower)->GetWorldLocation() - this->GetWorldLocation()).Length(); //�̵̹��ִ°;ȿ��� ���������� ã��
					if(distance < minDis)
					{
						minDis = distance; //���⼭ minDis�� ������������ �Ÿ����ǰ�
						farTower = nearTower;
					}
				}
				distance = (sameTower->GetWorldLocation() - this->GetWorldLocation()).Length(); //���� �����Ͱ��� �Ÿ�
				if (distance > minDis) //�������� Ÿ���� �����Ÿ������ �� �ָ� 
					continue;
				towers.erase(farTower);
			}
			towers.push_back(sameTower);
		}
	}

	if(towers.size() == merageCount && towerData.level < 3)
	{
		newTower = Pools::GetInstance().get()->PopPool(towerData.id + 1);
		dynamic_cast<TowerBase*>(newTower)->Init(this->GetWorldLocation());
		for(auto& sametower : towers)
		{
			Pools::GetInstance().get()->AddPool(sametower); //����Ÿ�� Ǯ���ְ�
			if(sametower->container)
			sametower->container->Clear();
		}
		Pools::GetInstance().get()->AddPool(this); // �ڱ⵵ Ǯ���ְ�
		if (this->container)
		{
			dynamic_cast<TowerBase*>(newTower)->container = this->container;
			this->container->Clear();//���⼭ �����̳ʸ� ��Ÿ���� �Ѱ��ְ� �ڱⲫ ���ְ�?
		}
	}
}
